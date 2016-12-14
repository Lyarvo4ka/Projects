#include <boost/test/unit_test.hpp>

#include "IOLibrary/Factories.h"
#include "IOLibrary/StandartRaw.h"

BOOST_AUTO_TEST_CASE(TestAddNewFactory)
{

	IO::RawFactoryManager factoryManager;
	std::string test1 = "test1";
	auto filePtr = IO::makeFilePtr(L"Empty file");
	factoryManager.Register(test1, new IO::StandartRawFactory());
	auto found_factory = factoryManager.Lookup(test1);
	//std::string standartRawName = "StandartRawFactory";
	//auto typeIdName = typeid(found_factory).name();
	//bool bResult = standartRawName.compare(typeIdName) == 0 ;
	BOOST_CHECK_EQUAL(bResult, true);
}