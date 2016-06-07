#ifndef QRDBDATABASE_H
#define QRDBDATABASE_H

#include "entity/qrsqldatabase.h"
#include "singleton/qrsingleton.h"

#include "qrframe_global.h"

NS_QRFRAME_BEGIN

class QRFRAMESHARED_EXPORT QrFrameDb
        : public QrOrm::QrSqlDatabase
        , public QrCommon::QrSingleton<QrFrame::QrFrameDb>
{
    QR_SINGLETON_DEFINE(QrFrameDb)

private:
    QrFrameDb();
};

NS_QRFRAME_END

#endif // QRDBDATABASE_H
