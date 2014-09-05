#pragma once
//#include "Abstract.h"

#include "dtm\DiskMaster.h"

using namespace DM;
#include <vector>
#include <memory>
using std::unique_ptr;

# include <time.h>

class DiskMock
	: public Disk

{
	static const DWORD BPS = 512;
public:
	DiskMock( PORT * port , ULONGLONG sectors)
		: bOpened_( FALSE )
		, sectors_( sectors )
		, native_sectors_( sectors )
		, port_( port )
	{

	}
	~DiskMock()
	{
		//if ( port_)
		//{
		//	delete port_;
		//	port_ = nullptr;
		//}
	}
	BOOL Open() override
	{
		bOpened_ = TRUE;
		return bOpened_;
	}

	BOOL Close() 
	{
		bOpened_ = FALSE;
		return TRUE;
	}

	DWORD ReadBlock(ULONGLONG block_offset, BYTE *buff, DWORD block_count) override
	{
		return 0;
	}

	DWORD WriteBlock(ULONGLONG block_offset,BYTE *buff, DWORD block_count) override
	{
		return 0;
	}

	ULONGLONG Size() override
	{
		return sectors_;
	}

	DWORD BlockSize() 
	{
		return BPS;
	}
	const PORT *Port(void) override
	{
		return port_;
	}

	const char *Model(void) override
	{
		return "DiskMock";
	}

	const char *SerialNumber(void) override
	{
		return "SERIAL MOCK";
	}

	ULONGLONG NativeSize(void)
	{
		return native_sectors_;
	}
	BOOL SetSize(ULONGLONG &new_size) override
	{
		native_sectors_ = new_size;
	}

private:
	BOOL bOpened_;
	ULONGLONG sectors_;
	ULONGLONG native_sectors_;
	PORT * port_;
};

static const char * usb1_name = "USB1";	// 1
static const char * usb2_name = "USB2";	// 2
static const char * sata1_name = "SATA1";	// 3
static const char * UnknownPort_name = "UNKNOWN PORT";	// 3


static PORT * CreatePort( DWORD bus_type , DWORD port_number )
{
	PORT * port = new PORT;
	ZeroMemory( port , sizeof(PORT) );
	port->number = port_number;
	port->bus_type = bus_type;

	switch( port_number )
	{
	case kUsb1:
		strcpy_s(  port->name , PORT_NAME_MAX_LENGTH , usb1_name);
		port->features = kReadOnly;
		break;

	case kUsb2:
		strcpy_s(  port->name , PORT_NAME_MAX_LENGTH , usb2_name);
		port->features = kReadWrite;
		break;

	case kSata1:
		strcpy_s(  port->name , PORT_NAME_MAX_LENGTH , sata1_name);
		port->features = kReadWrite;
		break;
	default:
		strcpy_s(  port->name , PORT_NAME_MAX_LENGTH , UnknownPort_name);
	}

	return port;
}

const ULONGLONG usb1SectorsCount = 3000;
const ULONGLONG usb2SectorsCount = 100000;
const ULONGLONG sata1SectorsCount = 1000000;

static ULONGLONG GetSectorFromPortNumber( DWORD port_number )
{
	switch ( port_number )
	{
	case kUsb1:
		return usb1SectorsCount;
	case kUsb2:
		return usb1SectorsCount;
	case kSata1:
		return sata1SectorsCount;
	}
	return 0;
}

static DiskMock * CreatDiskMock(PORT * port, ULONGLONG sectors = 0)
{
	return new DiskMock( port , sectors );
}

enum DetectMock
{
	enAllGood,
	enSourceNot,
	enTargetNot,
	enAllNot
};

class DiskMasterMock
	: public DiskController

{
	static const DWORD Default_ID = 0xFFFFFFFF;
	static const DWORD Default_PostCount = 3;
public:
	DiskMasterMock( DWORD id )
		: id_ ( id )
		, unique_id_ ( Default_ID )
		, bOpened_ ( FALSE )
		, bBreak_ ( false )
	{

		PORT * usb1Port = CreatePort( kUsb , kUsb1);
		usb1Port->dc = this;
		ports_.push_back(usb1Port);
		disks_.push_back(nullptr);

		PORT * usb2Port = CreatePort( kUsb , kUsb2);
		usb2Port->dc = this;
		ports_.push_back(usb2Port);
		disks_.push_back(nullptr);


		PORT * sata1Port = CreatePort( kSata , kSata1 );
		sata1Port->dc = this;
		ports_.push_back(sata1Port);
		disks_.push_back(nullptr);



	}
	~DiskMasterMock(void)
	{
		auto portIter = ports_.begin();
		while ( portIter != ports_.end() )
		{
			delete *portIter;
			++portIter;
		}
		auto diskIter = disks_.begin();
		while ( diskIter != disks_.end() )
		{
			delete *diskIter;
			++diskIter;
		}
		disks_.clear();

	}

	BOOL Open() override
	{
		bOpened_ = TRUE;
		return bOpened_;
	}
	BOOL Close() override
	{
		bOpened_ = FALSE;
		return TRUE;
	}
	BOOL IsOpen() override
	{
		return bOpened_;
	}
	DWORD GetID(void) override
	{
		return id_;
	}
	DWORD GetUniqueID(void) override
	{
		return unique_id_;
	}
	const char *GetName(void) override
	{
		return "DiskMasterMock";
	}
	DWORD PortsCount(void) override
	{
		return Default_PostCount;
	}
	const PORT *Port(DWORD index) override	//???????????????
	{
		if ( index < ports_.size() )
			return ports_.at(index);
		return nullptr;
	}
	DWORD Rescan(void) override	//???????????????
	{
		return 0;
	}
	Disk *Rescan(DWORD port_number) override	//???????????????
	{
		return nullptr;
	}
	Disk *GetDisk(DWORD port_number) override	//??????????????
	{
		if ( port_number < disks_.size() )
			return disks_.at(port_number);
		return nullptr;
	}
	BOOL Copy(DWORD src_port, DWORD dst_port, DWORD param) override
	{
		return FALSE;
	}
	BOOL CopyEx(DWORD src_port, DWORD dst_port, ULONGLONG &src_offset, ULONGLONG &dst_offset, ULONGLONG &count, DWORD param) override
	{
		PORT * source_port = (PORT *)Port(src_port);
		assert( source_port != nullptr );
		auto source_disk = GetDisk(src_port);

		PORT * target_port = (PORT *)Port(dst_port);
		assert( target_port != nullptr );
		auto target_disk = GetDisk( dst_port);

		if ( count == 0)
		{
			for ( std::size_t iDisk =  0 ; iDisk < disks_.size() ; ++iDisk )
			{
				if ( auto del_disk = disks_.at( iDisk ) )
				{
					this->Notify( kDiskRemoved , del_disk );
					delete del_disk;
					disks_.at(iDisk) = nullptr;
				}
			}
			//if ( source_disk ) 
			//{
			//	this->Notify( kDiskRemoved , source_disk);
			//	delete source_disk;
			//	disks_.at(src_port) = nullptr;
			//}


			//if ( target_disk ) 
			//{
			//	this->Notify( kDiskRemoved , target_disk);
			//	delete target_disk;
			//	disks_.at(dst_port) = nullptr;
			//}


			if ( param == enAllGood || param == enTargetNot )
			{
				source_disk = CreatDiskMock( source_port , GetSectorFromPortNumber( src_port ) ) ;
				disks_.at(src_port) = source_disk;
				this->Notify(kNewDiskDetected, source_disk );
			}
			else
			{
				WORD ErrorCode = kDetectErrorUsb1;
				this->Notify(kDetectError , (void *) ErrorCode );
			}

			if ( param == enAllGood || param == enSourceNot)
			{
				target_disk = CreatDiskMock( target_port , GetSectorFromPortNumber( dst_port ) ) ;
				disks_.at(dst_port) = target_disk;
				this->Notify(kNewDiskDetected, target_disk );
			}
			else
			{
				WORD ErrorCode = (target_port->number == kUsb2) ? kDetectErrorUsb2 : kDetectErrorSata1;
				this->Notify(kDetectError , (void *) ErrorCode );
			}
			return TRUE;
		}
		else
		{
			bBreak_ = false;

			const int block = 128;

			ULONGLONG sector = 0;
			//srand( time_t( time(NULL) ) );
			int randRes = 0;
			ULONGLONG badSector = 0;

			DM_TASK_INFO taskInfo;
			ZeroMemory( &taskInfo , sizeof ( DM_TASK_INFO ) );
			ULONGLONG remainSectors = 0;
			LONGLONG sectorsToCopy = 0;
			ULONGLONG curSector = src_offset;

 			while ( sector < count )
			{
				if ( block < count )
				{
					sectorsToCopy = sector + block;
					remainSectors = block;
					if ( sectorsToCopy > count )
						remainSectors = count - sector;
				}
				else
					remainSectors = count;


				
				::Sleep(1300);
				randRes = ( rand() % remainSectors + 1 ) - remainSectors / 2 ;
				if ( randRes > 0 )
				{
					if ( randRes < remainSectors )
					{
						badSector = curSector + sector + randRes;

						this->Notify( kBadBlock , (void *) &badSector );
					}
				}
				if ( bBreak_ )
				{
					sector = badSector;
					++sector;
					taskInfo.Lba = sector;
					this->Notify( kTaskBreak , (void *) &taskInfo );
					return FALSE;
				}
				else
					sector += remainSectors;
			}
			taskInfo.Lba = curSector + sector;
			this->Notify( kTaskComplete , (void *) &taskInfo );

			return TRUE;
		}

		return FALSE;
	}
	BOOL Erase(DWORD port, DWORD param)
	{

		return FALSE;
	}
	BOOL EraseEx(DWORD port, ULONGLONG &offset, ULONGLONG &count, DWORD param)
	{

		return TestEx( port , offset , count , param );
	}
	BOOL Test(DWORD port, DWORD param)
	{


		return FALSE;
	}
	BOOL TestEx(DWORD port, ULONGLONG &offset, ULONGLONG &count, DWORD param) override
	{

		PORT * pPort = (PORT *)Port(port);
		assert( pPort != nullptr );
		auto disk = GetDisk(port);

		if ( count == 0)
		{
			for ( std::size_t iDisk =  0 ; iDisk < disks_.size() ; ++iDisk )
			{
				if ( auto del_disk = disks_.at( iDisk ) )
				{
					this->Notify( kDiskRemoved , del_disk );
					delete del_disk;
					disks_.at(iDisk) = nullptr;
				}
			}

			if ( param == enAllGood )
			{
				disk = CreatDiskMock( pPort , GetSectorFromPortNumber( port ) ) ;
				disks_.at( port ) = disk;
				this->Notify(kNewDiskDetected, disk );
			}
			else
			{
				WORD ErrorCode = kDetectErrorUsb1;
				this->Notify(kDetectError , (void *) ErrorCode );
			}
			return TRUE;
		}
		else
		{
			bBreak_ = false;

			const int block = 128;

			ULONGLONG sector = 0;
			//srand( time_t( time(NULL) ) );
			int randRes = 0;
			ULONGLONG badSector = 0;

			DM_TASK_INFO taskInfo;
			ZeroMemory( &taskInfo , sizeof ( DM_TASK_INFO ) );
			ULONGLONG remainSectors = 0;
			LONGLONG sectorsToCopy = 0;
			ULONGLONG curSector = offset;

			while ( sector < count )
			{
				if ( block < count )
				{
					sectorsToCopy = sector + block;
					remainSectors = block;
					if ( sectorsToCopy > count )
						remainSectors = count - sector;
				}
				else
					remainSectors = count;



				::Sleep(100);
				randRes = ( rand() % remainSectors + 1 ) - remainSectors / 3 ;
				if ( randRes > 0 )
				{
					if ( randRes < remainSectors )
					{
						badSector = curSector + sector + randRes;

						this->Notify( kBadBlock , (void *) &badSector );
					}
				}
				if ( bBreak_ )
				{
					sector = badSector;
					++sector;
					taskInfo.Lba = sector;
					this->Notify( kTaskBreak , (void *) &taskInfo );
					return FALSE;
				}
				else
					sector += remainSectors;
			}
			taskInfo.Lba = curSector + sector;
			this->Notify( kTaskComplete , (void *) &taskInfo );

			return TRUE;
		}

		return FALSE;
	}
	void Break(void) override
	{
		bBreak_ = true;
	}
	BOOL ReadBlock(DWORD port, ULONGLONG &offset,  BYTE *buff, DWORD block_size) override
	{
		if ( block_size == 1 )
		{
			char read_data[ SECTOR_SIZE ] ;
			QFile file( "mbr.bin" );
			if ( file.open(QIODevice::ReadOnly) )
			{
				auto read_size = file.read(read_data , SECTOR_SIZE ) ;
				file.close();

				if ( read_size == SECTOR_SIZE )
				{
					memcpy( buff , read_data , SECTOR_SIZE );
					return TRUE;
				}
			}
		}
		return FALSE;
	}
	//BOOL WriteBlock(DWORD port, ULONGLONG &offset, BYTE *buff, DWORD block_size) override
	//{
	//	return FALSE;
	//}
private:
	DWORD id_;
	DWORD unique_id_;
	BOOL bOpened_;
	bool bBreak_;
	std::vector< PORT * > ports_;
	std::vector< Disk * > disks_;
};


