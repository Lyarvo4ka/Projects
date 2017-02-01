#pragma once


#include "AbstractRaw.h"
#include "Factories.h"

namespace IO
{
	const uint8_t mpeg_data[] = { 0x00 , 0x00 , 0x01 , 0xBA };
	const uint32_t mpeg_data_size = SIZEOF_ARRAY(mpeg_data);
	const uint32_t default_mpeg_data_size = 2048;
	const uint32_t DEFAULT_MPEG_SPECIFY_COUNT = 262144;


	class RawMPEG
		: public DefaultRaw
	{
	private:
		uint32_t mpegBlockSize_ = default_mpeg_data_size;
		uint32_t blocksForSpecify_ = DEFAULT_MPEG_SPECIFY_COUNT;
	public:
		RawMPEG(IODevicePtr device)
			: DefaultRaw(device)
		{
		}
		~RawMPEG()
		{}

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
			bool bEnd = false;
			uint32_t iBlock = 0;

			while (offset < this->getSize())
			{ 
				setPosition(offset);
				bytes_read = ReadData(data_buffer->data(), data_buffer->size());
				if (bytes_read == 0 )
					break;


				for (iBlock = 0; iBlock < data_buffer->size(); iBlock += mpegBlockSize_)
				{
					if (memcmp(data_buffer->data() + iBlock, mpeg_data, mpeg_data_size) != 0)
					{
						bEnd = true;
						break;
					}
				}

				appendToFile(target_file, offset, iBlock);

				if (bEnd)
					break;

				offset += bytes_read;
			}

			return offset - start_offset;
		}
		bool Specify(const uint64_t start_offset) override
		{
			uint32_t dataSize = mpegBlockSize_ * blocksForSpecify_;

			auto data_array = makeDataArray(dataSize);

			setPosition(start_offset);
			if (ReadData(data_array->data(), data_array->size()) == 0)
				return false;

			for (uint32_t iBlock = 0; iBlock < data_array->size(); iBlock += mpegBlockSize_)
			{
				if (memcmp(data_array->data() + iBlock, mpeg_data, mpeg_data_size) != 0)
					return false;
			}

			return true;
		}
		void setMpegBlockSize(const uint32_t mpegBlockSize)
		{
			mpegBlockSize_ = mpegBlockSize;
		}
		void setBlocksForSpecify(const uint32_t blocksForSpecify)
		{
			blocksForSpecify_ = blocksForSpecify;
		}


	};

	class RawMPEGFactory
		: public RawFactory
	{
	public:
		RawAlgorithm * createRawAlgorithm(IODevicePtr device) override
		{
			return new RawMPEG(device);
		}
	};
};