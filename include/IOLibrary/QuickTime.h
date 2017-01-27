#pragma once



#include "constants.h"
#include "iofs.h"
#include "StandartRaw.h"

#include <iostream>

namespace IO
{

	const char s_ftyp[] = "ftyp";
	const char s_moov[] = "moov";
	const char s_mdat[] = "mdat";
	const char s_wide[] = "wide";
	const char s_skip[] = "skip";
	const char s_free[] = "free";
	const char s_pnot[] = "pnot";
	const char s_prfl[] = "prfl";
	const char s_mvhd[] = "mvhd";
	const char s_clip[] = "clip";
	const char s_trak[] = "trak";
	const char s_udta[] = "udta";
	const char s_ctab[] = "ctab";
	const char s_cmov[] = "cmov";
	const char s_rmra[] = "rmra";
	const char s_uuid[] = "uuid";
	const char s_meta[] = "meta";

	const int qt_keyword_size = 4;

	using array_keywords = std::vector<const char *>;


	const array_keywords qt_array = { s_ftyp, s_moov, s_mdat, s_wide , s_free, s_skip, s_pnot, s_prfl,
									  s_mvhd, s_clip, s_trak, s_udta, s_ctab, s_cmov, s_rmra , s_uuid, s_meta };


#pragma pack(1)
	struct qt_block_t
	{
		uint32_t block_size;
		char block_type[qt_keyword_size];
	};
#pragma pack()

	using ListQtBlock = std::list<qt_block_t>;

	const uint32_t qt_block_struct_size = sizeof(qt_block_t);

	inline bool isQuickTimeKeyword(const qt_block_t & pQtBlock , const char * keyword_name )
	{
		return (memcmp(pQtBlock.block_type, keyword_name, qt_keyword_size) == 0);
	}

	inline bool isQuickTime(const qt_block_t & pQtBlock)
	{
		for ( auto keyword_name : qt_array)
			if (isQuickTimeKeyword(pQtBlock, keyword_name)) 
				return true;

		return false;
	}

	inline bool isPresentInArrayKeywords(const array_keywords & keywords , const char * key_val)
	{
		for (auto theKeyword : keywords)
		{
			if (memcmp(theKeyword, key_val, qt_keyword_size) == 0)
				return true;
		}
		return false;
	}

	//inline void to_big_endian64(uint64_t & val)
	//{
	//	const int type_size = sizeof(uint64_t);
	//	uint8_t * byte_buffer = (uint8_t *)&val;
	//	uint8_t temp = 0;
	//	for (int iByte = 0; iByte < type_size / 2; ++iByte)
	//	{
	//		temp = byte_buffer[iByte];
	//		byte_buffer[iByte] = byte_buffer[type_size - iByte - 1];
	//		byte_buffer[type_size - iByte - 1] = temp;
	//	}
	//}
	inline void toBE64(uint64_t & val)
	{
		val = _byteswap_uint64(val);
	}
	inline void toBE32(uint32_t & val)
	{
		val = _byteswap_ulong(val);
	}


	

	class QuickTimeRaw
		: public StandartRaw
	{
	private:
		ListQtBlock keywords_;
		uint64_t sizeToWrite_ = 0;
	public:
		explicit QuickTimeRaw(IODevicePtr device)
			: StandartRaw(device)
		{
		}


		virtual ~QuickTimeRaw()
		{
		}

		uint64_t readQtAtoms(const uint64_t start_offset, ListQtBlock & list_blocks)
		{
			qt_block_t qt_block = { 0 };
			uint32_t bytes_read = 0;
			uint64_t keyword_offset = start_offset;

			while (true)
			{
				this->setPosition(keyword_offset);
				if (!(bytes_read = this->ReadData((uint8_t*)&qt_block, sizeof(qt_block_t))))
					 break;

				if (!isQuickTime(qt_block))
					break;

				if (qt_block.block_size == 0)
					break;

				toBE32((uint32_t &)qt_block.block_size);

				uint64_t write_size = ReadQtAtomSize(qt_block, keyword_offset);
				if (write_size == 0)
					break;

				list_blocks.push_back(qt_block);

				keyword_offset += write_size;
			}

			return keyword_offset;
		}

		uint64_t SaveRawFile(File & target_file, const uint64_t start_offset) override
		{
			if (!target_file.isOpen())
			{
				wprintf(L"Target file wasn't opened.\n");
				return 0;
			}
			
			if (sizeToWrite_ > 0)
				return appendToFile(target_file, start_offset, sizeToWrite_);

			return 0;
		}
		bool Specify(const uint64_t start_offset) override
		{
			keywords_.clear();
			auto sizeKeywords = readQtAtoms(start_offset, keywords_);
			if (isPresentMainKeywords(keywords_))
				sizeToWrite_ = sizeKeywords;
			return false;
		}
		bool isPresentMainKeywords(const ListQtBlock & keywords )
		{
			bool bmdat = false;
			bool bmoov = false;

			for (auto & refQtBlock : keywords)
			{
				if (memcmp(refQtBlock.block_type, s_mdat, qt_keyword_size) == 0)
					bmdat = true;
				else if (memcmp(refQtBlock.block_type, s_moov, qt_keyword_size) == 0)
					bmoov = true;

				if (bmdat && bmoov)
					return true;
			}
			
			return false;
		}
		uint64_t ReadQtAtomSize(qt_block_t &qt_block, uint64_t keyword_offset)
		{
			uint64_t write_size = qt_block.block_size;

			if (qt_block.block_size == 1)
			{
				uint64_t ext_size = 0;
				uint64_t ext_size_offset = keyword_offset + sizeof(qt_block_t);

				this->setPosition(ext_size_offset);
				if (!this->ReadData((uint8_t*)&ext_size, sizeof(uint64_t)))
					return 0;
				toBE64(ext_size);
				write_size = ext_size;
			}
			return write_size;
		}
	};

	class QuickTimeRawFactory
		: public RawFactory
	{
	public:
		RawAlgorithm * createRawAlgorithm(IODevicePtr device) override
		{
			return new QuickTimeRaw(device);
		}
	};

	const uint8_t mdat_header_start[] = { 0x00, 0x00, 0x00, 0x02, 0x09, 0x10, 0x00, 0x00 };

	class QTFragmentRaw
		: public QuickTimeRaw
	{
	public:
		QTFragmentRaw(IODevicePtr device)
			: QuickTimeRaw(device)
		{
		}


		uint64_t SaveRawFile(File & target_file, const uint64_t start_offset) override
		{
			setBlockSize(32768);
			ListQtBlock qt_list;
			auto target_size = readQtAtoms(start_offset, qt_list);
			qt_block_t mdat_block = { 0 };
			uint64_t write_size = 0;
			for (auto theKeyword : qt_list)
			{
				if (memcmp(theKeyword.block_type, s_mdat, qt_keyword_size) == 0)
				{
					// write header data
					appendToFile(target_file, start_offset, write_size + qt_block_struct_size);

					auto data_array = IO::makeDataArray(getBlockSize());
					uint64_t mdat_start = start_offset - getBlockSize();
					uint32_t bytes_read = 0;
					//while (mdat_start>0)
					//{
					//	setPosition(mdat_start);
					//	bytes_read = ReadData(data_array->data(), data_array->size());
					//	if ( bytes_read == 0)
					//		break;

					//	for (auto iSector = 0; iSector < data_array->size(); iSector += default_sector_size)
					//	{
					//		if (memcmp(data_array->data() + iSector, mdat_header_start, SIZEOF_ARRAY(mdat_header_start)) == 0)
					//		{
					//			uint32_t mdat2ndSize = theKeyword.block_size - qt_block_struct_size;
					//			mdat_start = mdat_start + iSector;

					//			uint64_t free_pos = mdat_start + mdat2ndSize;
					//			qt_block_t free_block = { 0 };
					//			setPosition(free_pos);
					//			bytes_read = ReadData((ByteArray)&free_block, qt_block_struct_size);
					//			if (memcmp(free_block.block_type, s_free, qt_keyword_size) == 0)
					//			{
					//				toBE32(free_block.block_size);
					//				uint64_t main_offset = mdat_start + mdat2ndSize + free_block.block_size ;
					//				if ( main_offset == start_offset)
					//				{
					//					appendToFile(target_file, mdat_start, mdat2ndSize + free_block.block_size);
					//					return 0;
					//				}
					//			}

					//		}
					//	}
					//	mdat_start -= getBlockSize();
					//}

					

				}
				write_size += theKeyword.block_size;
			}
			return 0;
		}
		bool Specify(const uint64_t start_offset) override
		{
			return true;
		}
	};

}
		// save fragment only 'mdat' data, when found nulls more then 5000, skip this cluster.
		//uint64_t SaveFragmentMdat(File * target_file, uint64_t offset, uint32_t & copy_size)
		//{
		//	Buffer buffer(block_size_);
		//	ZeroMemory(buffer.data, block_size_);

		//	uint32_t bytes_to_copy = block_size_;

		//	uint64_t cur_pos = 0;
		//	uint64_t read_pos = 0;
		//	uint32_t write_size = 0;
		//	const uint32_t nulls_count = 5000;
		//	uint32_t null_counter = 0;

		//	uint32_t bytesRead = 0;
		//	uint32_t bytesWritten = 0;
		//	uint64_t write_offset = target_file->Size();

		//	bool isNulls = false;
		//	uint32_t real_size = 0;

		//	while (cur_pos < copy_size)
		//	{
		//		read_pos = offset + cur_pos;
		//		write_size = block_size_;
		//		null_counter = 0;
		//		isNulls = false;
		//		if ((read_pos % block_size_) != 0)
		//		{
		//			write_size = block_size_ - read_pos % block_size_;
		//		}

		//		bytes_to_copy = calcBlockSize(cur_pos, copy_size, write_size);

		//		device_->setPosition(read_pos);
		//		bytesRead = device_->ReadData(buffer.data, bytes_to_copy);
		//		if (bytesRead == 0)
		//			break;

		//		for (uint32_t iByte = 0; iByte < bytes_to_copy; ++iByte)
		//		{
		//			if (buffer.data[iByte] == 0)
		//			{
		//				++null_counter;
		//				if (null_counter > nulls_count)
		//				{
		//					isNulls = true;
		//					break;
		//				}
		//			}

		//		}
		//		if (isNulls)
		//		{
		//			cur_pos += block_size_ ;
		//			copy_size += block_size_ ;
		//			continue;
		//		}



		//		target_file->setPosition(write_offset);
		//		bytesWritten = target_file->WriteData(buffer.data, bytes_to_copy);
		//		if (bytesWritten == 0)
		//			break;

		//		write_offset += bytesWritten;
		//		cur_pos += bytesWritten;
		//		real_size += bytesWritten;
		//	}
		//	return cur_pos;

		//}
		//uint64_t AppendDataToFile(File * target_file, uint64_t offset, uint64_t copy_size)
		//{
		//	if (!device_)
		//		return 0;
		//	if (!target_file)
		//		return 0;
		//	if (!target_file->isOpen())
		//		return 0;

		//	Buffer buffer(block_size_);
		//	ZeroMemory(buffer.data, block_size_);

		//	uint64_t cur_pos = 0;
		//	uint64_t read_pos = 0;
		//	uint32_t bytes_to_copy = block_size_;

		//	uint32_t bytesRead = 0;
		//	uint32_t bytesWritten = 0;
		//	uint64_t write_offset = target_file->Size();


		//	while (cur_pos < copy_size)
		//	{
		//		bytes_to_copy = calcBlockSize(cur_pos, copy_size, block_size_);

		//		read_pos = offset + cur_pos;

		//		device_->setPosition(read_pos);
		//		bytesRead = device_->ReadData(buffer.data, bytes_to_copy);
		//		if (bytesRead == 0)
		//			break;

		//		target_file->setPosition(write_offset);
		//		bytesWritten = target_file->WriteData(buffer.data, bytes_to_copy);
		//		if (bytesWritten == 0)
		//			break;

		//		write_offset += bytesWritten;
		//		cur_pos += bytesWritten;
		//	}


		//	return cur_pos;
		//}


/*

	/*
	Make fragment raw files.
	1. 'mdat' data block
	2. Header data ( 'mdat' keyword in the end of block)
	
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

					if (memcmp(qt_block.block_type, qt_array[2], qt_keyword_size) == 0)
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
			if (memcmp(pQtBlock->block_type, s_mdat, qt_keyword_size) == 0)
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
		uint64_t readKeywordsSizes(const uint64_t start_offset, const array_keywords & key_array)
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

				if (!isPresentInArrayKeywords(key_array , qt_block.block_type))
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
				array_keywords array_mdatANDskip = { s_mdat , s_skip };
				auto size_MdatFree = readKeywordsSizes(header_offset, array_mdatANDskip);
				if (size_MdatFree > 0)
				{
					uint64_t aling_cluster = size_MdatFree / this->getBlockSize();
					++aling_cluster;
					aling_cluster *= this->getBlockSize();
					uint64_t ftyp_offset = header_offset + aling_cluster;
					array_keywords array_ftypANDmoov = { s_ftyp , s_moov };
					auto size_FtypAndMoov = readKeywordsSizes(ftyp_offset, array_ftypANDmoov);
					if (size_FtypAndMoov > 0)
					{
						auto target_file = toFullPath(target_folder, counter++, L".mov");
						File new_file(target_file);
						if (new_file.Open(OpenMode::Create))
						{
							AppendDataToFile(&new_file, ftyp_offset, size_FtypAndMoov);
							AppendDataToFile(&new_file, header_offset, size_MdatFree);

							offset = ftyp_offset;
							offset += this->getBlockSize();
							continue;
						}

					}

				}
				offset += default_sector_size;
			}


		}




	};
	

	class QuitTimeRawNoSize
		: public QuickTimeRaw
	{
	public:
		QuitTimeRawNoSize(IODevice * device)
			: QuickTimeRaw(device)
		{

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

			while (true)
			{
				if (!findHeaderOffset(offset, header_offset))
				{
					wprintf(L"Not Found Header\n");
					break;
				}
				
				auto target_file = toFullPath(target_folder, counter++, L".mov");
				offset = SaveWithOutMDatSize(header_offset, target_file);
				offset += default_sector_size;


			}
		}
		uint64_t SaveWithOutMDatSize( const uint64_t start_offset , const path_string & target_name)
		{
			File write_file(target_name);
			if (!write_file.Open(OpenMode::Create))
				return start_offset;

			auto source = this->getDevice();

			qt_block_t qt_atom = { 0 };

			uint32_t bytes_read = 0;
			uint64_t mdat_offset = 0;
			uint32_t mdat_target_pos = 0;
			uint64_t moov_offset = 0;

			uint64_t current_pos = start_offset;

			uint64_t full_targe_size = 0;

			bool bFoundMoov = false;
			
			// read 'ftyp'
			source->setPosition(current_pos);
			bytes_read = source->ReadData((ByteArray)&qt_atom, qt_block_struct_size);
			if (memcmp(qt_atom.block_type, s_ftyp, qt_keyword_size) == 0)
			{
			//	printf("%s\t", qt_atom.block_type);
				to_big_endian32((uint32_t &)qt_atom.block_size);
				current_pos += qt_atom.block_size;
				mdat_target_pos = qt_atom.block_size;


				source->setPosition(current_pos);
				bytes_read = source->ReadData((ByteArray)&qt_atom, qt_block_struct_size);
				if (memcmp(qt_atom.block_type, s_mdat, qt_keyword_size) == 0)
				{
					//printf("%s\t", qt_atom.block_type);

					mdat_offset = current_pos;

					Buffer buffer(this->getBlockSize());
					while (true)
					{
						source->setPosition(current_pos);
						bytes_read = source->ReadData(buffer.data, buffer.data_size);
						if ( bytes_read == 0)
							break;

						for (uint32_t iByte = 0; iByte < bytes_read; ++iByte)
						{
							qt_block_t * pQt_block = (qt_block_t *)&buffer.data[iByte];
							if (memcmp(pQt_block->block_type, s_moov, qt_keyword_size) == 0)
							{
								//printf("%s\t", pQt_block->block_type);

								moov_offset = current_pos;
								moov_offset += iByte;

								full_targe_size = moov_offset - start_offset;
								to_big_endian32((uint32_t &)pQt_block->block_size);
								full_targe_size += pQt_block->block_size;

								bFoundMoov = true;
								break;
							}

						}
						if (bFoundMoov)
							break;
						current_pos += bytes_read;
					}

				}
			}

			if (bFoundMoov)
				if (full_targe_size > 0)
				{
					AppendDataToFile(&write_file, start_offset, full_targe_size);
					uint32_t new_mdat_size = (uint32_t)(moov_offset - mdat_offset);
					to_big_endian32(new_mdat_size);

					write_file.setPosition(mdat_target_pos);
					write_file.WriteData((ByteArray)&new_mdat_size, sizeof(uint32_t));


				}

			full_targe_size /= default_sector_size;
			++full_targe_size;
			full_targe_size *= default_sector_size;
			full_targe_size += start_offset;
			return full_targe_size;
		}
	};
	*/
