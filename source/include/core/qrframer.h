#ifndef QRFRAME_H
#define QRFRAME_H

#include "qrglobal.h"
#include "qrframe_global.h"
#include "entity/qrsqldatabase.h"

NS_QRFRAME_BEGIN

class QrFramerPrivate;
class QrMainWindow;


/*!
 * \brief framer configuration
 */
class QRFRAMESHARED_EXPORT QrFramerConfig{
public:
    QrFramerConfig()
    {}

    bool installLog = true;

    bool splashscreen = false;
    QString splashscreenBgQrcPath;

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

public:
    void setConfig(const QrFramerConfig& config);
    void setMainWindow(QrMainWindow *mainwindow);

public:
    virtual bool start();
    virtual bool loadFramework();
    virtual bool initFramework();
};

NS_QRFRAME_END

#endif // QRFRAME_H
