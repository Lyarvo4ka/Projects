#pragma once
#include "QuickTime.h"



/*
{
"qt_fragment":
{
"header":
[
{
"textdata":"mdat",
"offset": 4
}

],
"extension": ".mov"
}
}
*/


/*
Восстановление фрагментированных файлов QuickTime.
1. Ищем сигнатуру "mdat".
2. Отпрыгиваем на размер который хранится в заголовке "mdat" (может быть 64bit).
3. Выравниваем по размеру сектора. И ищем сигнатуру "ftyp".
4. После "ftyp" должна бить сигнатура "moov", а "free" не обьязательно.
5. Сохраняем сначала структуры "ftyp", "moov", "free", а потом "mdat".
*/
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
		qt_block_t mdat_block = qt_block_t();
		// read mdat size
		auto mdat_atom = readQtAtom(start_offset);
		if (!mdat_atom.isValid())
			return 0;

		uint64_t find_pos = start_offset + mdat_atom.size();
		find_pos = alingToSector(find_pos);
		find_pos += this->getSectorSize();

		auto ftyp_atom = findQtKeyword(find_pos, s_ftyp);
		if (!ftyp_atom.isValid())
			return 0;

		uint64_t moov_offset = ftyp_atom.offset() + ftyp_atom.size();
		auto moov_atom = readQtAtom(moov_offset);
		if (!moov_atom.isValid())
			if (moov_atom.compareKeyword(s_moov))
			{
				uint64_t writeSize = ftyp_atom.size() + moov_atom.size();

				uint64_t free_offset = moov_atom.offset() + moov_atom.size();
				auto free_atom = readQtAtom(free_offset);
				if (free_atom.isValid())
					if (free_atom.compareKeyword(s_free))
						writeSize += free_atom.size();

				uint64_t target_size = appendToFile(target_file, ftyp_atom.offset(), writeSize);
				target_size += appendToFile(target_file, start_offset, mdat_atom.size());
				return target_size;
			}
		return 0;
	}



	bool Specify(const uint64_t start_offset) override
	{
		return true;
	}
};


class QTFragmentRawFactory
	: public RawFactory
{
public:
	RawAlgorithm * createRawAlgorithm(IODevicePtr device) override
	{
		return new QTFragmentRaw(device);
	}
};

struct DataEntropy
{
	double entropy;
	DataArray::Ptr data_array;
};

/*
Восстановление фрагментированных видео файлов (QuickTime). Одно видео высокого разрешения одно маленького.
Идет подщет ентропии для каждого кластера. Если не подходит под критерий то кластер не сохраняется.
Испрользуется окно в 3 кластера чтоб не исключить нужный кластер.

"ESER_YDXJ":{
"header":
[
{
"textdata":"ftyp",
"offset": 4
},
{
"textdata":"moov",
"offset": 4
},
{
"textdata":"mdat",
"offset": 4
}

],
"extension": ".mov"
},

*/
class ESER_YDXJ_QtRaw
	: public QuickTimeRaw
{
public:
	ESER_YDXJ_QtRaw(IODevicePtr device)
		: QuickTimeRaw(device)
	{

	}

	uint64_t SaveRawFile(File & target_file, const uint64_t start_offset) override
	{
		const uint32_t cluster_size = 32768;
		const double entropy_border = 7.9927;

		uint64_t offset = start_offset;
		uint64_t file_size = 0;
		uint32_t cluster_number = 0;

		for (auto i = 0; i < 11; ++i)
		{
			auto cluster_data = IO::makeDataArray(cluster_size);
			setPosition(offset);
			if (!ReadData(cluster_data->data(), cluster_data->size()))
			{
				printf("Error read cluster %I64d\n", offset / cluster_size);
				break;
			}
			appendToFile(target_file, offset, cluster_size);
			++cluster_number;
			offset += cluster_size;
		}

		std::unique_ptr<DataEntropy> prev = std::make_unique<DataEntropy>();
		prev->data_array = IO::makeDataArray(cluster_size);
		setPosition(offset);
		ReadData(prev->data_array->data(), prev->data_array->size());
		prev->entropy = calcEntropy(prev->data_array->data(), prev->data_array->size());
		appendToFile(target_file, offset, cluster_size);
		offset += cluster_size;


		//uint64_t curr_offset = offset;
		std::unique_ptr<DataEntropy> curr = std::make_unique<DataEntropy>();
		curr->data_array = IO::makeDataArray(cluster_size);
		setPosition(offset);
		ReadData(curr->data_array->data(), curr->data_array->size());
		offset += cluster_size;
		curr->entropy = calcEntropy(curr->data_array->data(), curr->data_array->size());
		//			appendToFile(target_file, offset, cluster_size);

		uint32_t nCount = 0;
		uint32_t moov_offset = 0;

		uint32_t number_nulls = 0;

		while (true)
		{
			std::unique_ptr<DataEntropy> next = std::make_unique<DataEntropy>();
			next->data_array = IO::makeDataArray(cluster_size);
			setPosition(offset);
			if (!ReadData(next->data_array->data(), next->data_array->size()))
			{
				printf("Error read cluster %I64d\n", offset / cluster_size);
				break;
			}
			next->entropy = calcEntropy(next->data_array->data(), next->data_array->size());



			nCount = 0;
			if (prev->entropy > entropy_border)
				++nCount;
			if (curr->entropy > entropy_border)
				++nCount;
			if (next->entropy > entropy_border)
				++nCount;

			//number_nulls = calc_nulls(next->data_array->data(), next->data_array->size());
			//nCount = 0;
			//if (number_nulls < 280)
			//	nCount = 2;


			if (!findMOOV(curr->data_array->data(), curr->data_array->size(), moov_offset))
			{
				if (nCount >= 2)
					appendToFile(target_file, offset - cluster_size, cluster_size);
				else
				{
					printf("skip cluster #%d\r\n", cluster_number);
				}
			}
			else
			{
				uint32_t moov_pos = moov_offset - sizeof(s_moov) + 1;
				appendToFile(target_file, offset - cluster_size, moov_pos);
				file_size += moov_pos;

				uint64_t moov_offset = offset - cluster_size + moov_pos;
				qt_block_t qt_block = { 0 };

				setPosition(moov_offset);
				ReadData((ByteArray)&qt_block, qt_block_struct_size);
				if (isQuickTime(qt_block))
				{
					toBE32((uint32_t &)qt_block.block_size);

					appendToFile(target_file, moov_offset, qt_block.block_size);
					file_size += qt_block.block_size;
				}
				return file_size;

			}
			prev = std::move(curr);
			curr = std::move(next);

			++cluster_number;
			offset += cluster_size;
			file_size += cluster_size;
		}
		return file_size;

	}
	bool findMOOV(const ByteArray data, const uint32_t size, uint32_t & moov_pos)
	{
		for (moov_pos = 0; moov_pos < size - sizeof(s_moov); ++moov_pos)
			if (memcmp(data + moov_pos, s_moov, sizeof(s_moov)) == 0)
				return true;

		return false;
	}

	bool Specify(const uint64_t start_offset) override
	{
		return true;
	}
	bool Verify(const IO::path_string & file_path) override
	{
		auto target_file = IO::makeFilePtr(file_path);
		if (!target_file->Open(IO::OpenMode::OpenRead))
		{
			wprintf(L"Target file wasn't opened.\n");
			return false;

		}
		QuickTimeRaw qtRaw(target_file);
		//ListQtBlock qtList ;
		QuickTimeList keywrodsList;
		auto file_size = qtRaw.readAllQtAtoms(0, keywrodsList);
		return qtRaw.isPresentMainKeywords(qtList);

	}

};

class ESER_YDXJ_QtRawFactory
	: public RawFactory
{
public:
	RawAlgorithm * createRawAlgorithm(IODevicePtr device) override
	{
		return new ESER_YDXJ_QtRaw(device);
	}
};


const char str_gpssv[] = "$GPGSV";
const uint32_t str_gpssv_size = SIZEOF_ARRAY(str_gpssv) - 1;
const char eightNulls[] = { 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 };
const uint32_t eightNulls_size = SIZEOF_ARRAY(eightNulls);



/*
Восстановление фрагментированных видео файлов (QuickTime). Встречаются кластера тексторвый тип(.gps) и  (.3gf).
- gps классифицируем наличием ключевого слова ( $GPGSV ).
- 3gf классифицируем наличием 8-м нулями.

*/

class BlackVue_QtRaw
	:public ESER_YDXJ_QtRaw
{
private:
	uint32_t cluster_size_ = 32768;
public:
	BlackVue_QtRaw(IODevicePtr device)
		: ESER_YDXJ_QtRaw(device)
	{

	}

	uint64_t SaveRawFile(File & target_file, const uint64_t start_offset) override
	{
		uint64_t offset = 0;
		const path_string gps_ext = L".gps";
		const path_string threeGF_ext = L".3gf";


		boost::filesystem::path target_path(target_file.getFileName());
		auto onlyFileName = target_path.stem();
		auto folderPath = target_path.parent_path();
		auto gpsFileName = addBackSlash(folderPath.generic_wstring()) + onlyFileName.generic_wstring() + gps_ext;
		auto gps_file = makeFilePtr(gpsFileName);
		if (!gps_file->Open(OpenMode::Create))
		{
			wprintf(L"Error create  file ", gpsFileName.c_str());
			return 0;
		}

		auto threeGFFileName = addBackSlash(folderPath.generic_wstring()) + onlyFileName.generic_wstring() + threeGF_ext;
		auto thrgf_file = makeFilePtr(threeGFFileName);
		if (!thrgf_file->Open(OpenMode::Create))
		{
			wprintf(L"Error create  file ", threeGFFileName.c_str());
			return 0;
		}


		// Save first cluster
		appendToFile(target_file, start_offset, cluster_size_);
		uint64_t file_size = cluster_size_;

		DataArray data_buffer(cluster_size_);
		offset = start_offset;
		offset += cluster_size_;

		uint32_t moov_offset = 0;
		uint32_t cluster_number = 1;

		while (true)
		{
			setPosition(offset);
			ReadData(data_buffer.data(), data_buffer.size());

			if (!findMOOV(data_buffer.data(), data_buffer.size(), moov_offset))
			{
				if (isGPS(data_buffer.data(), data_buffer.size()))
				{

					gps_file->WriteData(data_buffer.data(), data_buffer.size());
					int k = 1;
					k = 2;
				}
				else if (is3GF(data_buffer.data(), data_buffer.size()))
				{
					thrgf_file->WriteData(data_buffer.data(), data_buffer.size());
					int k = 1;
					k = 2;

				}
				else
				{
					appendToFile(target_file, offset, data_buffer.size());
					file_size += data_buffer.size();
				}

			}
			else
			{
				uint32_t moov_pos = moov_offset - sizeof(s_moov) + 1;
				appendToFile(target_file, offset, moov_pos);
				file_size += moov_pos;

				uint64_t moov_offset = offset + moov_pos;
				qt_block_t qt_block = { 0 };

				setPosition(moov_offset);
				ReadData((ByteArray)&qt_block, qt_block_struct_size);
				if (isQuickTime(qt_block))
				{
					toBE32((uint32_t &)qt_block.block_size);

					appendToFile(target_file, moov_offset, qt_block.block_size);
					file_size += qt_block.block_size;
				}
				return file_size;

			}
			offset += cluster_size_;
			++cluster_number;
		}





		return 0;
	}

	bool Specify(const uint64_t start_offset) override
	{
		return true;
	}

	bool Verify(const IO::path_string & file_path) override
	{
		return ESER_YDXJ_QtRaw::Verify(file_path);
	}
	bool isGPS(ByteArray data, const uint32_t size)
	{
		for (uint32_t i = 0; i < size - str_gpssv_size; ++i)
		{
			if (memcmp(data + i, str_gpssv, str_gpssv_size) == 0)
				return true;
		}

		return false;
	}

	bool is3GF(ByteArray data, const uint32_t size)
	{
		for (uint32_t i = 0; i < size - eightNulls_size; ++i)
		{
			if (memcmp(data + i, eightNulls, eightNulls_size) == 0)
				return true;
		}

		return false;
	}


};

class BlackVue_QtRawFactory
	: public RawFactory
{
public:
	RawAlgorithm * createRawAlgorithm(IODevicePtr device) override
	{
		return new BlackVue_QtRaw(device);
	}
};


/*
Восстановление фрагментированных видео файлов (QuickTime). С начали идут несколько заголовков("moov"), потом сам видео поток ("mdat").
В заголовке есть полный размер файла. Из этого размера можно вычислить размер "mdat".
Идето поиск "mdat" с таким размером.
*/
class Canon80D_FragmentRaw
	: public QuickTimeRaw
{
public:
	Canon80D_FragmentRaw(IODevicePtr device)
		: QuickTimeRaw(device)
	{

	}
	uint64_t SaveRawFile(File & target_file, const uint64_t start_offset) override
	{
		const uint32_t fullFileSizeOffset = 2084;

		// 1. Читаем header.
		qt_block_t qtBlock = qt_block_t();
		setPosition(start_offset);
		ReadData((IO::ByteArray)&qtBlock, qt_block_struct_size);
		if (!isQuickTime(qtBlock))
		{
			wprintf(L"Error wrong qt_header.\n");
			return 0;
		}
		uint32_t header_size = qtBlock.block_size;
		toBE32(header_size);

		uint64_t offset = start_offset;
		offset += header_size;
		// 2. Читаем следующий должен быть moov
		ZeroMemory(&qtBlock, qt_block_struct_size);
		setPosition(offset);
		ReadData((IO::ByteArray)&qtBlock, qt_block_struct_size);
		if (!isQuickTime(qtBlock) || (memcmp(qtBlock.block_type, s_moov, qt_keyword_size) != 0))
		{
			wprintf(L"Error wrong moov.\n");
			return 0;
		}

		uint32_t moov_size = qtBlock.block_size;
		toBE32(moov_size);

		// 3. Читаем полный размер файла.
		uint32_t full_size = 0;
		offset = start_offset;
		offset += fullFileSizeOffset;
		setPosition(offset);
		ReadData((IO::ByteArray) & full_size, 4);


		uint32_t mdat_size = full_size - moov_size - header_size;

		int l = 0;
		l = 1;

		qt_block_t mdat_cmp;
		mdat_cmp.block_size = mdat_size;
		toBE32(mdat_cmp.block_size);
		memcpy(mdat_cmp.block_type, s_mdat, qt_keyword_size);

		DataArray buffer(getBlockSize());

		//const uint32_t GB_4 = UINT32_MAX;
		uint64_t mdat_start = start_offset;
		//uint64_t search_end = mdat_start + GB_4;
		//if (search_end > getSize())
		//	search_end = getSize();
		uint32_t bytes_read = 0;
		while (mdat_start <= getSize())
		{
			setPosition(mdat_start);
			//setPosition(0x7000000);
			bytes_read = ReadData(buffer.data(), buffer.size());
			if (bytes_read == 0)
				return 0;

			for (uint32_t iSector = 0; iSector < buffer.size(); iSector += default_sector_size)
			{
				memcpy(&qtBlock, buffer.data() + iSector, qt_block_struct_size);
				if (memcmp(&qtBlock, &mdat_cmp, qt_block_struct_size) == 0)
				{
					uint64_t mdat_offset = mdat_start + iSector;
					appendToFile(target_file, start_offset, header_size + moov_size);
					uint32_t write_size = mdat_cmp.block_size;
					toBE32(write_size);
					return appendToFile(target_file, mdat_offset, write_size);

				}
			}
			mdat_start += buffer.size();

		}



		return 0;
	}
	bool Specify(const uint64_t start_offset) override
	{
		return true;
	}

	bool Verify(const IO::path_string & file_path) override
	{
		return true;
	}
};

class Canon80D_FragmentRawFactory
	: public RawFactory
{
public:
	RawAlgorithm * createRawAlgorithm(IODevicePtr device) override
	{
		return new Canon80D_FragmentRaw(device);
	}
};

struct EntropyCluster
{
	EntropyCluster(uint64_t offset, double theEntropy)
		: cluster_offset(offset)
		, entropy(theEntropy)
	{}
	uint64_t cluster_offset = 0;
	double entropy = 0.0;
};

struct FTYP_start
{
	bool bFound = false;
	uint64_t offset = 0;
};
