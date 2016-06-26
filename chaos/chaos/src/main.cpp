#include <QApplication>
#include <QtCore/qdebug.h>

#include "core/qrframer.h"
#include "db/qrframedb.h"

#include "gui/qrnormalmainwindow.h"
#include "gui/qrnavigation.h"

USING_NS_QRFRAME;
USING_NS_CHAOS_BASE;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QrFramerConfig frameConfig;
    frameConfig.dbFolder = "data";
    frameConfig.installLog = false;

    QrChaosMainwindow mwindow;

    QrFramer framer;
    framer.setConfig(frameConfig);
    framer.setMainWindow(&mwindow);
    framer.start();

    return a.exec();
}
