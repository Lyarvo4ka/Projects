// libstructstorageTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE StructStorageLibTestModule

#include <boost/test/unit_test.hpp>

#include "libstructstorage\libstructstorage.h"

BOOST_AUTO_TEST_CASE(getTimeFromFileTimeTest)
{
	//SYSTEMTIME sys_time = { 2015, 03, 3, 25, 18, 50, 45, 0 };
	//FILETIME file_time;
	//file_time.dwHighDateTime = 30435116;
	//file_time.dwLowDateTime = 2580033664;

	//std::string time_actual = getTimeFromFileTime(file_time);
	//std::string time_expected = "18-50-45";
	//BOOST_CHECK_EQUAL(time_actual, time_expected);

	//time_actual = getDateFromFileTime(file_time);
	//time_expected = "2015-03-25";
	//BOOST_CHECK_EQUAL(time_actual, time_expected);

	//time_actual = getDateTimeFromFileTime(file_time);
	//time_expected = "2015-03-25-18-50-45";
	//BOOST_CHECK_EQUAL(time_actual, time_expected);

	std::string expected = "2014";
	BOOST_CHECK_EQUAL(toString(2014,4) , expected);

	expected = "2015";
	BOOST_CHECK_EQUAL(toYearString(2015), expected);

	expected = "01";
	BOOST_CHECK_EQUAL(toStringDate(1), expected);

	FileDateTime startTime;
	std::string actual = startTime.getYear();
	expected = "1601";
	BOOST_CHECK_EQUAL(actual, expected);
	expected = "01";
	actual = startTime.getMonth();
	BOOST_CHECK_EQUAL(actual, expected);


}