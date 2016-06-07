#ifndef QRFRAME_GLOBAL_H
#define QRFRAME_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QRFRAME_LIBRARY)
#  define QRFRAMESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QRFRAMESHARED_EXPORT Q_DECL_IMPORT
#endif

//  qrframe namespace
#define NS_QRFRAME_BEGIN \
    namespace Qters { \
    namespace QrFrame {
#define NS_QRFRAME_END \
    } \
    }
#define USING_NS_QRFRAME    using namespace Qters::QrFrame
#define NS_QRFRAME  ::Qters::QrFrame

#endif // QRFRAME_GLOBAL_H
