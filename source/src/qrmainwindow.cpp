#include "qrmainwindow.h"

#include <QtCore/qdebug.h>

#include "core/qrframer.h"

USING_NS_QRFRAME;

QrMainWindow::QrMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qInfo() << "begin show mainwindow";
    init();
}

QrMainWindow::~QrMainWindow()
{
    qInfo() << "end mainwindow";
}

bool QrMainWindow::init()
{
    return QrFramer::getInstance()->loadFramework()
            && QrFramer::getInstance()->initFramework();
}

