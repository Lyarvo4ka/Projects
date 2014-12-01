#include "MTS_raw.h"


ClusterMap::ClusterMap() 
: clusterMap_(nullptr)
, count_(0)
, first_( UNKNOWN_CLUSER )
, current_( UNKNOWN_CLUSER )
, next_( UNKNOWN_CLUSER )
{

}

void ClusterMap::clear_map()
{
	if (clusterMap_)
	{
		delete[] clusterMap_;
		clusterMap_ = nullptr;
	}
	count_ = 0;
}

void ClusterMap::create_map(size_map map_count)
{
	clear_map();
	clusterMap_ = new BYTE[map_count];
	count_ = map_count;
}

bool ClusterMap::load(const std::string & file_map)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	if (!IO::open_read(hFile, file_map))
	{
		printf("Error. Open file to LOAD.\r\n");
		return false;
	}

	count_ = IO::getFileSize(hFile);
	if (count_ == 0)
	{
		printf("Error. File is NULL .\r\n");
		return false;
	}

	clear_map();
	create_map(count_);

	bool bResult = IO::read_all(hFile, clusterMap_, count_);
	CloseHandle(hFile);

	return bResult;
}

bool ClusterMap::save(const std::string & file_map)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	if (!IO::create_file(hFile, file_map))
	{
		printf("Error. Create file.\r\n");
		return false;
	}
	bool bResult = IO::write_all(hFile, clusterMap_, count_);
	CloseHandle(hFile);

	return bResult;
}

void ClusterMap::set_current(size_map new_current)
{
	current_ = new_current;
}

size_map ClusterMap::current() const
{
	return current_;
}

size_map ClusterMap::first() const
{
	for (size_map iCluster = 0; iCluster < count_, ++iCluster)
	{
		if (clusterMap_[iCluster] == FREE_CLUSER)
			return iCluster;
	}
	return END_CLUSTER;
}

size_map ClusterMap::next()
{
	bool bLastCluster = true;
	for (next_ = (current_ + 1); next_ < count_; ++next_)
	{
		if (clusterMap_[next_] == ClusterType::FREE_CLUSER)
		{
			bLastCluster = false;
			break;
		}
	}

	return (!bLastCluster) ? next_ : END_CLUSTER;
}



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

//}
//

