#pragma once
#include "physicaldrive.h"
#include <string>

namespace IO
{

	class IODevice
	{
	public:
		virtual ~IODevice() = 0 {};
		virtual bool Open(OpenMode) = 0;
		virtual void Close() = 0;
		virtual bool isOpen() = 0;
		virtual void setPosition(uint64_t offset) = 0;
		virtual uint32_t ReadData(uint8_t * data, uint32_t read_size) = 0;
		virtual uint32_t WriteData(uint8_t * data, uint32_t read_size) = 0;
		virtual uint64_t Size() const = 0;
	};


	class File
		: public IODevice
	{
	private:
		HANDLE hFile_;
		uint64_t position_;
		uint64_t size_;
		path_string file_name_;
		bool bOpen_;
	public:
		File(const path_string & file_name)
			: hFile_(INVALID_HANDLE_VALUE)
			, position_( 0 )
			, size_(0)
			, file_name_(file_name)
			, bOpen_(false)
		{

		}

		bool Open( OpenMode openMode) override
		{
			uint32_t win_open_mode = 0;

			switch (openMode)
			{
			case OpenMode::OpenRead:
			case OpenMode::OpenWrite:
				win_open_mode = OPEN_EXISTING;
			case OpenMode::Create:
				win_open_mode = CREATE_ALWAYS;
			}

			::CreateFile( file_name_.c_str(), 
						  GENERIC_READ | GENERIC_WRITE,
						  FILE_SHARE_READ | FILE_SHARE_WRITE,
						  NULL,
						  win_open_mode,
						  0,
						  NULL);
		}

		void setPosition(uint64_t offset) override 
		{
			position_ = offset;
			LARGE_INTEGER liPos = { position_ };
			::SetFilePointerEx(hFile_, liPos, NULL, FILE_BEGIN);

		};

		uint32_t ReadData(uint8_t * data, uint32_t read_size) override
		{
			uint32_t bytes_read = 0;
			//if ( !::ReadFile(hFile_ , buffer , read_size , &bytes_read) )
		};

	};

	class BlockDevice
		: public IODevice
	{
	public:
		virtual uint32_t ReadBlock(int8_t * data, uint32_t read_size) = 0;
		virtual uint32_t WriteBlock(uint8_t * data, uint32_t read_size) = 0;

	};

	class DiskDevice
		: public BlockDevice
	{
	private:
		PhysicalDrive *physical_drive_;
	public:
		DiskDevice(PhysicalDrive * physical_drive)
			:physical_drive_(physical_drive)
		{	

		}

	};

	//class FileDevice
	//	: public BlockDevice
	//{
	//public:
	//	FileDevice(const path_string & path)
	//		: BlockDevice(path)
	//	{

	//	}

	//};

}
