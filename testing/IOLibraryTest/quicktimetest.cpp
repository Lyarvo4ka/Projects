#include "IOLibrary/QuickTime.h"

#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>

#include "MocFile.h"


namespace std {
	inline std::ostream& operator<<(std::ostream& out, const std::wstring& value)
	{
		std::string string_value(value.begin(), value.end());
		out << string_value;
		return out;
	}
}

BOOST_AUTO_TEST_CASE(TestNumberToSting)
{
	IO::path_string actual = L"0000000001";
	uint32_t number = 1;
	IO::path_string expected = IO::toNumberString(number);
	BOOST_CHECK_EQUAL(actual, expected);

	number = ULONG_MAX;
	actual = L"4294967295";
	expected = IO::toNumberString(number);
	BOOST_CHECK_EQUAL(actual, expected);

	++number;
	actual = L"4294967296";
	//actual = L"0000000000";
	expected = IO::toNumberString(number);
	BOOST_CHECK(actual != expected);

}

BOOST_AUTO_TEST_CASE(TestIsPresetInKeywordArray)
{
	IO::array_keywords array_mdat_moov = { IO::s_mdat ,IO::s_moov };
	auto expected = IO::isPresentInArrayKeywords(array_mdat_moov, IO::s_mdat);
	BOOST_CHECK_EQUAL(true, expected);
	expected = IO::isPresentInArrayKeywords(array_mdat_moov, IO::s_moov);
	BOOST_CHECK_EQUAL(true, expected);

	expected = IO::isPresentInArrayKeywords(array_mdat_moov, IO::s_ftyp);
	BOOST_CHECK_EQUAL(false, expected);
}

BOOST_AUTO_TEST_CASE(Test_readQtAtoms)
{
	const uint32_t data_size = 1024;
	const uint32_t key_size = 4;


	const uint32_t bkl_1 = 10;
	const uint32_t bkl_2 = 20;
	const uint32_t bkl_3 = 50;



	auto moc_file = std::make_shared<MocFile>(data_size);

	IO::qt_block_t qt_block = { 0 };
	uint32_t offset = 0;
	uint32_t block_size = sizeof(IO::qt_block_t);
	memcpy(qt_block.block_type, IO::s_ftyp, key_size);
	qt_block.block_size = bkl_1;
	IO::to_big_endian32(qt_block.block_size);
	moc_file->WriteData((IO::ByteArray) &qt_block, block_size);

	offset += bkl_1 + block_size;
	memcpy(qt_block.block_type, IO::s_moov, key_size);
	qt_block.block_size = bkl_2;
	IO::to_big_endian32(qt_block.block_size);
	moc_file->setPosition(offset);
	moc_file->WriteData((IO::ByteArray) &qt_block, block_size);

	offset += bkl_2 + block_size;
	memcpy(qt_block.block_type, IO::s_mdat, key_size);
	qt_block.block_size = bkl_3;
	IO::to_big_endian32(qt_block.block_size);
	moc_file->setPosition(offset);
	moc_file->WriteData((IO::ByteArray) &qt_block, block_size);

	uint32_t expected = offset + bkl_3 + block_size;

	IO::QuickTimeRaw qt_raw(moc_file);
	IO::ListQtBlock keywords;
	auto file_size = qt_raw.readQtAtoms(0, keywords);
	//BOOST_CHECK_EQUAL(expected, file_size);
}



