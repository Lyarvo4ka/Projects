#include <boost/test/unit_test.hpp>

#include "IOLibrary/StandartRaw.h"

const uint8_t test_footer[] = { 0xAA , 0xBB , 0xCC , 0xDD , 0xEE, 0xFF};
const uint32_t test_footer_size = SIZEOF_ARRAY(test_footer);

BOOST_AUTO_TEST_CASE(TestFindFooter)
{
	IO::StandartRaw standartRaw(nullptr);
	const uint32_t test_size = 1024;
	const uint32_t footer_offset = 10;

	IO::DataArray data1(test_size);
	ZeroMemory(data1.data(), data1.size());

	IO::DataArray footer_data(test_footer, test_footer_size);

	uint32_t footer_pos = 0;
	auto actual = standartRaw.findFooter(data1, data1.size(), footer_data, footer_pos);
	BOOST_CHECK_EQUAL(actual, false);

	memcpy(data1.data() + footer_offset, footer_data.data(), footer_data.size());

	actual = standartRaw.findFooter(data1, data1.size(), footer_data, footer_pos);
	BOOST_CHECK_EQUAL(actual, true);
	BOOST_CHECK_EQUAL(footer_offset, footer_pos);

}

BOOST_AUTO_TEST_CASE(Test_calcToSectorSize)
{
	IO::StandartRaw standartRaw(nullptr);
	standartRaw.setBlockSize(1024);
	standartRaw.setSectorSize(512);

	auto actual = standartRaw.calcToSectorSize(10);
	BOOST_CHECK_EQUAL(actual, 512);

	actual = standartRaw.calcToSectorSize(520);
	BOOST_CHECK_EQUAL(actual, 1024);
}

#include "MocFile.h"
//class StandartRawMock
//	: public IO::StandartRaw
//{
//public:
//	uint32_t target_size = 0;
//	std::shared_ptr<MocFile> target_file_;
//public:
//	StandartRawMock(IO::IODevicePtr device)
//		: StandartRaw(device)
//	{
//		setBlockSize(1024);
//		setSectorSize(512);
//	}
//	IO::FilePtr createMockFile(const uint32_t size)
//	{
//		target_file_ = std::make_shared<MocFile>(size);
//		return target_file_;
//	}
//	IO::FilePtr createFile(const IO::path_string & target_name) override
//	{
//		return createMockFile(target_size);
//	}
//	IO::FilePtr SaveRawFile(const IO::FileStruct & file_struct, const uint64_t header_offset, const IO::path_string & target_name) override
//	{
//		return IO::StandartRaw::SaveRawFile(file_struct, header_offset, target_name);
//	}
//};

BOOST_AUTO_TEST_CASE(test_appendToFile)
{
	auto src_file = std::make_shared<MocFile>(20);
	IO::DataArray src_data(10);
	for (uint32_t i = 0; i < src_data.size(); ++i)
	{
		src_data.data()[i] = i;
	}
	//memset(src_data.data(), 0xAA, src_data.size());
	src_file->setPosition(10);
	src_file->WriteData(src_data.data(), src_data.size());
	IO::StandartRaw standart_raw(src_file);
	standart_raw.setBlockSize(5);
	auto dst_file = std::make_shared<MocFile>(5);
	auto actual = standart_raw.appendToFile(*dst_file, 10, 10);
	BOOST_CHECK_EQUAL(actual, 10);


	BOOST_CHECK_EQUAL(dst_file->Size(), 5 + 10);

	IO::DataArray read_data(10);
	dst_file->setPosition(5);
	dst_file->ReadData(read_data.data(), read_data.size());
	auto res = memcmp(read_data.data(), src_data.data(), read_data.size());
	BOOST_CHECK_EQUAL(res, 0);

	actual = standart_raw.appendToFile(*dst_file, 1000, 10);
	BOOST_CHECK_EQUAL(actual, 0);


}

BOOST_AUTO_TEST_CASE(test_SaveRawFile)
{
	IO::DataArray footer_data(test_footer, test_footer_size);
	const uint32_t footer_offset = 12;

	const uint32_t src_size = 30;
	auto src_file = std::make_shared<MocFile>(src_size);
	IO::DataArray src_data(src_size);
	memset(src_data.data(), 0xEB, src_data.size());
	memcpy(src_data.data() + footer_offset, footer_data, test_footer_size);
	src_file->WriteData(src_data.data(), src_data.size());

	auto file_struct = IO::makeFileStruct("test Footer");
	file_struct->addFooter(test_footer, 3);
	file_struct->setFooterTailEndSize(3);
	file_struct->setMaxFileSize(src_size);


	MocFile dst_file1(0);
	IO::StandartRaw standart_raw(src_file);
	standart_raw.setBlockSize(10);
	standart_raw.setSectorSize(5);
	standart_raw.setFooter(file_struct->getFooter(), file_struct->getFooterTailEndSize());
	standart_raw.setMaxFileSize(file_struct->getMaxFileSize());

	const uint32_t start_offset = 3;

	auto saved_size = standart_raw.SaveRawFile(dst_file1, start_offset);
	auto expected_size = footer_offset - start_offset + file_struct->getFooter()->size() + file_struct->getFooterTailEndSize();
	BOOST_CHECK_EQUAL(saved_size, expected_size);

	MocFile dst_file2(0);
	saved_size = standart_raw.SaveRawFile(dst_file2, src_size + 1);
	BOOST_CHECK_EQUAL(saved_size, 0);

	memset(src_data.data(), 0xEB, src_data.size());
	src_file->setPosition(0);
	src_file->WriteData(src_data.data(), src_data.size());

	// no found footer
	MocFile dst_file3(0);
	saved_size = standart_raw.SaveRawFile(dst_file3, start_offset);
	BOOST_CHECK_EQUAL(saved_size, src_size - start_offset);

}

//////////////////////////////////////////////////////////////////////////
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


BOOST_AUTO_TEST_CASE(test_OnlyHeadersRaw_SaveRawFile)
{
	IO::DataArray footer_data(test_footer, test_footer_size);
	const uint32_t footer_offset = 15;

	const uint32_t src_size = 30;
	auto src_file = std::make_shared<MocFile>(src_size);
	IO::DataArray src_data(src_size);
	memset(src_data.data(), 0xEB, src_data.size());
	memcpy(src_data.data() + footer_offset, footer_data, test_footer_size);
	src_file->WriteData(src_data.data(), src_data.size());

	auto file_struct = IO::makeFileStruct("test Footer");
	file_struct->addFooter(test_footer, 3);


	MocFile dst_file1(0);
	IO::OnlyHeadersRaw test_raw(src_file);
	test_raw.setFooter(file_struct->getFooter(), 0);
	test_raw.setBlockSize(10);
	test_raw.setSectorSize(5);
	test_raw.setFooter(file_struct->getFooter(), file_struct->getFooterTailEndSize());

	const uint32_t start_offset = 0;

	auto saved_size = test_raw.SaveRawFile(dst_file1, 0);
	auto expected_size = footer_offset;
	BOOST_CHECK_EQUAL(saved_size, expected_size);

	//MocFile dst_file3(0);
	//saved_size = standart_raw.SaveRawFile(dst_file3, start_offset);
	//BOOST_CHECK_EQUAL(saved_size, src_size - start_offset);

}
