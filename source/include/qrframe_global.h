#ifndef QRFRAME_GLOBAL_H
#define QRFRAME_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QRFRAME_LIBRARY)
#  define QRFRAMESHARED_EXPORT Q_DECL_EXPORT
#else
#  define QRFRAMESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QRFRAME_GLOBAL_H
