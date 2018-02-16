#include "gtest/gtest.h"

#include <IOLibrary\QuickTime.h>
#include "mockfile.h"


TEST(QuickTimeTest, QTFragmentRaw_find_qt_keyword)
{
	using namespace IO;
	const uint32_t file_size = 2048;
	const uint32_t name_position = 1536;

	auto src_file = makeMockFile(file_size);
	src_file->setPosition(name_position);

	qt_block_t qt_block = qt_block_t();
	qt_block.block_size = 8;
	memcpy(qt_block.block_type, IO::s_ftyp, qt_keyword_size);
	src_file->WriteData((ByteArray)&qt_block, qt_block_struct_size);

	QTFragmentRaw fragmentRaw(src_file);
	fragmentRaw.setBlockSize(1024);
	const std::string keyword_name = "ftyp";
	auto qt_handle = fragmentRaw.find_qt_keyword(0, keyword_name);

	EXPECT_TRUE(qt_handle.isValid());
	EXPECT_EQ(qt_handle.offset() , name_position);

	const std::string wrong_keyword = "wrong keyword";
	auto qt_handle2 = fragmentRaw.find_qt_keyword(0, wrong_keyword);
	EXPECT_FALSE(qt_handle2.isValid());

}