﻿#ifndef QRFRAME_H
#define QRFRAME_H

#include <functional>

#include <QtGui/qcolor.h>

#include "qrglobal.h"
#include "qrframe_global.h"
#include "entity/qrsqldatabase.h"

NS_QRFRAME_BEGIN

class QrFramerPrivate;
class QrMainWindow;
class QrSplashStep;

/*!
 * \brief framer configuration
 */
class QRFRAMESHARED_EXPORT QrFramerConfig{
public:
    QrFramerConfig();

    bool installLog = true;

    bool splashscreen = false;
    QString splashscreenBgQrcPath;
    QColor splashColor = Qt::white;

    bool customServiceNames = false;
    std::function<QVector<QString>()> customServiceNamesFunc;

    Qters::QrOrm::QrSqlDatabaseParams dbParams;
};

/*!
 * \brief do some job about framework
 */
class QRFRAMESHARED_EXPORT QrFramer
{
    QR_DECLARE_PRIVATE(QrFramer)

public:
    QrFramer();
    virtual ~QrFramer();

public:
    void setConfig(const QrFramerConfig& config);
    void setMainWindow(QrMainWindow *mainwindow);

    //  should be add before call start()
    void addSplashStep(const QrSplashStep& splashStep);

public:
    //  init logger and database
    virtual bool init();
    //  call init first
    virtual bool start();

protected:
    virtual bool loadFramework();
    virtual bool initFramework();
};

NS_QRFRAME_END

#endif // QRFRAME_H
