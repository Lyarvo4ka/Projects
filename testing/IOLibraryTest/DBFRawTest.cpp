#include <boost/test/unit_test.hpp>

#include "IOLibrary/dbf.h"

BOOST_AUTO_TEST_CASE(Test_isValidData)
{

	IO::dbf_header header = { 0 };
	IO::DBFRaw dbf_raw(nullptr);

	BOOST_CHECK_EQUAL(dbf_raw.isValidDate(header), false);

	header.yymmdd[0] = 16;
	BOOST_CHECK_EQUAL(dbf_raw.isValidDate(header), false);

	header.yymmdd[1] = 1;
	BOOST_CHECK_EQUAL(dbf_raw.isValidDate(header), false);

	header.yymmdd[2] = 1;
	BOOST_CHECK_EQUAL(dbf_raw.isValidDate(header), true);

	header.yymmdd[0] = 17;
	BOOST_CHECK_EQUAL(dbf_raw.isValidDate(header), false);

	header.yymmdd[0] = 16;
	header.yymmdd[1] = 13;
	BOOST_CHECK_EQUAL(dbf_raw.isValidDate(header), false);

	header.yymmdd[1] = 1;
	header.yymmdd[2] = 32;
	BOOST_CHECK_EQUAL(dbf_raw.isValidDate(header), false);
}