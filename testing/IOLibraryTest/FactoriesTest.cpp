#include <boost/test/unit_test.hpp>

#include "IOLibrary/Factories.h"
#include "IOLibrary/StandartRaw.h"
#include "IOLibrary/QuickTime.h"

BOOST_AUTO_TEST_CASE(TestAddNewFactory)
{

	IO::RawFactoryManager factoryManager;
	std::string standart_name = "standartRaw";
	std::string qt_name = "QtRaw";

	factoryManager.Register(standart_name, std::make_unique<IO::StandartRawFactory>());
	factoryManager.Register(qt_name, std::make_unique<IO::QuickTimeRawFactory>());

	auto found_factory = factoryManager.Lookup(standart_name);
	BOOST_CHECK(found_factory != nullptr);

	found_factory = factoryManager.Lookup(qt_name);
	BOOST_CHECK(found_factory != nullptr);

	std::string no_name = "No name";
	found_factory = factoryManager.Lookup(no_name);
	BOOST_CHECK(found_factory == nullptr);

}