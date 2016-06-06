#ifndef QRFRAME_GLOBAL_H
#define QRFRAME_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QRFRAME_LIBRARY)
#  define QRFRAMESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QRFRAMESHARED_EXPORT Q_DECL_IMPORT
#endif

#if !define(NS_QRFRAME_BEGIN)
#define NS_QRFRAME_BEGIN  \
    namespace Qters { \
    namespace QrFrame { \
#endif

#if !define(NS_QRFRAME_END)
#define NS_QRFRAME_END  \
    } \
    } \
#endif

#if !define(USING_NS_QRFRAME)
#define USING_NS_QRFRAME  \
    using namespace Qters::QrFrame
#endif


#endif // QRFRAME_GLOBAL_H
