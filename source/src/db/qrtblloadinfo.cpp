#include "db/qrtblloadinfo.h"

#include "db/qrframedb.h"

#include "qrsqlhelper.h"
#include "qrdbresultsguard.h"
#include "generator/qrselectsql.h"

USING_NS_QRFRAME;

int QrTblLoadInfo::getId() const
{
    return id;
}

void QrTblLoadInfo::setId(int value)
{
    id = value;
}

QString QrTblLoadInfo::getLoad_name() const
{
    return load_name;
}

void QrTblLoadInfo::setLoad_name(const QString &value)
{
    load_name = value;
}

bool QrTblLoadInfoHelper::getLoadServices(QVector<QString>& loadServices)
{
    QrTblLoadInfo tblFrameLoadInfo;

    QrSelectSql selectSql;
    auto query = selectSql.setTable(&tblFrameLoadInfo)
            .columns("load_name").getSqlQuery();

    auto database = QrFrameDb::getInstance()->getDatabase();
    auto error = QrSqlHelper::call_query(query, &database);
    if (error.isValid()) {
        qFatal("could't get frame's load services");
        return false;
    }

    loadServices.clear();
    QrDbResultsGuard<QrTblLoadInfo> dbObjs;
    Q_FOREACH(auto result, dbObjs.fetchResultsBySqlQuery(query)) {
        if (loadServices.contains(result->getLoad_name())) {
            continue;
        }
        loadServices.push_back(result->getLoad_name());
    }

    if (loadServices.isEmpty()) {
        qInfo("load services is empty");
        return false;
    }

    return true;
}
