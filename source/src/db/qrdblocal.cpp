#include "db/qrdblocal.h"

#include "entity/qrsqldatabase.h"

USING_NS_QRFRAME;
USING_NS_QRORM;

QR_SINGLETON_IMPLEMENT(QrDbLocal)

QrDbLocal::QrDbLocal()
    : QrSingleton<QrDbLocal>("QrDbLocal")
{
    static QrSqlDatabaseParams param;
    param.driverName = "QSQLITE";
    param.folder = "data";
    param.databaseName = "frame_db.db";
    setParams (param);
}

