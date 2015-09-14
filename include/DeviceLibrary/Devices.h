#pragma once
#pragma warning (disable : 4251)

const int major_version  = 1;
const int minor_version  = 1;
const int patch_version = 0;

#include "Imports.h"

#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <WinIoCtl.h>  
//#include "ntddk.h"
//#include "ntddstor.h"
#pragma comment(lib, "setupapi.lib")

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::wstring;

#include <memory>

#define SECTOR_SIZE 512
#define  IDE_ATA_IDENTIFY    0xEC  //  Returns ID sector for ATA.

static const string csBytes = "bytes";
static const string csKB = "KB";
static const string csMB = "MB";
static const string csGB = "GB";
static const string csTB = "TB";

static const string csATA = "ATA";
static const string csUSB = "USB";
static const string csWriteProtector = "Write Protector";
static const string csBadDriveAdapter = "BadDriveAdapter";
#define WRITE_PROTECTOR 0x20
#define BADDRIVEADAPTER 0x21

enum enSizeData {BytesSize = 0, KBytesSize = 1, MBytesSize = 2, GBytesSize = 3, TBytesSize = 4};



#pragma pack (1)
// ATA8 specification
typedef struct _IDENTIFY_DISK_ATA					// Word(dec)
{
	USHORT		GeneralConfiguration;				// 000
	USHORT		CylindersCHS;// Obsolete			// 001
	USHORT		SpecificConfiguration;				// 002
	USHORT		HeadsCHS;// Obsolete				// 003
	USHORT		Retired1[2];						// 004-005
	USHORT		SectorsCHS;// Obsolete				// 006
	USHORT		ReservedCFA1[2];					// 007-008
	USHORT		Retired2;							// 009
	UCHAR		SerialNumber[20];					// 010-019
	USHORT		Retired3[2];						// 020-021
	USHORT		NumberBytesLong;// Obsolete			// 022
	UCHAR		FirmwareRevision[8];				// 023-026
	UCHAR		ModelNumber[40];					// 027-046
	USHORT		MaxNumSectorsForMultiple;			// 047
	USHORT		TrustedComputingSupported;			// 048
	ULONG		Capabilities;						// 049-050
	USHORT		SettingsTimePIO;// Obsolete			// 051
	USHORT		SettingsTimeDMA;// Obsolete			// 052
	USHORT		SupportedModes;						// 053
	USHORT		CylindersCurrent;// Obsolete		// 054
	USHORT		HeadsCurrent;// Obsolete			// 055
	USHORT		SectorsCurrent;// Obsolete			// 056
	ULONG		CapacityCHS;// Obsolete				// 057-058
	USHORT		NumSectorsForMultiple;				// 059
	ULONG		TotalNumberLBA28;					// 060-061
	USHORT		ModeDMA;// Obsolete					// 062
	USHORT		ModeMultiwordDMA;					// 063
	USHORT		ModePIO;							// 064
	USHORT		MinCycleTimeMultiwordDMA;			// 065
	USHORT		VendorCycleTimeMultiwordDMA;		// 066
	USHORT		MinCycleTimePIOwithoutIORDY;		// 067
	USHORT		MinCycleTimePIOwithIORDY;			// 068
	USHORT		Reserved1[2];						// 069-070
	USHORT		ReservedIdentifyPacketDevice[4];	// 071-074
	USHORT		QueueDepth;							// 075
	USHORT		CapabilitiesSATA;					// 076
	USHORT		ReservedSATA;						// 077
	USHORT		FeaturesSupportedSATA;				// 078
	USHORT		FeaturesEnabledSATA;				// 079
	USHORT		MajorVersionNumber;					// 080
	USHORT		MinorVersionNumber;					// 081
	USHORT		FeatureSetSupported1;				// 082
	USHORT		FeatureSetSupported2;				// 083
	USHORT		FeatureSetSupported3;				// 084
	USHORT		FeatureSetSupportedOrEnabled1;		// 085
	USHORT		FeatureSetSupportedOrEnabled2;		// 086
	USHORT		FeatureSetSupportedOrEnabled3;		// 087
	USHORT		ModeUltraDMA;						// 088
	USHORT		TimeSecuriteEraseNormal;			// 089
	USHORT		TimeSecuriteEraseEnhanced;			// 090
	USHORT		CurrentAdvancedPowerManagementLevel;// 091
	USHORT		MasterPasswordIdentifier;			// 092
	USHORT		HardwareResetResults;				// 093
	USHORT		FeatureSetAAM;						// 094
	USHORT		StreamMinimumRequestSize;			// 095
	USHORT		StreamTransferTimeDMA;				// 096
	USHORT		StreamAccessLatency;				// 097
	ULONG		StreamingPerformanceGranularity;	// 098-099
	ULONGLONG	TotalNumberLBA48;					// 100-103
	USHORT		StreamTransferTimePIO;				// 104
	USHORT		Reserved2;							// 105
	USHORT		PhysicalAndLogicalSectorSize;		// 106
	USHORT		InterSeekDelay;						// 107
	USHORT		WorldWideName[4];					// 108-111
	USHORT		ReservedWorldWideName[4];			// 112-115
	USHORT		ReservedTLC;						// 116
	ULONG		LogicalSectorSize;					// 117-118
	USHORT		FeatureSetSupported4;				// 119
	USHORT		FeatureSetSupportedOrEnabled4;		// 120
	USHORT		ReservedSupportedAndEnabledExp[6];	// 121-126
	USHORT		RemovableMediaSupported;// Obsolete	// 127
	USHORT		SecurityStatus;						// 128
	USHORT		VendorSpecific[31];					// 129-159
	USHORT		PowerModeCFA;						// 160
	USHORT		ReservedCFA2[7];					// 161-167
	USHORT		DeviceNominalFormFactor;			// 168
	USHORT		Reserved3[7];						// 169-175
	UCHAR		MediaSerialNumber[40];				// 176-195
	UCHAR		MediaManufacturer[20];				// 196-205
	USHORT		CommandTransportSCT;				// 206
	USHORT		ReservedCE_ATA1[2];					// 207-208
	USHORT		AlignmentLogicalToPhysical;			// 209
	ULONG		WriteReadVerifySectorCountMode3;	// 210-211
	ULONG		WriteReadVerifySectorCountMode2;	// 212-213
	USHORT		NonVolatileCacheCapabilities;		// 214
	ULONG		NonVolatileCacheSize;				// 215-216
	USHORT		NominalMediaRotationRate;			// 217
	USHORT		Reserved4;							// 218
	USHORT		NonVolatileCacheOptions;			// 219
	USHORT		WriteReadVerifyCurrentMode;			// 220
	USHORT		Reserved5;							// 221
	USHORT		TransportMajorVersion;				// 222
	USHORT		TransportMinorVersion;				// 223
	USHORT		ReservedCE_ATA2[10];				// 224-233
	USHORT		MinNumberSectorsDownloadMicrocode;	// 234
	USHORT		MaxNumberSectorsDownloadMicrocode;	// 235
	USHORT		Reserved6[19];						// 236-254
	USHORT		IntegrityWord;						// 255
} IDENTIFY_DISK_ATA, *PIDENTIFY_DISK_ATA;
#pragma pack ()


#pragma pack (2)
typedef struct _MEDIA_SERIAL_NUMBER_DATA {
	ULONG SerialNumberLength;
	ULONG Result;
	ULONG Reserved[2];
	UCHAR SerialNumberData[1];
} MEDIA_SERIAL_NUMBER_DATA, *PMEDIA_SERIAL_NUMBER_DATA;
#pragma pack ()

//#define IOCTL_STORAGE_GET_MEDIA_SERIAL_NUMBER CTL_CODE(IOCTL_STORAGE_BASE, 0x0304, METHOD_BUFFERED, FILE_ANY_ACCESS)
//const DWORD IO_GET_MEDIA_SERIAL_NUMBER = ( (FILE_DEVICE_MASS_STORAGE << 16) | (FILE_ANY_ACCESS << 14) | (0x0304 << 2) | METHOD_BUFFERED);


//////////////////////////////////////////
/*			Device Interface			*/
//////////////////////////////////////////

class DllExport IDevice
{
public:
	// Interface Methods
	//virtual ULONG AddRef() = 0;
	//virtual HRESULT QueryInterface(REFIID riid, void **ppvObject) = 0;
	//virtual ULONG Release() = 0;
	// Constructor
	IDevice();
	// Destructor
	virtual ~IDevice(){};
	// Methods SET
	void SetPath(wchar_t *);
	void SetName(unsigned char *);
	void SetSerialNumber(unsigned char *);
	void SetNumber(DWORD _dwNuber);
	void SetBytesPerSector(DWORD _dwBPS);
	void SetSize(LONGLONG _lSize);
	void SetSectorCount(LONGLONG _lSectorCount);
	void SetMaxTransferSize(DWORD _dwMaxTransferSize);
	void SetBusType(BYTE _BusType);
	// Methods GET
	LONGLONG GetSize() const;
	double GetCapacity() const;
	const char * GetSizeData() const;
	const char * GetBusTypeStr() const;
	BYTE GetBusType() const;	
	virtual wstring GetPath() const = 0;
	virtual const char * GetName() const = 0;
	virtual const char * GetSerialNumber() const = 0;
	virtual DWORD GetNumber() const = 0;
	virtual DWORD GetBytesPerSector() const = 0;
	virtual LONGLONG GetSectorCount() const = 0;
	virtual DWORD GetMaxTransferSize() const = 0;
	bool isSystemDisk() const;
	void SetSystemDisk(bool _bSystem = false);
	// Open Disk Device to Read.
	// First argument its reference to HANDLE, second open to synchronous or asynchronous 
	virtual BOOL OpenRead(HANDLE &_hDeviceHandle, BOOL _bAsynchronous = FALSE) = 0;
	virtual BOOL OpenWrite(HANDLE &_hDeviceHandle, BOOL _bAsynchronous = FALSE) = 0;
protected:
	wstring m_sDevicePath;
	string m_sDeviceName;
	string m_sSerialNumber;
	string m_sSizeData;
	DWORD m_dwDeviceNumber;
	DWORD m_dwBytesPerSector;
	double m_dCapacity;
	LONGLONG m_lSecorCount;
	LONGLONG m_lSize;
	DWORD m_dwMaxTransferSize;
	BYTE m_BusType;
private:
	void SetSizeData(DWORD _dwDataCount);
	bool m_bSystem;
};

//////////////////////////////////////////
/*			CDiskDevice					*/
//////////////////////////////////////////
class DllExport CDiskDevice : public IDevice
{
public:
	CDiskDevice();
	~CDiskDevice();
	// Methods GET
	virtual wstring GetPath() const ;
	virtual const char * GetName() const ;
	virtual const char * GetSerialNumber() const ;
	virtual DWORD GetNumber() const ;
	virtual DWORD GetBytesPerSector() const ;
	virtual LONGLONG GetSectorCount() const ;
	virtual DWORD GetMaxTransferSize() const ;

	virtual BOOL OpenRead(HANDLE &_hDeviceHandle, BOOL _bSynchronous = FALSE);
	virtual BOOL OpenWrite(HANDLE &_hDeviceHandle, BOOL _bSynchronous = FALSE);
};
//////////////////////////////////////////
/*			CFileDevice					*/
//////////////////////////////////////////
class DllExport CFileDevice : public IDevice
{
public:
	CFileDevice();
	~CFileDevice();
	// Methods GET
	virtual wstring GetPath() const ;
	virtual const char * GetName() const ;
	virtual const char * GetSerialNumber() const ;
	virtual DWORD GetNumber() const ;
	virtual DWORD GetBytesPerSector() const ;
	virtual LONGLONG GetSectorCount() const ;
	virtual DWORD GetMaxTransferSize() const ;

	virtual BOOL OpenRead(HANDLE &_hDeviceHandle, BOOL _bSynchronous = FALSE);
	virtual BOOL OpenWrite(HANDLE &_hDeviceHandle, BOOL _bSynchronous = FALSE);
};



//////////////////////////////////////////
/*			CDiviceList					*/
//////////////////////////////////////////
//typedef shared_ptr<IDevice> DevicePtr;
typedef std::shared_ptr<IDevice> DevicePtr;

class DllExport CDiviceList
{
public:	
	CDiviceList();
	virtual ~CDiviceList();
	void AddDevice(IDevice *);
	void AddDevice(DevicePtr);
	void RemoveDevice(size_t _iIndex);
	void RemoveAll();
	size_t GetCount() const;
	DevicePtr GetDevice(size_t _iIndex) const;
	DevicePtr FindDevice(DWORD _iDeviceNumber);
	DevicePtr operator[] (size_t _Index);
	bool operator()(DevicePtr pDevice1, DevicePtr pDevice2);
	void SORT();
private:
	/*bool operator()( const CDiviceList & _rDeviceList);*/
	vector<DevicePtr> m_SmartDeviceList;
};

//////////////////////////////////////////
/*			CPhysicalDevice				*/
//////////////////////////////////////////
class DllExport CPhysicalDevice
{
public:
	CPhysicalDevice();
	~CPhysicalDevice();
	DWORD GetDevicesCount();
	BOOL GetDevices(CDiviceList & _deviceList);
	BOOL GetDevice(IDevice *_pDevice, DWORD _iMemberIndex);
	BOOL GetSerialFromSmart(IDevice *_pDevice);
	BOOL GetUsbSerial(IDevice * pDevice);
	BOOL CloseDevInfo(HDEVINFO &_hDevInfo);
private:
	BOOL GetHDEVINFO(HDEVINFO &_hDevInfo);
	BOOL GetNextDevice(DWORD _DevIndex);
	BOOL GetDevicePath(IDevice *_pDevice);
	BOOL GetDeviceName(IDevice *_pDevice);
	BOOL GetMaxTransferSize(IDevice *_pDevice);
	BOOL GetDiskGeometry(IDevice *_pDevice);
	BOOL GetSerialNumber(IDevice *_pDevice);
	BOOL GetSystemDevice(CDiviceList & _deviceList);
	void ExchangeBytes(BYTE * _Data, size_t _Size);

	HDEVINFO m_hDevInfo;
	SP_DEVICE_INTERFACE_DATA m_spDeviceInterfaceData;
	SP_DEVINFO_DATA m_spDevInfoData;
};