#include <boost/test/unit_test.hpp>

#include "IOLibrary/AbstractRaw.h"

IO::DataArray::Ptr createTeastDataArrayPtr(const uint32_t size , const uint8_t test_val)
{
	auto data_array = IO::makeDataArray(size);
	memset(data_array->data(), test_val, size);
	return data_array;
}

const uint8_t const_header_1[] = { 0xAA, 0xBB, 0xCC, 0xDD };
const uint32_t const_header_1_size = SIZEOF_ARRAY(const_header_1);

const uint8_t const_header_2[] = { 0x00, 0x11 , 0x22 , 0x33, 0x44, 0x55};
const uint32_t const_header_2_size = SIZEOF_ARRAY(const_header_2);


IO::ByteArray createFromConstData(const uint8_t const_data[] ,uint32_t size)
{
	IO::ByteArray data = new uint8_t[size];
	memcpy(data, const_data, size);
	return data;
}

void deleteDataArray(IO::DataArray * data_array)
{
	delete data_array;
}

class my_exception {};

BOOST_AUTO_TEST_CASE(TestDataArrayConstructors)
{
	IO::DataArray const_ctor(const_header_1, const_header_1_size);
	BOOST_CHECK_EQUAL(const_ctor.size(), const_header_1_size);
	auto actual = const_ctor.compareData((IO::ByteArray)const_header_1, const_header_1_size);
	BOOST_CHECK_EQUAL(actual, true);

	IO::ByteArray data_array = new uint8_t[const_header_1_size];
	memcpy(data_array, const_header_1, const_header_1_size);


	IO::DataArray standard_ctor(data_array, const_header_1_size);
	BOOST_CHECK_EQUAL(standard_ctor.size(), const_header_1_size);
	actual = standard_ctor.compareData((IO::ByteArray)const_header_1, const_header_1_size);
	BOOST_CHECK_EQUAL(actual, true);

	//IO::DataArray *throw_ctor = new IO::DataArray((IO::ByteArray)headerTest, headerTest_size);
	//deleteDataArray(throw_ctor);
	////_CrtIsValidHeapPointer
	//BOOST_CHECK_THROW(deleteDataArray(throw_ctor) , my_exception);
	

}

BOOST_AUTO_TEST_CASE(TestCompareDataArray)
{
	auto data_array = createTeastDataArrayPtr(5 , 0xFF);
	auto data2 = createTeastDataArrayPtr(512 , 0xFF);
	BOOST_CHECK_EQUAL(data_array->compareData(data2->data(), 512) , true);
}
BOOST_AUTO_TEST_CASE(TestDataArrayEqual)
{
	auto data1 = IO::makeDataArray(const_header_1, const_header_1_size);
	auto data2 = IO::makeDataArray(const_header_1, const_header_1_size);
	auto data3= IO::makeDataArray(const_header_2 , const_header_2_size);

	BOOST_CHECK_EQUAL(data1 == data2, true);
	BOOST_CHECK_EQUAL(data1 == data3, false);
}

////////////////////////////////SignatureOffset//////////////////////////////////////////

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


////////////////////////////////FileStruct//////////////////////////////////////////
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

BOOST_AUTO_TEST_CASE(TestFileStructAdd)
{
	uint32_t offset_1 = 0;
	uint32_t offset_2 = 10;
	auto file_struct = IO::makeFileStruct("test");

	file_struct->add(createFromConstData(const_header_1 , const_header_1_size), const_header_1_size, offset_1);
	BOOST_CHECK_EQUAL(file_struct->headersCount(), 1);

	file_struct->add(createFromConstData(const_header_1, const_header_1_size), const_header_1_size, offset_1);
	BOOST_CHECK_EQUAL(file_struct->headersCount(), 1);

	file_struct->add(createFromConstData(const_header_2, const_header_2_size), const_header_2_size, offset_1);
	BOOST_CHECK_EQUAL(file_struct->headersCount(), 1);


	file_struct->add(createFromConstData(const_header_2, const_header_2_size), const_header_2_size, offset_2);
	BOOST_CHECK_EQUAL(file_struct->headersCount(), 2);
}