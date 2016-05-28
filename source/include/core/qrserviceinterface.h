#ifndef JZSERVICEINTERFACE_H
#define JZSERVICEINTERFACE_H

#include <QtCore/qobject.h>

#include "qrframe_global.h"
#include "qrmoduleinterface.h"

namespace Qters {

namespace QrFrame {

/*!
 * \brief   service's interface
 *
 *  Separate each functional service that privide to Module,
 *  so Qters's Framework can support the collaboration between company departments.
 *
 *  the sevices would be loaded by QPluginLoader which had been configed in database;
 */
class QRFRAMESHARED_EXPORT QrServiceInterface
{
public:
    virtual ~QrServiceInterface() = default;

public:
    virtual bool init() = 0;
};

}   //  namespace QrFrame

}   //  namespace Qters

QT_BEGIN_NAMESPACE
    #define QrServiceInterface_iid "com.qters.qrframe.qrserviceinterface"
    Q_DECLARE_INTERFACE(Qters::QrFrame::QrServiceInterface, QrServiceInterface_iid)
QT_END_NAMESPACE

#endif // JZSERVICEINTERFACE_H
