#include "qrmainwindow.h"

#include <QtCore/qdebug.h>

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
    return true;
}

