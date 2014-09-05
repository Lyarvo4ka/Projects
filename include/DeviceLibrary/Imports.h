#pragma once
#define ImportDll   __declspec( dllimport )
#define ExportDll   __declspec( dllexport )


#ifndef DEVICELIBRARY_EXPORTS
#define DllExport ImportDll
#else
#define DllExport ExportDll
#endif


