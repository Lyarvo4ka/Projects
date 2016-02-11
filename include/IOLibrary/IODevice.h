#pragma once

#include <stdint.h>
#include <windows.h>
#include <string>

namespace IO
{
	enum class OpenMode : uint32_t {OpenRead, OpenWrite, Create} ;

	class IODevice
	{
	public:
		virtual bool open(OpenMode) = 0;
		virtual void close() = 0;
		virtual bool is_open() = 0;
		virtual void set_position(uint64_t offset) = 0;
		virtual uint32_t read_data(uint8_t * data, uint32_t read_size) = 0;
		virtual uint32_t write_data(uint8_t * data, uint32_t read_size) = 0;
		virtual uint64_t size() const = 0;
	};

	class IBlockDevice
	{
	public:
		virtual uint32_t read_block()  = 0;
		//virtual 
	};

	class File
		: public IODevice
	{
	private:
		HANDLE hFile_;
		uint64_t position_;
		uint64_t size_;
		std::wstring file_name_;
		bool bOpen_;
	public:
		File(const std::wstring & file_name)
			: hFile_(INVALID_HANDLE_VALUE)
			, position_( 0 )
			, size_(0)
			, file_name_(file_name)
			, bOpen_(false)
		{

		}

		bool open( OpenMode openMode) override
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

		void set_position(uint64_t offset) override 
		{
			position_ = offset;
			LARGE_INTEGER liPos = { position_ };
			::SetFilePointerEx(hFile_, liPos, NULL, FILE_BEGIN);

		};

		uint32_t read_data(uint8_t * data, uint32_t read_size) override
		{
			uint32_t bytes_read = 0;
			//if ( !::ReadFile(hFile_ , buffer , read_size , &bytes_read) )
		};

	};


	class PysicalDrive
	{
	private:
		uint32_t drive_number_;
		uint32_t bytes_per_sector_;
		uint64_t number_sectors_;
//		std::wstring path_;
	public:
		//PysicalDrive(const std::string path)
		//	: drive_number_(0)
		//	, number_sectors_(0)
		//	, bytes_per_sector_(0)
		//	, path_(path)
		//{

		//}


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
}
