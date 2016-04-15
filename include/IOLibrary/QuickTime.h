#pragma once

#include "IODevice.h"

#include "constants.h"


namespace IO
{
	const int qt_keyword_size = 4;
#pragma pack(1)
	struct qt_block_t
	{
		DWORD block_size;
		char block_type[qt_keyword_size];
	};
#pragma pack()

	inline bool isQuickTime(const qt_block_t * pQtBlock)
	{
		for (auto iKeyword = 0; iKeyword < QTKeyword::qt_array_size; ++iKeyword)
			if (memcmp(pQtBlock->block_type, QTKeyword::qt_array[iKeyword], qt_keyword_size) == 0)
				return true;

		return false;
	}

	bool isQuickTimeHeader(const qt_block_t * pQtBlock)
	{
		for (auto iKeyword = 0; iKeyword < 3; ++iKeyword)
			if (memcmp(pQtBlock->block_type, QTKeyword::qt_array[iKeyword], qt_keyword_size) == 0)
				return true;
		return false;
	}

	inline void to_big_endian64(uint64_t & val)
	{
		const int type_size = sizeof(uint64_t);
		uint8_t * byte_buffer = (uint8_t *)&val;
		uint8_t temp = 0;
		for (int iByte = 0; iByte < type_size / 2; ++iByte)
		{
			temp = byte_buffer[iByte];
			byte_buffer[iByte] = byte_buffer[type_size - iByte - 1];
			byte_buffer[type_size - iByte - 1] = temp;
		}
	}

	inline path_string NumberToString(const uint32_t number)
	{
		const int numValues = 10;
		wchar_t buff[numValues];
		ZeroMemory(buff, sizeof(wchar_t) * numValues);

		swprintf_s(buff, numValues, L"%.9d", number);
		return buff;
	}

	inline path_string MakeFileName(const uint32_t number, const path_string & extension)
	{
		return NumberToString(number) + extension;
	}

	inline path_string MakeFilePath(const path_string & folder, const uint32_t number, const path_string & extension)
	{
		return folder + NumberToString(number) + extension;
	}


	class QuickTimeRaw
	{
	private:
		IODevice* device_;
		uint32_t block_size_;
		uint32_t sector_size_;
	public:
		QuickTimeRaw(IODevice * device)
			: device_(device)
			, block_size_(default_block_size)
			, sector_size_(default_sector_size)
		{
		}
		~QuickTimeRaw()
		{
			if (device_)
			{
				delete device_;
				device_ = nullptr;
			}
		}
		void setBlockSize(const uint32_t block_size)
		{
			this->block_size_ = block_size;
		}
		void setSectorSize(const uint32_t sector_size)
		{
			this->sector_size_ = sector_size;
		}

		void execute(const path_string & target_folder)
		{
			if (!device_->Open(OpenMode::OpenRead))
			{
				wprintf(L"Error to open.\n");	// ????????
				return;
			}

			bool bResult = false;

			uint64_t offset = 0;
			uint64_t header_offset = 0;
			uint32_t counter = 0;
			while (true)
			{
				if (!findHeaderOffset(offset, header_offset))
				{
					wprintf(L"Not Found Header\n");
					break;
				}
				auto target_file = MakeFilePath(target_folder, counter++, L".mov");
				offset = SaveToFile(header_offset, target_file);
				offset += default_sector_size;

			}
		}

		bool findHeaderOffset(uint64_t offset, uint64_t & header_offset)
		{
			uint32_t bytes_read = 0;
			Buffer buffer(block_size_);

			while (true)
			{
				device_->setPosition(offset);
				bytes_read = device_->ReadData(buffer.data, block_size_);
				if (bytes_read == 0)
				{
					printf("Error read drive\r\n");
					break;
				}

				for (int iSector = 0; iSector < bytes_read; iSector += sector_size_)
				{
					qt_block_t * pQt_block = (qt_block_t *)&buffer.data[iSector];
					if (isQuickTimeHeader(pQt_block))
					{
						header_offset = offset + iSector;
						return true;
					}
				}
				offset += bytes_read;
			}
			return false;
		}
		uint64_t SaveToFile(const uint64_t header_offset, const path_string & target_name)
		{
			File write_file(target_name);
			if (!write_file.Open(OpenMode::OpenWrite))
				return header_offset;

			uint64_t keyword_offset = header_offset;

			bool isBeenMDAT = false;

			while (true)
			{
				qt_block_t qt_block = { 0 };
				device_->setPosition(keyword_offset);
				int bytes_read = device_->ReadData((uint8_t*)&qt_block, sizeof(qt_block_t));
				if (bytes_read == 0)
					return keyword_offset;
				if (qt_block.block_size == 0)
					break;

				qt_block.block_size = ntohl(qt_block.block_size);


				if (!isQuickTime(&qt_block))
					break;

				if (memcmp(qt_block.block_type, QTKeyword::qt_array[2], qt_keyword_size) == 0)
					isBeenMDAT = true;

				uint64_t write_size = ReadQtAtomSize(qt_block, keyword_offset);
				if (write_size == 0)
					break;

				auto bytes_written = AppendDataToFile(&write_file, keyword_offset, write_size);
				if (bytes_written != write_size)
					break;

				keyword_offset += write_size;
			}

			write_file.Close();
			keyword_offset /= default_sector_size;
			keyword_offset *= default_sector_size;
			if (!isBeenMDAT)
				keyword_offset = header_offset;
			return keyword_offset;

		}
		uint64_t AppendDataToFile(File * target_file, uint64_t offset, uint64_t copy_size)
		{
			if (!device_)
				return false;
			if (!target_file)
				return false;
			if (!target_file->isOpen())
				return false;

			Buffer buffer(block_size_);
			ZeroMemory(buffer.data, default_block_size);

			uint64_t cur_pos = 0;
			uint64_t read_pos = 0;
			uint32_t bytes_to_copy = block_size_;

			uint32_t bytesRead = 0;
			uint32_t bytesWritten = 0;
			uint64_t write_offset = 0;


			while (cur_pos < copy_size)
			{
				bytes_to_copy = getBytesForBlock(cur_pos, copy_size, block_size_);

				read_pos = offset + cur_pos;

				device_->setPosition(read_pos);
				bytesRead = device_->ReadData(buffer.data, bytes_to_copy);
				if (bytesRead == 0)
					break;

				target_file->setPosition(write_offset);
				bytesWritten = target_file->WriteData(buffer.data, bytes_to_copy);
				if (bytesWritten == 0)
					break;

				write_offset += bytesWritten;
				cur_pos += bytesWritten;
			}


			return true;
		}
		uint64_t ReadQtAtomSize(qt_block_t &qt_block, uint64_t keyword_offset)
		{
			uint64_t write_size = qt_block.block_size;

			if (qt_block.block_size == 1)
			{
				uint64_t ext_size = 0;
				uint64_t ext_size_offset = keyword_offset + sizeof(qt_block_t);

				device_->setPosition(ext_size_offset);
				if (!device_->ReadData((uint8_t*)&ext_size, sizeof(uint64_t)))
					return 0;
				to_big_endian64(ext_size);
				write_size = ext_size;
			}
			return write_size;
		}
	};

}