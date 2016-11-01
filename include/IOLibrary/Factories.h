#pragma once

#include "iolibrary_global.h"
#include "IODevice.h"
#include <map>
namespace IO
{
	//class RawAlgorithm;

	//class IOLIBRARY_EXPORT RawFactory
	//{
	//public:
	//	virtual ~RawFactory() {}
	//	virtual RawAlgorithm * createRawAlgorithm(IODevicePtr) = 0;
	//};

	//using RawFactoryPtr = std::unique_ptr<RawFactory>;


	//class IOLIBRARY_EXPORT StandartRawFactory
	//	: public RawFactory
	//{
	//public:
	//	RawAlgorithm * createRawAlgorithm(IODevicePtr device) override;
	//};



	//class IOLIBRARY_EXPORT RawFactoryManager
	//{
	//	using FactoryMap = std::map<std::string, RawFactoryPtr> ;
	//	using FactoryPair = std::pair<std::string, RawFactoryPtr> ;
	//private:
	//	FactoryMap factories_;
	//public:

	//	void Register(const std::string & algorithmName, RawFactory * rawFactory);
	//	RawFactory * Lookup(const std::string & algorithmName);
	//};
};