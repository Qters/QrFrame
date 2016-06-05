#ifndef SECOND_MODULE_H
#define SECOND_MODULE_H

#include <QtCore/qobject.h>

#include "second_module_global.h"
#include "core/qrmoduleinterface.h"

class SECONDMODULESHARED_EXPORT SecondModule : public QObject, public Qters::QrFrame::QrModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.qrmoduleinterface.second" FILE "secondmodule.json")
    Q_INTERFACES(QrModuleInterface)

    // QrModuleInterface interface
public:
    virtual bool init() override;
};

#endif // FIRST_MODULE_H
