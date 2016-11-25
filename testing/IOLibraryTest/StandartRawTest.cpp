#include <boost/test/unit_test.hpp>

#include "IOLibrary/StandartRaw.h"

const uint8_t test_footer[] = { 0xAA , 0xBB , 0xCC , 0xDD , 0xEE, 0xFF};

BOOST_AUTO_TEST_CASE(TestFindFooter)
{
	IO::StandartRaw standartRaw(nullptr);
	const uint32_t test_size = 1024;
	const uint32_t footer_offset = 10;

	IO::DataArray data1(test_size);
	ZeroMemory(data1.data(), data1.size());

	IO::DataArray footer_data(test_footer, SIZEOF_ARRAY(test_footer));

	uint32_t footer_pos = 0;
	auto actual = standartRaw.findFooter(data1, data1.size(), footer_data, footer_pos);
	BOOST_CHECK_EQUAL(actual, false);

	memcpy(data1.data() + footer_offset, footer_data.data(), footer_data.size());

	actual = standartRaw.findFooter(data1, data1.size(), footer_data, footer_pos);
	BOOST_CHECK_EQUAL(actual, true);
	BOOST_CHECK_EQUAL(footer_offset, footer_pos);

}

BOOST_AUTO_TEST_CASE(Test_addAlignedToBlockSize)
{
	IO::StandartRaw standartRaw(nullptr);
	standartRaw.setBlockSize(1024);
	standartRaw.setSectorSize(512);

	auto actual = standartRaw.addAlignedToBlockSize(10);
	BOOST_CHECK_EQUAL(actual, 1536);

	actual = standartRaw.addAlignedToBlockSize(520);
	BOOST_CHECK_EQUAL(actual, 2048);
}

#include "MocFile.h"
class StandartRawMock
	: public IO::StandartRaw
{
public:
	StandartRawMock(IO::IODevicePtr device)
		: StandartRaw(device)
	{
		setBlockSize(1024);
		setSectorSize(512);
	}
	IO::FilePtr createFile(const IO::path_string & target_name) override
	{
		return std::dynamic_pointer_cast<IO::File>(std::make_shared<MocFile>(4096));
	}
	uint64_t SaveRawFile(IO::FileStruct::Ptr file_struct, const uint64_t header_offset, const IO::path_string & target_name) override
	{
		return IO::StandartRaw::SaveRawFile(file_struct, header_offset, target_name);
	}
};

BOOST_AUTO_TEST_CASE(testSaveRawFile)
{
	StandartRawMock raw_mock(std::make_shared<MocFile>(8096));
	IO::DataArray footer_data(test_footer, SIZEOF_ARRAY(test_footer));


}

BOOST_AUTO_TEST_CASE(TestCompareBetween)
{
	IO::StandartRaw standartRaw(nullptr);
	const uint32_t test_size = 1024;
	IO::DataArray data1(test_size);
	ZeroMemory(data1.data(), data1.size());
	IO::DataArray data2(test_size);
	ZeroMemory(data2.data(), data2.size());

	IO::DataArray footer_data(test_footer,SIZEOF_ARRAY(test_footer));

	const uint32_t data1_count = 2;
	memcpy(data1.data() + data1.size() - data1_count , test_footer, data1_count);
	memcpy(data2.data(), test_footer + data1_count, SIZEOF_ARRAY(test_footer) - data1_count);

	uint32_t footer_pos = 0;
	bool actual = standartRaw.compareBetween(data1, data2, footer_data, footer_pos);
	BOOST_CHECK_EQUAL(actual, true);
	BOOST_CHECK_EQUAL(footer_pos, data1.size() - data1_count);

	data2.data()[0] = 0x99;
	actual = standartRaw.compareBetween(data1, data2, footer_data, footer_pos);
	BOOST_CHECK_EQUAL(actual, false);
	//standartRaw.compareBetween
}
