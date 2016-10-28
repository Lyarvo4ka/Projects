#pragma once

#include "AbstractRaw.h"
#include <map>
namespace IO
{
	class RawFactory
	{
	public:
		virtual ~RawFactory() {}
		virtual RawAlgorithm * createRaw(IODevicePtr) = 0;
	};

	using RawFactoryPtr = std::unique_ptr<RawFactory>;


	class StandartRawFactory
		: public RawFactory
	{
		RawAlgorithm * createRaw(IODevicePtr device) override
		{
			return new StandartRaw(device);
		};
	};

	class RawManager
	{
		using FactoryMap = std::map<std::string, RawFactoryPtr> ;
		using FactoryPair = std::pair<std::string, RawFactoryPtr> ;
	private:
		std::map<std::string, RawFactory *> factories_;
	public:

		void Register(const std::string & algorithmName, RawFactory * rawFactory)
		{
			if (factories_.find(algorithmName) == factories_.end())
			{
				auto rawFactoryPtr = std::make_unique<RawFactory>(rawFactory);
				factories_.insert(std::make_pair(algorithmName, rawFactoryPtr));
			}
		}
		RawFactory * Lookup(const std::string & algorithmName)
		{
			auto findIter = factories_.find(algorithmName);
			if (findIter != factories_.end())
			{
				return findIter->second.get();
			}
			return nullptr;
		}
	};
};