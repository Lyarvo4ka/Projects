#include "utility.h"
#include "zlib.h"

inline int IO::AcronisDecompress::decode_block(const uint64_t start_offset, const uint64_t end_offset, DataArray & dst_data_array)
{
	auto read_block_size = end_offset - start_offset;
	DataArray src_data_array(read_block_size);
	file_.setPosition(start_offset);
	file_.ReadData(src_data_array.data(), src_data_array.size());


	uLongf dst_size = dst_data_array.size();
	auto ires = uncompress(dst_data_array.data(), &dst_size, src_data_array.data(), src_data_array.size());
	return ires;
}
