#ifndef ABSTRACT_RAW_H
#define ABSTRACT_RAW_H


#include "iofunctions.h"
#include "IODevice.h"
#include <memory>

#include "utility.h"

namespace IO
{
	
	//using BufferPtr = std::unique_ptr<Buffer>;
	//static BufferPtr BufferFactory(const ByteArray data, uint32_t data_size)
	//{
	//	return std::make_unique<Buffer>(data, data_size);
	//}
	class DataArray
	{
		ByteArray data_;
		uint32_t size_;
	public:
		DataArray(const ByteArray data, uint32_t size)
			: data_(data)
			, size_(size)
		{

		}

		DataArray(const uint32_t size)
			:data_(nullptr)
			,size_(size)
		{
			if (size > 0)
			{
				data_ = new uint8_t[size];
			}
		}
		~DataArray()
		{
			if (data_)
			{
				delete[] data_;
				data_ = nullptr;
			}
		}
		uint32_t size() const
		{
			return size_;
		}
		ByteArray data()
		{
			return data_;
		}
		ByteArray data() const
		{
			return data_;
		}
		operator ByteArray()
		{
			return data_;
		}
		bool compare( const ByteArray data , uint32_t size , uint32_t offset = 0) 
		{
			if (size >= this->size())
			{
				
				if (std::memcmp(data_ , data + offset, this->size()) == 0)
					return true;
			}
			return false;
		}
		bool compare( const DataArray & dataArray , uint32_t offset = 0)
		{

			return compare(dataArray.data(), dataArray.size(), offset);
		}
	};

	using SignatureArray = std::vector<DataArray>;

	class SignatureOffset
	{
		uint32_t signature_offset_ = 0;
		SignatureArray signatureArray_;

	public:
		SignatureOffset( DataArray & dataArray, uint32_t signature_offset = 0)
		{
			signature_offset_ = signature_offset;
			addSignature(dataArray);
		}
		void addSignature(const DataArray & dataArray)
		{
			signatureArray_.emplace_back(dataArray);
		}
		void addSignature(ByteArray data, uint32_t size)
		{
			signatureArray_.emplace_back(DataArray(data, size));
		}
		bool FindSignature(const ByteArray data, uint32_t size)
		{
			for (auto & theSignature : signatureArray_)
			{
				if (theSignature.compare(data, size, signature_offset_))
					return true;
			}
			return false;
		}
	};

	using HeaderArray = std::vector<SignatureOffset>;
	class FileFormat
	{
		HeaderArray headers_;
		std::string formatName_;
		path_list ext_list_;
	public:
		FileFormat(const std::string & formatName)
			: formatName_(formatName)
		{

		}
		void add(SignatureOffset & signAndOffset)
		{
			headers_.emplace_back(signAndOffset);
		}

		bool compareWithAllHeaders(ByteArray data, uint32_t size)
		{
			for (auto & theHeader : headers_)
			{
				if (!theHeader.FindSignature(data, size))
					return false;
			}
			return true;
		}
	};

	using FileFormatPtr = std::shared_ptr<FileFormat>;
	static FileFormatPtr MakeFileFormat(const std::string formatName)
	{
		return std::make_shared<FileFormat>(formatName);
	}

	class Header_t	// ??????
	{
		//std::list<BufferPtr> headers_array;	// ??????
		ByteArray header_ = nullptr;
		uint32_t header_size_ = 0;
		uint32_t header_offset = 0;
		ByteArray footer_ = nullptr;
		uint32_t footer_size_ = 0;
		uint32_t add_footer_size = 0;
		uint64_t max_file_size = 0;
	public:
		Header_t(const ByteArray header, uint32_t header_size)
		{
			this->header_size_ = header_size;
			this->header_ = new uint8_t[this->header_size_];
			memcpy(this->header_, header , this->header_size_);
		}
		~Header_t()
		{
			if (header_)
			{
				delete[] header_;
				header_ = nullptr;
			}
			if (footer_)
			{
				delete[] footer_;
				footer_ = nullptr;
			}
		}
		void setHeaderOffset(const uint32_t header_offset)
		{
			this->header_offset = header_offset;
		}
		void setFooter(const ByteArray footer, uint32_t footer_size)
		{
			this->footer_ = new uint8_t[footer_size];
			memcpy(this->footer_, footer, footer_size);
			this->footer_size_ = footer_size;
		}
		void setAddFooterSize(const uint32_t add_footer_size)
		{
			this->add_footer_size = add_footer_size;
		}
		uint32_t getAddFooterSize() const
		{
			return add_footer_size;
		}
		void setMaxFileSize(const uint64_t max_file_size)
		{
			this->max_file_size = max_file_size;
		}
		uint64_t getMaxFileSize() const
		{
			return max_file_size;
		}
		bool isHeader(const ByteArray data)
		{
			//for (auto & header : headers_array)
			//{
			if (memcmp(header_,
				data + header_offset,
				header_size_) == 0)
				return true;

			//}
			return false;
		}
		bool isFooter(const ByteArray data, const uint32_t data_size , uint32_t & footer_pos)
		{
			for (uint32_t iByte = 0; iByte < data_size - footer_size_; ++iByte)
			{
				if (memcmp(footer_, data + iByte, footer_size_) == 0)
				{
					footer_pos = iByte;
					return true;
				}
			}
			return false;
		}
	};
	using HeaderPtr = std::shared_ptr<Header_t>;
	static HeaderPtr HeaderFactory(ByteArray data, uint32_t data_size)
	{
		return std::make_shared<Header_t>(data, data_size);
	}


	class HeaderBase
	{
	private:
		std::list<FileFormatPtr> listHeaders_;
	public:
		void addFileFormat(FileFormatPtr new_file_format)
		{
			listHeaders_.push_back(new_file_format);
		}
		FileFormatPtr find(const ByteArray data , uint32_t size)
		{
			for (auto theHeader : listHeaders_)
			{
				if (theHeader->compareWithAllHeaders(data, size))
					return theHeader;
			}
			return nullptr;
		}
	};

	class RawAlgorithm;

	class SignatureFinder
	{
		IODevicePtr device_;
		uint32_t block_size_ = default_block_size;
		uint32_t sector_size_ = default_sector_size;
		HeaderBase * header_base_;
	public:
		SignatureFinder(IODevicePtr device)
			: device_(device)
		{
			header_base_ = new HeaderBase();
			ByteArray header_data = new uint8_t[Signatures::mxf_header_size];
			std::memcpy(header_data, Signatures::mxf_header, Signatures::mxf_header_size);
			
			DataArray header(header_data, Signatures::mxf_header_size);
			SignatureOffset signOffset(header);
			auto file_format = MakeFileFormat("mxf");
			file_format->add(signOffset);

			header_base_->addFileFormat(file_format);

		}
		~SignatureFinder()
		{
			if (header_base_)
			{
				delete header_base_;
				header_base_ = nullptr;
			}
		}
		void setBlockSize(const uint32_t block_size)
		{
			this->block_size_ = block_size;
		}
		HeaderPtr findHeader(const uint64_t start_offset, uint64_t & header_pos)
		{
			//if (!device_->Open(OpenMode::OpenRead))
			//{
			//	wprintf_s(L"Error open device\n");
			//	return nullptr;
			//}

			//uint64_t file_size = device_->Size();
			//uint64_t offset = start_offset;
			//Buffer buffer(block_size_);
			//uint32_t bytes_read = 0;
			//uint32_t result_offset = 0;

			//while (offset < file_size)
			//{
			//	device_->setPosition(offset);
			//	bytes_read = device_->ReadData(buffer.data, block_size_);
			//	if (bytes_read == 0)
			//	{
			//		printf("Error read drive\r\n");
			//		break;
			//	}
			//	if (auto header_ptr = cmpHeader(buffer, bytes_read, result_offset))
			//	{
			//		header_pos = offset;
			//		header_pos += result_offset;
			//		return header_ptr;
			//	}

			//	offset += bytes_read;
			//}
			return nullptr;
		}

		HeaderPtr cmpHeader(const Buffer & buffer, const uint32_t size, uint32_t header_pos)
		{
			//for (uint32_t iPos = 0; iPos < size; iPos += sector_size_)
			//{
			//	if (auto header_ptr = header_base_->findHeader(buffer.data))
			//	{
			//		header_pos = iPos;
			//		return header_ptr;
			//	}
			//}
			return nullptr;
		}


		RawAlgorithm * createRawAlgorithm(HeaderPtr headerPtr)
		{
			
			return nullptr;
		}

	};

	class FileMake
	{
		path_string folder_;
		uint64_t counter = 0;
	public:
		FilePtr create(const uint64_t offset_value, const path_string & extension)
		{
			if (boost::filesystem::exists(folder_))
			{
				auto ext_folder = addBackSlash(folder_) + extension;
				if (boost::filesystem::exists(ext_folder))
				{
					path_string new_file_name/* = toNumberString(offset_value)*/;
					// create new file name;

					auto file_ptr = makeFilePtr(new_file_name);
				}
			}
		}

	};

	class RawAlgorithm
	{
		virtual uint64_t SaveRawFile(HeaderPtr & header_ptr, const uint64_t header_offset, const path_string & target_name) = 0;
	};

	const uint8_t zbk_header[] = { 0x0F , 0x00 , 0x0B , 0x67 , 0x63 , 0x66 , 0x67 , 0x50 , 0x72 , 0x67 , 0x50 , 0x6C , 0x75 , 0x73 };
	const uint32_t zbk_header_size = SIZEOF_ARRAY(zbk_header);
	const uint8_t zbk_footer[] = { 0x50 , 0x4B , 0x05 , 0x06 , 0x00 , 0x00 , 0x00 , 0x00 };
	const uint32_t zbk_footer_size = SIZEOF_ARRAY(zbk_footer);

	using u8 = unsigned char;
	using u16 = unsigned short;
	struct zbh_header_t
	{
		u16 reserver0;
		u8 day;
		u8 month;
		u16 year;
		u8 hour;
		u8 seconds;
		u8 reserved1[5];

	};

	class StandartRaw
		: public RawAlgorithm
	{
	private:
		IODevicePtr device_;
		uint32_t block_size_ = default_block_size;
		uint32_t sector_size_ = default_sector_size;
	public:
		StandartRaw(IODevicePtr device)
			:device_(device)
		{

		}
		void setBlockSize(const uint32_t block_size)
		{
			this->block_size_ = block_size;
		}
		uint32_t getBlockSize() const
		{
			return block_size_;
		}
		void setSectorSize(const uint32_t sector_size)
		{
			this->sector_size_ = sector_size;
		}
		uint32_t getSectorSize() const
		{
			return sector_size_;
		}
		uint32_t ReadData(ByteArray data, uint32_t size)
		{
			return device_->ReadData(data, size);
		}
		void setPosition(uint64_t offset)
		{
			device_->setPosition(offset);
		}
		uint64_t SaveRawFile(HeaderPtr &header_ptr, const uint64_t header_offset, const path_string & target_name) override
		{
			File target_file(target_name);
			if (!target_file.Open(OpenMode::Create))
			{
				wprintf(L"Error create file\n");
			}

			Buffer buffer(block_size_);
			uint32_t bytes_read = 0;
			uint64_t offset = header_offset;
			uint32_t footer_pos = 0;
			uint64_t target_size = 0;

			while (true)
			{
				device_->setPosition(offset);
				bytes_read = device_->ReadData(buffer.data, block_size_);
				if (bytes_read == 0)
				{
					printf("Error read drive\r\n");
					break;
				}

				if (header_ptr->isFooter(buffer.data, bytes_read, footer_pos))
				{
					uint32_t write_size = footer_pos + header_ptr->getAddFooterSize();
					if (target_file.WriteData(buffer.data, write_size) == 0)
					{
						printf("Error write to file\r\n");
						break;
					}
					target_size += write_size;
					return target_size;
				}
				else
				{
					if (target_file.WriteData(buffer.data, bytes_read) == 0)
					{
						printf("Error write to file\r\n");
						break;
					}
				}

				target_size += bytes_read;
				if (target_size > header_ptr->getMaxFileSize())
					return target_size;

				offset += bytes_read;
			}


			return 0;
		}


	};

	class ZBKRaw
		: public RawAlgorithm
	{
	private:
		IODevicePtr device_;
		uint32_t block_size_ = default_block_size;
		uint32_t sector_size_ = default_sector_size;
	public:
		ZBKRaw(IODevicePtr device)
			:device_(device)
		{

		}
		void setBlockSize(const uint32_t block_size)
		{
			this->block_size_ = block_size;
		}
		uint32_t getBlockSize() const
		{
			return block_size_;
		}
		void setSectorSize(const uint32_t sector_size)
		{
			this->sector_size_ = sector_size;
		}
		uint32_t getSectorSize() const
		{
			return sector_size_;
		}
		HeaderPtr findHeaderAndOffset(const uint64_t start_offset, uint64_t & header_offset)
		{
			uint32_t bytes_read = 0;
			Buffer buffer(block_size_);
			
			uint32_t header_size = zbk_header_size;
			uint32_t signature_offset = 2;

			uint32_t footer_size = zbk_footer_size;
			uint32_t add_footer_size = 22;
			auto header_ptr = HeaderFactory((const ByteArray)&zbk_header[0], header_size);
			header_ptr->setHeaderOffset(signature_offset);
			header_ptr->setFooter((const ByteArray)&zbk_footer, footer_size);
			header_ptr->setAddFooterSize(add_footer_size);
			header_ptr->setMaxFileSize(0x12C00000);


			uint64_t offset = start_offset;
			

			while (true)
			{
				device_->setPosition(offset);
				bytes_read = device_->ReadData(buffer.data, block_size_);
				if (bytes_read == 0)
				{
					printf("Error read drive\r\n");
					break;
				}

				for (uint32_t iSector = 0; iSector < bytes_read; iSector += sector_size_)
				{
					if (header_ptr->isHeader(buffer.data+ iSector))
					{
						header_offset = offset;
						header_offset += iSector;
						return header_ptr;
					}
				}
				offset += bytes_read;
			}
			return nullptr;
		}
		uint64_t SaveRawFile(HeaderPtr &header_ptr, const uint64_t header_offset , const path_string & target_name) override
		{
			File target_file(target_name);
			if (!target_file.Open(OpenMode::Create))
			{
				wprintf(L"Error create file\n");
			}

			Buffer buffer(block_size_);
			uint32_t bytes_read = 0;
			uint64_t offset = header_offset;
			uint32_t footer_pos = 0;
			uint64_t target_size = 0;

			while (true)
			{
				device_->setPosition(offset);
				bytes_read = device_->ReadData(buffer.data, block_size_);
				if (bytes_read == 0)
				{
					printf("Error read drive\r\n");
					break;
				}

				if (header_ptr->isFooter(buffer.data, bytes_read, footer_pos))
				{
					uint32_t write_size = footer_pos + header_ptr->getAddFooterSize();
					if (target_file.WriteData(buffer.data, write_size) == 0)
					{
						printf("Error write to file\r\n");
						break;
					}
					target_size += write_size;
					return target_size;
				}
				else
				{
					if (target_file.WriteData(buffer.data, bytes_read) == 0)
					{
						printf("Error write to file\r\n");
						break;
					}
				}

				target_size += bytes_read;
				if (target_size > header_ptr->getMaxFileSize())
					return target_size;

				offset += bytes_read;
			}


			return 0;
		}

		void execute(const path_string &target_folder) 
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

				if (auto header_ptr = findHeaderAndOffset(offset, header_offset))
				{

					auto target_file = toFullPath(target_folder, counter++, L".zbk");
					uint64_t file_size = SaveRawFile(header_ptr, header_offset, target_file);
					//if (file_size != 0)
					//{
					//	header_offset += file_size;
					//	header_offset /= sector_size_;
					//	header_offset *= sector_size_;
					//	offset = header_offset;
					//}
					offset = header_offset;


				}
				else
				{
					wprintf(L"Not Found Header\n");
					break;
				}

				offset += sector_size_;

			}

		}

	};


};



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

#endif
