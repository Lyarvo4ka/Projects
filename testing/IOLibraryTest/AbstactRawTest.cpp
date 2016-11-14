#include <boost/test/unit_test.hpp>

#include "IOLibrary/AbstractRaw.h"

IO::DataArray::Ptr createTeastDataArrayPtr(const uint32_t size , const uint8_t test_val)
{
	auto data_array = IO::makeDataArray(size);
	memset(data_array->data(), test_val, size);
	return data_array;
}

const uint8_t headerTest[] = { 0xAA, 0xBB, 0xCC, 0xDD };
const uint32_t headerTest_size = SIZEOF_ARRAY(headerTest);

void deleteDataArray(IO::DataArray * data_array)
{
	delete data_array;
}

BOOST_AUTO_TEST_CASE(TestDataArrayConstructos)
{
	IO::DataArray const_ctor(headerTest, headerTest_size);
	BOOST_CHECK_EQUAL(const_ctor.size(), headerTest_size);
	auto actual = const_ctor.compare((IO::ByteArray)headerTest, headerTest_size);
	BOOST_CHECK_EQUAL(actual, true);

	IO::ByteArray data_array = new uint8_t[headerTest_size];
	memcpy(data_array, headerTest, headerTest_size);


	IO::DataArray standard_ctor(data_array, headerTest_size);
	BOOST_CHECK_EQUAL(standard_ctor.size(), headerTest_size);
	actual = standard_ctor.compare((IO::ByteArray)headerTest, headerTest_size);
	BOOST_CHECK_EQUAL(actual, true);

	IO::DataArray *throw_ctor = new IO::DataArray((IO::ByteArray)headerTest, headerTest_size);
	deleteDataArray(throw_ctor);
	//_CrtIsValidHeapPointer
	//BOOST_CHECK_THROW(deleteDataArray(throw_ctor) , std::runtime_error);
	

}


BOOST_AUTO_TEST_CASE(TestCompareDataArray)
{
	auto data_array = createTeastDataArrayPtr(5 , 0xFF);
	auto data2 = createTeastDataArrayPtr(512 , 0xFF);
	BOOST_CHECK_EQUAL(data_array->compare(data2->data(), 512) , true);
}

void addsing(IO::SignatureOffset & signOffset)
{
	const uint32_t size = 5;
	signOffset.addSignature(createTeastDataArrayPtr(size, 0xFF));
}
BOOST_AUTO_TEST_CASE(TestFindSignature)
{
	IO::SignatureOffset signOffset;
	addsing(signOffset);
	const uint32_t data2_size = 512;
	auto data2 = createTeastDataArrayPtr(data2_size , 0xFF);
	BOOST_CHECK_EQUAL(signOffset.FindSignature(data2->data(), data2_size), true);

	data2->data()[0] = 0x00;
	BOOST_CHECK_EQUAL(signOffset.FindSignature(data2->data(), data2_size), false);

	signOffset.setOffset(1);
	BOOST_CHECK_EQUAL(signOffset.FindSignature(data2->data(), data2_size), true);
}

BOOST_AUTO_TEST_CASE(TestcompareWithAllHeaders)
{
	auto signOffset = IO::makeSignatureOffset();
	addsing(*signOffset);
	const uint32_t header2_size = 5;
	auto header2 = createTeastDataArrayPtr(header2_size, 0xAA);
	const uint32_t header2_offset = 10;

	const uint32_t data2_size = 512;
	auto data2 = createTeastDataArrayPtr(data2_size, 0xFF);
	for (auto i = 0; i < header2_size; ++i)
	{
		data2->data()[i + header2_offset] = 0xAA;
	}
	auto signOffset2 = IO::makeSignatureOffset();
	signOffset2->addSignature(std::move(header2));
	signOffset2->setOffset(header2_offset);


	IO::FileStruct file_struct("test");
	file_struct.add(std::move(signOffset));
	file_struct.add(std::move(signOffset2));
	
	BOOST_CHECK_EQUAL(file_struct.compareWithAllHeaders(data2->data(), data2_size), true);

}
