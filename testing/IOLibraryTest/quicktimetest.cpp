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

BOOST_AUTO_TEST_CASE(Test_toBE32)
{
	uint32_t val32	  = 0x01020304;
	uint32_t expected = 0x04030201;
	IO::toBE32(val32);
	BOOST_CHECK_EQUAL(val32, expected);

}

BOOST_AUTO_TEST_CASE(Test_toBE64)
{
	uint64_t val64 =	0x0102030405060708;
	uint64_t expected = 0x0807060504030201;
	IO::toBE64(val64);
	BOOST_CHECK_EQUAL(val64, expected);

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

BOOST_AUTO_TEST_CASE(TestisPresentMainKeywords)
{
	IO::QuickTimeRaw qt_raw(nullptr);
	IO::ListQtBlock qt_blocks;
	IO::qt_block_t qtBlock;

	memcpy(qtBlock.block_type, IO::s_free, IO::qt_keyword_size);
	qt_blocks.push_back(qtBlock);
	BOOST_CHECK_EQUAL(false, qt_raw.isPresentMainKeywords(qt_blocks));

	memcpy(qtBlock.block_type, IO::s_moov, IO::qt_keyword_size);
	qt_blocks.push_back(qtBlock);
	BOOST_CHECK_EQUAL(false, qt_raw.isPresentMainKeywords(qt_blocks));

	memcpy(qtBlock.block_type, IO::s_mdat, IO::qt_keyword_size);
	qt_blocks.push_back(qtBlock);
	BOOST_CHECK_EQUAL(true, qt_raw.isPresentMainKeywords(qt_blocks));


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
	IO::toBE32(qt_block.block_size);
	moc_file->WriteData((IO::ByteArray) &qt_block, block_size);

	offset += bkl_1;
	memcpy(qt_block.block_type, IO::s_moov, key_size);
	qt_block.block_size = bkl_2;
	IO::toBE32(qt_block.block_size);
	moc_file->setPosition(offset);
	moc_file->WriteData((IO::ByteArray) &qt_block, block_size);

	offset += bkl_2;
	memcpy(qt_block.block_type, IO::s_mdat, key_size);
	qt_block.block_size = bkl_3;
	IO::toBE32(qt_block.block_size);
	moc_file->setPosition(offset);
	moc_file->WriteData((IO::ByteArray) &qt_block, block_size);

	uint32_t expected = offset + bkl_3;

	IO::QuickTimeRaw qt_raw(moc_file);
	IO::ListQtBlock keywords;
	auto file_size = qt_raw.readQtAtoms(0, keywords);
	BOOST_CHECK_EQUAL(expected, file_size);
}



