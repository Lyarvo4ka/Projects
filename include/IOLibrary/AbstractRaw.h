#ifndef ABSTRACT_RAW_H
#define ABSTRACT_RAW_H

#include "IODevice.h"
#include <memory>

namespace IO
{
	using BufferPtr = std::unique_ptr<Buffer>;
	static BufferPtr BufferFactory(const ByteArray data,  uint32_t data_size)
	{
		return std::make_unique<Buffer>(data,data_size);
	}
	struct Header_t
	{
		BufferPtr header_data;
		uint32_t header_offset;

		Header_t(ByteArray data, uint32_t data_size)
			: header_data (BufferFactory(data , data_size))
		{

		}
	};



	using HeaderPtr = std::shared_ptr<Header_t>;

	static HeaderPtr HeaderFactory(ByteArray data, uint32_t data_size)
	{
		return std::make_shared<Header_t>(Header_t(data, data_size));
	}


	class HeaderBase
	{
	private:
		std::list<HeaderPtr> listHeaders_;
	public:
		void addHeader(HeaderPtr new_header)
		{
			listHeaders_.push_back(new_header);
		}
		HeaderPtr findHeader(const ByteArray data)
		{
			for (auto theHeader : listHeaders_)
			{
				if (memcmp(	theHeader->header_data->data + theHeader->header_offset, 
							data, 
							theHeader->header_data->data_size) == 0)
					return theHeader;
			}
			return nullptr;
		}
	};



	class AbstractRaw
	{
	public:
		
		virtual void execute(HeaderPtr header, const uint64_t & header_offset) = 0;


	};

	class StandartRaw
		: public AbstractRaw
	{
	private:
		IODevicePtr device_;
		uint32_t block_size_;
		uint32_t sector_size_;
	public:
		StandartRaw(IODevicePtr device)
			:device_(device)
		{

		}
		void setBlockSize(const uint32_t block_size)
		{
			this->block_size_ = block_size;
		}
		void setSectorSize(const uint32_t sector_size)
		{
			this->sector_size_ = sector_size;
		}
		HeaderPtr findHeaderAndOffset(const uint64_t start_offset, uint64_t & header_offset)
		{
			return nullptr;
		}
		void execute(HeaderPtr header, const uint64_t & header_offset) override
		{
			if (!device_->Open(OpenMode::OpenRead))
			{
				wprintf(L"Error to open.\n");	// ????????
				return;
			}

			uint64_t offset = (uint64_t)0x0;
			uint64_t header_offset = 0;
			uint32_t counter = 0;
			while (true)
			{
				if (!findHeaderAndOffset(offset, header_offset))
				{
					wprintf(L"Not Found Header\n");
					break;
				}

				auto target_file = target_folder + std::to_wstring(counter++) + L".mts";
				offset = SaveToFile(header_offset, target_file);
				offset += sector_size_;

			}

		}

	};


};
//class Header_t
//{
//public:
//
//
//};





/*
class AbstractRaw
{
public:
	AbstractRaw( const std::string & file_name  )
		: hSource_( INVALID_HANDLE_VALUE )
		, bReady_( false )
	{
		bReady_ = IO::open_read( hSource_ , file_name );
	}
	AbstractRaw( const DWORD drive_number  )
		: hSource_( INVALID_HANDLE_VALUE )
		, bReady_( false )
	{
		std::string drive_path( drivePathFromNumber( drive_number ) );
		bReady_ = IO::open_read( hSource_ , drive_path );
	}
	virtual ~AbstractRaw()
	{
		close();
	}
	bool isReady() const
	{
		return bReady_;
	}
	void close()
	{
		if ( hSource_ != INVALID_HANDLE_VALUE )
		{
			CloseHandle( hSource_ );
			hSource_ = INVALID_HANDLE_VALUE;
			bReady_ = false;
		}
	}
	HANDLE * getHandle() 
	{
		return &hSource_;
	}
	virtual void execute() = 0;
private:
	HANDLE hSource_;
	bool bReady_;
};
*/
#endif
