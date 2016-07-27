#include "gui/header/qrheader.h"

#include <QtCore/qfile.h>
#include <QtCore/qdebug.h>
#include <QtCore/qtextstream.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qtoolbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qmenu.h>
#include <QtGui/qevent.h>

#include "db/qrtblframeconfig.h"
#include "gui/header/qrheadermenu.h"

NS_CHAOS_BASE_BEGIN

class QrHeaderPrivate{
    QR_DECLARE_PUBLIC(QrHeader)

public:
    QrHeaderPrivate(QrHeader *q);

public:
    bool loadSkin();
    void initUI();
    void addBottomLayout(QVBoxLayout *mainLayout);
    void addTopLayout(QVBoxLayout *mainLayout);
    void connectSignals();
    QMainWindow* getMainWindow();
    void switchMaxOrNormal(bool fullScrn);
    void connectPressSignal(QAbstractButton *toolButton);
    void setQssObjectNames();

public:
    bool clickOnButton = false;
    QPoint srcPos = QPoint(0, 0);
    QToolButton *skinButton = nullptr;
    QToolButton *maximumnButton = nullptr;
    QToolButton *minimumButton = nullptr;
    QToolButton *restoreBtn = nullptr;
    QToolButton *closeButton = nullptr;
    QrHeaderMenu *headerMenu = nullptr;
};

QrHeaderPrivate::QrHeaderPrivate(QrHeader *q) : q_ptr(q)
{
}

QMainWindow *QrHeaderPrivate::getMainWindow()
{
    Q_Q(QrHeader);
    QFrame* frame = dynamic_cast<QFrame*>(q->parentWidget());
    Q_ASSERT(nullptr != frame);
    if(nullptr == frame) {
        return nullptr;
    }

    QMainWindow* mainwindow = dynamic_cast<QMainWindow*>(frame->parentWidget());
    Q_ASSERT(nullptr != mainwindow);
    if(nullptr == mainwindow) {
        return nullptr;
    }

    return mainwindow;
}

void QrHeaderPrivate::switchMaxOrNormal(bool fullScrn)
{
    if(fullScrn) {
        maximumnButton->hide();
        restoreBtn->show();
        restoreBtn->update();
    } else {
        restoreBtn->hide();
        maximumnButton->show();
        maximumnButton->update();
    }
}

void QrHeaderPrivate::initUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    addTopLayout(mainLayout);
    addBottomLayout(mainLayout);

    Q_Q(QrHeader);
    q->setLayout(mainLayout);
}

void QrHeaderPrivate::addTopLayout(QVBoxLayout *mainLayout) {
    Q_Q(QrHeader);
    skinButton = new QToolButton(q);
    skinButton->setToolTip(QObject::tr("skin"));
    skinButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    skinButton->setPopupMode(QToolButton::InstantPopup);
    loadSkin();

    minimumButton = new QToolButton(q);
    minimumButton->setToolTip(QObject::tr("minimum"));

    maximumnButton = new QToolButton(q);
    maximumnButton->setToolTip(QObject::tr("maximumn"));

    restoreBtn = new QToolButton(q);
    restoreBtn->setToolTip(QObject::tr("restore"));
    restoreBtn->hide();

    closeButton = new QToolButton(q);
    closeButton->setToolTip(QObject::tr("close"));

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);
    topLayout->addStretch();
    topLayout->addWidget(skinButton);
    topLayout->addWidget(minimumButton);
    topLayout->addWidget(maximumnButton);
    topLayout->addWidget(restoreBtn);
    topLayout->addWidget(closeButton);

    mainLayout->addLayout(topLayout);
}

void QrHeaderPrivate::addBottomLayout(QVBoxLayout *mainLayout) {
    static QString type = "gui";
    static QString key = "quick_menu";

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->setContentsMargins(0, 0, 0, 7);
    bottomLayout->setSpacing(10);

    Q_Q(QrHeader);
    QString needQuickMenu;
    if ( ! Qters::QrFrame::QrTblFrameConfigHelper::getValueBy(type, key, &needQuickMenu) ) {
        needQuickMenu = "false";
    }
    if ("true" == needQuickMenu) {
        headerMenu = new QrHeaderMenu(q);
        bottomLayout->addWidget(headerMenu);
        q->setFixedHeight(50);
    }

    mainLayout->addLayout(bottomLayout);
}

bool QrHeaderPrivate::loadSkin() {
    static const QString dbSkinType = "skin";
    static const QString dbKey = "qsses";
    QString qsses;
    if (! Qters::QrFrame::QrTblFrameConfigHelper::getValueBy(dbSkinType, dbKey, &qsses)) {
        return false;
    }

    QMenu *skinMenu = new QMenu();
    Q_FOREACH(auto qss, qsses.split(';')) {
        auto qssProps = qss.split(',');
        if (2 != qssProps.size()) {
            qWarning() << "qss property in database in unrecognized." << qssProps;
            continue;
        }
        auto action = new QAction(qssProps.at(0), skinMenu);
        action->setData(qssProps.at(1));    //  qss file path
        skinMenu->addAction(action);
    }
    skinButton->setMenu(skinMenu);

    QObject::connect(skinMenu, &QMenu::triggered, [](QAction *action){
        QFile qssFile(action->data().toString());
        if (!qssFile.exists()) {
            qDebug() << "Unable to set stylesheet, file not found"
                     << action->text()
                     << action->data().toString() ;
        } else {
            qssFile.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&qssFile);
            qApp->setStyleSheet(ts.readAll());
        }
    });

    return true;
}

void QrHeaderPrivate::connectSignals() {
    QObject::connect(closeButton, &QToolButton::clicked, [this](){
        getMainWindow()->close();
    });

    QObject::connect(maximumnButton, &QToolButton::clicked, [this](){
        if(!getMainWindow()->isFullScreen()) {
            getMainWindow()->showFullScreen();
            switchMaxOrNormal(true);
        }
    });

    QObject::connect(restoreBtn, &QToolButton::clicked, [this](){
        if(getMainWindow()->isFullScreen()) {
            getMainWindow()->showNormal();
            switchMaxOrNormal(false);
        }
    });

    QObject::connect(minimumButton, &QToolButton::clicked, [this](){
        getMainWindow()->showMinimized();
    });

    connectPressSignal(skinButton);
    connectPressSignal(restoreBtn);
    connectPressSignal(minimumButton);
    connectPressSignal(maximumnButton);
    connectPressSignal(closeButton);
}

void QrHeaderPrivate::connectPressSignal(QAbstractButton *toolButton)
{
    QObject::connect(toolButton, &QAbstractButton::pressed, [this](){
        clickOnButton = true;
    });
}

void QrHeaderPrivate::setQssObjectNames() {
    Q_Q(QrHeader);
    q->setObjectName("QrHeader");

    skinButton->setObjectName("QrHeader_skinButton");
    maximumnButton->setObjectName("QrHeader_maximumnButton");
    minimumButton->setObjectName("QrHeader_minimumButton");
    restoreBtn->setObjectName("QrHeader_restoreBtn");
    closeButton->setObjectName("QrHeader_closeButton");
}

NS_CHAOS_BASE_END


USING_NS_CHAOS_BASE;

QrHeader::QrHeader(QWidget *parent)
    :QFrame(parent), d_ptr(new QrHeaderPrivate(this))
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedHeight(30);

    d_ptr->initUI();
    d_ptr->connectSignals();
    d_ptr->setQssObjectNames();
}

void QrHeader::mousePressEvent(QMouseEvent *event)
{
    Q_D(QrHeader);
    if(d->clickOnButton) {
        d->clickOnButton = false;
    }
    if (Qt::LeftButton == event->button()) {
        d->srcPos = event->pos();
        event->accept();
    }
}

void QrHeader::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QrHeader);
    if (d->clickOnButton) {
        d->clickOnButton = false;
    }
    if (Qt::LeftButton == event->button()) {
        d->srcPos = event->pos();
        event->accept();
    }
}

void QrHeader::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    Q_D(QrHeader);
    auto mainWindow = d->getMainWindow ();
    if (mainWindow->isFullScreen ()) {
        mainWindow->showNormal ();
        d->switchMaxOrNormal(false);
    } else {
        mainWindow->showFullScreen();
        d->switchMaxOrNormal(true);
    }
}

void QrHeader::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(QrHeader);
    if (d->clickOnButton) {
        return;
    }
    if (Qt::LeftButton == event->buttons()) {
        if(d->getMainWindow()->isFullScreen()) {
            d->switchMaxOrNormal(true);
        } else {
            d->getMainWindow()->move(event->globalPos() - d->srcPos);
            d->switchMaxOrNormal (false);
        }

        event->accept();
    }
}

