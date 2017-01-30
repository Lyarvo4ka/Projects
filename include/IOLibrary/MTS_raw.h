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

	private:
		//DataArray::Ptr specify_buffer;
	public:
		RawMTS( IODevicePtr device)
			: DefaultRaw(device)
		{
			setBlockSize(BLOCK_SIZE);
		}
		~RawMTS()
		{
		}
		uint64_t SaveRawFile(File & target_file, const uint64_t start_offset) override
		{
			if (!target_file.isOpen())
			{
				wprintf(L"Target file wasn't opened.\n");
				return 0;
			}
			uint32_t bytes_read = 0;
			auto data_buffer = makeDataArray(getBlockSize());

			uint64_t offset = start_offset;

			uint32_t iFrame = 0;

			bool bEnd = false;

			while (offset < this->getSize())
			{
				setPosition(offset);
				bytes_read = ReadData(data_buffer->data(), data_buffer->size());
				if (bytes_read == 0)
					break;

				for (iFrame = 0; iFrame < bytes_read; iFrame += FRAME_SIZE)
				{
					if (data_buffer->data[iFrame + marker_0x47_offset] != marker_0x47)
					{
						//wprintf(L"Found in mts incorrect marker.(It's not 0x47).Start find new mts header.\n");
						bEnd = true;
						break;
					}
				}
				appendToFile(target_file, offset, iFrame);

				if (bEnd)
					break;

				offset += bytes_read;
			}

			return offset - start_offset;
		}
		bool Specify(const uint64_t header_offset) override
		{
			const uint32_t specify_count = 10;
			const uint32_t specify_size = specify_count * BLOCK_SIZE;
			auto specify_buffer = makeDataArray(specify_size);
			uint32_t bytes_read = 0;
			if (ReadData(specify_buffer->data(), specify_buffer->size()) == 0)
				return false;

			for (auto iFrame = marker_0x47_offset; iFrame < specify_buffer->size(); iFrame += FRAME_SIZE)
			{
				if (specify_buffer[iFrame] != marker_0x47)
					return false;
			}
			return true;
		}

	};
}

#endif