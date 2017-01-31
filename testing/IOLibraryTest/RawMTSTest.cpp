
#include <boost/test/unit_test.hpp>

#include "IOLibrary/RawMTS.h"
#include "MocFile.h"


const uint32_t frames_count = 5;
const uint32_t source_size = (frames_count + 1) * IO::FRAME_SIZE;

struct  F_MTS_FileData
{
	F_MTS_FileData()
	{

		src_file_ = std::make_shared<MocFile>(source_size);

	}
	void setMarker()
	{
		auto file_data = src_file_->getData();
		memset(file_data->data(), 0xAA, source_size);
		for (auto iFrame = IO::FRAME_SIZE; iFrame < frames_count*IO::FRAME_SIZE; iFrame += IO::FRAME_SIZE)
			file_data->data()[iFrame + 4] = IO::marker_0x47;
	}
	std::shared_ptr<MocFile> src_file_;
};

BOOST_FIXTURE_TEST_SUITE(TestRawMTS , F_MTS_FileData)

BOOST_AUTO_TEST_CASE(RawMTS_Specify_Test)
{
	IO::RawMTS mts_raw(src_file_);
	uint32_t specify_count = 3;
	mts_raw.setFramesCountToSpecify(specify_count);
	mts_raw.setBlockSize(IO::FRAME_SIZE);

	BOOST_CHECK_EQUAL(mts_raw.Specify(0), false);
	this->setMarker();
	BOOST_CHECK_EQUAL(mts_raw.Specify(IO::FRAME_SIZE), true);

}
BOOST_AUTO_TEST_CASE(RawMTS_SaveRawFile_Test)
{
	this->setMarker();
	IO::RawMTS raw_mts(src_file_);
	raw_mts.setBlockSize(IO::FRAME_SIZE);
	auto dst_file = std::make_shared<MocFile>(0);

	auto target_size = raw_mts.SaveRawFile(*dst_file, 0);
	BOOST_CHECK_EQUAL(target_size,0);

	target_size = raw_mts.SaveRawFile(*dst_file, IO::FRAME_SIZE);
	BOOST_CHECK_EQUAL(target_size, (frames_count - 1)*IO::FRAME_SIZE);
	BOOST_CHECK_EQUAL(dst_file->Size(), (frames_count - 1)*IO::FRAME_SIZE);


}
BOOST_AUTO_TEST_SUITE_END()
