#ifndef QRDBDATABASE_H
#define QRDBDATABASE_H

#include "entity/qrsqldatabase.h"

#include "singleton/qrsingleton.h"

namespace Qters {

namespace QrFrame {

class QrDbLocal
        : public QrOrm::QrSqlDatabase
        , public QrCommon::QrSingleton<QrFrame::QrDbLocal>
{
    QR_SINGLETON_DEFINE(QrDbLocal)

private:
    QrDbLocal();
};

}   //  namespace QrFrame

}   //  namespace Qters

#endif // QRDBDATABASE_H
