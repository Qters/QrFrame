#include "db/qrdblocal.h"

#include "entity/qrsqldatabase.h"


using namespace Qters::QrFrame;
using namespace Qters::QrOrm;


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

