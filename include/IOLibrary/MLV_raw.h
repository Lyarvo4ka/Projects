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


#endif