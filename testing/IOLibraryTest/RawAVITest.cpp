#include <boost/test/unit_test.hpp>

#include "IOLibrary/RawRIFF.h"
#include "MocFile.h"

const uint32_t test_block_size = 10;
const uint32_t test_src_size = 25;

BOOST_AUTO_TEST_CASE(RawAVI_Specify)
{
	auto src_file_ = std::make_shared<MocFile>(test_src_size);
	IO::RawRIFF avi_raw(src_file_);
	avi_raw.setBlockSize(test_block_size);

	IO::riff_header_struct avi_struct = { 0 };
	avi_struct.size = 23;
	src_file_->setPosition(0);
	src_file_->WriteData((IO::ByteArray) &avi_struct, sizeof(IO::riff_header_struct));
	//bool bResult = avi_raw.Specify(0);
	//BOOST_CHECK_EQUAL(bResult , false);

	avi_raw.setMinFileSize(5);
	

	


}
