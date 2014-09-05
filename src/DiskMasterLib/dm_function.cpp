#include "DiskMasterLib\dm_function.h"


bool DMTool::isUSB( const DiskDevicePtr & disk_device)
{
	if ( !disk_device ) 
		return false;

	return (disk_device->getPort()->bus_type == DM::kUsb);
}
bool DMTool::isSATA( const DiskDevicePtr & disk_device)
{
	if ( !disk_device ) 
		return false;

	return (disk_device->getPort()->bus_type == DM::kSata);
}
QString DMTool::displayName( const DiskDevicePtr & disk_device )
{
	return ( disk_device ) ? disk_device->getModel().c_str() : QString();
}
QIcon DMTool::identifyIcon( const DiskDevicePtr & disk_device )
{
	return QIcon();
}

//std::string DMError::getErrorName( uint detect_code )
//{
//	switch(detect_code)
//	{
//	case kDetectErrorUsb1:
//		return DMError::sDetectUsb1;
//	case kDetectErrorUsb2:
//		return DMError::sDetectUsb2;
//	case kDetectErrorSata1:
//		return DMError::sDetectSata;
//	case kDetectErrorSata1Lock:
//		return DMError::sSataLock;
//	default:
//		return DMError::UnknownError;
//	}
//}