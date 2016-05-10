#ifndef MTS_RAW_H
#define MTS_RAW_H

#include "IODevice.h"

#include "constants.h"



namespace IO
{
	const uint8_t markder_0x47 = 0x47;

	class RawMTS
	{
	private:
		uint32_t block_size_;
		uint32_t sector_size_;
		IODevice* device_;
	public:
		RawMTS( IODevice * device)
			: device_(device)
			, block_size_ ( 0 )
			, sector_size_(default_sector_size)
		{}
		~RawMTS()
		{
			if (device_)
			{
				delete device_;
				device_ = nullptr;
			}
		}

		void execute()
		{
			if (!device_->Open(OpenMode::OpenRead))
			{
				wprintf(L"Error to open.\n");	// ????????
				return;
			}


		}
		bool isMTSHeader(const uint8_t * data_sector)
		{
			return (memcmp(data_sector + Signatures::mts_header_offset, data_sector + Signatures::mts_header_offset, Signatures::mts_header_size) == 0);
		}
		bool findMTSOffset(uint64_t offset, uint64_t & header_offset)
		{
			uint32_t bytes_read = 0;
			Buffer buffer(block_size_);

			while (true)
			{
				device_->setPosition(offset);
				bytes_read = device_->ReadData(buffer.data, block_size_);
				if (bytes_read == 0)
				{
					printf("Error read drive\r\n");
					break;
				}

				for (int iSector = 0; iSector < bytes_read; iSector += sector_size_)
				{
					uint8_t * pSector = (uint8_t *)&buffer.data[iSector];
					if (isMTSHeader(pSector))
					{
						header_offset = offset + iSector;
						return true;
					}
				}
				offset += bytes_read;
			}
			return false;


		}
		uint64_t SaveToFile(const uint64_t header_offset, const path_string & target_name)
		{

		}
	};
}

#endif