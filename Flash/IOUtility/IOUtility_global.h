#ifndef IOUTILITY_GLOBAL_H
#define IOUTILITY_GLOBAL_H

#define ImportDll   __declspec( dllimport )
#define ExportDll   __declspec( dllexport )


#ifndef IOTILITY_EXPORTS
#define DllExport ImportDll
#else
#define DllExport ExportDll

#endif