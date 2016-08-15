#include <boost/test/unit_test.hpp>

#include "IOLibrary/ext2.h"


BOOST_AUTO_TEST_CASE(isLessThanValueTest)
{
	uint32_t * pTestValues = new uint32_t[5];
	pTestValues[0] = 0x1;
	pTestValues[1] = 0x2;
	pTestValues[2] = 0x3;
	pTestValues[3] = 0x4;
	pTestValues[4] = 0x5;
	IO::ext2_raw ext(nullptr);

	uint32_t null_pos = 0;
	auto actual = ext.isLessThanValue(pTestValues + 0, pTestValues + 5, 10 , null_pos);
	BOOST_CHECK_EQUAL(actual, true);
	BOOST_CHECK_EQUAL(ext.isFullTable(null_pos, 5), true);

	pTestValues[4] = 0x0;
	null_pos = 0;
	actual = ext.isLessThanValue(pTestValues + 0, pTestValues + 5, 10, null_pos);
	BOOST_CHECK_EQUAL(actual, true);
	BOOST_CHECK_EQUAL(null_pos, 4);
	BOOST_CHECK_EQUAL(ext.isFullTable(null_pos, 5), false);

	pTestValues[3] = 11;
	actual = ext.isLessThanValue(pTestValues + 0, pTestValues + 5, 10, null_pos);
	BOOST_CHECK_EQUAL(actual, false);

	delete[] pTestValues;
}

BOOST_AUTO_TEST_CASE (isOnlyNullsTest)
{
	uint32_t * pTestValues = new uint32_t[5];
	pTestValues[0] = 0x1;
	pTestValues[1] = 0x2;
	pTestValues[2] = 0x0;
	pTestValues[3] = 0x0;
	pTestValues[4] = 0x0;

	IO::ext2_raw ext(nullptr);

	auto actual = ext.isOnlyNulls(pTestValues + 2, pTestValues + 5);
	BOOST_CHECK_EQUAL(actual, true);

	pTestValues[3] = 0x3;
	actual = ext.isOnlyNulls(pTestValues + 2, pTestValues + 5);
	BOOST_CHECK_EQUAL(actual, false);

	delete[] pTestValues;
}

BOOST_AUTO_TEST_CASE(hasDuplicatesTest)
{
	uint32_t * pTestValues = new uint32_t[5];
	pTestValues[0] = 0x0;
	pTestValues[1] = 0x1;
	pTestValues[2] = 0x2;
	pTestValues[3] = 0x3;
	pTestValues[4] = 0x4;

	IO::ext2_raw ext(nullptr);

	auto actual = ext.hasDuplicates(pTestValues + 0, pTestValues + 5);
	BOOST_CHECK_EQUAL(actual, false);

	pTestValues[3] = 0x1;
	actual = ext.hasDuplicates(pTestValues + 0, pTestValues + 5);
	BOOST_CHECK_EQUAL(actual, true);
	delete[] pTestValues;
}

