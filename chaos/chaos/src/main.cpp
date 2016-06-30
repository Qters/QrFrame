#include <QApplication>
#include <QtCore/qdebug.h>

#include "core/qrframer.h"
#include "db/qrframedb.h"
#include "entity/qrsqldatabase.h"

#include "gui/qrchaosmainwindow.h"

USING_NS_QRFRAME;
USING_NS_CHAOS_BASE;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Qters::QrOrm::QrSqlDatabaseParams dbParam;
    dbParam.driverName = "QSQLITE";
    dbParam.folder = "data";
    dbParam.databaseName = "chaos.db";

    QrFramerConfig frameConfig;
    frameConfig.dbParams = dbParam;
    frameConfig.installLog = false;

    QrChaosMainwindow mwindow;

    QrFramer framer;
    framer.setConfig(frameConfig);
    framer.setMainWindow(&mwindow);
    framer.start();

    return a.exec();
}
