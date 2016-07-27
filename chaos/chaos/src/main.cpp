﻿#include <QApplication>
#include <QtCore/qdebug.h>

#include "core/qrframer.h"
#include "db/qrframedb.h"
#include "entity/qrsqldatabase.h"
#include "qrrunguard.h"

#include "gui/qrchaosmainwindow.h"

USING_NS_QRCOMMON;
USING_NS_QRFRAME;
USING_NS_CHAOS_BASE;

#include <qfile.h>

int main(int argc, char *argv[])
{
    QrRunGuard guard("qters.farme.chaos.v1");
    if ( !guard.tryToRun() ) {
        return 0;
    }

    QApplication app(argc, argv);

    Qters::QrOrm::QrSqlDatabaseParams dbParam;
    dbParam.driverName = "QSQLITE";
    dbParam.folder = "data";
    dbParam.databaseName = "chaos.db";

    QrFramerConfig frameConfig;
    frameConfig.dbParams = dbParam;
    frameConfig.installLog = false;

    QFile qssFile("blue.qss");
    if(qssFile.open(QIODevice::ReadOnly))
    {
        QString styleSheet = QLatin1String(qssFile.readAll());
        qDebug()<<styleSheet;
        app.setStyleSheet(styleSheet);
    }

    QrChaosMainwindow mwindow;

    QrFramer framer;
    framer.setConfig(frameConfig);
    framer.setMainWindow(&mwindow);
    framer.start();

    return app.exec();
}
