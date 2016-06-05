#ifndef FIRST_SERVICE_H
#define FIRST_SERVICE_H

#include <QObject>

#include "first_service_global.h"
#include "core/qrserviceinterface.h"

class FIRSTSERVICESHARED_EXPORT FirstService : public QObject, public Qters::QrFrame::QrServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.qrserviceinterface.first" FILE "firstservice.json")
    Q_INTERFACES(Qters::QrFrame::QrServiceInterface)

    // QrServiceInterface interface
public:
    virtual bool init() override;
};

#endif // FIRST_SERVICE_H
