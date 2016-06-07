#ifndef QRDBDATABASE_H
#define QRDBDATABASE_H

#include "entity/qrsqldatabase.h"
#include "singleton/qrsingleton.h"

#include "qrframe_global.h"

NS_QRFRAME_BEGIN

class QRFRAMESHARED_EXPORT QrDbLocal
        : public QrOrm::QrSqlDatabase
        , public QrCommon::QrSingleton<QrFrame::QrDbLocal>
{
    QR_SINGLETON_DEFINE(QrDbLocal)

private:
    QrDbLocal();
};

NS_QRFRAME_END

#endif // QRDBDATABASE_H
