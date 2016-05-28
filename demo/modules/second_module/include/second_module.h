#ifndef SECOND_MODULE_H
#define SECOND_MODULE_H

#include "second_module_global.h"
#include "core/qrmoduleinterface.h"

class SECONDMODULESHARED_EXPORT SecondModule : public Qters::QrFrame::QrModuleInterface
{
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.qrmoduleinterface")
    Q_INTERFACES(Qters::QrFrame::QrModuleInterface)

public:
    SecondModule();

    // QrModuleInterface interface
public:
    virtual bool init() override;
};

#endif // FIRST_MODULE_H
