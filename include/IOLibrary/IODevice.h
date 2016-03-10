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
				break;
			case OpenMode::Create:
				win_open_mode = CREATE_ALWAYS;
				break;
			}

			hFile_ = ::CreateFile(file_name_.c_str(),
				GENERIC_READ | GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				win_open_mode,
				0,
				NULL);

			if (hFile_ != INVALID_HANDLE_VALUE)
			{
				bOpen_ = true;
				LARGE_INTEGER liSize = { 0 };
				::GetFileSizeEx(hFile_, &liSize);
				size_ = liSize.QuadPart;
			}
			else
				bOpen_ = false;

			return bOpen_;
		}
		
		void Close() override
		{
			if (hFile_ != INVALID_HANDLE_VALUE)
			{
				::CloseHandle(hFile_);
				hFile_ = INVALID_HANDLE_VALUE;
			}
			bOpen_ = false;

		}
		bool isOpen()
		{
			return bOpen_;
		}

		void setPosition(uint64_t offset) override 
		{
			position_ = offset;
			LARGE_INTEGER liPos = { position_ };
			::SetFilePointerEx(hFile_, liPos, NULL, FILE_BEGIN);

		};

		uint32_t ReadData(uint8_t * data, uint32_t read_size) override
		{
			if (data == nullptr)
				return 0;
			if (read_size == 0)
				return 0;

			DWORD bytes_read = 0;


			if (!::ReadFile(hFile_, data, read_size, &bytes_read, NULL))
				return 0;
			return bytes_read;
		};

		uint32_t WriteData(uint8_t * data, uint32_t write_size) override
		{
			if (data == nullptr)
				return 0;
			if (write_size == 0)
				return 0;

			DWORD bytes_written = 0;


			if (!::WriteFile(hFile_, data, write_size, &bytes_written, NULL))
				return 0;
			return bytes_written;
		};

		uint64_t Size() const override
		{
			return size_;
		}
		void setSize(uint64_t new_size)
		{
			if (size_ != new_size)
			{
				size_ = new_size;
				LARGE_INTEGER li = { size_ };
				::SetFilePointerEx(hFile_, li, NULL, FILE_BEGIN);
			}
		}
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
		PhysicalDrivePtr physical_drive_;
	public:
		DiskDevice(PhysicalDrivePtr physical_drive)
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
