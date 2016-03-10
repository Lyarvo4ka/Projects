#include <boost/test/unit_test.hpp>

//BOOST_AUTO_TEST_SUITE(TestIODevice)
//
#include "IOLibrary/IODevice.h"
//
//
//struct F_File
//{
//	F_File()
//	{
//		pFile = new IO::File(L"d:\\test_folder\\1.docx");
//	}
//	~F_File()
//	{
//		delete pFile;
//	}
//	IO::IODevice * pFile;
//};

BOOST_AUTO_TEST_SUITE(TestIODevice)

BOOST_AUTO_TEST_CASE(test_name1)
{
	IO::File ioFile(L"d:\\test_folder\\1.docx");

}

BOOST_AUTO_TEST_SUITE_END()