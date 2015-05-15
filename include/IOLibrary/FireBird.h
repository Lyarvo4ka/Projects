#ifndef FIREBIRD_H
#define FIREBIR_H

#include <windows.h>
#include <sqltypes.h>
#include "AbstractRaw.h"
#include "constants.h"

#pragma pack( 1 )
struct firebird_page
{
	SCHAR pag_type;
	UCHAR pag_flags;
	USHORT pag_checksum;
	ULONG pag_generation;
	ULONG pag_scn;
	ULONG reserved;
	bool isFireBirdPage()
	{
		if (pag_type >= 0x01 && pag_type <= 0xA)
			if (pag_checksum == 0x3039)
				return true;
		return false;
	}
};
#pragma pack()

const int firebird_size = sizeof(firebird_page);
const int FB_Size = 8 * 1024;


class FileWriter
{
public:
	FileWriter(const std::string & target_folder)
		:folder_(target_folder)
		, counter_(0)
		, bReady_(false)
		, bNewFile_(false)
		, hHandle_( INVALID_HANDLE_VALUE)
	{

	}

	void AddPage(BYTE * buffer, DWORD buffer_size, LONGLONG page_offset)
	{
		if (bNewFile_)
		{
			if (bReady_)
				CloseHandle(hHandle_);

			create_new_file(page_offset);

			bNewFile_ = false;
		}
		DWORD bytesWritten = 0;
		bool bResult = IO::write_block(hHandle_, buffer, buffer_size, bytesWritten);
		if (bytesWritten == 0 || !bResult )
		{
			printf("Error write to file");
		}

	}

	void create_new_file(LONGLONG page_offset_name)
	{
		
		std::string file_name = IO::file_offset_name(folder_, page_offset_name, ".fdb");
		if (!IO::create_file(hHandle_, file_name))
		{
			printf("Error create file: %s", file_name.c_str());
			exit(-3);
		}
		bReady_ = true;
	}

	void setNewFile()
	{
		bNewFile_ = true;
	}

private:
	bool bNewFile_;
	bool bReady_;
	std::string folder_;
	int counter_;
	HANDLE hHandle_;

};

class FireBird_Raw
	: public AbstractRaw
{
public:
	FireBird_Raw(const DWORD drive_number , const std::string & target_folder)
		: AbstractRaw(drive_number)
		, folder_(target_folder)
		, fileWriter_(nullptr)

	{
		fileWriter_ = new FileWriter(target_folder);
	}
	~FireBird_Raw()
	{
		delete fileWriter_;
	}
	void execute() override
	{
		BYTE buffer[BLOCK_SIZE];
		DWORD bytesRead = 0;
		HANDLE *hSource = this->getHandle();

		bool bResult = false;
		firebird_page * pFireBird = nullptr;

		LONGLONG offset = 0;

		while (true)
		{
			IO::set_position(*this->getHandle(), offset);
			bResult = IO::read_block(*hSource, buffer, BLOCK_SIZE, bytesRead);
			if ( bytesRead == 0 || !bResult )
				break;

			for (DWORD iPage = 0; iPage < BLOCK_SIZE; iPage += FB_Size)
			{
				pFireBird = (firebird_page *)&(buffer[iPage]);
				if (pFireBird->isFireBirdPage())
				{
					LONGLONG file_offset = offset;
					offset += iPage;
					fileWriter_->AddPage(buffer, FB_Size, offset);
				}
			}

			offset += bytesRead;

		}


	}
private:
	std::string folder_;
	FileWriter *fileWriter_;
};


//enum page_type { UNDEFINE , };

#endif