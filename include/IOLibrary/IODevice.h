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
		virtual uint32_t read_data(uint8_t * buffer, uint32_t read_size) = 0;
	};

	class File
		: public IODevice
	{
	private:
		HANDLE hFile_;
	public:
		bool open(const std::wstring & file_name, OpenMode openMode) override
		{
			::CreateFile( file_name.c_str(), 
						  GENERIC_READ | GENERIC_WRITE,
						  FILE_SHARE_READ | FILE_SHARE_WRITE,
						  NULL,
					      static_cast<DWORD>( openMode ), 
						  0,
						  NULL);
		}
		void set_position(uint64_t offset) override {};

		uint32_t read_data(uint8_t * buffer, uint32_t read_size) override
		{
			uint32_t bytes_read = 0;
			//if ( !::ReadFile(hFile_ , buffer , read_size , &bytes_read) )
		};

	};
}
