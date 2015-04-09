#ifndef LIBUI_GLOBAL_H
#define LIBUI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LIBUI_LIB
# define LIBUI_EXPORT Q_DECL_EXPORT
#else
# define LIBUI_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBUI_GLOBAL_H
