#ifndef FIRST_MODULE_GLOBAL_H
#define FIRST_MODULE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FIRST_MODULE_LIBRARY)
#  define FIRSTMODULESHARED_EXPORT Q_DECL_EXPORT
#else
#  define FIRSTMODULESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QFIRST_MODULE_GLOBAL_H
