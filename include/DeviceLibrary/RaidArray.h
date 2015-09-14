#ifndef RAID_H
#define RAID_H

#include "Devices.h"

enum RaidLevelID { raid5 };

typedef ULONGLONG LBA;

class RaidArray
{
	typedef std::vector<DevicePtr> DiskArray;

private:
	DiskArray disk_array_;
	DWORD block_size_;

public:
	void set_block_size(DWORD block_size)
	{
		block_size_ = block_size;
	}
	void add_disk(DevicePtr disk_device)
	{
		disk_array_.push_back(disk_device);
	}
	void add_file(DevicePtr file_device)
	{
		disk_array_.push_back(file_device);
	}
	DWORD block_size() const
	{
		return block_size_;
	}
	DevicePtr get_device(DWORD number) const
	{
		return (disk_array_.size() < number) ? disk_array_.at(number) : nullptr;
	}
	int disk_count() const
	{
		return disk_array_.size();
	}

	virtual bool read_block(LBA block_number, BYTE * data_buffer) = 0;
	virtual bool write_block(LBA block_number, BYTE * data_buffer) = 0;

};
class Raid5
	: public RaidArray
{
public:
	bool read_block(LBA block_number, BYTE * data_buffer) override
	{
		return false;
	}
	bool write_block(LBA block_number, BYTE * data_buffer) override
	{
		return false;
	}
};



#endif