#ifndef QRFIRSTSERVICE_H
#define QRFIRSTSERVICE_H

#include "qrglobal.h"
#include "core/qrifservice.h"
#include "qrchaosfirstservice_global.h"

NS_CHAOS_FIRST_SERVICE_BEGIN

class QrFirstServicePrivate;

class CHAOS_FIRSTSERVICESHARED_EXPORT QrFirstService : public QObject, public Qters::QrFrame::QrIfService
{
    Q_OBJECT
    QR_DECLARE_PRIVATE(QrFirstService)
    Q_PLUGIN_METADATA(IID "com.qters.qrframe.normal.service.first" FILE "firstservice.json")
    Q_INTERFACES(Qters::QrFrame::QrIfService)

public:
    QrFirstService();

    // QrIfService interface
public:
    virtual bool init() override;

private slots:
    void onLabel();
};

NS_CHAOS_FIRST_SERVICE_END

#endif // QRFIRSTSERVICE_H
