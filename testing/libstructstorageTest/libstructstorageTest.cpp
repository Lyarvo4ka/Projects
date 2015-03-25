// libstructstorageTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE StructStorageLibTestModule

#include <boost/test/unit_test.hpp>

#include "libstructstorage\libstructstorage.h"

BOOST_AUTO_TEST_CASE(getTimeFromFileTimeTest)
{
	SYSTEMTIME sys_time = { 2015, 03, 3, 25, 18, 50, 45, 0 };
	FILETIME file_time;
	if (::SystemTimeToFileTime(&sys_time, &file_time))
	{
		std::string time_actual = getTimeFromFileTime(file_time);
		std::string time_expected = "18-50-45";
		BOOST_CHECK_EQUAL(time_actual, time_expected);

		time_actual = getDateFromFileTime(file_time);
		time_expected = "2015-03-25";
		BOOST_CHECK_EQUAL(time_actual, time_expected);

		time_actual = getDateTimeFromFileTime(file_time);
		time_expected = "2015-03-25-18-50-45";
		BOOST_CHECK_EQUAL(time_actual, time_expected);


	}
}