#include <boost/test/unit_test.hpp>

#include "IOLibrary/Factories.h"

BOOST_AUTO_TEST_CASE(TestAddNewFactory)
{

	IO::RawFactoryManager factoryManager;
	std::string test1 = "test1";
	auto filePtr = IO::makeFilePtr(L"Empty file");
	factoryManager.Register(test1, new StandartRawFactory());
	auto resFactory = factoryManager
}