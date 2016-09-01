#pragma once
#include "constants.h"
#include "IODevice.h"
namespace IO
{
	/*
	This function compare each sector with marker signature "bad sector" and if found it then set file size
	*/
	inline void changeSizeIfFindMarker(const path_string & file_name)
	{
		File the_file(file_name);
		if (!the_file.Open(OpenMode::OpenRead))
		{
			wprintf_s(L"Error open file.\n");
			return;
		}
		wprintf_s(L"File %s has been opened.\n", file_name.c_str());

		uint32_t bytes_read = 0;
		uint32_t marker_pos = 0;
		uint64_t offset = 0;
		Buffer buffer(default_block_size);

		while (offset < the_file.Size())
		{
			bytes_read = the_file.ReadData(buffer.data, buffer.data_size);
			if (bytes_read == 0)
			{
				wprintf_s(L"Error read file.\n");
				return;

			}

			if (bytes_read <= Signatures::bad_sector_marker_size)
				break;

			for (uint32_t iSector = 0; iSector < bytes_read; iSector += default_sector_size)
			{
				if ((bytes_read - iSector) < Signatures::bad_sector_marker_size)
					break;

				if (memcmp(buffer.data + iSector, Signatures::bad_sector_marker, Signatures::bad_sector_marker_size) == 0)
				{
					uint64_t new_file_size = offset;
					new_file_size += iSector;
					the_file.setSize(new_file_size);
					wprintf_s(L"File size was modified.\n");

					return;
				}
			}
			offset += bytes_read;

		}
		wprintf_s(L"Not found bad sector marker.\n");
	}
}