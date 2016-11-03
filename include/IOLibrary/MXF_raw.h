
#include "AbstractRaw.h"

namespace IO
{
	class MXF_rawFragment
		: public StandartRaw
	{
	public:
		MXF_rawFragment(const IODevicePtr & device)
			: StandartRaw(device)
		{

		}

		uint64_t SaveRawFile(HeaderPtr &header_ptr, const uint64_t header_offset, const path_string & target_name) override
		{
			File target_file(target_name);
			if (!target_file.Open(OpenMode::Create))
			{
				wprintf(L"Error create file\n");
			}

			const uint8_t fragment_sign[] = { 0x01 , 0x00 , 0x02 , 0x00 };
			const uint32_t fragment_sign_size = SIZEOF_ARRAY(fragment_sign);
			const uint32_t num_skip_cluster = 56;

			Buffer buffer(this->getBlockSize());

			uint32_t bytes_read = 0;
			uint32_t bytes_written = 0;
			uint64_t offset = header_offset;
			bool bFoundFooter = false;
			uint32_t iPos = 0;
			uint64_t written_size = 0;

			while (true)
			{
				this->setPosition(offset);
				bytes_read = this->ReadData(buffer.data, buffer.data_size);
				if (bytes_read == 0)
				{
					printf("Error read drive\r\n");
					break;
				}

				if (memcmp(buffer.data, fragment_sign, fragment_sign_size) != 0)
				{
					bFoundFooter = false;
					for (iPos = 0; iPos < bytes_read - Signatures::mxf_footer_size; ++iPos)
					{
						if (memcmp(buffer.data + iPos, Signatures::mxf_footer, Signatures::mxf_footer_size) == 0)
						{
							bFoundFooter = true;
							break;
						}
					}

					if (bFoundFooter)
					{
						auto write_size = iPos + default_sector_size;
						if ( write_size <= bytes_read)
							bytes_written = target_file.WriteData(buffer.data, write_size);
						break;
					}
					else
						bytes_written = target_file.WriteData(buffer.data, bytes_read);

					written_size += bytes_written;
				}
				else
				{
					// skip 57 clusters.
					offset += this->getBlockSize() * num_skip_cluster;
					continue;
				}

				offset += bytes_read;
			}
			return written_size;
		}
	};
};