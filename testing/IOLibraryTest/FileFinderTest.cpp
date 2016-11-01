#include "IOLibrary/Finder.h"

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(FindTest)
{
	//IO::path_string root_folder = L"d:\\NVIDIA\\";
	//IO::path_string root_folder = L"c:\\NVIDIA\\";
	//IO::Finder finder;

	//IO::path_list ext_list = { L".doc", L".docx" , L".xls", L".xlsx" };

	//finder.FindFiles(root_folder );
	//finder.printAll();

}

BOOST_AUTO_TEST_CASE(getNotNullFromEndTest)
{
	uint32_t size = 10;
	uint32_t pos = 4;
	IO::Buffer buffer(size);
	ZeroMemory(buffer.data, buffer.data_size);
	buffer.data[size - pos] = 0xFF;
	auto resPos = IO::NotNullPosFromEnd(buffer);
	BOOST_CHECK_EQUAL(resPos, size - pos);
}