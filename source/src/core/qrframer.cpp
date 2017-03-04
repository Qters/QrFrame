#include "core/qrframer.h"

#include <QtCore/qpluginloader.h>
#include <QtCore/qdebug.h>
#include <QtWidgets/qapplication.h>
#include <QtCore/qpair.h>
#include <QtCore/qdir.h>
#include <QtCore/qdatetime.h>

#include "db/qrframedb.h"
#include "core/qrifservice.h"
#include "db/qrtblframeconfig.h"
#include "qrmainwindow.h"

#include "Logger.h"
#include "FileAppender.h"

#include "qrutf8.h"
#include "qrsqlhelper.h"
#include "qrsplashscreen.h"

NS_QRFRAME_BEGIN

class QrFramerPrivate{
public:
    static bool installLog();
    static bool initLogInfoByDatabase(bool *defaultUse,
                                      QString *defaultFolder,
                                      Logger::LogLevel *defaultLevel);

public:
    bool initByConfig();
    bool getServices(QVector<QString> &serviceNames);
    bool loadServices();
    bool initServices();

public:
    QrMainWindow *mainwindow;
    QrSplashScreen *splashScreen = nullptr;
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
    Q_D(QrFramer);
    d->splashScreen = new QrSplashScreen(d->frameConfig.splashscreenBgQrcPath);
    d->splashScreen->setMessageColor(d->frameConfig.splashColor);
}

QrFramer::~QrFramer()
{
    Q_D(QrFramer);
    if(nullptr != d->splashScreen) {
        delete d->splashScreen;
        d->splashScreen = nullptr;
    }
}

void QrFramer::setMainWindow(QrMainWindow *mainwindow)
{
    Q_D(QrFramer);
    d->mainwindow = mainwindow;
}

void QrFramer::addSplashStep(const QrSplashStep &splashStep)
{
    Q_D(QrFramer);
    d->splashScreen->addStepFunction(splashStep);
}

bool QrFramer::start()
{
    Q_D(QrFramer);

    d->initByConfig();

    loadFramework();

    d->mainwindow->init();

    initFramework();

    if(! d->splashScreen->start(d->frameConfig.splashscreen)) {
        qWarning() << "frame init fail";
        return false;
    }

    d->mainwindow->show();

    d->splashScreen->finish(d->mainwindow);

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

    QrSplashStep initDbStep;
    initDbStep.message = QObject::tr("初始化数据库");
    initDbStep.failMsg = "fail to init database";
    initDbStep.function = [](){
        qDebug() << "begin load database";
        auto success = QrSqlHelper::makesureDbExist(QrFrameDb::getInstance());
        qDebug() << "end load database";
        return success;
    };
    d->splashScreen->addStepFunction(initDbStep);

    QrSplashStep getServicesStep;
    getServicesStep.message = QObject::tr("获取服务模块");
    getServicesStep.failMsg = "fail to get services";
    getServicesStep.function = [this](){
        Q_D(QrFramer);
        return d->getServices(d->serviceNames);
    };
    d->splashScreen->addStepFunction(getServicesStep);

    return d->loadServices();
}

bool QrFramer::initFramework()
{
    Q_D(QrFramer);
    return d->initServices();
}

//////////////////////////////////////////////////
bool QrFramerPrivate::getServices(QVector<QString>& serviceNames){
    static const QString dbServiceType = "service";
    static const QString dbKey = "dlls";

    QString dlls;
    if (! QrTblFrameConfigHelper::getValueBy(dbServiceType, dbKey, &dlls)) {
        return false;
    }

    Q_FOREACH(auto dll, dlls.split(';')){
        if (dll.isEmpty()) {
            continue;
        }
        serviceNames.push_back(dll);
    }

    return true;
}

bool QrFramerPrivate::loadServices() {
    static const QString dbServiceType = "service";
    static const QString dbKey = "folder";
    static const QString defaultFolder = "services";

    QString pluginFolder;
    QMap<QString, QString> serviceValues;
    if ( QrTblFrameConfigHelper::getKeyValuesByType(dbServiceType, &serviceValues)) {
        if (! serviceValues[dbKey].isEmpty()) {
            pluginFolder = serviceValues[dbKey];
        } else {
            pluginFolder = defaultFolder;
            QrTblFrameConfigHelper::setVauleBy(dbServiceType, dbKey, pluginFolder);
        }
    }

    const QString absPathOfServicePlugin = QApplication::applicationDirPath() + "/" + pluginFolder + "/";

    QrSplashStep serviceStep;
    serviceStep.message = QObject::tr("加载服务");
    serviceStep.failMsg = QString("fail to load services");
    serviceStep.function = [this, absPathOfServicePlugin](){
        if (serviceNames.isEmpty()) {
            qInfo() << "services is empty";
            return true;
        }

        loadedServices.clear();
        Q_FOREACH(auto serviceName, serviceNames) {
            QPluginLoader serviceLoader;
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
            loadedServices.append(qMakePair<QString, QObject*>(absFileNameOfServicePlugin, servicePllugin));
        };

        return true;
    };
    splashScreen->addStepFunction(serviceStep);

    return true;
}

bool QrFramerPrivate::initServices() {
    QrSplashStep splashStep;
    splashStep.message = QObject::tr("初始化服务");
    splashStep.failMsg = QString("fail to init services");
    splashStep.function = [this](){
        Q_FOREACH(auto service, loadedServices) {
            auto serviceName = service.first;
            auto serviceObject = service.second;

            auto *serviceIf = qobject_cast<QrIfService*>(serviceObject);
            if (nullptr == serviceIf) {
                qWarning() << serviceName << " is not a service";
                continue;
            }
            if (! serviceIf->init()) {
                qWarning() << "fail to init " << serviceName << " service.";
                continue;
            }
            qInfo() << "service " << serviceName << " init success.";
        }

        return true;
    };
    splashScreen->addStepFunction(splashStep);

    return true;
}

bool QrFramerPrivate::initByConfig()
{
    QrFrameDb::getInstance()->setParams(frameConfig.dbParams);

    QrSplashStep splashStep;
    splashStep.message = QObject::tr("初始化日志服务");
    splashStep.failMsg = "framer initialize fail by config";
    splashStep.function = [this](){
        bool initSuc = true;
        if (frameConfig.installLog) {   //  should do it first after init database params
            initSuc = QrFramerPrivate::installLog();
        }

        qInfo() << "frame database's is "
                << frameConfig.dbParams.folder
                << "/" << frameConfig.dbParams.databaseName;

        return initSuc;
    };

    splashScreen->addStepFunction(splashStep);

    return true;
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
        if ("use" == iter.key()) {
            *defaultUse = (iter.value() == "true" || iter.value() == "1");
        } else if ("folder" == iter.key()) {
            *defaultFolder = iter.value();
        } else if ("level" == iter.key()) {
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
