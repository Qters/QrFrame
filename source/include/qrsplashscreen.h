#ifndef QRSPLASHSCREEN_H
#define QRSPLASHSCREEN_H

#include <functional>

#include <QtWidgets/qsplashscreen.h>

#include "qrglobal.h"

#include "qrframe_global.h"

class QRFRAMESHARED_EXPORT QrSplashStep {
public:
    typedef std::function<bool()> StepFunction;

public:
    StepFunction function;
    QString message;
    QString failMsg;
};

class QrSplashScreenPrivate;
class QRFRAMESHARED_EXPORT QrSplashScreen : public QSplashScreen
{
    Q_OBJECT

    QR_DECLARE_PRIVATE(QrSplashScreen)

public:

public:
    explicit QrSplashScreen(const QPixmap &pixmap = QPixmap(), Qt::WindowFlags f = Qt::WindowFlags());
    QrSplashScreen(QWidget *parent, const QPixmap &pixmap = QPixmap(), Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~QrSplashScreen();

public:
    void addStepFunction(QrSplashStep function);
    bool start(bool isShow);
};

#endif // QRSPLASHSCREEN_H
