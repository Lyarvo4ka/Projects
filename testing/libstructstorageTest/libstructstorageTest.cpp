// libstructstorageTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE StructStorageLibTestModule

#include <boost/test/unit_test.hpp>

#include "libstructstorage\libstructstorage.h"

BOOST_AUTO_TEST_CASE(getTimeFromFileTimeTest)
{
	FILETIME file_time;

	BOOST_CHECK_EQUAL( getTimeFromFileTime(file_time) , "");

}