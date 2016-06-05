#ifndef SECOND_SERVICE_H
#define SECOND_SERVICE_H

#include <QtCore/qobject.h>

#include "second_service_global.h"
#include "core/qrserviceinterface.h"

class SECONDSERVICESHARED_EXPORT SecondService : public QObject, public Qters::QrFrame::QrServiceInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.demo.service.second" FILE "secondservice.json")
    Q_INTERFACES(Qters::QrFrame::QrServiceInterface)

    // QrServiceInterface interface
public:
    virtual bool init() override;
};

#endif // SECOND_SERVICE_H
