#ifndef QRNAVIGATIONHEADER_H
#define QRNAVIGATIONHEADER_H

#include <QtWidgets/qframe.h>

#include "qrchaosbase_global.h"
#include "qrglobal.h"

NS_CHAOS_BASE_BEGIN

class QrNavigationHeaderPrivate;

class CHAOSBASE_SHAREDEXPORT QrNavigationHeader : public QFrame
{
    QR_DECLARE_PRIVATE(QrNavigationHeader)
public:
    QrNavigationHeader(QWidget* parent = 0);
};

NS_CHAOS_BASE_END

#endif // QRNAVIGATIONHEADER_H
