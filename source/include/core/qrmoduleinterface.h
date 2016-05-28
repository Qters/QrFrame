#ifndef QRMODULEINTERFACE_H
#define QRMODULEINTERFACE_H

#include <QtCore/qglobal.h>
#include <QtCore/qobject.h>

#include "qrframe_global.h"

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

namespace Qters {

namespace QrFrame {

/*!
 * \brief   module's interface
 *
 *  Separate each functional modules or each logical moduel,
 *  so that can support the collaboration between company departments.
 *
 *  the modules would be loaded by QPluginLoader which had been configed in database;
 */
class QRFRAMESHARED_EXPORT QrModuleInterface
{
public:
    virtual ~QrModuleInterface() = default;

public:
    virtual bool init() = 0;
};

}   //  namespace QrFrame

}   //  namespace Qters

QT_BEGIN_NAMESPACE
    #define QrModuleInterface_iid "com.qters.qrframe.qrmoduleinterface"
    Q_DECLARE_INTERFACE(Qters::QrFrame::QrModuleInterface, QrModuleInterface_iid)
QT_END_NAMESPACE

#endif // QRMODULEINTERFACE_H
