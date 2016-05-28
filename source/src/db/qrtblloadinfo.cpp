#include "db/qrtblloadinfo.h"

#include "db/qrdblocal.h"

#include "qrsqlhelper.h"
#include "qrdbresultsguard.h"
#include "generator/qrselectsql.h"

using namespace Qters::QrFrame;

int QrTblLoadInfo::getId() const
{
    return id;
}

void QrTblLoadInfo::setId(int value)
{
    id = value;
}

int QrTblLoadInfo::getType_id() const
{
    return type_id;
}

void QrTblLoadInfo::setType_id(int value)
{
    type_id = value;
}

QString QrTblLoadInfo::getLoad_name() const
{
    return load_name;
}

void QrTblLoadInfo::setLoad_name(const QString &value)
{
    load_name = value;
}

bool QrTblLoadInfoHelper::getLoadNamesByLoadType(QrTblLoadType::LoadType typeId, QVector<QString>& loadNames)
{
    QrTblLoadInfo tblFrameLoadInfo;

    QrSelectSql selectSql;
    auto query = selectSql.setTable(&tblFrameLoadInfo)
            .columns("load_name")
            .where("type_id").isEqualTo(static_cast<int>(typeId))
            .getSqlQuery();

    auto database = QrDbLocal::getInstance()->getDatabase();
    auto error = QrSqlHelper::call_query(query, &database);
    if (error.isValid()) {
        qFatal("could't get frame's load names by type %d", typeId);
        return false;
    }

    loadNames.clear();
    QrDbResultsGuard<QrTblLoadInfo> dbObjs;
    Q_FOREACH(auto result, dbObjs.fetchResultsBySqlQuery(query)) {
        if (loadNames.contains(result->getLoad_name())) {
            continue;
        }
        loadNames.push_back(result->getLoad_name());
    }

    if (loadNames.isEmpty()) {
        qInfo("frame's load names by type %d is empty", typeId);
        return false;
    }

    return true;
}
