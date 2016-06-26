#ifndef QRFRAMEWINDOWSPLITTER_H
#define QRFRAMEWINDOWSPLITTER_H

#include <QtWidgets/qsplitter.h>

#include "qrchaosbase_global.h"
#include "qrglobal.h"

NS_CHAOS_BASE_BEGIN

class QrFrameWindowSplitterPrivate;

class CHAOSBASE_SHAREDEXPORT QrFrameWindowSplitter : public QSplitter
{
    QR_DECLARE_PRIVATE(QrFrameWindowSplitter)

public:
    explicit QrFrameWindowSplitter(QWidget* parent = nullptr);
    void initHandle(int index);
};

NS_CHAOS_BASE_END

#endif // QRFRAMEWINDOWSPLITTER_H
