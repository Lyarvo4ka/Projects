#include "disk.h"

Disk::Disk()
{
	memset(&IdentifyInfo,0x00,512);
	isEnableLBA48 = false;
	isEnableLBA = false;

	UDMAModeSup=0x00;
	sizeMultiple=0x00;
}

Disk::~Disk()
{

}

bool Disk::ParseIdentify(void)
{
	if ((IdentifyInfo.Capabilities) & DISK_SUPPORTED_LBA)
	{
		isEnableLBA = TRUE;
		if ((((IdentifyInfo.CommandSetsEnabled & DISK_SUPPORTED_LBA48)!=0) | 
			 ((IdentifyInfo.CommandSetsSupported & DISK_SUPPORTED_LBA48)!=0)) & 
				(IdentifyInfo.MaximumUserLBA48!=0))
		{
			isEnableLBA48 = TRUE;
			////////////////////////////////////////////////
			//curr_hdd.PioMultipleRead=READ_MULTIPLE_EXT;
			//curr_hdd.PioSectorsRead=READ_SECTOR_EXT;
			//curr_hdd.PioMultipleWrite=WRITE_MULTIPLE_EXT;
			//curr_hdd.PioSectorsWrite=WRITE_SECTOR_EXT;
			//curr_hdd.PioVerify=READ_VERIFY_EXT;
			//curr_hdd.UdmaRead=READ_DMA_EXT;
			//curr_hdd.UdmaWrite=WRITE_DMA_EXT;
			////////////////////////////////////////////////
			//size = IdentifyInfo.MaximumUserLBA48;
			for(int i=0;i<6;i+=2)
			{
				*((unsigned char*)&size+i+1) = *((unsigned char*)&IdentifyInfo.MaximumUserLBA48+i);
				*((unsigned char*)&size+i) = *((unsigned char*)&IdentifyInfo.MaximumUserLBA48+i+1);
			}
		}
		else
		{
			//////////////////////////////////////////
			/*curr_hdd.PioMultipleRead=READ_MULTIPLE;
			curr_hdd.PioSectorsRead=READ_SECTOR;
			curr_hdd.PioMultipleWrite=WRITE_MULTIPLE;
			curr_hdd.PioSectorsWrite=WRITE_SECTOR;
			curr_hdd.PioVerify=READ_VERIFY;
			curr_hdd.UdmaRead=READ_DMA;
			curr_hdd.UdmaWrite=WRITE_DMA;*/
			//////////////////////////////////////////
			isEnableLBA48 = FALSE;
			for(int i=0;i<4;i+=2)
			{
				*((unsigned char*)&size+i+1) = *((unsigned char*)&IdentifyInfo.TotalNumberUserAddresableSector+i);
				*((unsigned char*)&size+i) = *((unsigned char*)&IdentifyInfo.TotalNumberUserAddresableSector+i+1);
			}

			//size = IdentifyInfo.TotalNumberUserAddresableSector;
		}
	}
	else //else capabilities
	{
		isEnableLBA = FALSE;	
		
		size = IdentifyInfo.CylindersCurrent *
			 IdentifyInfo.HeadsCurrent *
			 IdentifyInfo.SectorsCurrent;
		return 0;	// device doesn't support LBASupport-less devices 	
	}

	if (IdentifyInfo.Capabilities & DISK_SUPPORTED_DMA)
	{
		CheckUdmaMode();
		isEnableDMA = TRUE;
		//DecToAscii(&curr_hdd.UDMAModeSup,1);
	}
	else // not supported DMA
	{
		isEnableDMA = FALSE;
	}
	
	sizeMultiple=LOBYTE(IdentifyInfo.MultipleSectors);
	if(!sizeMultiple)
		sizeMultiple = 1;
		
	return 1;
}



void Disk::CheckUdmaMode(void)
{	
	CHAR i;


	UDMAModeSup=0;
	UDMAModeSel=0;
	
	for(i=6;i>=0;i--)
	{
		if(IdentifyInfo.ModeUltraDMA & 1<<i)
		{
			UDMAModeSup=i;
			break;
		}
	}
	
	for(i=15;i>=8;i--)
	{
		if(IdentifyInfo.ModeUltraDMA & 1<<i)
		{
			UDMAModeSel=i;
			break;
		}
	}
}