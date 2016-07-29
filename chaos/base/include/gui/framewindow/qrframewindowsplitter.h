#ifndef QRFRAMEWINDOWSPLITTER_H
#define QRFRAMEWINDOWSPLITTER_H

#include <QtWidgets/qsplitter.h>
#include <QtWidgets/qpushbutton.h>

#include "qrchaosbase_global.h"
#include "qrglobal.h"

NS_CHAOS_BASE_BEGIN

class QrHandleButtonPrivate;
class QrFrameWindowSplitterPrivate;

class CHAOSBASE_SHAREDEXPORT QrHandleButton : public QPushButton{
    QR_DECLARE_PRIVATE(QrHandleButton)

public:
    explicit QrHandleButton(QWidget *parent=0);

public:
    enum class HandleStatus{
        Open,
        Close,
    };

public:
    void updateQss(HandleStatus status);
};

class CHAOSBASE_SHAREDEXPORT QrFrameWindowSplitter : public QSplitter
{
    QR_DECLARE_PRIVATE(QrFrameWindowSplitter)

public:
    explicit QrFrameWindowSplitter(QWidget* parent = nullptr);
    void initHandle(int index);
};

NS_CHAOS_BASE_END

#endif // QRFRAMEWINDOWSPLITTER_H
