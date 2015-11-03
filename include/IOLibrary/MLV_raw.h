#ifndef MLV_RAW_H
#define MLV_RAW_H

#include "constants.h"
#include <stdint.h>

const uint32_t mlv_keyword_size = 4;

#pragma pack(1)
struct mlv_block_t
{
	uint8_t block_type[mlv_keyword_size];
	uint32_t block_size;
};
#pragma pack

const int mlv_struct_size = sizeof(mlv_block_t);

inline bool isMlvBlock(const mlv_block_t * pMlvBlock)
{
	for (auto iKeyword = 0; iKeyword < MLVKeywords::mlv_array_size; ++iKeyword)
		if (memcmp(pMlvBlock, MLVKeywords::mlv_array[iKeyword], mlv_keyword_size) == 0)
			return true;

	return false;
}

uint32_t read_block_drive(HANDLE & hDrive, uint64_t offset, uint8_t * data_buffer, uint32_t read_size)
{
	if (hDrive == INVALID_HANDLE_VALUE)
		return 0;

	DWORD bytesRead = 0;

	uint32_t sector_offset = offset % SECTOR_SIZE;
	uint32_t sector_to_read = (sector_offset + read_size) / SECTOR_SIZE + 1;
	uint32_t bytes_to_read = sector_to_read * SECTOR_SIZE;
	if (bytes_to_read == 0)
		bytes_to_read = SECTOR_SIZE;

	uint8_t * sector_buffer = new uint8_t[bytes_to_read];

	LARGE_INTEGER liPos = { 0 };
	liPos.QuadPart = offset;
	::SetFilePointerEx(hDrive, liPos, NULL , FILE_BEGIN);

	if (::ReadFile(hDrive, sector_buffer, bytes_to_read, &bytesRead, NULL))
		if (bytesRead > 0)
		{
			memcpy(data_buffer, sector_buffer + sector_offset, read_size);
			bytesRead = read_size;
		}

	delete[] sector_buffer;

	return bytesRead;

}


#include "AbstractRaw.h"

const uint64_t sectros_3Tb = 5860533168;

class AbstractReader
{
public:
	AbstractReader(){};
	virtual ~AbstractReader(){};

	virtual bool open() = 0;
	virtual void close() = 0;
	virtual int read_data(uint8_t * data, int read_size, uint64_t offset) = 0;

};

class PhysicalReader
	: public AbstractReader
{
private:
	HANDLE hDrive_;
	bool bOpened_;
	int sector_size_;
	int number_sectors_;
	uint8_t *buffer_;
	std::string path_;
public:
	PhysicalReader(const int drive_number )
		: hDrive_(INVALID_HANDLE_VALUE)
		, bOpened_(false)
		, sector_size_(default_sector_size)
		, number_sectors_(defalut_number_sectors)
		, buffer_(nullptr)
	{
		path_ = drivePathFromNumber(drive_number);
		int buffer_size = number_sectors_*sector_size_;
		buffer_ = new uint8_t[buffer_size];
		ZeroMemory(buffer_, buffer_size);
	}
	~PhysicalReader()
	{
		close();
		remove_buffer();
	}
	bool open() override
	{
		bOpened_ = IO::open_read(hDrive_, path_);
		return bOpened_;
	}
	void close()
	{
		CloseHandle(hDrive_);
	}
	int read_data(uint8_t * data, int read_size, uint64_t offset)
	{
		if (!bOpened_)
			return -1;


		uint32_t sector_offset = offset % sector_size_;
		uint32_t sector_to_read = (sector_offset + read_size) / sector_size_ + 1;
		uint32_t bytes_to_read = sector_to_read * sector_size_;
		if (bytes_to_read == 0)
			bytes_to_read = sector_size_;

		int bytesWereRead = 0;

		uint8_t * sector_buffer = new uint8_t[bytes_to_read];

		LARGE_INTEGER liPos = { 0 };
		liPos.QuadPart = offset;	// ?????
		::SetFilePointerEx(hDrive, liPos, NULL, FILE_BEGIN);

		if (::ReadFile(hDrive, sector_buffer, bytes_to_read, &bytesWereRead, NULL))
		if (bytesRead > 0)
		{
			memcpy(data_buffer, sector_buffer + sector_offset, read_size);
			bytesRead = read_size;
		}

		delete[] sector_buffer;

		return bytesRead;
	}
private:
	void remove_buffer()
	{
		if (buffer_)
		{
			delete[] buffer_;
			buffer_ = nullptr;
		}
	}

};

class MLV_raw
	: public AbstractRaw
{
private:
	std::string target_folder_;
public:
	MLV_raw(DWORD drive_number, const std::string target_folder)
		:AbstractRaw(drive_number)
		, target_folder_(target_folder)
	{

	}

	void execute() override
	{
		HANDLE *hDrive = this->getHandle();
		const uint64_t drive_max = sectros_3Tb * SECTOR_SIZE;

		if (!this->isReady())
		{
			printf("Error open drive\r\n");
			return;
		}

		uint32_t counter = 0;

		uint64_t offset = 0;
		uint64_t header_offset = 0;

		uint8_t read_buffer[BLOCK_SIZE];

		DWORD bytesRead = 0;

		

		offset = 0;
		//offset = 0xE4B06EAA00;
		

		while (offset < drive_max)
		{
			header_offset = search_header(hDrive, offset);
			if ( header_offset == ERROR_RESULT )
				break;

			std::string target_name = IO::file_path_number(target_folder_, counter++, ".mlv");
			offset = saveMLV(target_name, hDrive, header_offset);
			offset += SECTOR_SIZE;

		}




	}

	uint64_t saveMLV(const std::string & target_name,  HANDLE * hDrive, uint64_t header_offset)
	{
		

		HANDLE hTarget = INVALID_HANDLE_VALUE;
		if (!IO::create_file(hTarget, target_name))
		{
			printf("Error create target file\r\n");
			return header_offset;
		}

		uint64_t keyword_offset = header_offset;

		while (true)
		{
			mlv_block_t mlv_blocl_header = { 0 };
			if (uint32_t bytes_read = read_block_drive(*hDrive, keyword_offset, (uint8_t*)&mlv_blocl_header, mlv_struct_size))
			{
				if (isMlvBlock((const mlv_block_t*)&mlv_blocl_header))
				{
					//uint32_t full_block_size = mlv_blocl_header.block_size + mlv_struct_size;
					if ((mlv_blocl_header.block_size > 0) && (mlv_blocl_header.block_size < 5*1024*1024))
					{

						uint8_t * block_data = new uint8_t[mlv_blocl_header.block_size];
						DWORD bytesWritten = 0;
						bool bResult = false;
						if (bytes_read = read_block_drive(*hDrive, keyword_offset, block_data, mlv_blocl_header.block_size))
						{
							bResult = IO::write_block(hTarget, block_data, bytes_read, bytesWritten);
							if (!bResult || (bytesWritten == 0))
							{
								delete[] block_data;
								printf("Error write to file.\r\n");
								break;
							}

							keyword_offset += bytesWritten;
						}

						delete[] block_data;
					}
					else
						break;
				}
				else
					break;
			}
			else
				break;

		}

		CloseHandle(hTarget);
		keyword_offset /= SECTOR_SIZE;
		keyword_offset *= SECTOR_SIZE;
		return keyword_offset;
	}

	uint64_t search_header(HANDLE * hDrive, uint64_t start_offset)
	{
		uint8_t read_buffer[BLOCK_SIZE];
		DWORD bytesRead = 0;

		uint64_t header_offset = 0;

		while (true)
		{
			bytesRead = read_block_drive(*hDrive, start_offset, read_buffer, BLOCK_SIZE);
			if (bytesRead == 0)
			{
				printf("Error read drive\r\n");
				break;
			}

			for (auto iSector = 0; iSector < BLOCK_SIZE; iSector += SECTOR_SIZE)
			{
				if (memcmp(read_buffer + iSector, MLVKeywords::mlv_array[0], mlv_keyword_size) == 0)
				{
					header_offset = start_offset;
					header_offset += iSector;
					return header_offset;
				}
			}
			start_offset += bytesRead;
		}
		return ERROR_RESULT;
	}

};


#endif