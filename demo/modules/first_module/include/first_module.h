#ifndef FIRST_MODULE_H
#define FIRST_MODULE_H

#include "first_module_global.h"
#include "core/qrmoduleinterface.h"

class FIRSTMODULESHARED_EXPORT FirstModule : public Qters::QrFrame::QrModuleInterface
{
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.qrmoduleinterface")
    Q_INTERFACES(Qters::QrFrame::QrModuleInterface)

public:
    FirstModule();

    // QrModuleInterface interface
public:
    virtual bool init() override;
};

#endif // FIRST_MODULE_H
