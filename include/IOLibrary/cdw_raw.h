#pragma once

#include "IODevice.h"

namespace IO
{
	const uint8_t cdw_header1[] = { 0x4B , 0x46 };
	const uint8_t cdw_header2[] = { 0x01 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 };
	const uint32_t cdw_header2_offset = 16;


	class cdw_raw
	{
	private:
		IODevice * device_;
	public:
		cdw_raw(IODevice * device)
			: device_(device)
		{

		}

		bool isHeader(const uint8_t * data)
		{
			if (memcmp(data, cdw_header1, SIZEOF_ARRAY(cdw_header1)) == 0)
				if (memcmp(data + cdw_header2_offset, cdw_header2, SIZEOF_ARRAY(cdw_header2)) == 0)
					return true;
			return false;
		}

		void execute(const path_string & target_folder)
		{
			if (!device_->Open(OpenMode::OpenRead))
			{
				wprintf_s(L"Error source device wasn't open\n");
				return;
			}



		}
	};
};
