
#include "stdafx.h"

#include <boost/test/unit_test.hpp>

#include "IOLibrary\Entropy.h"


BOOST_AUTO_TEST_CASE(getEntropyTest)
{
	double nullVal = 0.0;

	BOOST_CHECK_EQUAL(IO::getEntropy(nullptr, 0), nullVal);

}