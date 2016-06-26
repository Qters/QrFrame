#ifndef SECOND_SERVICE_H
#define SECOND_SERVICE_H

#include <QtCore/qobject.h>

#include "qrdemo_global.h"
#include "second_service_global.h"
#include "core/qrifservice.h"

NS_QRDEMO_BEGIN

class SECONDSERVICESHARED_EXPORT SecondService : public QObject, public Qters::QrFrame::QrIfService
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.demo.service.second" FILE "secondservice.json")
    Q_INTERFACES(Qters::QrFrame::QrIfService)

    // QrIfService interface
public:
    virtual bool init() override;
};

NS_QRDEMO_END

#endif // SECOND_SERVICE_H
