
#include <boost/test/unit_test.hpp>

#include "IOLibrary/MTS_raw.h"
#include "MocFile.h"

BOOST_AUTO_TEST_CASE(MTS_rawSpecifyTest)
{
	uint32_t specify_count = 3;
	uint32_t specify_size = IO::FRAME_SIZE * (specify_count + 2);
	auto moc_file = std::make_shared<MocFile>(specify_size);

	IO::RawMTS mts_raw(moc_file);
	mts_raw.setFramesCount(specify_count);
	mts_raw.setBlockSize(IO::FRAME_SIZE);

	BOOST_CHECK_EQUAL(mts_raw.Specify(0), false);
	
	auto file_data = moc_file->getData();
	for (auto iFrame = IO::FRAME_SIZE; iFrame < specify_count; iFrame += IO::FRAME_SIZE)
	{
		file_data[iFrame+4] = IO::marker_0x47;
	}
	BOOST_CHECK_EQUAL(mts_raw.Specify(IO::FRAME_SIZE), true);


}