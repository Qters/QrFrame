#ifndef SECOND_SERVICE_H
#define SECOND_SERVICE_H

#include "second_service_global.h"
#include "core/qrserviceinterface.h"

class SECONDSERVICESHARED_EXPORT SecondService : public Qters::QrFrame::QrServiceInterface
{
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.qrserviceinterface")
    Q_INTERFACES(Qters::QrFrame::QrServiceInterface)

public:
    SecondService();

    // QrServiceInterface interface
public:
    virtual bool init() override;
};

#endif // SECOND_SERVICE_H
