#include "framesimplemainwindow.h"

#include <QApplication>
#include <QtCore/qdebug.h>

#include "core/qrframer.h"

#include "db/qrframedb.h"

USING_NS_QRFRAME;
USING_NS_QRDEMO;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QrFramerConfig frameConfig;
    frameConfig.dbFolder = "demo/frame_simple/data";
    frameConfig.installLog = true;

    FrameSimpleMainWindow mwindow;

    QrFramer framer;
    framer.setConfig(frameConfig);
    framer.setMainWindow(&mwindow);
    framer.start();

    return a.exec();
}
