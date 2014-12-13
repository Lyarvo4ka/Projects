#include "MTS_raw.h"

#include "constants.h"


ClusterMap::ClusterMap() 
: clusterMap_(nullptr)
, count_(0)
, first_(WRONG_CLUSTER)
, current_(WRONG_CLUSTER)
, next_(WRONG_CLUSTER)
{

}
ClusterMap::ClusterMap(size_map map_count)
:ClusterMap()
{
	this->create_map(map_count);
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
	memset(clusterMap_ , FREE_CLUSER , count_);
}

bool ClusterMap::load(const std::string & file_map)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	if (!IO::open_read(hFile, file_map))
	{
		printf("Error. Open file to LOAD.\r\n");
		return false;
	}

	count_ = (size_map)IO::getFileSize(hFile);
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

void ClusterMap::update(size_map cluster_number, ClusterType cluster_type)
{
	if ( cluster_number < count_ )
		clusterMap_[cluster_number] = cluster_type;
}
void ClusterMap::set_current(size_map new_current)
{
	current_ = new_current;
}

size_map ClusterMap::current() const
{
	return current_;
}

size_map ClusterMap::first() 
{
	for (size_map iCluster = 0; iCluster < count_; ++iCluster)
	{
		if (clusterMap_[iCluster] == FREE_CLUSER)
		{
			first_ = iCluster;
			return first_;
		}
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




//////////////////////////////////////////////////////////////////////////

MTS_raw::MTS_raw(const std::string & file_name, const std::string output_folder) : AbstractRaw(file_name)
, folder_(output_folder)
, cluster_map_(nullptr)
{

}

MTS_raw::~MTS_raw()
{
	if (!cluster_map_)
	{
		delete[] cluster_map_;
		cluster_map_ = nullptr;
	}
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
	size_map cluster_count = file_size / ClusterSize;

	cluster_map_ = new ClusterMap(cluster_count);

	BYTE buffer[ClusterSize]; 
	BYTE prev_buffer[ClusterSize];
	BYTE new_buffer[ClusterSize];

	size_map cur_cluster = cluster_map_->first();

	DWORD counter = 0;

	DWORD bytesWritten = 0;


	cur_cluster = 254;
	while (true)
	{
		cluster_map_->set_current(cur_cluster);
		if ( !this->ReadCluster(buffer, ClusterSize, cur_cluster) )
		{
			printf("Error. Read cluster #%d\r\n", cur_cluster);
			break;
		}

		if ( this->isHeader(buffer) )
		{
			size_map header_cluster = cur_cluster;
			printf("Found mts header cluster #%d\r\n", header_cluster);
			auto target_name = IO::file_path_number(folder_, counter++ , ".mts");

			HANDLE hWrite = INVALID_HANDLE_VALUE;
			if ( !IO::create_file(hWrite , target_name) )
			{
				printf("Error. Couldn't create file %s.\r\n", target_name.c_str());
				break;
			}

			if ( !this->WriteCluster(hWrite , buffer , ClusterSize) )
				break;
			cluster_map_->update(header_cluster, USED_CLUSER);

			size_map next_cluster = 0;
			memcpy(prev_buffer , buffer , ClusterSize);

			int cur_offset = 0;
			int cluster_counter = 1;
			DWORD cur_value = 0;
			DWORD prev_value = 0;

			while (true )
			{
				cur_offset = array_offsets[cluster_counter%offset_count];

				next_cluster = cluster_map_->next();
				if (next_cluster == 21758)
				{
					int k = 1;
					k =2;
				}
				cluster_map_->set_current(next_cluster);
				if (!this->ReadCluster(new_buffer, ClusterSize, next_cluster))
				{
					printf("Error. Read cluster #%d\r\n", next_cluster);
					break;
				}

				DWORD * prev_value_ptr = (DWORD *)&prev_buffer[ClusterSize - (atom_size - cur_offset)];
				prev_value = *prev_value_ptr;
				to_big_endian(prev_value);


				DWORD * cur_value_ptr = (DWORD *)& new_buffer[cur_offset];
				cur_value = *cur_value_ptr;
				to_big_endian( cur_value);

				DWORD difference = cur_value - prev_value;
				
				if (isPresentInArray(difference))
				{
					if (!this->WriteCluster(hWrite, new_buffer, ClusterSize))
						break;
					cluster_map_->update(next_cluster, USED_CLUSER);
					memcpy(prev_buffer, new_buffer, ClusterSize);
					++cluster_counter;
				}

			}



		}
		cluster_map_->set_current(cur_cluster);
		cur_cluster = cluster_map_->next();

	}
}

bool MTS_raw::isHeader(const BYTE * buffer) const
{
	return ( memcmp( & buffer[Signatures::mts_header_offset] , Signatures::mts_header , Signatures::mts_header_size) == 0);
}

bool MTS_raw::ReadCluster(BYTE * buffer, DWORD cluster_size, size_map cluster_number)
{
	DWORD bytesRead = 0;

	auto offset = (LONGLONG)cluster_number * (LONGLONG)cluster_size ;
	offset += 25230848;
	IO::set_position(*this->getHandle(), offset);

	bool bResult = IO::read_block(*this->getHandle() , buffer , cluster_size , bytesRead ) ;
	if (!bResult || (bytesRead == 0))
	{
		printf("Error. Write to file.\r\n");
		return false;
	}

	return true;

}
bool MTS_raw::WriteCluster(HANDLE & hWrite, BYTE * buffer, DWORD cluster_size)
{
	DWORD bytesWritten = 0;
	bool bResult = IO::write_block(hWrite , buffer , cluster_size , bytesWritten) ;
	if (!bResult || (bytesWritten == 0) )
	{
		printf("Error. Write to file.\r\n");
		return false;
	}

	return true;

}


bool isPresentInArray(DWORD diff_value)
{
	for (int iArray = 0; iArray < diff_count ; ++iArray)
	if (diff_array[iArray] == diff_value)
		return true;
	return false;
}

void get_difference(const std::string & file_name, const DWORD packed_size)
{

}