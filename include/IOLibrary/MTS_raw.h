#ifndef MTS_RAW_H
#define MTS_RAW_H

#include "AbstractRaw.h"

enum ClusterType { FREE = 0, USED = 1 };


class MTS_raw
	: public AbstractRaw
{
	
	static const DWORD ClusterSize = 131072;
	static const LONGLONG EndCluster = -1;
public:

	MTS_raw(const std::string & file_name, const std::string output_folder);
	~MTS_raw();

	//LONGLONG findHeader(LONGLONG start_offset)
	//{

	//}
	void execute() override;


	//void createClusterMap(LONGLONG cluster_count);
	//void ChangeClusterMap(LONGLONG cluster_number, ClusterType cluster_type);

	//DWORD readCluster(DWORD cluster_number , BYTE * pData);

	//LONGLONG getFirstCluster();
	//LONGLONG getNextCluster();

private:
	std::string folder_;
	LONGLONG first_;
	LONGLONG current_;
	LONGLONG next_;

};

class ClusterMap
{
private:
	void clear_map()
	{
		if (clusterMap_)
		{
			delete [] clusterMap_;
			clusterMap_ = nullptr;
		}

	}
	void create_map( DWORD map_count)
	{
		clear_map();
		clusterMap_ = new BYTE[map_count];
	}

public:
	ClusterMap();

	bool save( std::string & file_map )
	{
		//IO::	
	}
	bool load( std::string & file_map)
	{
		HANDLE hFile = INVALID_HANDLE_VALUE;
		if ( !IO::open_read(hFile , file_map))
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

		return IO::read_all(hFile , clusterMap_ , count_ );
	}
private:
	BYTE * clusterMap_;
	DWORD count_;
};

#endif