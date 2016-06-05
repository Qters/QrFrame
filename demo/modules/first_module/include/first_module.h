#ifndef FIRST_MODULE_H
#define FIRST_MODULE_H

#include <QtCore/qobject.h>

#include "first_module_global.h"
#include "core/qrmoduleinterface.h"

class FIRSTMODULESHARED_EXPORT FirstModule : public QObject, public Qters::QrFrame::QrModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.qrmoduleinterface.first" FILE "firstmodule.json")
    Q_INTERFACES(Qters::QrFrame::QrModuleInterface)

    // QrModuleInterface interface
public:
    virtual bool init() override;
};

#endif // FIRST_MODULE_H
