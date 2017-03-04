#include "qrsplashscreen.h"

#include <QtCore/qdebug.h>

#include <QtWidgets/qprogressbar.h>

#include <QtGui/qpixmap.h>

NS_QRFRAME_BEGIN

class QrSplashScreenPrivate {
    QR_DECLARE_PUBLIC(QrSplashScreen)

public:
    QColor messageColor = Qt::white;
    QProgressBar *progressBar = nullptr;
    QVector<QrSplashStep> functions;

public:
    QrSplashScreenPrivate(QrSplashScreen *q);

public:
    void init();
};

NS_QRFRAME_END


USING_NS_QRFRAME;

QrSplashScreenPrivate::QrSplashScreenPrivate(QrSplashScreen *q)
    : q_ptr(q)
{}

void QrSplashScreenPrivate::init()
{
    Q_Q(QrSplashScreen);
    progressBar = new QProgressBar(q);
    progressBar->setObjectName("splashscreen_progressbar");
    progressBar->setGeometry(0, q->pixmap().height()-50, q->pixmap().width(), 30);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
}

////////////////////////////////////////

QrSplashScreen::QrSplashScreen(const QPixmap &pixmap, Qt::WindowFlags f)
    : QSplashScreen(pixmap, f),
      d_ptr(new QrSplashScreenPrivate(this))
{
    Q_D(QrSplashScreen);
    d->init();
}

QrSplashScreen::QrSplashScreen(QWidget *parent, const QPixmap &pixmap, Qt::WindowFlags f)
    : QSplashScreen(parent, pixmap, f),
      d_ptr(new QrSplashScreenPrivate(this))
{
    Q_D(QrSplashScreen);
    d->init();
}

QrSplashScreen::~QrSplashScreen()
{

}

void QrSplashScreen::addStepFunction(QrSplashStep function)
{
    Q_D(QrSplashScreen);
    d->functions.push_back(function);
}

bool QrSplashScreen::start(bool isShow)
{
    if(isShow) {
        show();
    }

    bool success = true;
    Q_D(QrSplashScreen);
    auto functionCount = d->functions.count();
    auto functionProgressValue = 100/functionCount;
    Q_FOREACH(QrSplashStep function, d->functions) {
        showMessage(function.message, Qt::AlignLeft | Qt::AlignBottom, d->messageColor);
        bool functionSuccess = function.function();
        if(! functionSuccess) {
            qInfo() << function.failMsg;
        }
        success &= functionSuccess;
        d->progressBar->setValue(d->progressBar->value() + functionProgressValue);
    }
    d->progressBar->setValue(100);

    return success;
}

void QrSplashScreen::setMessageColor(const QColor &color)
{
    Q_D(QrSplashScreen);
    d->messageColor = color;
}

