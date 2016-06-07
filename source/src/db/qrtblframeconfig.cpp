#include "db/qrtblframeconfig.h"

#include "db/qrframedb.h"

#include "qrsqlhelper.h"
#include "qrdbresultsguard.h"
#include "generator/qrselectsql.h"
#include "generator/qrupdatesql.h"

USING_NS_QRFRAME;

int QrTblFrameConfig::getId() const
{
    return id;
}

void QrTblFrameConfig::setId(int value)
{
    id = value;
}

QString QrTblFrameConfig::getKey() const
{
    return key;
}

void QrTblFrameConfig::setKey(const QString &value)
{
    key = value;
}

QString QrTblFrameConfig::getValue() const
{
    return value;
}

void QrTblFrameConfig::setValue(const QString &value)
{
    this->value = value;
}

QString QrTblFrameConfig::getType() const
{
    return type;
}

void QrTblFrameConfig::setType(const QString & value)
{
    type = value;
}

bool QrTblFrameConfigHelper::getValueByKey(const QString& key,
                                           QString *configValue)
{
    Q_ASSERT(nullptr != configValue);

    QMap<QString, QString> configValues;
    if (! getKeyValuesBy("key", key, &configValues)) {
        return false;
    }

    *configValue = configValues.first();
    return true;
}

bool QrTblFrameConfigHelper::setVauleByKey(const QString& key, const QString &configValue)
{
    QrTblFrameConfig tblConfig;

    auto database = QrFrameDb::getInstance()->getDatabase();
    QrUpdateSql updateSql;
    auto error = QrSqlHelper::call_query(
                updateSql.setTable(&tblConfig)
                .colvals(qMakePair<QString, QVariant>("value", configValue))
                .where("key").isEqualTo(key).getSqlQuery(),
                &database);
    if (error.isValid()) {
        qFatal("could't set frame's config value by %s", key);
        return false;
    }

    return true;
}

bool QrTblFrameConfigHelper::getKeyValuesByType(const QString &type, QMap<QString, QString> *configValues)
{
    Q_ASSERT(nullptr != configValues);

    return getKeyValuesBy("type", type, configValues);
}

bool QrTblFrameConfigHelper::getKeyValuesBy(const QString &by, const QString &value, QMap<QString, QString> *configValues)
{
    Q_ASSERT(nullptr != configValues);

    QrTblFrameConfig tblConfig;
    QrSelectSql selectSql;
    auto query = selectSql.setTable(&tblConfig)
            .columns("key", "value")
            .where(by).isEqualTo(value)
            .getSqlQuery();

    auto database = QrFrameDb::getInstance()->getDatabase();
    auto error = QrSqlHelper::call_query(query, &database);
    if (error.isValid()) {
        qInfo("could't get frame's config value by %s=%s", by, value);
        return false;
    }

    QrDbResultsGuard<QrTblFrameConfig> dbObjs;
    Q_FOREACH(auto result, dbObjs.fetchResultsBySqlQuery(query)) {
        (*configValues)[result->getKey()] = result->getValue();
    }

    if (configValues->isEmpty()) {
        qInfo("config values of %s=%s is empty", by, value);
        return false;
    }

    return true;
}
