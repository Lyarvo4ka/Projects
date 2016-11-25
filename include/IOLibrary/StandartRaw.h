#pragma once


#include "AbstractRaw.h"

namespace IO
{
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

		uint32_t addAlignedToBlockSize(const uint32_t add_size)
		{
			uint32_t size = add_size / getSectorSize() + 1;
			size *= getSectorSize();
			return getBlockSize() + size;
		}
		virtual FilePtr createFile(const path_string & target_name)
		{
			auto file = makeFilePtr(target_name);
			if (!file->Open(OpenMode::Create))
				wprintf(L"Error create file\n");
			return file;
		}
		uint64_t SaveRawFile(FileStruct::Ptr file_struct, const uint64_t header_offset, const path_string & target_name) override
		{
			auto target_file = createFile(target_name);
			if (!target_file->isOpen())
				return 0;

			auto footer_data = file_struct->getFooter();
			if (!footer_data)
				return appendToFile(*target_file, header_offset, file_struct->getMaxFileSize());

			uint32_t bytes_read = 0;
			uint32_t bytes_written = 0;

			uint64_t offset = header_offset;

			uint32_t footer_pos = 0;
			uint32_t bytes_to_write = getBlockSize();

			uint32_t sizeToRead = addAlignedToBlockSize(footer_data->size());
			auto buffer = makeDataArray(sizeToRead);

			while (offset < this->getSize())
			{
				setPosition(offset);
				bytes_read = ReadData(buffer->data(), sizeToRead);
				if (bytes_read == 0 )
				{
					wprintf(L"Error read block\n");
					break;
				}
				if (findFooter(*buffer.get(), bytes_read, *footer_data, footer_pos))
				{
					offset += bytes_written;
					bytes_written = target_file.WriteData(buffer->data(), footer_pos + footer_data->size());
					break;
				}

				if (bytes_read < getBlockSize() )
					bytes_to_write = bytes_read;

				bytes_written = target_file.WriteData(buffer->data(), bytes_to_write);
				if  (bytes_written == 0 )
				{
					wprintf(L"Error write block\n");
					break;
				}


				offset += bytes_written;
			}
			return offset - header_offset;

		}
	/*
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


			if ((bytes_read = ReadBlockData(*current, offset)))
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

					// Read next block
					if ((bytes_read = ReadNextBlock(*next, offset)))
					{
						if (compareBetween(*current, *next, *footer_data, footer_pos))
						{
							auto write_chunk = footer_data->size() - (current->size() - footer_pos) + file_struct->getFooterTailEndSize();
							bytes_written = appendBetween(target_file, *current, *next, write_chunk);
							return target_size + bytes_written;
						}

						if ((bytes_written = target_file.WriteData(current->data(), bytes_read)))
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
	*/
		bool findFooter(const DataArray &data_array, uint32_t data_size, const DataArray & footer_data, uint32_t & footer_pos)
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
		bool compareBetween(const DataArray & data1, const DataArray & data2, const DataArray & footer_data, uint32_t & footer_pos)
		{
			ByteArray pData = nullptr;
			uint32_t pos = 0;
			for (uint32_t iByte = 1; iByte < footer_data.size(); ++iByte)
			{
				pos = data1.size() - footer_data.size() + iByte;
				pData = (ByteArray)(data1.data() + pos);
				if (memcmp(pData, footer_data.data(), footer_data.size() - iByte) == 0)
					if (memcmp(data2.data(), footer_data.data() + footer_data.size() - iByte, iByte) == 0)
					{
						footer_pos = pos;
						return true;
					}
			}
			return false;
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

};