#include "IOLibrary/QuickTime.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TestNumberToSting)
{
	IO::path_string actual = L"0000000001";
	uint32_t number = 1;
	IO::path_string expected = IO::NumberToString(number);

	BOOST_CHECK(actual == expected);
}