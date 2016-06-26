#ifndef FRAMESIMPLEMAINWINDOW_H
#define FRAMESIMPLEMAINWINDOW_H

#include "qrdemo_global.h"
#include "qrmainwindow.h"

NS_QRDEMO_BEGIN

class FrameSimpleMainWindow : public Qters::QrFrame::QrMainWindow
{
    Q_OBJECT

public:
    FrameSimpleMainWindow(QWidget *parent = 0);
    ~FrameSimpleMainWindow();
};

NS_QRDEMO_END

#endif // FRAMESIMPLEMAINWINDOW_H
