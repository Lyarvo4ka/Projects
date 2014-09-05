#ifndef DISKMASTERLIB_GLOBAL_H
#define DISKMASTERLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#include "DiskMasterLib\typedef.h"

#ifdef DISKMASTERLIB_LIB 
# define DISKMASTERLIB_EXPORT Q_DECL_EXPORT
#else
# define DISKMASTERLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // DISKMASTERLIB_GLOBAL_H
