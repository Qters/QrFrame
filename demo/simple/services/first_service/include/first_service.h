#ifndef FIRST_SERVICE_H
#define FIRST_SERVICE_H

#include <QObject>

#include "qrdemo_global.h"
#include "first_service_global.h"
#include "core/qrifservice.h"

NS_QRDEMO_BEGIN

class FIRSTSERVICESHARED_EXPORT FirstService : public QObject, public Qters::QrFrame::QrIfService
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.qrifservice.first" FILE "firstservice.json")
    Q_INTERFACES(Qters::QrFrame::QrIfService)

    // QrIfService interface
public:
    virtual bool init() override;
};

NS_QRDEMO_END

#endif // FIRST_SERVICE_H
