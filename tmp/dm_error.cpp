#include "DiskMasterLib\dm_error.h"

//#include "dtm\DiskMaster.h"

std::string DMError::getErrorName( uint detect_code )
{
	switch(detect_code)
	{
	case kDetectErrorUsb1:
		return DMError::sDetectUsb1;
	case kDetectErrorUsb2:
		return DMError::sDetectUsb2;
	case kDetectErrorSata1:
		return DMError::sDetectSata;
	case kDetectErrorSata1Lock:
		return DMError::sSataLock;
	default:
		return DMError::UnknownError;
	}
}