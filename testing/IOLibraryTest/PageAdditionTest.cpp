#include "IOLibrary/pageaddition.h"

#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE(isAdditionPageTest)
{
	isAdditionPage(0x62);
	BOOST_CHECK_EQUAL(isAdditionPage(0x62), true);
	BOOST_CHECK_EQUAL(isAdditionPage(0x60), true);

	BOOST_CHECK_EQUAL(isAdditionPage(0x40), false);

}

BOOST_AUTO_TEST_CASE(toBankNumberTest)
{
	BOOST_CHECK_EQUAL(toBankNumber(0x62), 0x22);
	BOOST_CHECK_EQUAL(toBankNumber(0x31), 0x31);

	BOOST_CHECK_EQUAL(toBankNumber(0x43), 0x03);

}

BOOST_AUTO_TEST_CASE(joinToPageNumberTest)
{
	BOOST_CHECK_EQUAL(joinToPageNumber(0x41 , 0x16), 0x0116);
	BOOST_CHECK_EQUAL(joinToPageNumber(0x74, 0x83), 0x0183);
	BOOST_CHECK_EQUAL(joinToPageNumber(0x34, 0x13), 0x0013);

}