#ifndef QRFRAME_H
#define QRFRAME_H

#include "qrframe_global.h"

#include "qrglobal.h"
#include "singleton/qrsingleton.h"

namespace Qters {

namespace QrFrame {

class QrFramerPrivate;

/*!
 * \brief do some job about framework
 */
class QRFRAMESHARED_EXPORT QrFramer : public QrCommon::QrSingleton<QrFrame::QrFramer>
{
    QR_SINGLETON_DEFINE(QrFramer)
    QR_DECLARE_PRIVATE(QrFramer)

public:
    static bool installLog();

private:
    QrFramer();

public:
    virtual bool loadFramework();
    virtual bool initFramework();
};

}   //  namespace QrFrame

}   //  namespace Qters

#endif // QRFRAME_H
