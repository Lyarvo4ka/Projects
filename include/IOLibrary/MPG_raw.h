#pragma once


#include "AbstractRaw.h"

namespace IO
{
	const uint8_t mpeg_specify_data[] = { 0x00 , 0x00 , 0x01 , 0xBA };
	const uint32_t mpeg_specify_data_size = SIZEOF_ARRAY(mpeg_specify_data);


	class RawMPEG
		: public DefaultRaw
	{
		static const uint32_t mpeg_data_size = 2048;
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
				bytes_read = ReadData(data_buffer->data(), data_buffer->size());
				if (bytes_read == 0 )
					break;


				for (iBlock = 0; iBlock < data_buffer->size(); iBlock += mpeg_data_size)
				{
					if (memcmp(data_buffer->data() + iBlock, mpeg_specify_data, mpeg_specify_data_size) != 0)
					{
						bEnd = true;
						break;
					}
				}

				appendToFile(target_file, offset, iBlock);

				if ( bEnd )
					break;
				
				offset += bytes_read;
			}

			return 0;
		}
		bool Specify(const uint64_t start_offset) override
		{
			const uint32_t specify_count = 262144;
			const uint32_t specify_bytes = mpeg_data_size * specify_count;

			auto data_array = makeDataArray(specify_bytes);

			if (ReadData(data_array->data(), data_array->size()) == 0)
				return false;

			for (auto iBlock = 0; iBlock < data_array->size(); iBlock += 2048)
			{
				if (memcmp(data_array->data() + iBlock, mpeg_specify_data, mpeg_specify_data_size) != 0)
					return false;
			}

			return true;
		}


	};


};