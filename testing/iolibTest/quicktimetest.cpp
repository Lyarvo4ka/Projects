#include "gtest/gtest.h"

#include <IOLibrary\QuickTime.h>
#include "mockfile.h"

const uint32_t cftyp_size = 10;
const uint32_t cmoov_size = 20;
const uint32_t cmdat_size = 30;

const uint32_t ftyp_ofset = 0;
const uint32_t moov_offset = cftyp_size;
const uint32_t mdat_offset = cftyp_size + cmoov_size;

IO::qt_block_t generateQtBlock(const char * keyword_name, uint32_t block_size)
{
	IO::qt_block_t qt_block;
	memcpy(qt_block.block_type, keyword_name, IO::qt_keyword_size);
	auto be_size = block_size;
	IO::toBE32(be_size);
	qt_block.block_size = be_size;
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
	auto data_array = src_file->getData();

	auto ftyp_block = writeQtAtom(*data_array, ftyp_ofset, ftyp_size, IO::s_ftyp);
	auto moov_block = writeQtAtom(*data_array, moov_offset, moov_size, IO::s_moov);

	auto mdat_block = writeQtAtom(*data_array, mdat_offset, mdat_size, IO::s_mdat);
	return src_file;
}

TEST(QuickTimeTest, readQtAtom)
{
	using namespace IO;
	QuickTimeRaw qt_raw(createFtypMoovMdat(cftyp_size, cmoov_size , cmdat_size));

	qt_block_t ftyp_block;
	auto ftyp_size = qt_raw.readQtAtom(0, ftyp_block);
	EXPECT_EQ(ftyp_size, cftyp_size);
	EXPECT_TRUE(cmp_keyword(ftyp_block,s_ftyp));
	EXPECT_EQ(ftyp_block.block_size, cftyp_size);

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