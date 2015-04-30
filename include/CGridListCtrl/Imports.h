#pragma once
#define ImportDll   __declspec( dllimport )
#define ExportDll   __declspec( dllexport )


#ifndef CGRID_LIST_CTRL
#define DllExport ImportDll
#else
#define DllExport ExportDll
#endif