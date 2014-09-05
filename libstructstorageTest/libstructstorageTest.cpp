// libstructstorageTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE StructStorageLibTestModule

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( Test )
{
	BOOST_CHECK_EQUAL( IO::isLastBackspace("c:\\asd\\" ) , true );
	BOOST_CHECK_EQUAL( IO::isLastBackspace("c:\\asd" ) , false );
}