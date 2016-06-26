#ifndef QRCHAOS_FIRST_SERVICE_GLOBAL_H
#define QRCHAOS_FIRST_SERVICE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CHAOS_FIRSTSERVICE_LIBRARY)
#  define CHAOS_FIRSTSERVICESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CHAOS_FIRSTSERVICESHARED_EXPORT Q_DECL_IMPORT
#endif

//  qrchaos's service namespace
#define NS_CHAOS_FIRST_SERVICE_BEGIN \
    namespace Qters {   \
    namespace QrFrame { \
    namespace QrChaos {   \
    namespace QrFirstService {

#define NS_CHAOS_FIRST_SERVICE_END \
    } \
    } \
    } \
    }

#define USING_NS_CHAOS_FIRST_SERVICE    using namespace Qters::QrFrame::QrChaos::QrFirstService

#endif // QRCHAOS_FIRST_SERVICE_GLOBAL_H
