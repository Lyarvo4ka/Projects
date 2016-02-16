#pragma once

#include <stdint.h>
#include <windows.h>
#include <string>

namespace IO
{
	using path_string = std::wstring ;
	enum class OpenMode : uint32_t {OpenRead, OpenWrite, Create} ;

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
	private:
		uint32_t drive_number_;
		uint32_t bytes_per_sector_;
		uint64_t number_sectors_;
		path_string path_;
	public:
		BlockDevice(const path_string & path)
			: drive_number_(0)
			, number_sectors_(0)
			, bytes_per_sector_(0)
			, path_(path)
		{

		}
		virtual uint32_t ReadBlock(int8_t * data, uint32_t read_size) = 0;
		virtual uint32_t WriteBlock(uint8_t * data, uint32_t read_size) = 0;

		//void setPath(const path_string & new_path)
		//{
		//	path_ = new_path;
		//}
		path_string getPath() const
		{
			return path_;
		}
		void setDriveNumber(uint32_t drive_number)
		{
			drive_number_ = drive_number;
		}
		uint32_t getDriveNumber() const
		{
			return drive_number_;
		}
		void setNumberSectors(uint64_t number_sectors)
		{
			number_sectors_ = number_sectors;
		}
		uint64_t getNumberSectors() const
		{
			return number_sectors_;
		}
		void setBytesPerSector(uint32_t bytes_per_sector)
		{
			bytes_per_sector_ = bytes_per_sector;
		}
		uint32_t getBytesPerSector() const
		{
			return bytes_per_sector_;
		}
	};

	class DiskDevice
		: public BlockDevice
	{
	public:
		DiskDevice(const path_string & path)
			: BlockDevice( path )
		{

		}

	};

	class FileDevice
		: public BlockDevice
	{
	public:
		FileDevice(const path_string & path)
			: BlockDevice(path)
		{

		}

	};

}
