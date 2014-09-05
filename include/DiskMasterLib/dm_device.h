#pragma once

//#define NOMINMAX

#include "DiskMasterLib\diskmasterlib_global.h"

#include <windows.h>
#include <memory>

#include <string>
using std::string;
#include <vector>
using std::vector;

 #include <QDebug>
 #include <QThread>
 #include <QReadWriteLock>
 #include <QMutex>
 #include <QString>


#include "dm_constant.h"
#include "dtm\Abstract.h"


//using namespace DM;

//#include "DiskMasterLib\dm_error.h"


class DiskDevice;
typedef std::tr1::shared_ptr<DiskDevice> DiskDevicePtr;


class AbstractDevice
{
public:
	AbstractDevice()
	{

	}
	virtual ~AbstractDevice()
	{

	}

};
typedef std::tr1::shared_ptr<AbstractDevice> AbstractDevicePtr;

/************************************************************************/
/*					        RootDevice									*/
/************************************************************************/
class RootDevice
	: public AbstractDevice
{
public:
	RootDevice()
	{
		/*DMError::getErrorName(0);*/
	}
	virtual ~RootDevice()
	{
		qDebug("Destructor [\'RootDevice\']");
	}
};

typedef std::tr1::shared_ptr<RootDevice> RootDevicePtr;
inline bool comparePorts ( const DM::PORT & port1, const DM::PORT & port2)
{
	return (port1.number == port2.number) ? true : false;
}
bool DISKMASTERLIB_EXPORT compareDevicePort ( const DiskDevicePtr & disk_device, const DM::PORT & port);
inline bool operator == ( const DM::PORT & port1, const DM::PORT & port2)
{
	return comparePorts(port1,port2);
}

/************************************************************************/
/*						      DiskDevice								*/
/************************************************************************/
class DISKMASTERLIB_EXPORT DiskDevice
	: public AbstractDevice
{
public:
	explicit DiskDevice(const DM::PORT * dm_port);
	explicit DiskDevice(DM::Disk * dm_disk);
	explicit DiskDevice(DM::PORT * dm_port, DM::Disk * dm_disk);
	virtual ~DiskDevice();
	
	bool Open( )
	{
		QWriteLocker loker( & lock_);
		if ( DiskPtr_ )
			return DiskPtr_->Open();
		return false;
	}
	bool Close()
	{
		QWriteLocker locker( & lock_ );
		if ( DiskPtr_ )
			return DiskPtr_->Close();
		return false;
	}
	DWORD ReadBlock(ULONGLONG block_offset, BYTE *buff, DWORD block_count)
	{
		QWriteLocker locker( & lock_ );
		if ( DiskPtr_ )
			return DiskPtr_->ReadBlock(block_offset , buff , block_count);
		return 0;
	}
	DWORD WriteBlock(ULONGLONG block_offset, BYTE *buff, DWORD block_count)
	{
		QWriteLocker locker( & lock_ );
		if ( DiskPtr_ )
			return DiskPtr_->WriteBlock(block_offset , buff , block_count);
		return 0;
	}
	void setDisk( DM::Disk * dm_disk);

	const DM::PORT * getPort() const;
	string getModel() const;
	string getSerialNumber() const;
	ULONGLONG getSize() const;
	ULONGLONG getNativeSize() const;
	DWORD getBlockSize() const;
	bool operator == ( const DiskDevice & dm_disk)
	{
		return comparePorts(*this->getPort(), *dm_disk.getPort());
	}
	bool operator == ( const DM::PORT * port)
	{
		return comparePorts(*this->getPort(),*port);
	}
	bool isDetected() const;
	bool isReadOnly() const;
private:
	DM::Disk * DiskPtr_;
	DM::PORT * PortPtr_;
	QReadWriteLock lock_;
};
typedef vector<DiskDevicePtr> DiskDeviceArray;
//QIcon identifyIcon( const DiskDevicePtr & disk_ptr );

/************************************************************************/
/*					        DiskMasterDevice							*/
/************************************************************************/
class DISKMASTERLIB_EXPORT DiskMasterDevice 
	: public AbstractDevice
{
public:
	DiskMasterDevice( DM::DiskController * disk_master );
	virtual ~DiskMasterDevice();

	bool Open();
	void Close();
	bool isReady() const ;

	void AddSource( const DiskDevicePtr & source_disk );
	void AddTarget( const DiskDevicePtr & target_disk );

	DWORD getID() const;

	DiskDevicePtr getDevice( int nIndex ) const 
	{
		assert( nIndex >= 0 );
		if ( nIndex < source_count() )
		{
			return source_list_.at( nIndex );
		}
		else
		{
			int iTarget = nIndex - source_count();
			if ( iTarget < target_count() )
				return target_list_.at( iTarget );
		}
		return nullptr;
	}
	DiskDevicePtr getSource(int nIndex) const;
	int source_count() const;

	DiskDevicePtr getTarget(int nIndex) const;
	int target_count() const;
	int getSourceIndex( const DM::PORT * port ) ;
	int getTargetIndex( const DM::PORT * port ) ;
	int getDeviceIndex( const DM::PORT * port );

	int count() const
	{
		return source_count() + target_count();
	}

	DiskDevicePtr getDiskDevice( const DM::PORT * port);
	const DM::PORT * getPortByNumber( const DWORD portNumber);

	bool Rescan(const DiskDevicePtr & detect_device);
	void DetectByCopy(const DM::PORT * port1, const DM::PORT * port2);
	bool Copy(DWORD source_port, DWORD target_port);
	bool CopyEx(DWORD source_port, DWORD target_port, ULONGLONG source_offset, ULONGLONG target_offset, ULONGLONG sectors_count , DWORD param = 0 );
	bool Verify( DWORD device_port);
	bool VerifyEx( DWORD device_port, ULONGLONG device_offset, ULONGLONG sectors_count , DWORD param = 0);
	bool Erase( DWORD device_port , DWORD erase_param );
	bool EraseEx( DWORD device_port, ULONGLONG device_offset, ULONGLONG sectors_count, DWORD erase_param , DWORD param = 0 );
	void Break();
	//BOOL ReadBlock(DWORD port, ULONGLONG &offset,  BYTE *buff, DWORD block_size);
	//bool WriteBlock(DWORD port, ULONGLONG &offset, BYTE *buff, DWORD block_size);

	DM::DCNotifier * getNotifier() const;
private:
	void ClearDevices(DiskDeviceArray & device_list)
	{
		auto Iter = device_list.begin();
		while (Iter != device_list.end())
		{
			(*Iter)->setDisk(nullptr);
			++Iter;
		}
	}
private:
	bool bReady;
	QReadWriteLock lock_;
	DM::DiskController * disk_master_;

	DiskDeviceArray source_list_;
	DiskDeviceArray target_list_;
};

typedef std::tr1::shared_ptr<DiskMasterDevice> DiskMasterPtr2;
DiskMasterPtr2 toDiskMaster(const AbstractDevicePtr & abstract_device);

class compareDiskToPort
	: public std::binary_function< DiskDevicePtr , const DM::PORT *  , bool >
{
public:
	bool operator() ( const DiskDevicePtr & disk_device, const DM::PORT * dm_port) const
	{
		return ( comparePorts(*disk_device->getPort() , *dm_port) );
	}
};

class compareDiskToPortNumber
	: public std::binary_function< DiskDevicePtr , const DWORD, bool >
{
public:
	bool operator() ( const DiskDevicePtr & disk_device, const DWORD dm_port_number) const
	{

		return disk_device->getPort()->number == dm_port_number ;
	}
};

typedef std::vector<const DM::PORT*> PortArray;
//inline bool compareDiskPorts(const DiskDevicePtr & disk_device, const DM::PORT * dm_port)
//{
//	return (*disk_device->getPort() == *dm_port);
//}

/************************************************************************/
/*							  DeviceHolder                              */
/************************************************************************/
#include "dtm\DiskMasterManager.h"

using namespace DM;

class DISKMASTERLIB_EXPORT DeviceHolder
	: public QThread
	, public DM::ManagerObserver
{
	Q_OBJECT
public:
	DeviceHolder(QObject * parent = 0);
	virtual ~DeviceHolder();

	void Update(ManagerNotifier *manager, void *device, DWORD event_code);
	void some_funk();
signals:
	void AddDevice(DM::DiskController *);
	void RemoveDevice(DM::DiskController *);

protected:
	void run();
};