#include "db/qrtblloadtype.h"

#include "db/qrdblocal.h"

#include "qrsqlhelper.h"
#include "qrdbresultsguard.h"
#include "generator/qrselectsql.h"

using namespace Qters::QrFrame;

QString QrTblLoadType::getNote() const
{
    return note;
}

void QrTblLoadType::setNote(const QString &value)
{
    note = value;
}

int QrTblLoadType::getId() const
{
    return id;
}

void QrTblLoadType::setId(int value)
{
    id = value;
}

int QrTblLoadType::getType() const
{
    return type;
}

void QrTblLoadType::setType(int value)
{
    type = value;
}

bool QrTblLoadTypeHelper::getLoadTypes(QVector<QrTblLoadType::LoadType>& loadTypes)
{
    QrTblLoadType tblLoadTypes;
    QrSelectSql selectSql;
    auto query = selectSql.setTable(&tblLoadTypes)
            .columns("type").getSqlQuery();

    auto database = QrDbLocal::getInstance()->getDatabase();
    auto error = QrSqlHelper::call_query(query, &database);
    if (error.isValid()) {
        qWarning("could't get frame's load type");
        return false;
    }

    loadTypes.clear();
    QrDbResultsGuard<QrTblLoadType> dbObjs;
    Q_FOREACH(auto result, dbObjs.fetchResultsBySqlQuery(query)) {
        auto emType = static_cast<QrTblLoadType::LoadType>(result->getType());
        if (loadTypes.contains(emType)) {
            continue;
        }
        loadTypes.push_back(emType);
    }

    if (loadTypes.isEmpty()) {
        qWarning("frame's load type is empty");
        return false;
    }

    return true;
}
