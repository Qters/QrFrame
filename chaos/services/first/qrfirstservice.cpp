#include "qrfirstservice.h"

#include <QtCore/qdebug.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qapplication.h>

#include "gui/qrnavigation.h"
#include "gui/qrworkspace.h"
#include "gui/qrsystemtray.h"

NS_CHAOS_FIRST_SERVICE_BEGIN

class QrFirstServicePrivate{
public:
    QLabel *label;
};

NS_CHAOS_FIRST_SERVICE_END

USING_NS_CHAOS_BASE;
USING_NS_CHAOS_FIRST_SERVICE;

QrFirstService::QrFirstService()
    :d_ptr(new QrFirstServicePrivate)
{

}

bool QrFirstService::init()
{
    QrNavigation::qrconnect("product.qrcommon", this, SLOT(onLabel()));

    Q_D(QrFirstService);
    d->label = new QLabel("label");

    return true;
}

void QrFirstService::onLabel()
{
    Q_D(QrFirstService);
    QrWorkspace::appendTab(d->label, "const tabpage");
}
