#pragma once
#include "QuickTime.h"
using namespace IO;


class GoPro

{
	const uint16_t val_0x4750 = 0x5047;
	const uint8_t jpg_sing[3] = { 0xFF, 0xD8 , 0xFF };
private:
	IO::IODevice * device_;
	uint32_t cluster_size_;
public:
	GoPro(IO::IODevice * device)
		: device_(device)
		, cluster_size_(0)
	{

	}
	~GoPro()
	{
		if (device_)
		{
			delete device_;
			device_ = nullptr;
		}
	}
	void setClusterSize(const uint32_t cluster_size)
	{
		this->cluster_size_ = cluster_size;
	}
	bool ReadCluster(const uint32_t number , Buffer * buffer)
	{
		if (!buffer)
			return false;
		uint64_t offset = (uint64_t)number * (uint64_t)cluster_size_;
		if (offset >= device_->Size())
			return false;

		device_->setPosition(offset);
		auto bytes_read = device_->ReadData(buffer->data, buffer->data_size);
		if (bytes_read != cluster_size_)
			return false;
		return true;
	}
	uint32_t SaveFile_WithoutLRV(const uint32_t cluster_number, path_string target_name)
	{
		File write_file(target_name);
		if (!write_file.Open(OpenMode::Create))
		{
			wprintf(L"Error create file.\n");
			return cluster_number;
		}

		uint32_t number = cluster_number;
		Buffer buffer(this->cluster_size_);
		if (!ReadCluster(number++, &buffer))
			return number;

		write_file.WriteData(buffer.data, buffer.data_size);

		while (ReadCluster(number, &buffer) )
		{
			if (memcmp(buffer.data, jpg_sing, 3) == 0)
				break;

			if ( calc0x4750(&buffer) < 10 )
				write_file.WriteData(buffer.data, buffer.data_size);

			++number;
		}
		return number;
	}
	uint32_t calc0x4750(const Buffer * buffer)
	{
		uint32_t val_pos = 0;
		uint32_t counter = 0;
		while (val_pos < buffer->data_size -1 )
		{
			uint16_t* buff_val = (uint16_t*)(buffer->data + val_pos);
			if (*buff_val == val_0x4750)
				++counter;

			++val_pos;
		}
		return counter;
	}
	void execute(const path_string & folder)
	{
		if (!device_->Open(OpenMode::OpenRead))
		{
			wprintf(L"Error open.\n");
			return;
		}
		if (cluster_size_ == 0)
		{
			wprintf(L"Cluster size is 0");
			return ;
		}

		uint32_t counter = 0;

		uint32_t cluster_number = 0;
		Buffer buffer(cluster_size_);
		while (ReadCluster(cluster_number , &buffer) )
		{
			qt_block_t * pQt_block = (qt_block_t *)buffer.data;
			if (IO::isQuickTimeHeader(pQt_block))
			{
				path_string target_name = MakeFilePath(folder, counter++, L".mp4");

				cluster_number = SaveFile_WithoutLRV(cluster_number, target_name);

			}
			++cluster_number;
		}

	}

};