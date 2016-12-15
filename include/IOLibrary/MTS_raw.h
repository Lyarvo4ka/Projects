#ifndef MTS_RAW_H
#define MTS_RAW_H


#include "AbstractRaw.h"


namespace IO
{
	const uint8_t marker_0x47 = 0x47;
	const uint32_t marker_0x47_offset = 4;

	inline uint32_t alingToSector(const uint32_t offset, const uint32_t sector_size)
	{
		uint32_t sector = offset % sector_size;
		sector *= sector_size;
		return sector;
	}


	class RawMTS
		: public DefaultRaw
	{
		static const uint32_t FRAME_SIZE = 192;
		static const uint32_t BLOCK_SIZE = 192 * 512;
	public:
		RawMTS( IODevicePtr device)
			: DefaultRaw(device)
		{}
		~RawMTS()
		{
		}
		FilePtr SaveRawFile(const FileStruct & file_struct, const uint64_t header_offset, const path_string & target_name) override
		{
			auto write_file = std::make_shared<File>(target_name);
			if (!write_file->Open(OpenMode::Create))
				return write_file;

			uint32_t bytes_read = 0;
			Buffer buffer(block_size_);

			uint64_t offset = header_offset;

			bool bCountinue = true;
			while (offset < device_->Size())
			{
				device_->setPosition(offset);
				bytes_read = device_->ReadData(buffer.data, block_size_);
				if (bytes_read == 0)
					break;

				bCountinue = true;
				uint32_t iFrame = 0;
				for (iFrame = 0; iFrame < bytes_read; iFrame += FRAME_SIZE)
				{
					if (buffer.data[iFrame + marker_0x47_offset] != marker_0x47)
					{
						wprintf(L"Found in mts incorrect marker.(It's not 0x47).Start find new mts header.\n");
						bCountinue = false;
						break;
					}
				}
				AppendFile(write_file, buffer.data, iFrame);

				if (!bCountinue)
				{
					uint64_t new_offset = offset;
					new_offset += alingToSector(iFrame, sector_size_);
					return new_offset;
				}


				offset += bytes_read;
			}

			return header_offset;


			return nullptr;
		}
		bool Specify(const uint64_t header_offset) override
		{
			return false;
		}
		void execute(const path_string & target_folder)
		{
			//if (!device_->Open(OpenMode::OpenRead))
			//{
			//	wprintf(L"Error to open.\n");	// ????????
			//	return;
			//}

			//uint64_t offset = (uint64_t)0x0;
			//uint64_t header_offset = 0;
			//uint32_t counter = 0;
			//while (true)
			//{
			//	if (!findMTSOffset(offset, header_offset))
			//	{
			//		wprintf(L"Not Found Header\n");
			//		break;
			//	}
			//	
			//	auto target_file = target_folder + std::to_wstring(counter++) + L".mts";
			//	offset = SaveToFile(header_offset, target_file);
			//	offset += sector_size_;

			//}


		}
		bool isMTSHeader(const uint8_t * data_sector)
		{
			return (memcmp(data_sector + Signatures::mts_header_offset, Signatures::mts_header, Signatures::mts_header_size) == 0);
		}
		bool isMTSFooter(const uint8_t * data_sector)
		{
			return (memcmp(data_sector + Signatures::mts_header_offset, Signatures::mts_footer, Signatures::mts_footer_size) == 0);
		}
		bool findMTSOffset(uint64_t offset, uint64_t & header_offset)
		{
			uint32_t bytes_read = 0;
			Buffer buffer(block_size_);

			while (true)
			{
				device_->setPosition(offset);
				ZeroMemory(buffer.data, buffer.data_size);
				bytes_read = device_->ReadData(buffer.data, block_size_);
				if (bytes_read == 0)
				{
					printf("Error read drive\r\n");
					break;
				}

				for (DWORD iSector = 0; iSector < bytes_read; iSector += sector_size_)
				{
					uint8_t * pSector = (uint8_t *)&buffer.data[iSector];
					if (isMTSHeader(pSector))
					{
						header_offset = offset + iSector;
						wprintf(L"Found MTS header %llu (sectors)\n", header_offset / sector_size_);
						return true;
					}
				}
				offset += bytes_read;
			}
			return false;


		}
		uint64_t SaveToFile(const uint64_t header_offset, const path_string & target_name)
		{
			return 0;
		}
		bool AppendFile(File & file_to_write, uint8_t * data, uint32_t data_size)
		{
			if (!file_to_write.isOpen())
				return false;
			file_to_write.setPosition(file_to_write.Size());
			return ( file_to_write.WriteData(data, data_size) == data_size);
		}
	};
}

#endif