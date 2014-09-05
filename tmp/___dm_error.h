#ifndef DM_ERROR_H
#define DM_ERROR_H

#include "DiskMasterLib\diskmasterlib_global.h"


#include <string>


namespace DMError
{
	const std::string UnknownError = "Unknown error";
	const std::string sDetectUsb1 = "Error to detect USB1";
	const std::string sDetectUsb2 = "Error to detect USB2";
	const std::string sDetectSata = "Error to detect SATA1";
	const std::string sSataLock = "Error SATA1 is locked";

	std::string DISKMASTERLIB_EXPORT getErrorName( uint detect_code );
}

#endif