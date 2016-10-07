#include "IOLibrary/QuickTime.h"

#include <boost/test/unit_test.hpp>
#include <boost/lexical_cast.hpp>


namespace std {
	inline std::ostream& operator<<(std::ostream& out, const std::wstring& value)
	{
		std::string string_value(value.begin(), value.end());
		out << string_value;
		return out;
	}
}

BOOST_AUTO_TEST_CASE(TestNumberToSting)
{
	IO::path_string actual = L"0000000001";
	uint32_t number = 1;
	IO::path_string expected = IO::toNumberString(number);
	BOOST_CHECK_EQUAL(actual, expected);

	number = ULONG_MAX;
	actual = L"4294967295";
	expected = IO::toNumberString(number);
	BOOST_CHECK_EQUAL(actual, expected);

	++number;
	actual = L"4294967296";
	//actual = L"0000000000";
	expected = IO::toNumberString(number);
	BOOST_CHECK(actual != expected);

}

BOOST_AUTO_TEST_CASE(TestIsPresetInKeywordArray)
{
	QTKeyword::keyword_array array_mdat_moov = { QTKeyword::mdat ,QTKeyword::moov };
	auto expected = IO::isPresentInKeywordArray(array_mdat_moov, QTKeyword::mdat);
	BOOST_CHECK_EQUAL(true, expected);
	expected = IO::isPresentInKeywordArray(array_mdat_moov, QTKeyword::moov);
	BOOST_CHECK_EQUAL(true, expected);

	expected = IO::isPresentInKeywordArray(array_mdat_moov, QTKeyword::ftyp);
	BOOST_CHECK_EQUAL(false, expected);


}

BOOST_AUTO_TEST_CASE(TestI)
