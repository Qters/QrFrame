#include "core/qrframer.h"

#include <QtCore/qpluginloader.h>
#include <QtCore/qdebug.h>
#include <QtWidgets/qapplication.h>
#include <QtCore/qpair.h>
#include <QtCore/qdir.h>

#include "db/qrdblocal.h"
#include "core/qrmoduleinterface.h"
#include "core/qrserviceinterface.h"
#include "db/qrtblloadinfo.h"
#include "db/qrtblloadtype.h"
#include "db/qrtblframeconfig.h"

#include "Logger.h"
#include "FileAppender.h"

#include "qrsqlhelper.h"

namespace Qters {

namespace QrFrame {

class QrFramerPrivate{
public:
    static bool initLogInfoByDatabase(bool *defaultUse,
                                      QString *defaultFolder,
                                      Logger::LogLevel *defaultLevel);

public:
    bool readPluginsAndServices();
    bool loadModules();
    bool loadServices();

public:
    bool loadPlugins(QVector<QString> pluginNames,
                     const QString& pathKey,
                     const QString& defaultFolder,
                     QVector<QPair<QString, QObject *> > *loadedPlugins) const;
    bool initModules();
    bool initServices();

public:
    QVector<QString> moduleNames;
    QVector<QString> serviceNames;
    QVector<QPair<QString, QObject *> > loadedModules;
    QVector<QPair<QString, QObject *> > loadedServices;
};

}   //  namespace QrFrame

}   //  namespace Qters

using namespace Qters::QrFrame;
using namespace Qters::QrCommon;
using namespace Qters::QrOrm;

//////////////////////////////////////////////////

QR_SINGLETON_IMPLEMENT(QrFramer)

QrFramer::QrFramer()
    : QrSingleton<QrFramer>("QrFramer")
    , d_ptr(new QrFramerPrivate)
{

}

bool QrFramer::installLog()
{
    qDebug() << "begin install log service";

    bool defaultUse = true;
    QString defaultFolder = "log";
    Logger::LogLevel defaultLevel = Logger::Info;

    QrFramerPrivate::initLogInfoByDatabase(&defaultUse, &defaultFolder, &defaultLevel);

    if (! defaultUse) {
        qInfo() << "install log sevice fail, please set in db if you want it.";
        return true;
    }

    QString logFilePath = QApplication::applicationDirPath() +
            "/" + defaultFolder;
    if (!QDir(logFilePath).exists()) {
        QDir().mkdir(logFilePath);
    }
    logFilePath += "/" + QString("app-%1.log")
            .arg (QDateTime::currentDateTime().date ().toString (Qt::ISODate));
    FileAppender* fileAppender = new FileAppender(logFilePath);
    fileAppender->setDetailsLevel(defaultLevel);
    qDebug() << "log is intalled! and logs are put in " << logFilePath;

    Logger::globalInstance ()->registerAppender (fileAppender);

    qInfo().noquote() << "\n\n============================================";
    qInfo() << "start log.";
    return true;
}

bool QrFramer::loadFramework()
{
    Q_D(QrFramer);
    qDebug() << "begin load framework";

    bool suc = QrSqlHelper::makesureDbExist(QrDbLocal::getInstance())
            && d->readPluginsAndServices()
            && d->loadServices()
            && d->loadModules();

    qDebug() << "end load framework";
    return suc;
}

bool QrFramer::initFramework()
{
    Q_D(QrFramer);
    qDebug() << "begin initialize framework";

    bool suc = d->initServices()
            && d->initModules();

    qDebug() << "end initialize framework";
    return suc;
}

//////////////////////////////////////////////////
bool QrFramerPrivate::readPluginsAndServices() {
    QVector<QrTblLoadType::LoadType> loadTypes;
    if (! QrTblLoadTypeHelper::getLoadTypes(loadTypes)) {
        return false;
    }

    QVector<QString> loadNames;
    Q_FOREACH(auto typeId, loadTypes) {
        if (! QrTblLoadInfoHelper::getLoadNamesByLoadType(typeId, loadNames)) {
            continue;
        }
        switch (typeId) {
        case QrTblLoadType::LoadType::Module:
            moduleNames = loadNames;
            break;
        case QrTblLoadType::LoadType::Service:
            serviceNames = loadNames;
            break;
        default:
            qInfo() << "could't recognize load type in loading";
            break;
        }
    }

    return true;
}

bool QrFramerPrivate::loadPlugins(QVector<QString> pluginNames,
                                  const QString& pathKey,
                                  const QString &defaultFolder,
                                  QVector<QPair<QString, QObject *> > *loadedPlugins) const {
    if (pluginNames.isEmpty()) {
        qInfo() << pathKey << "'s plugins is empty";
        return true;
    }

    QString pluginPath;
    if (! QrTblFrameConfigHelper::getValueByKey(pathKey, &pluginPath)) {
        pluginPath = defaultFolder;
        QrTblFrameConfigHelper::setVauleByKey(pathKey, pluginPath);
    }

    loadedPlugins->clear();
    QPluginLoader pluginLoader;
    const QString pluginAbsPath = QApplication::applicationDirPath() + "/" + pluginPath + "/";
    Q_FOREACH(auto pluginName, pluginNames) {
        QString pluginAbsName = pluginAbsPath + pluginName;
#ifdef QT_DEBUG
        pluginAbsName += "d";
#endif
        pluginAbsName += ".dll";
        pluginLoader.setFileName(pluginAbsName);
        QObject *plugin = pluginLoader.instance();
        if(nullptr == plugin){
            qWarning() << pluginAbsName << " is not a plugin object.";
            continue;
        }
        loadedPlugins->append(qMakePair<QString, QObject*>(pluginAbsName, plugin));
    }

    return true;
}

bool QrFramerPrivate::loadModules() {
    this->loadedModules.clear();
    if (! loadPlugins(this->moduleNames,
                      "modules_path",
                      "modules",
                      &loadedModules) ) {
        return false;
    }

    return true;
}

bool QrFramerPrivate::initModules() {
    Q_FOREACH(auto module, this->loadedModules) {
        auto *moduleIf = qobject_cast<QrModuleInterface*>(module.second);
        if (nullptr == moduleIf) {
            qWarning() << module.first << " is not a module";
            continue;
        }
        if (moduleIf->init()) {
            qWarning() << module.first << " init fail";
        }
    }

    return true;
}

bool QrFramerPrivate::loadServices() {
    this->loadedServices.clear();
    if (! loadPlugins(this->serviceNames,
                      "services_path",
                      "services",
                      &this->loadedServices) ) {
        return false;
    }

    return true;
}

bool QrFramerPrivate::initServices() {
    Q_FOREACH(auto service, this->loadedServices) {
        auto *serviceIf = qobject_cast<QrServiceInterface*>(service.second);
        if (nullptr == serviceIf) {
            qWarning() << service.first << " is not a service";
            continue;
        }
        if (serviceIf->init()) {
            qWarning() << service.first << " init fail";
        }
    }

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
