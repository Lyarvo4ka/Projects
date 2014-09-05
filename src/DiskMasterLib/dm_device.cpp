#include "DiskMasterLib\dm_device.h"
// warning C4482: nonstandard extension used: enum
#pragma warning(disable : 4482)


 #include <QWriteLocker>
 #include <QReadLocker>

#include "dtm\DiskMaster.h"

#include <functional>





bool compareDevicePort ( const DiskDevicePtr & disk_device, const DM::PORT & port)
{
	if (!disk_device)
		return false;

	return (disk_device->getPort()->number == port.number);
}

/************************************************************************/
/*								DiskDevice								*/
/************************************************************************/
DiskDevice::DiskDevice(const DM::PORT * dm_port)
	: PortPtr_((DM::PORT*)dm_port)
	, DiskPtr_(nullptr)
{

}
DiskDevice::DiskDevice(DM::Disk * dm_disk)
	: DiskPtr_(dm_disk)
	, PortPtr_(nullptr)
{
	QWriteLocker lock ( &lock_ );
	PortPtr_ = (DM::PORT*) DiskPtr_->Port();
}
DiskDevice::DiskDevice(DM::PORT * dm_port, DM::Disk * dm_disk)
	: DiskPtr_(dm_disk)
	, PortPtr_(dm_port)
{
}
DiskDevice::~DiskDevice()
{
	DiskPtr_ = nullptr;
	qDebug("Destructor [\'DiskDevice\']");
}
void DiskDevice::setDisk( DM::Disk * dm_disk)
{
	QWriteLocker lock ( &lock_ );
	DiskPtr_ = dm_disk;
}
const DM::PORT *DiskDevice::getPort() const
{
	QReadLocker lock ( (QReadWriteLock *) &lock_ );
	return (DiskPtr_) ? DiskPtr_->Port() : PortPtr_;
}
string DiskDevice::getModel() const
{
	QReadLocker lock ( (QReadWriteLock *)  &lock_ );
	return (DiskPtr_) ? DiskPtr_->Model() : "";
}
string DiskDevice::getSerialNumber() const
{
	QReadLocker lock ( (QReadWriteLock *)  &lock_ );
	string retString("no serial number");
	if (DiskPtr_) 
		if (DiskPtr_->SerialNumber() != 0)
			retString = DiskPtr_->SerialNumber();
	return retString;
}
ULONGLONG DiskDevice::getSize() const
{
	QReadLocker lock ( (QReadWriteLock *)  &lock_ );
	return (DiskPtr_) ? DiskPtr_->Size() : 0;
}
ULONGLONG DiskDevice::getNativeSize() const
{
	QReadLocker lock (  (QReadWriteLock *) &lock_ );
	return (DiskPtr_) ? DiskPtr_->NativeSize() : 0;
}
DWORD DiskDevice::getBlockSize() const
{
	QReadLocker lock ( (QReadWriteLock *)  &lock_ );
	return (DiskPtr_) ? DiskPtr_->BlockSize() : 0;
}

bool DiskDevice::isDetected() const
{
	QReadLocker lock ( (QReadWriteLock *)  &lock_ );
	return (DiskPtr_ ) ? true : false;
}
bool DiskDevice::isReadOnly() const
{
	QReadLocker lock ( (QReadWriteLock *)  &lock_ );
	return (this->getPort()->features == DM::kReadOnly);
}


/************************************************************************/
/*					        DiskMasterDevice							*/
/************************************************************************/
DiskMasterDevice::DiskMasterDevice(DM::DiskController * disk_master)
	: disk_master_(disk_master)
	, bReady(false)
{
	//this->Close();
	//this->Open();

	auto count = disk_master_->PortsCount();

	for (auto iPort = 0; iPort < count; ++iPort)
	{
		if (auto curPort = disk_master_->Port(iPort) )
		{
			if (curPort->features == DM::kReadOnly)
			{
				this->AddSource( DiskDevicePtr( new DiskDevice(curPort) ) );
			}
			else
				this->AddTarget( DiskDevicePtr( new DiskDevice(curPort) ) );

		}
	}
}
DiskMasterDevice::~DiskMasterDevice()
{
	this->Close();
	bReady = false;
	disk_master_ = nullptr;
	qDebug("Destructor [\'DiskMasterDevice\']");
}
bool DiskMasterDevice::Open()
{
	bReady = ( disk_master_->Open() ) ? true : false;
	return bReady;
}
void DiskMasterDevice::Close()
{
	if ( bReady )
	{
		disk_master_->Close();
		ClearDevices(source_list_);
		ClearDevices(target_list_);
	}
	bReady = false;
}
bool DiskMasterDevice::isReady() const
{
	return bReady;
}
void DiskMasterDevice::AddSource( const DiskDevicePtr & source_disk )
{
	QWriteLocker lock ( &lock_ );
	auto findIter = std::find(source_list_.begin(),source_list_.end(), source_disk);
	if (findIter == source_list_.end())
		source_list_.push_back(source_disk);
}
void DiskMasterDevice::AddTarget( const DiskDevicePtr & target_disk )
{
	QWriteLocker lock ( &lock_ );
	auto findIter = std::find(target_list_.begin(),target_list_.end(), target_disk);
	if (findIter == target_list_.end())
		target_list_.push_back(target_disk);
}
DWORD DiskMasterDevice::getID() const
{
	// must change to assert
	//assert (disk_master_ != nullptr );

	if (disk_master_)
		return disk_master_->GetID();
	return -1;
}
DiskDevicePtr DiskMasterDevice::getSource(int nIndex) const
{
	QReadLocker lock ( (QReadWriteLock *) &lock_ );
	return ( nIndex < source_list_.size() ) ? source_list_[nIndex] : DiskDevicePtr();
}
int DiskMasterDevice::source_count() const
{
	QReadLocker lock ( (QReadWriteLock *) &lock_ );
	return source_list_.size();
}
DiskDevicePtr DiskMasterDevice::getTarget(int nIndex) const
{
	QReadLocker lock ( (QReadWriteLock *) &lock_ );
	return ( nIndex < target_list_.size() ) ? target_list_[nIndex] : DiskDevicePtr();
}
int DiskMasterDevice::target_count() const
{
	QReadLocker lock ( (QReadWriteLock *) &lock_ );
	return target_list_.size();
}
bool DiskMasterDevice::Rescan(const DiskDevicePtr & detect_device)
{
	if (auto dm_disk = this->disk_master_->Rescan(detect_device->getPort()->number))
	{
		detect_device->setDisk((DM::Disk *) dm_disk);
		return true;
	}
	return false;
}
bool DiskMasterDevice::Copy(DWORD source_port, DWORD target_port)
{
	if ( disk_master_ )
		return (disk_master_->Copy(source_port,target_port,0) ) ? true : false;

	return false;
}
bool DiskMasterDevice::CopyEx(DWORD source_port, DWORD target_port, ULONGLONG source_offset, ULONGLONG target_offset, ULONGLONG sectors_count , DWORD param)
{
	if ( disk_master_ )
		return (disk_master_->CopyEx(source_port, target_port, source_offset, target_offset, sectors_count,param) ) ? true : false;

	return false;
}
bool DiskMasterDevice::Verify( DWORD device_port)
{
	if ( disk_master_ )
		return (disk_master_->Test(device_port, 0 ) ) ? true : false;

	return false;
}
bool DiskMasterDevice::VerifyEx( DWORD device_port, ULONGLONG device_offset, ULONGLONG sectors_count , DWORD param )
{
	if ( disk_master_ )
		return (disk_master_->TestEx(device_port, device_offset, sectors_count, 0) ) ? true : false;
	return false;
}
bool DiskMasterDevice::Erase( DWORD device_port , DWORD erase_param )
{
	if ( disk_master_ )
		return (disk_master_->Erase( device_port, erase_param ) ) ? true : false;
	return false;
}
bool DiskMasterDevice::EraseEx( DWORD device_port, ULONGLONG device_offset, ULONGLONG sectors_count, DWORD erase_param , DWORD param )
{
	if ( disk_master_ )
		return (disk_master_->EraseEx(device_port, device_offset, sectors_count, erase_param) ) ? true : false;
	return false;
}

void DiskMasterDevice::Break()
{
	if (disk_master_)
		disk_master_->Break();
}
DM::DCNotifier * DiskMasterDevice::getNotifier() const
{
	return disk_master_;
}
DiskDevicePtr DiskMasterDevice::getDiskDevice( const DM::PORT * port)
{
	QReadLocker lock ( &lock_ );
	if ( port )
	{
		auto findIter = std::find_if( source_list_.begin(), source_list_.end(), std::bind2nd( compareDiskToPort(), port) );
		if (findIter != source_list_.end())
			return *findIter;
		findIter = std::find_if( target_list_.begin(), target_list_.end(), std::bind2nd( compareDiskToPort(), port) );
		if ( findIter != target_list_.end())
			return *findIter;
	}

	return DiskDevicePtr(nullptr);
}
const DM::PORT * DiskMasterDevice::getPortByNumber( const DWORD portNumber)
{
	QReadLocker lock ( &lock_ );
	auto findIter = std::find_if( source_list_.begin(), source_list_.end(), std::bind2nd( compareDiskToPortNumber() , portNumber ) );
	if ( findIter != source_list_.end() )
		return (*findIter)->getPort();

	findIter = std::find_if( target_list_.begin(), target_list_.end(), std::bind2nd( compareDiskToPortNumber() , portNumber ) );
	if ( findIter != target_list_.end() )
		return (*findIter)->getPort();

	return nullptr;
}

int DiskMasterDevice::getSourceIndex( const DM::PORT * port ) 
{
	QReadLocker lock ( &lock_ );
	auto findIter = std::find_if( source_list_.begin(), source_list_.end(), std::bind2nd( compareDiskToPort(), port) );
	if ( findIter != source_list_.end() )
		return std::distance(source_list_.begin() , findIter);
	return -1;
}

int DiskMasterDevice::getTargetIndex( const DM::PORT * port ) 
{
	QReadLocker lock ( &lock_ );
	auto findIter = std::find_if( target_list_.begin(), target_list_.end(), std::bind2nd( compareDiskToPort(), port) );
	if ( findIter != target_list_.end() )
		return std::distance(target_list_.begin() , findIter);
	return -1;
}

int DiskMasterDevice::getDeviceIndex( const DM::PORT * port )
{
	int nIndex = getSourceIndex( port );
	if ( nIndex == -1 )
	{
		nIndex = getTargetIndex( port );
		if ( nIndex != -1 )
			nIndex += this->source_count();
	}
	return nIndex;
}

//BOOL DiskMasterDevice::ReadBlock( DWORD port, ULONGLONG &offset, BYTE *buff, DWORD block_size )
//{
//	QWriteLocker locker( & lock_ );
//	return disk_master_->ReadBlock(port , offset , buff , block_size) ;
//}

//bool DiskMasterDevice::WriteBlock( DWORD port, ULONGLONG &offset, BYTE *buff, DWORD block_size )
//{
//	QWriteLocker locker( & lock_ );
//	if ( DM::DiskMaster * pDiskMaster = dynamic_cast< DM::DiskMaster * > ( disk_master_) )
//		return pDiskMaster->WriteBlock(port , offset , buff , block_size) ;
//	return false;
//}

DiskMasterPtr2 toDiskMaster(const AbstractDevicePtr & abstract_device)
{
	return std::tr1::dynamic_pointer_cast<DiskMasterDevice>(abstract_device);
}

/************************************************************************/
/*							  DeviceHolder                              */
/************************************************************************/
DeviceHolder::DeviceHolder(QObject * parent)
	: QThread(parent)
{
	DM::GetDiskMasterManager()->Attach(this);
}
DeviceHolder::~DeviceHolder()
{
	this->exit();
	DM::GetDiskMasterManager()->Detach(this);
	qDebug("Destructor [\'DeviceHolder - Thread that send and receive signals\']");
}
void DeviceHolder::run()
{
	this->exec();
}
void DeviceHolder::Update(ManagerNotifier *manager, void *device, DWORD event_code)
{
	DiskController * disk_master = static_cast<DiskController*> (device);
	if (disk_master)
		switch (event_code)
	{
		case DM::kPlugged:
			//AddDiskMaster(disk_master);
			qDebug("sending [add] signal");
			emit AddDevice(disk_master);
			qDebug("end send");

			break;
		case DM::kUnplugged:
			//RemoveDiskMasterItem( disk_master );
			qDebug("sending [remove] signal");
			emit RemoveDevice(disk_master);
			break;
		default:
			qDebug("never this text...(default switch)");
	}
}
void DeviceHolder::some_funk()
{

}
