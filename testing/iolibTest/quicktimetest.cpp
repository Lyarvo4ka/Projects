#include "gtest/gtest.h"

#include <IOLibrary\QuickTime.h>
#include "mockfile.h"

const uint32_t cftyp_size = 10;
const uint32_t cmoov_size = 20;
const uint32_t cmdat_size = 30;

IO::qt_block_t generateQtBlock(const char * keyword_name, uint32_t block_size)
{
	IO::qt_block_t qt_block;
	memcpy(qt_block.block_type, keyword_name, IO::qt_keyword_size);
	qt_block.block_size = block_size;
	return qt_block;
}

IO::qt_block_t writeQtAtom(IO::DataArray & data_array, uint32_t offset, uint32_t size, const std::string & keyword_name)
{
	auto qt_block = generateQtBlock(keyword_name.c_str(), size);
	memcpy(data_array.data() + offset, &qt_block, IO::qt_block_struct_size);
	return qt_block;
}

// not implemented when block_size 1 (64bit size)
MockFile::Ptr createFtypMoovMdat(uint32_t ftyp_size , uint32_t moov_size, uint32_t mdat_size)
{
	const uint32_t file_size = ftyp_size + moov_size + mdat_size;
	auto src_file = makeMockFile(file_size);
	uint32_t offset = 0;


	auto data_array = src_file->getData();

	auto ftyp_block = writeQtAtom(*data_array, offset, ftyp_size, IO::s_ftyp);
	offset += ftyp_block.block_size;

	auto moov_block = writeQtAtom(*data_array, offset, moov_size, IO::s_moov);
	data_array = src_file->getData() + offset;
	offset += moov_block.block_size;

	auto mdat_block = writeQtAtom(*data_array, offset, mdat_size, IO::s_mdat);
	return src_file;
}

TEST(QuickTimeTest, findQtKeywordTest)
{
	using namespace IO;
	const uint32_t file_size = 2048;
	const uint32_t name_position = 1536;

	auto src_file = makeMockFile(file_size);
	QTFragmentRaw fragmentRaw(src_file);
	fragmentRaw.setBlockSize(1024);

	const std::string keyword_name = IO::s_ftyp;
	auto not_found_handle = fragmentRaw.findQtKeyword(0, keyword_name);
	EXPECT_FALSE(not_found_handle.isValid());

	qt_block_t qt_block = qt_block_t();
	qt_block.block_size = 8;
	memcpy(qt_block.block_type, IO::s_ftyp, qt_keyword_size);
	src_file->setPosition(name_position);
	src_file->WriteData((ByteArray)&qt_block, qt_block_struct_size);

	auto qt_handle = fragmentRaw.findQtKeyword(0, keyword_name);

	EXPECT_TRUE(qt_handle.isValid());
	EXPECT_EQ(qt_handle.offset(), name_position);

	const std::string wrong_keyword = "wrong keyword";
	auto qt_handle2 = fragmentRaw.findQtKeyword(0, wrong_keyword);
	EXPECT_FALSE(qt_handle2.isValid());
}