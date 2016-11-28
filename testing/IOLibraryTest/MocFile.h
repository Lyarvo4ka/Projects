#pragma once

#include "IOLibrary/AbstractRaw.h"

class MocFile
	: public IO::File
{
private:
	IO::DataArray::Ptr data_;
	uint64_t offset_ = 0;
public:
	MocFile(uint32_t file_size)
		: data_(IO::makeDataArray(file_size))
	{
	}
	bool Open(IO::OpenMode open_mode) override
	{
		return true;
	}
	void Close() override
	{

	}
	bool isOpen() override
	{
		return true;
	}
	void setPosition(uint64_t offset) override
	{
		offset_ = offset;
	}
	uint32_t ReadData(IO::ByteArray data, uint32_t read_size) override
	{
		if (offset_ >= data_->size())
			return 0;
		memcpy(data, data_->data() + offset_, read_size);
		return read_size;
	}
	virtual uint32_t WriteData(IO::ByteArray data, uint32_t read_size) override
	{
		if (offset_ >= data_->size())
			return 0;

		memcpy(data_->data() + offset_, data, read_size);
		return read_size;
	}
	virtual uint64_t Size() const
	{
		return data_->size();
	}

};
