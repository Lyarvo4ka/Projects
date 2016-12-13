#ifndef DBF_H
#define DBF_H

#include <windows.h>

#include "StandartRaw.h"

#pragma pack( 1 )
struct dbf_header
{
	uint8_t valid_base;
	uint8_t yymmdd[3];
	uint32_t numRecords;
	uint16_t header_size;
	uint16_t record_size;

}; 
#pragma pack()

int dbf_header_size = sizeof(dbf_header);
namespace IO
{
	class DBFRaw
		: public StandartRaw
	{
	private:
		uint32_t counter_ = 0;
	public:
		DBFRaw(IODevicePtr device)
			: StandartRaw(device)
		{

		}
		bool isValidDate(const dbf_header & header)
		{
			uint8_t year = header.yymmdd[0];
			uint8_t month = header.yymmdd[1];
			uint8_t day = header.yymmdd[2];

			if (year >= 15 && year <= 16)

			if (month > 0 && month <= 12)
			if (day > 0 && day <= 31)
				return true;
			return false;
		}
		uint64_t SaveRawFile(const FileStruct & file_struct, const uint64_t header_offset, const path_string & target_name) override
		{
			dbf_header header = { 0 };
			setPosition(header_offset);
			auto bytes_read = ReadData((ByteArray)&header, dbf_header_size);
			if (bytes_read == 0)
				return 0;

			if (!isValidDate(header))
				return 0;
			
			static uint32_t counter = 0;
			++counter;
			counter_ = counter;

			wchar_t buff[18] = {0};
			swprintf_s(buff, 18, L"%.2d-%.2d-%.2d", header.yymmdd[0], header.yymmdd[1], header.yymmdd[2]);
			path_string date_str(buff);

			path_string filename = addBackSlash(target_name) + date_str + L"-" + toNumberExtension(counter_++, L".dbf");


			uint32_t write_size = header.header_size + header.record_size*header.numRecords + 1;
			if (write_size <= 1)
				return 0;

			File file(filename);
			if (!file.Open(OpenMode::Create))
			{
				wprintf(L"Error create file\n");
				return 0;
			}
			 
			
			return appendToFile(file, header_offset, write_size);
		}

	};
}
#endif
