#include "SignatureTest.h"
#include "constants.h"

#include "boost/filesystem.hpp"

void Signture_Testing(const std::string & folder)
{
	
	FileFinder finder;
	stringlist extList = {".mov"};
	finder.FindFiles(folder, extList);
	auto file_list = finder.getFileNames();

	BYTE buff[SECTOR_SIZE];
	DWORD bytesRead = 0;

	bool bResult = false;

	auto fileIter = file_list.begin();
	while (fileIter != file_list.end())
	{
		std::string file_name = *fileIter;
		HANDLE hFile = INVALID_HANDLE_VALUE;
		if (!IO::open_read(hFile, file_name))
		{
			printf("Error to open file: %s", file_name.c_str());
			return;
		}
		
		bResult = IO::read_block(hFile, buff, SECTOR_SIZE, bytesRead);
		CloseHandle(hFile);
		if (!bResult && ( bytesRead == 0 ) )
		{
			printf("Error read file.%s" , file_name.c_str());
			break;
		}


		bool isGoodHeader = false;
		for ( auto iByte = 0 ; iByte < SECTOR_SIZE ; ++iByte)
			if ( buff[iByte] != 0x00 )
			{
				isGoodHeader = true;
				break;
			}

		if ( !isGoodHeader )
			boost::filesystem::rename(file_name , file_name + ".bad_file");
		++fileIter;
	}
}