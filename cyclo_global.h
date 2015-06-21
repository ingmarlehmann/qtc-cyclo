#ifndef CLOC_GLOBAL_H
#define CLOC_GLOBAL_H

#include <QtGlobal>

#if defined(CLOC_LIBRARY)
#  define CLOCSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CLOCSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CLOC_GLOBAL_H
