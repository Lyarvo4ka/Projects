#include <boost/test/unit_test.hpp>

#include "IOLibrary/AbstractRaw.h"

IO::DataArray::Ptr createTeastDataArrayPtr(const uint32_t size)
{
	auto data_array = IO::makeDataArray(size);
	memset(data_array->data(), 0xFF, size);
	return data_array;
}

BOOST_AUTO_TEST_CASE(TestCompareDataArray)
{
	auto data_array = createTeastDataArrayPtr(5);
	IO::ByteArray data2 = new uint8_t[512];
	memset(data2, 0xFF, 512);
	BOOST_CHECK_EQUAL(data_array->compare(data2, 512) , true);
	delete[] data2;

}

void addsing(IO::SignatureOffset & signOffset)
{
	const uint32_t size = 5;
	signOffset.addSignature(createTeastDataArrayPtr(size));
}
BOOST_AUTO_TEST_CASE(TestFindSignature)
{
	IO::SignatureOffset signOffset;
	addsing(signOffset);
	const uint32_t data2_size = 512;
	IO::ByteArray data2 = new uint8_t[data2_size];
	memset(data2, 0xFF, data2_size);
	BOOST_CHECK_EQUAL(signOffset.FindSignature(data2, data2_size), true);
	delete[] data2;


}
