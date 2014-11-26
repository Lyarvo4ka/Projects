#include "MTS_raw.h"



MTS_raw::MTS_raw(const std::string & file_name, const std::string output_folder) : AbstractRaw(file_name)
, folder_(output_folder)
//, pClusterMap_(nullptr)
//, clusterCount_(0)
//, curCluster_(0)
//, nextCluster_(0)
{

}

MTS_raw::~MTS_raw()
{
	//if (!pClusterMap_)
	//{
	//	delete[] pClusterMap_;
	//	pClusterMap_ = nullptr;
	//}
}

void MTS_raw::execute()
{
	if (!this->isReady())
	{
		printf("Error source device not ready.");
		return;
	}
	HANDLE * pHandle = this->getHandle();

	LONGLONG file_size = IO::getFileSize(*pHandle);
	LONGLONG cluster_count = file_size / ClusterSize;

	while (true)
	{

	}
}
//
//void MTS_raw::createClusterMap(LONGLONG cluster_count)
//{
//	clusterCount_ = cluster_count;
//	pClusterMap_ = new BYTE[clusterCount_];
//	memset(pClusterMap_, FREE, clusterCount_);
//}
//
//void MTS_raw::ChangeClusterMap(LONGLONG cluster_number, ClusterType cluster_type)
//{
//	pClusterMap_[cluster_number] = cluster_type;
//}
//
//DWORD MTS_raw::readCluster(DWORD cluster_number, BYTE * pData)
//{
//	IO::set_position(*this->getHandle(), (LONGLONG)cluster_number*ClusterSize);
//
//	DWORD bytesRead = 0;
//
//	if (!IO::read_block(*this->getHandle(), pData, ClusterSize, bytesRead))
//		return 0;
//
//	return bytesRead;
//}
//
//LONGLONG MTS_raw::getFirstCluster()
//{
//	for (curCluster_ = 0; curCluster_ < clusterCount_; ++curCluster_)
//	{
//		if (pClusterMap_[curCluster_] == ClusterType::FREE)
//			break;
//	}
//	return curCluster_;
//}
//
//LONGLONG MTS_raw::getNextCluster()
//{
//	bool bLastCluster = true;
//	for (nextCluster_ = (curCluster_ + 1); nextCluster_ < clusterCount_; ++nextCluster_)
//	{
//		if (pClusterMap_[nextCluster_] == ClusterType::FREE)
//		{
//			bLastCluster = false;
//			break;
//		}
//	}
//
//	return (!bLastCluster) ? nextCluster_ : EndCluster;
//}
//

