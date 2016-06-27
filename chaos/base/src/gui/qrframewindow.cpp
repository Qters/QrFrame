#include "gui/qrframewindow.h"

#include <QtWidgets/qboxlayout.h>

#include "gui/qrheader.h"
#include "gui/qrworkspace.h"
#include "gui/qrstatusbar.h"
#include "gui/qrsystemtray.h"
#include "gui/navigation/qrnavigation.h"
#include "gui/qrframewindowsplitter.h"

NS_CHAOS_BASE_BEGIN

class QrFrameWindowPrivate{
    QR_DECLARE_PUBLIC(QrFrameWindow)

public:
    QrFrameWindowPrivate(QrFrameWindow *q)
    : q_ptr(q)
    {}

public:
    void loadUI() ;

public:
    QrSystemTray *systemTray = nullptr;
    QrHeader *header = nullptr;
    QrNavigation *navigation = nullptr;
    QrWorkspace *worspace = nullptr;
    QrStatusBar *statusbar = nullptr;
};

class QrFrameWindowSplitterPrivate{
    QR_DECLARE_PUBLIC(QrFrameWindowSplitter)

public:
    QrFrameWindowSplitterPrivate(QrFrameWindowSplitter *q)
    : q_ptr(q) {}

};

void QrFrameWindowPrivate::loadUI()
{
    Q_Q(QrFrameWindow);

    header = new QrHeader(q);

    navigation = new QrNavigation(q);
    worspace = new QrWorkspace(q);
    QrFrameWindowSplitter* splitter = new QrFrameWindowSplitter(q);
    splitter->addWidget(navigation);
    splitter->addWidget(worspace);
    splitter->initHandle(1);

    statusbar = new QrStatusBar(q);

    QVBoxLayout* mainLayout = new QVBoxLayout(q);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(header);
    mainLayout->addWidget(splitter);
    mainLayout->addWidget(statusbar);
    q->setLayout(mainLayout);

    systemTray = new QrSystemTray(q);
}

NS_CHAOS_BASE_END


USING_NS_CHAOS_BASE;

QrFrameWindow::QrFrameWindow(QWidget* parent)
    : QFrame(parent), d_ptr(new QrFrameWindowPrivate(this))
{
    setWindowFlags(Qt::FramelessWindowHint);
    d_ptr->loadUI();
}

QrWorkspace *QrFrameWindow::getWorkspace()
{
    Q_D(QrFrameWindow);
    return d->worspace;
}

QrStatusBar *QrFrameWindow::getStatusbar()
{
    Q_D(QrFrameWindow);
    return d->statusbar;
}

QrHeader *QrFrameWindow::getHeader()
{
    Q_D(QrFrameWindow);
    return d->header;
}

QrNavigation *QrFrameWindow::getNavigation()
{
    Q_D(QrFrameWindow);
    return d->navigation;
}
