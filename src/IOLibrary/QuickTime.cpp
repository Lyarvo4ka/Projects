#include "QuickTime.h"

void IOLIBRARY_EXPORT IO::to_big_endian32(uint32_t & val)
{
	val = ntohl(val);
}
