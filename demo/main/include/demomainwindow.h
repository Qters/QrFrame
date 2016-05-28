#ifndef DEMOMAINWINDOW_H
#define DEMOMAINWINDOW_H

#include "qrmainwindow.h"

class DemoMainWindow : public Qters::QrFrame::QrMainWindow
{
    Q_OBJECT

public:
    DemoMainWindow(QWidget *parent = 0);
    ~DemoMainWindow();
};

#endif // DEMOMAINWINDOW_H
