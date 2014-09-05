#ifndef DM_FUNCTION_H
#define DM_FUNCTION_H

#include "DiskMasterLib\diskmasterlib_global.h"
#include "DiskMasterLib\dm_device.h"

#include <QIcon>


namespace DMTool
{
	bool DISKMASTERLIB_EXPORT isUSB( const DiskDevicePtr & disk_device);
	bool DISKMASTERLIB_EXPORT isSATA( const DiskDevicePtr & disk_device);
	QString DISKMASTERLIB_EXPORT displayName( const DiskDevicePtr & disk_device );
	QIcon DISKMASTERLIB_EXPORT identifyIcon( const DiskDevicePtr & disk_device );
};

#endif