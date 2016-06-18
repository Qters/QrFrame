#include "core/qrframer.h"

#include <QtCore/qpluginloader.h>
#include <QtCore/qdebug.h>
#include <QtWidgets/qapplication.h>
#include <QtCore/qpair.h>
#include <QtCore/qdir.h>
#include <QtCore/qdatetime.h>

#include "db/qrframedb.h"
#include "core/qrifservice.h"
#include "db/qrtblloadinfo.h"
#include "db/qrtblframeconfig.h"
#include "qrmainwindow.h"

#include "Logger.h"
#include "FileAppender.h"

#include "qrsqlhelper.h"

NS_QRFRAME_BEGIN

class QrFramerPrivate{
public:
    static bool installLog();
    static bool initLogInfoByDatabase(bool *defaultUse,
                                      QString *defaultFolder,
                                      Logger::LogLevel *defaultLevel);

public:
    bool initByConfig();
    bool loadServices();
    bool initServices();

public:
    QrMainWindow *mainwindow;
    QrFramerConfig frameConfig;
    QVector<QString> serviceNames;
    QVector<QPair<QString, QObject *> > loadedServices;
};

NS_QRFRAME_END

USING_NS_QRFRAME;
USING_NS_QRCOMMON;
USING_NS_QRORM;

//////////////////////////////////////////////////

QrFramer::QrFramer() : d_ptr(new QrFramerPrivate)
{

}

void QrFramer::setMainWindow(QrMainWindow *mainwindow)
{
    Q_D(QrFramer);
    d->mainwindow = mainwindow;
}

bool QrFramer::start()
{
    Q_D(QrFramer);
    if (! d->initByConfig()) {
        qWarning() << "framer initialize fail by config";
    }

    if (! loadFramework()
            && initFramework() ) {
        qWarning() << "framer start fail";
        return false;
    }

    if (! d->mainwindow->init()) {
        qWarning() << "mainwindow init fail";
        return false;
    }
    d->mainwindow->show();
    return true;
}

void QrFramer::setConfig(const QrFramerConfig &config)
{
    Q_D(QrFramer);
    d->frameConfig = config;
}

bool QrFramer::loadFramework()
{
    Q_D(QrFramer);
    qDebug() << "begin load framework";

    bool suc = QrSqlHelper::makesureDbExist(QrFrameDb::getInstance())
            && QrTblLoadInfoHelper::getLoadServices(d->serviceNames)
            && d->loadServices();

    qDebug() << "end load framework";
    return suc;
}

bool QrFramer::initFramework()
{
    Q_D(QrFramer);
    qDebug() << "begin initialize framework";

    bool suc = d->initServices();

    qDebug() << "end initialize framework";
    return suc;
}

//////////////////////////////////////////////////
bool QrFramerPrivate::loadServices() {
    static const QString dbKey = "services_folder";
    static const QString defaultFolder = "services";

    if (this->serviceNames.isEmpty()) {
        qInfo() << "services is empty";
        return true;
    }

    QString pluginFolder;
    if (! QrTblFrameConfigHelper::getValueByKey(dbKey, &pluginFolder)) {
        pluginFolder = defaultFolder;
        QrTblFrameConfigHelper::setVauleByKey(dbKey, pluginFolder);
    }

    this->loadedServices.clear();
    QPluginLoader serviceLoader;
    const QString absPathOfServicePlugin = QApplication::applicationDirPath() + "/" + pluginFolder + "/";
    Q_FOREACH(auto serviceName, this->serviceNames) {
        QString absFileNameOfServicePlugin = absPathOfServicePlugin + serviceName;
#ifdef QT_DEBUG
        absFileNameOfServicePlugin += "d";
#endif
        absFileNameOfServicePlugin += ".dll";
        serviceLoader.setFileName(absFileNameOfServicePlugin);
        QObject *servicePllugin = serviceLoader.instance();
        if(nullptr == servicePllugin){
            qWarning() << absFileNameOfServicePlugin << " is not a service plugin object.";
            continue;
        }
        qInfo() << serviceName << " loaded success.";
        this->loadedServices.append(qMakePair<QString, QObject*>(absFileNameOfServicePlugin, servicePllugin));
    }

    return true;
}

bool QrFramerPrivate::initServices() {
    Q_FOREACH(auto service, this->loadedServices) {
        auto *serviceIf = qobject_cast<QrIfService*>(service.second);
        if (nullptr == serviceIf) {
            qWarning() << service.first << " is not a service";
            continue;
        }
        if (! serviceIf->init()) {
            qWarning() << service.first << " init fail";
        }
        qInfo() << "service " << service.first << " init success.";
    }

    return true;
}

bool QrFramerPrivate::initByConfig()
{
    bool initSuc = true;

    if (initSuc && ! frameConfig.dbFolder.isEmpty()) {
        QrFrameDb::getInstance()->setFolderPath(frameConfig.dbFolder);
    }

    if (frameConfig.installLog) {   //  should do it first
        initSuc = QrFramerPrivate::installLog();
    }

    qInfo() << "frame database's folder is " << frameConfig.dbFolder;

    return initSuc;
}

bool QrFramerPrivate::installLog()
{
    qDebug() << "begin install log service";

    bool defaultUse = true;
    QString defaultFolder = "log";
    Logger::LogLevel defaultLevel = Logger::Debug;

    QrFramerPrivate::initLogInfoByDatabase(&defaultUse, &defaultFolder, &defaultLevel);

    if (! defaultUse) {
        qInfo() << "install log sevice fail, please set in db if you want it.";
        return true;
    }

    auto datetime = QDateTime::currentDateTime();
    QString logFilePath = QApplication::applicationDirPath()
            + "/" + defaultFolder
            + "/" + datetime.toString("yyyyMMdd");
    if (!QDir(logFilePath).exists()) {
        QDir().mkpath(logFilePath);
    }
    logFilePath += "/" + QString("%1.log")
            .arg (datetime.toString ("hh_mm_ss"));
    FileAppender* fileAppender = new FileAppender(logFilePath);
    fileAppender->setDetailsLevel(defaultLevel);
    qDebug() << "log is intalled! and logs are put in " << logFilePath;

    Logger::globalInstance ()->registerAppender (fileAppender);

    qInfo().noquote() << "\n\n============================================";
    qInfo() << "start log.";
    return true;
}

bool QrFramerPrivate::initLogInfoByDatabase(bool *defaultUse,
                                            QString *defaultFolder,
                                            Logger::LogLevel *defaultLevel){
    QMap<QString, QString> configValues;
    if (! QrTblFrameConfigHelper::getKeyValuesByType("log", &configValues)) {
        return false;
    }

    for (QMap<QString, QString>::const_iterator iter = configValues.constBegin();
         iter != configValues.constEnd();
         ++iter) {
        if ("log_use" == iter.key()) {
            *defaultUse = (iter.value() == "true" || iter.value() == "1");
        } else if ("log_folder" == iter.key()) {
            *defaultFolder = iter.value();
        } else if ("log_level" == iter.key()) {
            if ("trace" == iter.value().toLower()) {
                *defaultLevel = Logger::LogLevel::Trace;
            } else if ("debug" == iter.value().toLower()) {
                *defaultLevel = Logger::LogLevel::Debug;
            } else if ("info" == iter.value().toLower()) {
                *defaultLevel = Logger::LogLevel::Info;
            } else if ("warning" == iter.value().toLower()) {
                *defaultLevel = Logger::LogLevel::Warning;
            } else if ("error" == iter.value().toLower()) {
                *defaultLevel = Logger::LogLevel::Error;
            } else if ("fatal" == iter.value().toLower()) {
                *defaultLevel = Logger::LogLevel::Fatal;
            }
        }   //  log_level
    }   //  for

    return true;
}
