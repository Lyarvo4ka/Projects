
#include <boost/test/unit_test.hpp>

#include "IOLibrary/RawMPEG.h"
#include "MocFile.h"


const uint32_t test_blocks_count = 5;
const uint32_t test_mpeg_block_size = 5;
const uint32_t test_block_size = 10;
const uint32_t expected_blocks_count = 4;

struct  F_MPEG_FileData
{
	F_MPEG_FileData()
	{

		src_file_ = std::make_shared<MocFile>((test_blocks_count+1)*test_mpeg_block_size);

	}
	void setMarker()
	{
		auto file_data = src_file_->getData();
		memset(file_data->data(), 0xAA, file_data->size());
		for (auto iBlock = test_mpeg_block_size; iBlock < test_blocks_count*test_mpeg_block_size; iBlock += test_mpeg_block_size)
			memcpy(file_data->data() + iBlock, IO::mpeg_data , IO::mpeg_data_size);
	}
	std::shared_ptr<MocFile> src_file_;
};

BOOST_FIXTURE_TEST_SUITE(TestRawMPEG, F_MPEG_FileData)

BOOST_AUTO_TEST_CASE(RawMPEG_Specify_Test)
{
	IO::RawMPEG mpeg_raw(src_file_);
	mpeg_raw.setBlockSize(test_block_size);
	mpeg_raw.setMpegBlockSize(test_mpeg_block_size);
	mpeg_raw.setBlocksForSpecify(expected_blocks_count);

	BOOST_CHECK_EQUAL(mpeg_raw.Specify(0), false);
	this->setMarker();
	BOOST_CHECK_EQUAL(mpeg_raw.Specify(test_mpeg_block_size), true);

}
BOOST_AUTO_TEST_CASE(RawMPEG_SaveRawFile_Test)
{
	this->setMarker();
	IO::RawMPEG mpeg_raw(src_file_);
	mpeg_raw.setBlockSize(test_block_size);
	mpeg_raw.setMpegBlockSize(test_mpeg_block_size);
	mpeg_raw.setBlocksForSpecify(test_blocks_count);

	auto dst_file = std::make_shared<MocFile>(0);

	auto target_size = mpeg_raw.SaveRawFile(*dst_file, 0);
	BOOST_CHECK_EQUAL(target_size, 0);

	target_size = mpeg_raw.SaveRawFile(*dst_file, test_mpeg_block_size);
	BOOST_CHECK_EQUAL(target_size, expected_blocks_count*test_mpeg_block_size);
	BOOST_CHECK_EQUAL(dst_file->Size(), expected_blocks_count*test_mpeg_block_size);


}
BOOST_AUTO_TEST_SUITE_END()
