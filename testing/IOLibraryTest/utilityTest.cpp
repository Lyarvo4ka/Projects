#include <boost/test/unit_test.hpp>

#include "IOLibrary/utility.h"

BOOST_AUTO_TEST_CASE(toHexString_test)
{
	auto res = IO::toHexString(0xaaaa);
	bool cmp_result = (res.compare(L"aaaa") == 0);
	BOOST_CHECK_EQUAL(cmp_result, true);


}