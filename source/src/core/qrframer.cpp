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
    bool getServices(QVector<QString> &serviceNames);
    bool loadServices();
    bool initServices();
    void makesureSplashExist();
    bool initLogger();
    bool initDatabase();

public:
    bool isInit = false;
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
    d->makesureSplashExist();
    d->splashScreen->addStepFunction(splashStep);
}

bool QrFramer::init()
{
    Q_D(QrFramer);
    QrFrameDb::getInstance()->setParams(d->frameConfig.dbParams);

    if(! d->initLogger()) {
        qInfo() << "fail to init logger";
    }
    if(! d->initDatabase()) {
        qWarning() << "fail to init database";
        return false;
    }

    d->isInit = true;
    return true;
}

bool QrFramer::start()
{
    Q_D(QrFramer);
    if(! d->isInit) {
        qWarning() << "framer is not init.";
        return false;
    }

    d->makesureSplashExist();

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

    QrSplashStep getServicesStep;
    getServicesStep.message = QObject::tr("获取服务模块");
    getServicesStep.failMsg = "fail to get services";
    getServicesStep.function = [this](){
        Q_D(QrFramer);
        if(d->frameConfig.customServiceNames) { //  自定义获取服务名称
            d->serviceNames = d->frameConfig.customServiceNamesFunc();
            return true;
        }
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
            splashScreen->showMessageEx(QObject::tr("加载%1").arg(absFileNameOfServicePlugin));
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

            splashScreen->showMessageEx(QObject::tr("初始化%1").arg(serviceName));
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

void QrFramerPrivate::makesureSplashExist()
{
    if( nullptr == splashScreen) {
        splashScreen = new QrSplashScreen(frameConfig.splashscreenBgQrcPath);
        splashScreen->setMessageColor(frameConfig.splashColor);
    }
}

bool QrFramerPrivate::initLogger()
{
    qDebug() << "初始化日志服务";

    bool initSuc = true;
    if (frameConfig.installLog) {   //  should do it first after init database params
        initSuc = QrFramerPrivate::installLog();
    }

    qInfo() << "frame database's is "
            << frameConfig.dbParams.folder
            << "/" << frameConfig.dbParams.databaseName;

    return initSuc;
}

bool QrFramerPrivate::initDatabase()
{
    qDebug() << "初始化数据库";

    bool isInit = true;
    qDebug() << "begin load database";
    if (! QrSqlHelper::makesureDbExist(QrFrameDb::getInstance())) {
        isInit = false;
        qWarning() << "fail to init database";
    }
    qDebug() << "end load database";
    return isInit;
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


////////////////////////////////////////////

QrFramerConfig::QrFramerConfig()
    : customServiceNamesFunc([]{    return QVector<QString>();  })
{}
