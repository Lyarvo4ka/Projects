#ifndef ABSTRACT_RAW_H
#define ABSTRACT_RAW_H


#include "iofunctions.h"
#include "IODevice.h"
#include <memory>

#include "utility.h"

namespace IO
{
	class DataArray
	{
		ByteArray data_;
		uint32_t size_;
	public:
		using Ptr = std::unique_ptr<DataArray>;
		DataArray(const uint32_t size)
			:data_(nullptr)
			,size_(size)
		{
			if (size > 0)
			{
				data_ = new uint8_t[size];
			}
		}
		DataArray(ByteArray data, uint32_t size)
			: data_(data)
			, size_(size)
		{

		}
		DataArray(const uint8_t const_data[], uint32_t size)
			: data_(nullptr)
			, size_(size)
		{
			if (size_ > 0)
			{
				data_ = new uint8_t[size_];
				memcpy(data_, const_data, size_);

			}
		}

		~DataArray()
		{
			if (data_)
			{
				delete[] data_;
				data_ = nullptr;
//				printf("delete data\r\n");
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
		friend bool operator == (const DataArray::Ptr & left, const DataArray::Ptr & right) 
		{
			if (left->size() == right->size())
				return (memcmp(left->data(), right->data(), left->size()) == 0);
			return false;
		}
		bool compareData( const ByteArray data , uint32_t size , uint32_t offset = 0) 
		{
			if (size >= this->size())
			{
				
				if (std::memcmp(data_ , data + offset, this->size()) == 0)
					return true;
			}
			return false;
		}
		bool compareData( const DataArray & dataArray , uint32_t offset = 0)
		{

			return compareData(dataArray.data(), dataArray.size(), offset);
		}
	};
	inline DataArray::Ptr makeDataArray(ByteArray data, uint32_t size)
	{
		return std::make_unique<DataArray>(data, size);
	}
	inline DataArray::Ptr makeDataArray(const uint8_t const_data[], uint32_t size)
	{
		return std::make_unique<DataArray>(const_data, size);
	}

	inline DataArray::Ptr makeDataArray(uint32_t size)
	{
		return std::make_unique<DataArray>(size);
	}

	using SignatureArray = std::vector<DataArray::Ptr>;

	class SignatureOffset
	{
		uint32_t signature_offset_ = 0;
		SignatureArray signatureArray_;

	public:
		using Ptr = std::unique_ptr<SignatureOffset>;
		SignatureOffset()
		{

		}
		SignatureOffset(DataArray::Ptr dataArray, uint32_t signature_offset = 0)
		{
			signature_offset_ = signature_offset;
			addSignature(std::move(dataArray));
		}
		SignatureOffset(ByteArray data, uint32_t size, uint32_t signature_offset = 0)
		{
			signature_offset_ = signature_offset;
			addSignature(data , size);
		}
		void setOffset(const uint32_t signature_offset)
		{
			signature_offset_ = signature_offset;
		}
		uint32_t getOffset() const
		{
			return signature_offset_;
		}
		void addSignature(DataArray::Ptr dataArray)
		{
			signatureArray_.emplace_back(std::move( dataArray));
		}
		void addSignature(DataArray * data_array)
		{
			signatureArray_.emplace_back(data_array);
		}
		void addSignature(ByteArray data, uint32_t size)
		{
			signatureArray_.emplace_back(std::make_unique<DataArray>(data, size));
		}
		void addSignature(const uint8_t const_data[], uint32_t size)
		{
			signatureArray_.emplace_back(std::make_unique<DataArray>(const_data, size));
		}
		bool FindSignature(const ByteArray data, uint32_t size)
		{
			for (auto & theSignature : signatureArray_)
			{
				if (theSignature->compareData(data, size, signature_offset_))
					return true;
			}
			return false;
		}
		bool find(const DataArray::Ptr & data_array)
		{
			auto iter = std::find(signatureArray_.begin(), signatureArray_.end(), data_array);
			return (iter != signatureArray_.end()) ? true : false;
		}

	};

	inline SignatureOffset::Ptr makeSignatureOffset()
	{
		return std::make_unique<SignatureOffset>();
	}
	inline SignatureOffset::Ptr makeSignatureOffset(ByteArray data, uint32_t size, uint32_t signature_offset = 0)
	{
		return std::make_unique<SignatureOffset>(data , size , signature_offset);
	}
	inline SignatureOffset::Ptr makeSignatureOffset(DataArray::Ptr data_array, uint32_t signature_offset = 0)
	{
		return std::make_unique<SignatureOffset>(std::move(data_array), signature_offset);
	}

	using HeaderArray = std::vector<SignatureOffset::Ptr>;

	class FileStruct
	{
		HeaderArray headers_;
		std::string formatName_;
		path_list ext_list_;
		DataArray::Ptr footer_;
		uint32_t footerTailEndSize_ = 0;
		uint64_t maxFileSize_ = 0;
	public:
		using Ptr = std::shared_ptr<FileStruct>;
		FileStruct(const std::string & formatName)
			: formatName_(formatName)
		{

		}
		std::size_t headersCount() const
		{
			return headers_.size();
		}
		void addSignature(ByteArray data, uint32_t size, uint32_t header_offset)
		{
			addSignature(makeDataArray(data, size), header_offset);
		}

		void addSignature(DataArray::Ptr & data_array, uint32_t offset)
		{
			auto iter = findByOffset(offset);

			if (iter != headers_.end())
			{
				if (!(*iter)->find(data_array))
					(*iter)->addSignature(std::move(data_array));
				else
				{
					printf("This signature is already present\r\n");
				}
			}
			else
				headers_.emplace_back(makeSignatureOffset(std::move(data_array), offset));
		}
		void addSignature(SignatureOffset::Ptr signAndOffset)
		{
			headers_.emplace_back(std::move(signAndOffset));
		}

		void addFooter(DataArray::Ptr footer)
		{
			footer_ = std::move(footer);
		}
		void addFooter(ByteArray data, uint32_t size)
		{
			footer_ = std::move(makeDataArray(data, size));
		}
		void addFooter(const uint8_t const_data[], uint32_t size)
		{
			footer_ = std::move(makeDataArray(const_data, size));
		}
		DataArray * getFooter() const 
		{
			return footer_.get();
		}
		void setFooterTailEndSize(uint32_t footerTailEndSize)
		{
			footerTailEndSize_ = footerTailEndSize;
		}
		uint32_t getFooterTailEndSize() const
		{
			return footerTailEndSize_;
		}
		void setMaxFileSize(uint64_t maxFileSize)
		{
			maxFileSize_ = maxFileSize;
		}
		uint64_t getMaxFileSize() const
		{
			return maxFileSize_;
		}
		bool compareWithAllHeaders(ByteArray data, uint32_t size)
		{
			for (auto & theHeader : headers_)
			{
				if (!theHeader->FindSignature(data, size))
					return false;
			}
			return true;
		}
	private:
		HeaderArray::iterator findByOffset(uint32_t header_offset)
		{
			return std::find_if(headers_.begin(), headers_.end(),
				[header_offset](const SignatureOffset::Ptr & ptr)
			{
				return ptr->getOffset() == header_offset;
			}
			);

		}

	};
	
	inline FileStruct::Ptr makeFileStruct(const std::string & formatName)
	{
		return std::make_shared<FileStruct>(formatName);
	}

	class Header_t	// ??????
	{
		ByteArray footer_ = nullptr;
		uint32_t footer_size_ = 0;
		uint32_t add_footer_size = 0;
		uint64_t max_file_size = 0;
	public:
		~Header_t()
		{
			if (footer_)
			{
				delete[] footer_;
				footer_ = nullptr;
			}
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


	class HeaderBase
	{
	private:
		std::list<FileStruct::Ptr> listHeaders_;
	public:
		void addFileFormat(FileStruct::Ptr new_file_format)
		{
			listHeaders_.emplace_back(new_file_format);
		}
		FileStruct::Ptr find(const ByteArray data , uint32_t size)
		{
			for (auto & theFileStruct : listHeaders_)
			{
				if (theFileStruct->compareWithAllHeaders(data, size))
					return theFileStruct;
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
		FileStruct::Ptr findHeader(const uint64_t start_offset, uint64_t & header_pos)
		{
			if (!device_->Open(OpenMode::OpenRead))
			{
				wprintf_s(L"Error open device\n");
				return nullptr;
			}

			uint64_t file_size = device_->Size();
			uint64_t offset = start_offset;
			auto buffer = makeDataArray(block_size_);
			uint32_t bytes_read = 0;
			uint32_t result_offset = 0;

			while (offset < file_size)
			{
				device_->setPosition(offset);
				bytes_read = device_->ReadData(buffer->data(), block_size_);
				if (bytes_read == 0)
				{
					printf("Error read drive\r\n");
					break;
				}
				if (auto header_ptr = cmpHeader(buffer, bytes_read, result_offset))
				{
					header_pos = offset;
					header_pos += result_offset;
					return header_ptr;
				}

				offset += bytes_read;
			}
			return nullptr;
		}

		FileStruct::Ptr cmpHeader(const DataArray::Ptr & buffer, const uint32_t size, uint32_t header_pos)
		{
			for (uint32_t iPos = 0; iPos < size; iPos += sector_size_)
			{
				if (auto header_ptr = header_base_->find(buffer->data(), buffer->size()))
				{
					header_pos = iPos;
					return header_ptr;
				}
			}
			return nullptr;
		}


		RawAlgorithm * createRawAlgorithm(FileStruct::Ptr headerPtr)
		{
			
			return nullptr;
		}

	};

	class RawAlgorithm
	{
		virtual uint64_t SaveRawFile(FileStruct::Ptr  header_ptr, const uint64_t header_offset, const path_string & target_name) = 0;
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
		uint64_t getSize() const
		{
			return device_->Size();
		}
		uint32_t ReadBlockData(const DataArray & data, const uint64_t offset)
		{
			device_->setPosition(offset);
			return this->ReadData(data.data(), block_size_);
		}
		uint32_t ReadNextBlock(const DataArray & data, uint64_t & offset)
		{
			offset += block_size_;
			device_->setPosition(offset);
			return this->ReadData(data.data(), block_size_);
		}
		uint64_t SaveRawFile(FileStruct::Ptr file_struct, const uint64_t header_offset, const path_string & target_name) override
		{
			File target_file(target_name);
			if (!target_file.Open(OpenMode::Create))
			{
				wprintf(L"Error create file\n");
				return 0;
			}

			//auto buffer = makeDataArray(block_size_);
			uint32_t bytes_read = 0;
			uint32_t bytes_written = 0;

			uint64_t offset = header_offset;
			uint64_t target_size = 0;

			DataArray::Ptr currPtr = makeDataArray(block_size_);
			auto current = currPtr.get();
			DataArray::Ptr nextPtr = makeDataArray(block_size_);
			auto next = nextPtr.get();
			//DataArray * current = new DataArray(block_size_);
			//DataArray * next = new DataArray(block_size_);
			DataArray * temp = nullptr;

			uint32_t footer_pos = 0;
			auto footer_data = file_struct->getFooter();
			if (!footer_data)
				return appendToFile(target_file, header_offset, file_struct->getMaxFileSize());


			if ( (bytes_read = ReadBlockData(*current, offset)))
			while (offset < this->getSize())
			{
				// Find footer in first block
				if (findFooter(*current, current->size(), *footer_data, footer_pos))
				{
					// found footer
					auto write_size = footer_pos + file_struct->getFooterTailEndSize();
					bytes_written = target_file.WriteData(current->data(), write_size);
					if (write_size != bytes_written)
					{
						printf("Error write to file\r\n");
						return 0;
					}

					return target_size + write_size;
				}

				if ((bytes_read = ReadNextBlock(*next, offset)))
				{
					if (compareBetween(*current, *next, *footer_data, bytes_read, footer_pos))
					{
						auto write_chunk = footer_data->size() - (current->size() - footer_pos) + file_struct->getFooterTailEndSize();
						bytes_written = appendBetween(target_file, *current, *next, write_chunk);
						return target_size + bytes_written;
					}
	
					if ( (bytes_written = target_file.WriteData(current->data(), bytes_read)) )
					{
						target_size += bytes_written;
						if (target_size > file_struct->getMaxFileSize())
							return target_size;

						// change pointers
						temp = current;
						current = next;
						next = current;
					}
					else
					{
						printf("Error write to file\r\n");
						return 0;
					}
				}
				else
					return 0;
			}

			return 0;
		}
		bool findFooter(const DataArray &data_array, uint32_t data_size, const DataArray & footer_data , uint32_t & footer_pos)
		{
			for (uint32_t iByte = 0; iByte < data_size - footer_data.size(); ++iByte)
			{
				if (memcmp(data_array.data() + iByte, footer_data.data(), footer_data.size()) == 0)
				{
					printf("Found footer.\r\n");
					footer_pos = iByte;
					return true;
				}
			}
			return false;
		}
		bool compareBetween(const DataArray & data1, const DataArray & data2, const DataArray & footer_data , const uint32_t size , uint32_t & footer_pos)
		{
			ByteArray pData = nullptr;
			uint32_t pos = 0;
			for (auto iByte = 1; iByte < footer_data.size(); ++iByte)
			{
				pos = data1.size() - footer_data.size() + iByte;
				pData = (ByteArray)(data1.data() + pos);
				if ( memcmp(pData, footer_data.data() , footer_data.size() - iByte) == 0)
					if (memcmp(data2.data(), footer_data.data() - iByte, iByte) == 0)
					{
						footer_pos = pos;
						return true;
					}
			}
		}
		uint64_t appendToFile(File & write_file, const uint64_t source_offset, const uint64_t write_size)
		{
			auto target_offset = write_file.Size();
			uint32_t bytes_read = 0;
			uint32_t bytes_written = 0;
			uint64_t cur_pos = 0;
			uint32_t bytes_to_write = 0;
			auto buffer = makeDataArray(getBlockSize());
			while (cur_pos < write_size)
			{
				bytes_to_write = calcBlockSize(cur_pos, write_size, getBlockSize());

				setPosition(target_offset);
				bytes_read = ReadData(buffer->data(), bytes_to_write);
				if (bytes_read == 0)
				{
					printf("Error read drive\r\n");
					return cur_pos;
				}

				write_file.setPosition(target_offset);
				bytes_written = write_file.WriteData(buffer->data(), bytes_read);
				if (bytes_written == 0)
				{
					printf("Error write to file\r\n");
					return cur_pos;
				}

				target_offset += bytes_written;
				cur_pos += bytes_written;
			}

			return cur_pos;
		}
		uint32_t appendToFile(File & write_file, const ByteArray data, const uint32_t write_size)
		{
			auto target_offset = write_file.Size();
			write_file.setPosition(target_offset);
			return write_file.WriteData(data, write_size);
		}
		uint32_t appendBetween(File & write_file, const DataArray & data1, const DataArray & data2, const uint32_t data2_size)
		{
			uint32_t bytes_written = 0;
			if ((bytes_written = write_file.WriteData(data1.data(), data1.size())))
			{
				auto target_size = bytes_written;

				// Save second chunk
				if ((bytes_written = write_file.WriteData(data2.data(), data2_size)))
				{
					target_size += data2_size;
					return target_size;
				}
			}
			return 0;
		}


	};
/*
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

*/
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
