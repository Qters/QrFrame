#include "gui/framewindow/qrframewindowsplitter.h"

#include <QtCore/qdebug.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>

#include "gui/qrstyle.h"

NS_CHAOS_BASE_BEGIN

class QrHandleButtonPrivate{
    QR_DECLARE_PUBLIC(QrHandleButton)

public:
    QrHandleButtonPrivate(QrHandleButton *q) : q_ptr(q) {}
    QString ButtonQss(QrHandleButton::HandleStatus handleStatus) {
        QString pngPrifix;

        switch(handleStatus) {
        case QrHandleButton::HandleStatus::Open:
            pngPrifix = "open";
            break;
        case QrHandleButton::HandleStatus::Close:
            pngPrifix = "close";
            break;
        default:
            qDebug() << "button status does not exist.";
            return "";
        }

        return  "QPushButton#QrHandleButton {"
                "   background-image: url(:/navigation/images/blue/navigation/splitter_" + pngPrifix + "_def.png)"
                "}"
                "QPushButton#QrHandleButton:hover {"
                "   background-image: url(:/navigation/images/blue/navigation/splitter_" + pngPrifix + "_hov.png)"
                "}"
                "QPushButton#QrHandleButton:pressed {"
                "   background-image: url(:/navigation/images/blue/navigation/splitter_" + pngPrifix + "_clk.png)"
                "}";
    }

    void loadQss(QrHandleButton::HandleStatus handleStatus) {
        Q_Q(QrHandleButton);

        switch(QrStyle::curSkinIndex()){
        case QrStyle::SkinIndex::Default:
            break;
        case QrStyle::SkinIndex::Blue:
            q->setStyleSheet(ButtonQss(handleStatus));
            break;
        }
    }
};

///////////////////////////////////////
class QrFrameWindowSplitterPrivate{
    QR_DECLARE_PUBLIC(QrFrameWindowSplitter)

public:
    QrFrameWindowSplitterPrivate(QrFrameWindowSplitter *q);
    void setQssObjectNames();

public:
    QrHandleButton *handleBtn = nullptr;
};

QrFrameWindowSplitterPrivate::QrFrameWindowSplitterPrivate(QrFrameWindowSplitter *q)
    : q_ptr(q) {}

void QrFrameWindowSplitterPrivate::setQssObjectNames(){
    handleBtn->setObjectName("QrFrameWindowSplitter_handleBtn");
}

NS_CHAOS_BASE_END


USING_NS_CHAOS_BASE;

QrHandleButton::QrHandleButton(QWidget *parent)
    : QPushButton(parent),
      d_ptr(new QrHandleButtonPrivate(this))
{

}

void QrHandleButton::updateQss(QrHandleButton::HandleStatus status)
{
    Q_D(QrHandleButton);
    d->loadQss(status);
}

/////////////////////////////////////////////////////////////////
QrFrameWindowSplitter::QrFrameWindowSplitter(QWidget *parent)
    : QSplitter(parent),
      d_ptr(new QrFrameWindowSplitterPrivate(this))
{
    setOrientation(Qt::Horizontal);

    setObjectName("QrFrameWindowSplitter");
}

void QrFrameWindowSplitter::initHandle(int index)
{
    auto handle = this->handle(index);
    Q_ASSERT(nullptr != handle);
    if(nullptr == handle) {
        return;
    }

    Q_D(QrFrameWindowSplitter);
    d->handleBtn = new QrHandleButton(handle);
    d->handleBtn->setCursor(Qt::PointingHandCursor);
    connect(d->handleBtn,&QPushButton::clicked, [this, index](){
        Q_D(QrFrameWindowSplitter);
        if(0 == this->sizes().at(0)) {  //  close
            this->setSizes(QList<int>()<<this->widget(index)->width() << this->widget(index)->width());
            d->handleBtn->updateQss(QrHandleButton::HandleStatus::Close);
        } else {    //  open
            this->setSizes(QList<int>()<< 0 << this->widget(index)->width());
            d->handleBtn->updateQss(QrHandleButton::HandleStatus::Open);
        }
    });

    auto layout = new QVBoxLayout();
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(d->handleBtn);

    handle->setLayout(layout);

    d->setQssObjectNames();
}
