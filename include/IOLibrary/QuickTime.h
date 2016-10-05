#pragma once

#include "IODevice.h"

#include "constants.h"
#include "iofs.h"


namespace IO
{
	const int qt_keyword_size = 4;
#pragma pack(1)
	struct qt_block_t
	{
		uint32_t block_size;
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

	bool isPresentInKeywordArray(const QTKeyword::keyword_array & keywords , const char * key_val)
	{
		for (auto theKeyword : keywords)
		{
			if (memcmp(theKeyword, key_val, qt_keyword_size) == 0)
				return true;
		}
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

	void IOLIBRARY_EXPORT to_big_endian32(uint32_t & val);


	//inline path_string add

#include "iofunctions.h"
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
		IODevice* getDevice()
		{
			return device_;
		}
		virtual bool isQuickTimeHeader(const qt_block_t * pQtBlock)
		{
			for (auto iKeyword = 0; iKeyword < 1; ++iKeyword)
				if (memcmp(pQtBlock->block_type, QTKeyword::qt_array[iKeyword], qt_keyword_size) == 0)
					return true;
			return false;
		}
		virtual void execute(const path_string & target_folder)
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
				auto target_file = toFullPath(target_folder, counter++, L".mov");
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

				for (uint32_t iSector = 0; iSector < bytes_read; iSector += sector_size_)
				{
					qt_block_t * pQt_block = (qt_block_t *)&buffer.data[iSector];
					if (this->isQuickTimeHeader(pQt_block))
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
			if (!write_file.Open(OpenMode::Create))
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

				to_big_endian32((uint32_t &)qt_block.block_size);



				if (!isQuickTime(&qt_block))
					break;

				if (memcmp(qt_block.block_type, QTKeyword::qt_array[2], qt_keyword_size) == 0)
				{
					isBeenMDAT = true;
/*
					uint32_t new_size = qt_block.block_size;
					auto save_size = SaveFragmentMdat(&write_file, keyword_offset, new_size);
					//if (qt_block.block_size != save_size)
					//	break;

					keyword_offset += new_size;
*/
					continue;
				}

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

		// save fragment only 'mdat' data, when found nulls more then 5000, skip this cluster.
		uint64_t SaveFragmentMdat(File * target_file, uint64_t offset, uint32_t & copy_size)
		{
			Buffer buffer(block_size_);
			ZeroMemory(buffer.data, block_size_);

			uint32_t bytes_to_copy = block_size_;

			uint64_t cur_pos = 0;
			uint64_t read_pos = 0;
			uint32_t write_size = 0;
			const uint32_t nulls_count = 5000;
			uint32_t null_counter = 0;

			uint32_t bytesRead = 0;
			uint32_t bytesWritten = 0;
			uint64_t write_offset = target_file->Size();

			bool isNulls = false;
			uint32_t real_size = 0;

			while (cur_pos < copy_size)
			{
				read_pos = offset + cur_pos;
				write_size = block_size_;
				null_counter = 0;
				isNulls = false;
				if ((read_pos % block_size_) != 0)
				{
					write_size = block_size_ - read_pos % block_size_;
				}

				bytes_to_copy = calcBlockSize(cur_pos, copy_size, write_size);

				device_->setPosition(read_pos);
				bytesRead = device_->ReadData(buffer.data, bytes_to_copy);
				if (bytesRead == 0)
					break;

				for (uint32_t iByte = 0; iByte < bytes_to_copy; ++iByte)
				{
					if (buffer.data[iByte] == 0)
					{
						++null_counter;
						if (null_counter > nulls_count)
						{
							isNulls = true;
							break;
						}
					}

				}
				if (isNulls)
				{
					cur_pos += block_size_ ;
					copy_size += block_size_ ;
					continue;
				}



				target_file->setPosition(write_offset);
				bytesWritten = target_file->WriteData(buffer.data, bytes_to_copy);
				if (bytesWritten == 0)
					break;

				write_offset += bytesWritten;
				cur_pos += bytesWritten;
				real_size += bytesWritten;
			}
			return cur_pos;

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
			uint64_t write_offset = target_file->Size();


			while (cur_pos < copy_size)
			{
				bytes_to_copy = calcBlockSize(cur_pos, copy_size, block_size_);

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


			return cur_pos;
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



	/*
	Make fragment raw files.
	1. 'mdat' data block
	2. Header data ( 'mdat' keyword in the end of block)
	*/
	const uint32_t default_sectors_per_cluster = 64;
	const uint32_t defalut_cluster_size = default_sector_size * default_sectors_per_cluster;

	class QuickTimeFragmentRaw
		: public QuickTimeRaw
	{
	private:
		uint32_t cluster_size_;
	public:
		QuickTimeFragmentRaw(IODevice * device)
			: QuickTimeRaw(device)
			, cluster_size_(defalut_cluster_size)
		{

		}
		void setClusterSize(uint32_t cluster_size)
		{
			this->cluster_size_ = cluster_size;
		}
		void execute(const path_string & target_folder) override
		{
			auto source = this->getDevice();
			if (!source->Open(OpenMode::OpenRead))
			{
				wprintf(L"Error to open.\n");	// ????????
				return;
			}

			bool bResult = false;

			uint64_t offset = 0;
			uint64_t header_offset = 0;
			uint32_t counter = 0;
			const uint32_t four_clusters = 4;

			uint32_t bytes_read = 0;

			uint32_t cluster_per_mdat = 0;
			uint64_t mdat_offset = 0;
			uint64_t mdat_entry = 0;

			while (true)
			{
				if (!findHeaderOffset(offset, header_offset))
				{
					wprintf(L"Not Found Header\n");
					break;
				}
				auto target_name = toFullPath(target_folder, counter++, L".mp4");
				File write_file(target_name);
				if (!write_file.Open(OpenMode::Create))
				{
					wprintf(L"Error create file\n");
					break;
				}
				qt_block_t qt_block = {0};
				uint64_t keyword_offset = header_offset;

				while (true)
				{
					qt_block_t qt_block = { 0 };
					source->setPosition(keyword_offset);
					int bytes_read = source->ReadData((uint8_t*)&qt_block, sizeof(qt_block_t));
					if (bytes_read == 0)
						break;
					if (qt_block.block_size == 0)
						break;

					to_big_endian32((uint32_t &)qt_block.block_size);



					if (!isQuickTime(&qt_block))
						break;

					if (memcmp(qt_block.block_type, QTKeyword::qt_array[2], qt_keyword_size) == 0)
					{
						AppendDataToFile(&write_file, keyword_offset, sizeof(qt_block_t));
						uint32_t mdat_size = qt_block.block_size;
						cluster_per_mdat = mdat_size / cluster_size_ + 1;
						uint32_t mdat_aling_clusters = cluster_per_mdat * cluster_size_;
						if (header_offset > mdat_aling_clusters)
						{
							mdat_offset = header_offset - cluster_per_mdat * cluster_size_;
							AppendDataToFile(&write_file, mdat_offset, mdat_size - sizeof(qt_block_t));
						}

						break;
					}

					uint64_t write_size = ReadQtAtomSize(qt_block, keyword_offset);
					if (write_size == 0)
						break;

					auto bytes_written = AppendDataToFile(&write_file, keyword_offset, write_size);
					if (bytes_written != write_size)
						break;

					keyword_offset += write_size;
				}
				

				offset = header_offset + cluster_size_;


			}

		}
	};


	/*

	1. 'mdat' data block and save offset
	2. In the end of 'mdat', aling to cluster size and plus one cluster (+1 cluster) must 'ftyp' and 'moov' atom
	3. Save header data block
	4. Save 'mdat'.

	*/
	class CanonFragmentRaw
		:public QuickTimeRaw
	{
	public:
		CanonFragmentRaw(IODevice * device)
			: QuickTimeRaw(device)
		{


		}
		bool isMdat(const qt_block_t * pQtBlock)
		{
			if (memcmp(pQtBlock->block_type, QTKeyword::qt_array[QTKeyword::mdat_key_id], qt_keyword_size) == 0)
				return true;
			return false;
		}
		bool isQuickTimeHeader(const qt_block_t * pQtBlock) override
		{
			return isMdat(pQtBlock);
		}
		bool findMdatOffset(uint64_t offset, uint64_t & header_offset)
		{
			return findHeaderOffset(offset, header_offset);
		}
		uint64_t readKeywordsSizes(const uint64_t start_offset, const QTKeyword::keyword_array & key_array)
		{
			uint64_t keyword_offset = start_offset;
			auto device = this->getDevice();
			uint64_t result_size = 0;
			while (true)
			{
				qt_block_t qt_block = { 0 };
				device->setPosition(keyword_offset);
				int bytes_read = device->ReadData((uint8_t*)&qt_block, sizeof(qt_block_t));
				if (bytes_read == 0)
					return keyword_offset;
				if (qt_block.block_size == 0)
					break;

				to_big_endian32((uint32_t &)qt_block.block_size);

				if (!isPresentInKeywordArray(key_array , qt_block.block_type))
					break;

				uint64_t theSize = ReadQtAtomSize(qt_block, keyword_offset);
				if (theSize == 0)
					break;

				result_size += theSize;
				keyword_offset += theSize;
			}

			return result_size;
		}
		void execute(const path_string & target_folder)
		{
			if (!this->getDevice()->Open(OpenMode::OpenRead))
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
				if (!findMdatOffset(offset, header_offset))
				{
					wprintf(L"Not Found Mdat Keyword\n");
					break;
				}
				QTKeyword::keyword_array array_mdat_free = { QTKeyword::mdat , QTKeyword::free };
				auto mdat_free_size = readKeywordsSizes(header_offset, array_mdat_free);


				auto target_file = toFullPath(target_folder, counter++, L".mov");
				offset = SaveToFile(header_offset, target_file);
				offset += default_sector_size;
			}


		}




	};

}