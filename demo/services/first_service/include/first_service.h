#ifndef FIRST_SERVICE_H
#define FIRST_SERVICE_H

#include "first_service_global.h"
#include "core/qrserviceinterface.h"

class FIRSTSERVICESHARED_EXPORT FirstService : public Qters::QrFrame::QrServiceInterface
{
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.qrserviceinterface")
    Q_INTERFACES(Qters::QrFrame::QrServiceInterface)

public:
    FirstService();

    // QrServiceInterface interface
public:
    virtual bool init() override;
};

#endif // FIRST_SERVICE_H
