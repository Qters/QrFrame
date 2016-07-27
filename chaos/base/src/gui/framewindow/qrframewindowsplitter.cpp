#include "gui/framewindow/qrframewindowsplitter.h"

#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>

NS_CHAOS_BASE_BEGIN

class QrFrameWindowSplitterPrivate{
    QR_DECLARE_PUBLIC(QrFrameWindowSplitter)

public:
    QrFrameWindowSplitterPrivate(QrFrameWindowSplitter *q);
    void setQssObjectNames(){
        handleBtn->setObjectName("QrFrameWindowSplitter_handleBtn");
    }

public:
    QPushButton *handleBtn;
};

QrFrameWindowSplitterPrivate::QrFrameWindowSplitterPrivate(QrFrameWindowSplitter *q)
    : q_ptr(q) {}



NS_CHAOS_BASE_END


USING_NS_CHAOS_BASE;

QrFrameWindowSplitter::QrFrameWindowSplitter(QWidget *parent)
    : QSplitter(parent), d_ptr(new QrFrameWindowSplitterPrivate(this))
{
    setOrientation(Qt::Horizontal);
}

void QrFrameWindowSplitter::initHandle(int index)
{
    auto handle = this->handle(index);
    Q_ASSERT(nullptr != handle);
    if(nullptr == handle) {
        return;
    }

    Q_D(QrFrameWindowSplitter);
    d->handleBtn = new QPushButton(handle);
    d->handleBtn->setCursor(Qt::PointingHandCursor);
    connect(d->handleBtn,&QPushButton::clicked, [this, index](){
        if(0 == this->sizes().at(0)) {
             this->setSizes(QList<int>()<<this->widget(index)->width() << this->widget(index)->width());
        } else {
            this->setSizes(QList<int>()<< 0 << this->widget(index)->width());
        }
    });

    auto layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(d->handleBtn);

    handle->setLayout(layout);
}
