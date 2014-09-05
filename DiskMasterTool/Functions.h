#pragma once

 #include <QLCDNumber>
 #include <QLabel>
 #include <QComboBox>
 #include <QFile>
 #include <QFileInfo>
 #include <QDir>
 

#include "DiskMasterLib\dm_device.h"
#include "devicewidget.h"

#include "DiskMasterLib\diskmasterlib_global.h"


inline void UpdateDeviceView( const DiskDevicePtr & dispay_device,
					   QComboBox * DeviceAndPortName,
					   QLabel * SerialNumberText = 0,
					   QLabel * SectorsCountText = 0,
					   QLabel * BlockSizeText = 0  )
{
	if (dispay_device)
		if (DeviceAndPortName->count() > 0)
		{
			DeviceAndPortName->setItemText(DeviceAndPortName->currentIndex(), displayName(dispay_device) );

			if (SerialNumberText)
				SerialNumberText->setText( dispay_device->getSerialNumber().c_str() );
			if ( SectorsCountText )
				SectorsCountText->setText( QString::number(dispay_device->getSize()) );
			if ( BlockSizeText )
				BlockSizeText->setText( QString::number(dispay_device->getBlockSize()) );
		}

}
inline DWORD portFromNotDetected(WORD port_number )
{
	switch (port_number)
	{
	case DM_DetectError::kDetectErrorUsb1:
		return DM::DM_Port::kUsb1;
	case DM_DetectError::kDetectErrorUsb2:
		return DM::DM_Port::kUsb2;
	case DM_DetectError::kDetectErrorSata1:
		return DM::DM_Port::kSata1;
	}
	return Unknown_Port;
}

namespace FileSystem
{

	inline QString CreateFilePath( QString & folder_name , const QString & taskName ,  const QString & extension )
	{
		QDir dir( folder_name );
		QFileInfo file_info( dir , taskName + extension );
		return file_info.absoluteFilePath();
	}
	inline bool open_file ( QFile & file, const QString & file_name , QIODevice::OpenMode open_mode)
	{
		file.setFileName( file_name );
		if ( file.open( open_mode ) )
		{
			file.setPermissions( QFile::WriteOwner );
			return true;
		}

		return false;
	}
	inline bool Open_File( QFile & file , const QString & file_name )
	{
		return open_file( file , file_name, QIODevice::ReadWrite | QIODevice::Unbuffered);
	}
	inline bool Create_File( QFile & file, const QString & file_name )
	{
		return open_file( file , file_name , QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Unbuffered);
	}
}

inline qint32 getSectorDistance( const qlonglong current , const qlonglong prev)
{
	return (qint32) (current - prev );
}

inline qlonglong getMinValue(qlonglong value1 , qlonglong value2)
{
	return ( value1 <= value2 ) ? value1 : value2 ;
}

inline QString getDeviceInfoText( DiskDevicePtr & disk_ptr )
{
	QString text = "Device name : " + QString::fromStdString( disk_ptr->getModel() );
	text += "\nSerial number : " + QString::fromStdString( disk_ptr->getSerialNumber() );
	text += "\nNumber of sectors : " + QString::number( disk_ptr->getSize() ) + "\n";
	return text;
}

 #include <QAbstractButton>
inline void UpdateButton( QAbstractButton * button , const QString & text , const QIcon & incon )
{
	button->setText(text);
	button->setIcon(incon);
}

