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
		uint64_t SaveRawFile(File & target_file, const uint64_t start_offset) override
		{
			//auto write_file = std::make_shared<File>(target_name);
			//if (!write_file->Open(OpenMode::Create))
			//	return write_file;

			//uint32_t bytes_read = 0;
			//Buffer buffer(block_size_);

			//uint64_t offset = header_offset;

			//bool bCountinue = true;
			//while (offset < device_->Size())
			//{
			//	device_->setPosition(offset);
			//	bytes_read = device_->ReadData(buffer.data, block_size_);
			//	if (bytes_read == 0)
			//		break;

			//	bCountinue = true;
			//	uint32_t iFrame = 0;
			//	for (iFrame = 0; iFrame < bytes_read; iFrame += FRAME_SIZE)
			//	{
			//		if (buffer.data[iFrame + marker_0x47_offset] != marker_0x47)
			//		{
			//			wprintf(L"Found in mts incorrect marker.(It's not 0x47).Start find new mts header.\n");
			//			bCountinue = false;
			//			break;
			//		}
			//	}
			//	AppendFile(write_file, buffer.data, iFrame);

			//	if (!bCountinue)
			//	{
			//		uint64_t new_offset = offset;
			//		new_offset += alingToSector(iFrame, sector_size_);
			//		return new_offset;
			//	}


			//	offset += bytes_read;
			//}

			return start_offset;
		}
		bool Specify(const uint64_t header_offset) override
		{
			// Read 1 Mb and check marker 0x47
			return false;
		}
		bool isMTSHeader(const uint8_t * data_sector)
		{
			return (memcmp(data_sector + Signatures::mts_header_offset, Signatures::mts_header, Signatures::mts_header_size) == 0);
		}
		bool isMTSFooter(const uint8_t * data_sector)
		{
			return (memcmp(data_sector + Signatures::mts_header_offset, Signatures::mts_footer, Signatures::mts_footer_size) == 0);
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