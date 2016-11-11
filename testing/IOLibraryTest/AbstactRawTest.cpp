#include <boost/test/unit_test.hpp>

#include "IOLibrary/AbstractRaw.h"

BOOST_AUTO_TEST_CASE(TestCompareDataArray)
{
	const uint32_t size = 5;
	IO::DataArray data_array(new uint8_t[size], size);
	memset(data_array.data(), 0xFF , size);

	IO::ByteArray data2 = new uint8_t[512];
	memset(data2, 0xFF, 512);
	auto actual = data_array.compare(data2, 512);
	BOOST_CHECK_EQUAL(actual, true);
	delete[] data2;

}
