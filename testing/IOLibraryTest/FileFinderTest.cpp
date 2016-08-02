#include "IOLibrary/FileFinder.h"

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(FindTest)
{
	//IO::path_string root_folder = L"d:\\test_folder\\";
	IO::path_string root_folder = L"c:\\Logs\\";
	IO::FileFinder finder;

	IO::path_list ext_list = { L".doc", L".docx" , L".xls", L".xlsx" };

	finder.FindFiles(root_folder );
	finder.printAll();

}