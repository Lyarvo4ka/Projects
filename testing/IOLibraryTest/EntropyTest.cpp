
#include "stdafx.h"

#include <boost/test/unit_test.hpp>

#include "IOLibrary\Entropy.h"


BOOST_AUTO_TEST_CASE(getEntropyTest)
{
	double nullVal = 0.0;
	 
	//BOOST_CHECK_EQUAL(IO::getEntropy(nullptr, 0), nullVal);

}

#include "IOLibrary\BlockNumber.h"

BOOST_AUTO_TEST_CASE(MaskMarkerTest)
{
	    
	BOOST_CHECK_EQUAL(MaskMarker(0x44332211, 0x0003FFFF), 0x00012233);
	BOOST_CHECK_EQUAL(MaskMarker(0x00373524, 0x0003FFFF), 0x00003537);
}