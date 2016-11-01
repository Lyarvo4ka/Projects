#include "factories.h"
#include "AbstractRaw.h"

namespace IO
{
	//RawAlgorithm * StandartRawFactory::createRawAlgorithm(IODevicePtr device)
	//{
	//	return new StandartRaw(device);
	//}

	//void RawFactoryManager::Register(const std::string & algorithmName, RawFactory * rawFactory)
	//{
	//	if (factories_.find(algorithmName) == factories_.end())
	//	{
	//		auto rawFactoryPtr = std::make_unique<RawFactory>(rawFactory);
	//		factories_.insert(std::make_pair(algorithmName, rawFactoryPtr));
	//	}
	//}

	//IO::RawFactory * RawFactoryManager::Lookup(const std::string & algorithmName)
	//{
	//	auto findIter = factories_.find(algorithmName);
	//	if (findIter != factories_.end())
	//	{
	//		return findIter->second.get();
	//	}
	//	return nullptr;
	//}

};
