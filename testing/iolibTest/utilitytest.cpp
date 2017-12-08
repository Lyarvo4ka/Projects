#include "gtest/gtest.h"

#include "IOLibrary\utility.h"

TEST( UtilityTest, fileNameToOffsetTest)
{
	IO::path_string file1 = L"d:\\Temp\\1\\img016937500.bin";
	auto offset_val = IO::fileNameToOffset(file1);
	EXPECT_EQ(offset_val, 16937500);

}