#ifndef MTS_RAW_H
#define MTS_RAW_H

#include "AbstractRaw.h"



typedef unsigned long size_map;

enum ClusterType { FREE_CLUSER = 0, USED_CLUSER = 1 , UNKNOWN_CLUSER = 0xFF};
const int END_CLUSTER = ULONG_MAX;
const int WRONG_CLUSTER = ULONG_MAX - 1;

class ClusterMap
{
private:
	void clear_map();
	void create_map(size_map map_count);

public:
	ClusterMap();

	bool load(const std::string & file_map);
	bool save(const std::string & file_map);

	
	void set_current( size_map new_current);
	size_map current() const;
	size_map first() const;
	size_map next();
	
private:
	BYTE * clusterMap_;
	size_map count_;

	size_map first_;
	size_map current_;
	size_map next_;
};



class MTS_raw
	: public AbstractRaw
{
	
	static const DWORD ClusterSize = 131072;
public:

	MTS_raw(const std::string & file_name, const std::string output_folder);
	~MTS_raw();

	void execute() override;
	//void createClusterMap(LONGLONG cluster_count);
	//void ChangeClusterMap(LONGLONG cluster_number, ClusterType cluster_type);

	//DWORD readCluster(DWORD cluster_number , BYTE * pData);

	//LONGLONG getFirstCluster();
	//LONGLONG getNextCluster();

private:
	std::string folder_;

};


#endif