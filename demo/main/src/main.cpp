#include "demomainwindow.h"
#include <QApplication>

#include "core/qrframer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Qters::QrFrame::QrFramer::installLog();

    DemoMainWindow w;
    w.show();

    return a.exec();
}
