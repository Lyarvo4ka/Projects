#include "stdafx.h"
#include "CppUnitTest.h"

#include "libpdf/Pdfdocument.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace libpdftest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestParseDateString)
		{
			CString data_string;
			CString parsed_data;
			Assert::AreEqual(false, ParseDateString(data_string, parsed_data) );
		}

	};
}