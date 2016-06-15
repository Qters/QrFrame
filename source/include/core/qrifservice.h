#ifndef QRIFSERVICE_H
#define QRIFSERVICE_H

#include <QtCore/qobject.h>

#include "qrframe_global.h"

NS_QRFRAME_BEGIN

/*!
 * \brief   service's interface
 *
 *  Separate each functional service that privide to Module,
 *  so Qters's Framework can support the collaboration between company departments.
 *
 *  the sevices would be loaded by QPluginLoader which had been configed in database;
 */
class QRFRAMESHARED_EXPORT QrIfService
{
public:
    virtual ~QrIfService() = default;

public:
    virtual bool init() = 0;
};

NS_QRFRAME_END

#define QrIfService_iid "com.qters.qrframe.qrifservice"
Q_DECLARE_INTERFACE(Qters::QrFrame::QrIfService, QrIfService_iid)

#endif // QRIFSERVICE_H
