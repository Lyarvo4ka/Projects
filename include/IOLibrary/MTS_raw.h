#ifndef MTS_RAW_H
#define MTS_RAW_H

#include "AbstractRaw.h"



typedef unsigned long size_map;

enum ClusterType { FREE_CLUSER = 0, USED_CLUSER = 1 , UNKNOWN_CLUSER = 0xFF};
const int END_CLUSTER = ULONG_MAX;
const int WRONG_CLUSTER = ULONG_MAX - 1;


const int atom_size = 192;
const int offset_0 = 0;
const int offset_1 = 64;
const int offset_2 = 128;

const int offset_count = 3;

int array_offsets[offset_count] = { offset_0, offset_1, offset_2 };

const int diff_count = 5;
DWORD diff_array[diff_count] = { 0x05AB, 0x08d0, 0x11A0, 0x04f0 , 0x4f5a };



class ClusterMap
{
private:
	void clear_map();
	void create_map(size_map map_count);

public:
	ClusterMap();
	ClusterMap(size_map map_count);

	bool load(const std::string & file_map);
	bool save(const std::string & file_map);

	void update(size_map cluster_number , ClusterType cluster_type);

	void set_current( size_map new_current);
	size_map current() const;
	size_map first();
	size_map next();
	
private:
	BYTE * clusterMap_;
	size_map count_;

	size_map first_;
	size_map current_;
	size_map next_;
};



class IOLIBRARY_EXPORT MTS_raw
	: public AbstractRaw
{
	
	static const DWORD ClusterSize = 32768;
public:

	MTS_raw(const std::string & file_name, const std::string output_folder);
	~MTS_raw();

	void execute() override;

	bool isHeader(const BYTE * buffer) const;
	bool ReadCluster(BYTE * buffer, DWORD cluster_size, size_map cluster_number);
	bool WriteCluster(HANDLE & hWrite, BYTE * buffer, DWORD cluster_size);
private:
	std::string folder_;

	ClusterMap * cluster_map_;

};

bool isPresentInArray(DWORD diff_value);
void IOLIBRARY_EXPORT get_difference(const std::string & file_name, const DWORD packed_size);


#endif