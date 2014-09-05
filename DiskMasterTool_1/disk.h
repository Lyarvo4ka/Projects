#ifndef DISK_H
#define DISK_H

#include "windows.h"

#pragma pack(1)

typedef struct _IDENTIFY_DISK_IDE
{													// Word(dec)
	USHORT		General;							// 000
    USHORT		CylindersCHS;						// 001
    USHORT		SpecificConfig;						// 002
    USHORT		HeadsCHS;							// 003
    USHORT		Retired1[2];						// 004-005
    USHORT		SectorsCHS;							// 006
    USHORT		ReservedCFA1[2];					// 007-008
    USHORT		Retired2;							// 009
    UCHAR		Serial[20];							// 010-019
    USHORT		Retired3[2];						// 020-021
    USHORT		NumberBytesLong;					// 022
    UCHAR		FirmWare[8];						// 023-026
    UCHAR		Model[40];							// 027-046
    USHORT		MultipleSectors;					// 047
    USHORT		Reserved1;							// 048
    USHORT		Capabilities;						// 049
    USHORT		Capabilities1;						// 050
    USHORT		SettingsTimePIO;// Obsolete			// 051
    USHORT		SettingsTimeDMA;// Obsolete			// 052
    USHORT		ValidOptions;						// 053
    USHORT		CylindersCurrent;// Obsolete		// 054
    USHORT		HeadsCurrent;// Obsolete			// 055
    USHORT		SectorsCurrent;// Obsolete			// 056
    ULONG		CapacityCHS;// Obsolete				// 057-058
    USHORT		MultipleSectorsSet;					// 059
    ULONG		TotalNumberUserAddresableSector;	// 060-061
    USHORT		ModeDMA;// Obsolete					// 062
    USHORT		ModeMultiwordDMA;					// 063
    USHORT		SupportedModePIO;					// 064
    USHORT		MinCycleTimeMultiwordDMA;			// 065
    USHORT		VendorCycleTimeMultiwordDMA;		// 066
    USHORT		MinCycleTimePIOwithoutIORDY;		// 067
    USHORT		MinCycleTimePIOwithIORDY;			// 068
    USHORT		Reserved2[2];						// 069-070
    USHORT		ReservedIdentPackedDevice[4];		// 071-074
    USHORT		QueueDepth;							// 075
    USHORT		Reserved3[4];						// 076-079
    USHORT		MajorVersionNumber;					// 080
    USHORT		MinorVersionNumber;					// 081
    USHORT		CommandSetSupported;				// 082
	USHORT		CommandSetsSupported;				// 083
    USHORT		CommandSetSupportedExt;				// 084
    USHORT		CommandSetEnabled;					// 085
    USHORT		CommandSetsEnabled;					// 086
    USHORT		CommandSetDefault;					// 087
    USHORT		ModeUltraDMA;						// 088
    USHORT		TimeSecuriteErase;					// 089
    USHORT		TimeEnhancedSecuriteErase;			// 090
    USHORT		CurrentAdvancedPowerManagement;		// 091
    USHORT		MasterPasswordRevisionCode;			// 092
    USHORT		HardWareResetResult;				// 093
    USHORT		AcousticManagement;					// 094
    USHORT		StreamMinimumRequestSize;			// 095
    USHORT		StreamTransferTime;					// 096
    USHORT		StreamAccessLatency;				// 097
    ULONG		StreamingPerformanceGranularity;	// 098-099
    ULONGLONG	MaximumUserLBA48;					// 100-103
    USHORT		Reserved4[23];						// 104-126
    USHORT		RemovableMediaStatusNotification;	// 127
    USHORT		SecurityStatus;						// 128
    USHORT		VendorSpecific[31];					// 129-159
    USHORT		PowerMode1CFA;						// 160
    USHORT		ReservedCFA2[15];					// 161-175
    USHORT		CurrentMediaSerialNumber[30];		// 176-205
    USHORT		Reserved5[49];						// 206-254
    USHORT		IntegrityWord;						// 255  	
} IDENTIFY_IDE, *PIDENTIFY_IDE;

typedef struct _CUSTOM_IDENTIFY
{
	UCHAR Serial[20];
	UCHAR Model[16];
	UCHAR LBA48Enabled;
	UCHAR LBASupport;
	UCHAR UDMASupport;
	UCHAR HPASupport;
	UCHAR PasswSupport;
	UCHAR Size[8+20];
	UCHAR NativeSize[20];
	UCHAR MultipleSize;

} CUSTOM_IDENTIFY,*PCUSTOM_IDENTIFY;

#define DISK_SUPPORTED_DMA	 0x0001
#define DISK_SUPPORTED_LBA	 0x0002
#define DISK_SUPPORTED_LBA48 0x0004

#define CUSTOM_INFO_SIZE 150

class Disk
{

public:
	Disk();
	~Disk();
	
	IDENTIFY_IDE IdentifyInfo;
	CUSTOM_IDENTIFY identify;

	bool isEnableLBA48;
	bool isEnableLBA;
	bool isEnableDMA;

	unsigned char UDMAModeSup;
	unsigned char UDMAModeSel;	

	unsigned char sizeMultiple;
	unsigned long long size;

	bool ParseIdentify(void);
	void CheckUdmaMode(void);


};

#endif