#ifndef MLV_RAW_H
#define MLV_RAW_H

#include "constants.h"

const uint32_t mlv_keyword_size = 4;

struct mlv_block_t
{
	uint8_t block_type[mlv_keyword_size];
	uint32_t block_size;
};

inline bool isMlvBlock(const mlv_block_t * pMlvBlock)
{
	for (auto iKeyword = 0; iKeyword < MLVKeywords::mlv_array_size; ++iKeyword)
		if (memcmp(pMlvBlock, MLVKeywords::mlv_array[iKeyword], mlv_keyword_size) == 0)
			return true;

	return false;
}

uint32_t read_block_drive(HANDLE & hDrive, uint64_t offset, uint8_t * data_buffer, uint32_t read_size)
{
	if (hDrive == INVALID_HANDLE_VALUE)
		return 0;

	DWORD bytesRead = 0;

	uint32_t sector_offset = offset % SECTOR_SIZE;
	uint32_t sector_to_read = (sector_offset + read_size) / SECTOR_SIZE;
	uint32_t bytes_to_read = sector_to_read * SECTOR_SIZE;

	uint8_t * sector_buffer = new uint8_t[bytes_to_read];

	if (::ReadFile(hDrive, sector_buffer, bytes_to_read, &bytesRead, NULL))
		if (bytesRead > 0)	
			memcpy(data_buffer, sector_buffer + sector_offset, bytesRead);

	delete[] sector_buffer;

	return bytesRead;

}


#endif