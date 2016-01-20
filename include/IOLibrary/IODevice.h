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
		virtual bool open(const std::wstring & , OpenMode) = 0;
		virtual bool is_open() = 0;
		virtual void set_position(uint64_t offset) = 0;
		virtual uint32_t read_data(uint8_t * data, uint32_t read_size) = 0;
	};

	class FileDevice
		: public IODevice
	{
	private:
		HANDLE hFile_;
		uint64_t offset_;
	public:
		bool open(const std::wstring & file_name, OpenMode openMode) override
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

			::CreateFile( file_name.c_str(), 
						  GENERIC_READ | GENERIC_WRITE,
						  FILE_SHARE_READ | FILE_SHARE_WRITE,
						  NULL,
						  win_open_mode,
						  0,
						  NULL);
		}
		void set_position(uint64_t offset) override 
		{
			offset_ = offset;
			LARGE_INTEGER liPos = { offset_ };
			::SetFilePointerEx(hFile_, liPos, NULL, FILE_BEGIN);

		};

		uint32_t read_data(uint8_t * data, uint32_t read_size) override
		{
			uint32_t bytes_read = 0;
			//if ( !::ReadFile(hFile_ , buffer , read_size , &bytes_read) )
		};

	};
}
