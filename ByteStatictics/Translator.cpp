#include "StdAfx.h"
#include "Translator.h"

#include <assert.h>

#include <map>
using std::map;
using std::pair;


CTranslator::CTranslator(void)
{
}


CTranslator::~CTranslator(void)
{
}


TableTranslator::TableTranslator()
{

}
TableTranslator::~TableTranslator()
{

}
bool TableTranslator::OpenDump( const wstring & dumpPath)
{
	return open_read(dumpHandle_,dumpPath);
}
bool TableTranslator::OpenTable(const wstring & tablePath)
{
	return open_read(tableHandle_,tablePath);
}
bool TableTranslator::open_read(HANDLE & handle, const wstring & file_path)
{
	handle = CreateFile( file_path .c_str(),
						 GENERIC_READ ,
						 FILE_SHARE_READ,
						 NULL,
						 OPEN_EXISTING,
						 0,
						 NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;		
}
bool TableTranslator::open_write(HANDLE & handle, const wstring & file_path)
{
	handle = CreateFile( file_path .c_str(),
						 GENERIC_WRITE ,
						 FILE_SHARE_READ,
						 NULL,
						 CREATE_ALWAYS,
						 0,
						 NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;		
}
void TableTranslator::ReadTable()
{
	assert(tableHandle_ != INVALID_HANDLE_VALUE);

	LONG tableBytes = ::GetFileSize(tableHandle_,0);
	LONG table_size = tableBytes / sizeof(WORD);

	BYTE *pBuffer = new BYTE[tableBytes];

	DWORD bytesRead = 0;
	if ( ! ReadFile( tableHandle_, pBuffer, tableBytes, & bytesRead, NULL ) )
	{
		printf("Error read file");
		return;
	}

	WORD counter = 0;
	vecTable_.resize(table_size,0);
	WORD temp = 0;
	WORD *ptrBuffer = (WORD*) & pBuffer[0];
	while (counter < table_size)
	{
		temp = (*ptrBuffer << 8) | (*ptrBuffer >> 8);
		if (temp > 0x4000)
			vecTable_.at(counter) = temp - 0x4000;

		++ptrBuffer;
		++counter;
	}

	delete pBuffer;

}
void TableTranslator::SaveToFile(const wstring & outputStr, bool withService)
{
	assert(dumpHandle_ != INVALID_HANDLE_VALUE);

	LONG offset = 0;
	HANDLE hWrite_file = INVALID_HANDLE_VALUE;
	if ( !open_write(hWrite_file,outputStr) )
		return ;

	const LONG block_size = 0x8400;
	BYTE * pBuffer = new BYTE[block_size];
	DWORD bytesRead = 0;
	DWORD bytesWrite = 0;
	auto tableIter = vecTable_.begin();
	while ( tableIter != vecTable_.end() )
	{
		offset = *tableIter * block_size;
		::SetFilePointer(dumpHandle_,offset,NULL,FILE_BEGIN);
		if ( !::ReadFile(dumpHandle_,pBuffer,block_size,&bytesRead,NULL) )
		{
			printf("Error read file\r\n");
			break;
		}

		if ( !::WriteFile(hWrite_file,pBuffer,bytesRead,&bytesWrite,NULL) )
		{
			printf("Error write to file\r\n");
			break;
		}
		++tableIter;
	}

	delete pBuffer;
}

bool Open_Read(HANDLE & handle, const wstring & file_path)
{
	handle = CreateFile( file_path .c_str(),
						GENERIC_READ ,
						FILE_SHARE_READ,
						NULL,
						OPEN_EXISTING,
						0,
						NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;		
}
bool Open_Read(HANDLE & handle, const string & file_path)
{
	handle = CreateFileA( file_path .c_str(),
		GENERIC_READ ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	DWORD dwError = GetLastError();
	return (handle != INVALID_HANDLE_VALUE) ? true : false;		
}
bool Open_Write(HANDLE & handle, const wstring & file_path)
{
	handle = CreateFile( file_path .c_str(),
						GENERIC_READ | GENERIC_WRITE ,
						FILE_SHARE_READ,
						NULL,
						OPEN_EXISTING,
						0,
						NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;	
}
bool Open_Write(HANDLE & handle, const string & file_path)
{
	handle = CreateFileA( file_path .c_str(),
		GENERIC_READ | GENERIC_WRITE ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;	
}
bool Create_File(HANDLE & handle, const wstring & file_path)
{
	handle = CreateFile( file_path .c_str(),
						GENERIC_WRITE ,
						FILE_SHARE_READ,
						NULL,
						CREATE_ALWAYS,
						0,
						NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;	
}
bool Create_File(HANDLE & handle, const string & file_path)
{
	handle = CreateFileA( file_path .c_str(),
		GENERIC_WRITE ,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		0,
		NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;	
}
DWORD File_Size( HANDLE & handle)
{
	return ::GetFileSize(handle, NULL);
}


AdditionConflicts::AdditionConflicts()
{

}
void AdditionConflicts::FindFiles(const wstring & folder_path)
{
	HANDLE hFindFile = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA findData;

	TCHAR wFilePath[MAX_PATH];
	TCHAR wPath[MAX_PATH];
	TCHAR wDirPath[MAX_PATH];
	//if (GetFullPathName(_DirectoryPath,MAX_PATH,wPath,(LPTSTR*)&wFilePart) == 0)
	//	return FALSE;
	wcscpy(wDirPath,folder_path.c_str());
	wcscat(wDirPath,_T("\\*.*"));
	// First Check if Directory
	//if ((hFindFile = FindFirstFile(wDirPath,&findData)) != INVALID_HANDLE_VALUE)
	//{
	//	do 
	//	{
	//		if (!wcsncmp(findData.cFileName,_T("."),1) || !wcsncmp(findData.cFileName,_T(".."),2))
	//			continue;

	//		// Get PAHT to Directory
	//		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	//		{
	//			//if (GetFullPathName(_DirectoryPath,MAX_PATH,wPath,(LPTSTR*)&wFilePart) == 0)
	//			//	return FALSE;
	//			wcscpy(wPath,folder_path.c_str());
	//			wcscat(wPath,_T("\\"));
	//			wcscat(wPath,findData.cFileName);
	//			//wprintf(_T("%s   <DIR>\r\n"),wPath);
	//			FindFiles(wPath);
	//		}				

	//		//SearchFiles(
	//	}while(FindNextFile(hFindFile, &findData) );

	//	FindClose(hFindFile);
	//		
	//}

	if ((hFindFile = FindFirstFile(wDirPath,&findData)) != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if (!wcsncmp(findData.cFileName,_T("."),1) || !wcsncmp(findData.cFileName,_T(".."),2))
				continue;

			// Get PAHT to Directory
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				wcscpy(wFilePath,folder_path.c_str());
				wcscat(wFilePath,_T("\\"));
				wcscat(wFilePath,findData.cFileName);
				ListFiles_.push_back( wstring(wFilePath) );

			}				

			//SearchFiles(
		}while(FindNextFile(hFindFile, &findData) );

		FindClose(hFindFile);
	}

}


void AdditionConflicts::writeToImage(const wstring & file_name, const wstring & image_name)
{
	HANDLE hImage = INVALID_HANDLE_VALUE;
	bool bResult = false;
	wprintf(L"Compute file: %s\r\n",file_name.c_str());
	bResult = Open_Write(hImage,image_name);
	if (!bResult)
		bResult = Create_File(hImage,image_name);
	if (!bResult)
	{
		wprintf( L"Error open to write image file... (%s)\r\n" , image_name.c_str() );
		return;
	}

	HANDLE hReadFile = INVALID_HANDLE_VALUE;
	if ( !Open_Read(hReadFile, file_name) )
	{
		wprintf( L"Error open to read source file... (%s)\r\n" , file_name.c_str() );
		return;
	}
	LONG fileSize = ::GetFileSize(hReadFile,0);

	BYTE * data_buffer = new BYTE[fileSize];
	DWORD bytesRead = 0;
	//	read block
	if ( !ReadFile(hReadFile, data_buffer,fileSize, &bytesRead,NULL) )
	{
		wprintf( L"Error read from file... (%s)\r\n" , file_name.c_str() );
		return;
	}

	map<BYTE , pagesTo> mapPages;
	auto findIter = mapPages.begin();
	BYTE page_offset = 0;
	WORD *change_counter = NULL;
	DWORD file_offset = 0;
	WORD counts = 0;
	for (BYTE iPage = 0; iPage < pages_count; ++iPage)
	{
		file_offset = iPage * page_size_sa;
		page_offset = data_buffer[file_offset + 2051];
		change_counter = (WORD*)&data_buffer[file_offset + 2060];
		counts = *change_counter;
		//counts = counts >> 8 | counts << 8 ;
		findIter = mapPages.find(page_offset);
		if  (*change_counter > 0)
		if ( findIter == mapPages.end() )
		{
			pagesTo pages;
			pages.number = iPage;
			pages.counter = *change_counter;
			pages.pageOffset = page_offset;
			mapPages.insert( std::pair<BYTE, pagesTo> (page_offset, pages) );
		}
		else
		{
		//	if (findIter->second.counter < *change_counter)
			{
				findIter->second.counter = *change_counter;
				findIter->second.number = iPage;
				findIter->second.pageOffset = page_offset;
			}
		}
	}

	findIter = mapPages.begin();

	DWORD page_pos = 0;
	BYTE writeBuffer[page_size];
	DWORD writeOffset = 0;
	DWORD readOffset = 0;
	DWORD bytesWrite = 0;
	WORD * block_number = (WORD *) & data_buffer[2049];
	* block_number = *block_number >> 8 | *block_number<<8;
	while (findIter != mapPages.end())
	{
		page_pos = findIter->second.number * page_size_sa;
		memcpy( writeBuffer , data_buffer+page_pos , 2048 );
		for ( BYTE page_number = 0; page_number < 15; ++ page_number )
		{
			writeOffset = 2048 + page_number*2048;
			readOffset = 2048 + 112 + page_number*(2048 + 104);
			readOffset += page_pos;
			memcpy( writeBuffer + writeOffset, data_buffer + readOffset, 2048);
		}
		LARGE_INTEGER write_pos;
		write_pos.QuadPart = * block_number;
		write_pos.QuadPart *= block_size;

		write_pos.QuadPart += findIter->second.pageOffset * page_size;
		::SetFilePointerEx(hImage,write_pos,NULL,FILE_BEGIN);
		if ( !::WriteFile(hImage, writeBuffer,page_size,&bytesWrite,NULL) )
		{
			wprintf( L"Error open to image file... (%s)\r\n" , image_name.c_str() );
			return;
		}

		++findIter;
	}

	delete data_buffer;
	CloseHandle(hImage);

}
void AdditionConflicts::Execute(const wstring & image_name)
{
	auto it = ListFiles_.begin();
	while (it != ListFiles_.end())
	{
		writeToImage(*it,image_name);
		++it;
	}
}

void setHalfClusterFF(const wstring & file_name, const DWORD cluster_size)
{
	HANDLE hWriteFile = INVALID_HANDLE_VALUE;
	bool bResult = false;
	wstring write_file(file_name + L".result");
	//bResult = Open_Write(hWriteFile,write_file);
	//if (!bResult)
		bResult = Create_File(hWriteFile,write_file);
	if (!bResult)
	{
		wprintf( L"Error open to write image file... (%s)\r\n" , write_file.c_str() );
		return;
	}

	HANDLE hReadFile = INVALID_HANDLE_VALUE;
	if ( !Open_Read(hReadFile, file_name) )
	{
		wprintf( L"Error open to read source file... (%s)\r\n" , file_name.c_str() );
		return;
	}

	BYTE * buffer = new BYTE[cluster_size];
	DWORD bytes_read = 0;
	DWORD bytes_write = 0;
	DWORD half_size = cluster_size/2;
	while (true)
	{
		if ( ! ReadFile(hReadFile,buffer,cluster_size,&bytes_read,NULL) )
		{
			wprintf( L"Error to read source file... (%s)\r\n" , file_name.c_str() );
			break;
		}
		if (bytes_read == 0)
			break;

		memset(buffer,0xFF,cluster_size/2);

		if ( ! WriteFile(hWriteFile,buffer,bytes_read,&bytes_write,NULL) )
		{
			wprintf( L"Error to read source file... (%s)\r\n" , write_file.c_str() );
			break;
		}
	}

	delete buffer;

	CloseHandle(hReadFile);
	CloseHandle(hWriteFile);

}

XorCorrector::XorCorrector()
	: hInput_(INVALID_HANDLE_VALUE)
	, hOutput_(INVALID_HANDLE_VALUE)
{

}
XorCorrector::~XorCorrector()
{
	CloseHandle(hInput_);
	CloseHandle(hOutput_);
}
void XorCorrector::CorrectXor(const wstring & input_file, const wstring & output_file)
{
	if ( !Open_Read(hInput_,input_file) )
	{
		wprintf( L"Error to \'OPEN\' source file... (%s)\r\n" , input_file.c_str() );
		return;
	}


	if ( !Open_Write(hOutput_,output_file) )
		if (!Create_File(hOutput_,output_file) )
		{
			wprintf( L"Error to \'CREATE\' target file... (%s)\r\n" , output_file.c_str() );
			return;
		}


	LONG fileSize = ::GetFileSize(hInput_,0);

	BYTE * data_buffer = new BYTE[fileSize];
	DWORD bytesRead = 0;

	if ( ! ReadFile(hInput_,data_buffer,fileSize,&bytesRead,NULL) )
	{
		wprintf( L"Error to read source file... (%s)\r\n" , input_file.c_str() );
		delete data_buffer;
		return;
	}

	LONG bytePos = 0;
	BYTE byteValue = 0;
	BYTE tempValue = 0;
	BYTE count_0 = 0;
	BYTE count_1 = 0;
	while ( bytePos < fileSize )
	{
		byteValue = data_buffer[bytePos];

		if (byteValue != 0x00 && byteValue != 0xFF)
		{
			tempValue = byteValue;
			count_0 = 0;
			count_1 = 0;
			printf("Found value(\'%.2X\') %d ",tempValue, bytePos);
			for (BYTE iBit = 0 ; iBit < 8; ++iBit)
			{
				tempValue = byteValue >> iBit;
				tempValue &= 0x01;

				if (tempValue > 0)
					++count_1;
				else
					++count_0;
			}

			printf("{ [0 - \'%d\'],[1 - \'%d\'] } ",count_0,count_1);
			if ( count_0 == count_1)
				printf("count of 0 is equal to 1");
			else
				if ( count_0 > count_1)
				{
					data_buffer[bytePos] = 0;
					printf(" corrected to 0");
				}
				else
				{
					data_buffer[bytePos] = 0xFF;
					printf(" corrected to FF");
				}
				printf("\r\n");
		}
		++bytePos;
	}


	DWORD bytesWrite = 0;
	BYTE * write_page = new BYTE[8640];
	memset(write_page,0x11,8640);

	bytePos = 0;
	while ( bytePos < fileSize)
	{
		memcpy(write_page, data_buffer + bytePos, 1024);
		for (BYTE i = 0; i < 7; ++i)
			memcpy(write_page + 1024 + 48 + i *(1024 + 44), data_buffer + 1024 + i*1024,1024 );
		bytePos += 8192;

		if ( ! WriteFile(hOutput_,write_page,8640,&bytesWrite,NULL) )
		{
			wprintf( L"Error to write target file... (%s)\r\n" , output_file.c_str() );
			break;
		}
	}


	delete data_buffer;
	delete write_page;
}
void XorCorrector::SetNull(const wstring & input_file, const wstring & output_file)
{
	if ( !Open_Read(hInput_,input_file) )
	{
		wprintf( L"Error to \'OPEN\' source file... (%s)\r\n" , input_file.c_str() );
		return;
	}


	if ( !Open_Write(hOutput_,output_file) )
		if (!Create_File(hOutput_,output_file) )
		{
			wprintf( L"Error to \'CREATE\' target file... (%s)\r\n" , output_file.c_str() );
			return;
		}


	LONG fileSize = ::GetFileSize(hInput_,0);

	BYTE * data_buffer = new BYTE[fileSize];
	DWORD bytesRead = 0;

	if ( ! ReadFile(hInput_,data_buffer,fileSize,&bytesRead,NULL) )
	{
		wprintf( L"Error to read source file... (%s)\r\n" , input_file.c_str() );
		delete data_buffer;
		return;
	}

	DWORD bytesWrite = 0;
	BYTE * write_page = new BYTE[8640];
	memset(write_page,0,8640);

	LONG bytePos = 0;
	while ( bytePos < fileSize)
	{
		memset(write_page,0x00,8640-112);
		memset(write_page+ 8640-112,0xFF,112);

		//memcpy(write_page, data_buffer + bytePos, 1024);
		for (BYTE i = 0; i < 8; ++i)
			memcpy(write_page  + i *(1024 + 42), data_buffer + i *(1024 + 42) + bytePos,1024 );

		bytePos += 8640;

		if ( ! WriteFile(hOutput_,write_page,8640,&bytesWrite,NULL) )
		{
			wprintf( L"Error to write target file... (%s)\r\n" , output_file.c_str() );
			break;
		}
	}

	delete data_buffer;
	delete write_page;
}

BlockCutting::BlockCutting()
	: hInput_(INVALID_HANDLE_VALUE)
	, hOutput_(INVALID_HANDLE_VALUE)
{

}
BlockCutting::~BlockCutting()
{
	if ( hInput_ != INVALID_HANDLE_VALUE)
		CloseHandle(hInput_);
	hInput_ = INVALID_HANDLE_VALUE;

	if ( hOutput_ != INVALID_HANDLE_VALUE )
		CloseHandle(hOutput_);
	hOutput_ = INVALID_HANDLE_VALUE;
}
bool BlockCutting::OpenFiles(const wstring & filePath)
{
	if ( !Open_Read(hInput_ , filePath) )
	{
		wprintf( L"Error open file to read...(%s)\r\n",filePath.c_str() );
		return false;
	}
	const wstring output(L"E:\\Public\\31351\\Result.dump");
	if ( !Create_File(hOutput_ , output ) )
		if ( !Open_Write(hOutput_, output ) )
		{
			wprintf( L"Error open file to write...(%s)\r\n",output.c_str() );
			return false;
		}
	return true;
}
void BlockCutting::InitPagePos()
{
	PageArray block1;
	block1.AddPage( PagePos(2902,2) );
	block1.AddPage( PagePos(3296,2) );
	block1.AddPage( PagePos(3770,2) );
	block1.AddPage( PagePos(7576,2) );
	block1.AddPage( PagePos(7806,2) );
	block1.AddPage( PagePos(9178,6) );
	arrayBlock_.push_back(block1);

	PageArray block2;
	block2.AddPage( PagePos(2316,2) );
	block2.AddPage( PagePos(9170,14) );
	arrayBlock_.push_back(block2);

	PageArray block3;
	block3.AddPage( PagePos(3328,2) );
	block3.AddPage( PagePos(4228,2) );
	block3.AddPage( PagePos(4586,2) );
	block3.AddPage( PagePos(5198,2) );
	block3.AddPage( PagePos(6274,2) );
	block3.AddPage( PagePos(9178,6) );
	arrayBlock_.push_back(block3);

	PageArray block4;
	block4.AddPage( PagePos(92,2) );
	block4.AddPage( PagePos(1950,2) );
	block4.AddPage( PagePos(2014,2) );
	block4.AddPage( PagePos(2236,2) );
	block4.AddPage( PagePos(3282,2) );
	block4.AddPage( PagePos(3624,2) );
	block4.AddPage( PagePos(9180,4) );
	arrayBlock_.push_back(block4);
}
void BlockCutting::CutBlock(DWORD block_number , const BYTE * sourcePage, BYTE * targetPage)
{
	if (!sourcePage)
		return;

	if (!targetPage)
		return;

	int number = block_number % 4;
	PageArray curArray( arrayBlock_.at( number ) );
	int prev_source = 0;
	int prev_target = 0;
	int copy_size = 0;
	for (std::size_t offset = 0; offset < curArray.count() ; ++offset)
	{
		copy_size = curArray.getPage(offset)->offset() - prev_source;
		memcpy(targetPage + prev_target, sourcePage + prev_source, copy_size);
		prev_source = curArray.getPage(offset)->count() + curArray.getPage(offset)->offset();
		prev_target += copy_size;
	}
}
void BlockCutting::Execute()
{
	BYTE * pSourcePage = new BYTE[Page_Size];
	BYTE * pTargetPage = new BYTE[Page_Size - 16];
	
	if ( hInput_ == INVALID_HANDLE_VALUE)
		if ( hOutput_ == INVALID_HANDLE_VALUE)
			return;

	int iPage = 0;
	int iBlock = 0;

	DWORD byteRead = 0;
	DWORD byteWrite = 0;

	while (true)
	{
		if ( ! ReadFile(hInput_,pSourcePage,Page_Size, &byteRead, NULL ) )
		{
			printf("Error read file");
			break;
		}

		if (byteRead == 0)
			break;

		CutBlock(iBlock , pSourcePage, pTargetPage);
		if ( ! WriteFile(hOutput_, pTargetPage, Page_Size - 16, &byteWrite,NULL))
		{
			printf("Error write file");
			break;
		}

		++iPage;
		if (iPage >= Page_Count)
		{
			iPage = 0;
			++iBlock;
		}
	}


	delete pTargetPage;
	delete pSourcePage;
}

GatherByBlock::GatherByBlock()
	: hSource_(INVALID_HANDLE_VALUE)
	, hTarger_(INVALID_HANDLE_VALUE)
{

}
GatherByBlock::~GatherByBlock()
{
	CloseFile(hSource_);
	CloseFile(hTarger_);
}
bool GatherByBlock::OpenSource(const wstring & source_file)
{
	CloseFile(hSource_);
	return Open_Read(hSource_,source_file);
}
bool GatherByBlock::OpenTarget(const wstring & target_file)
{
	CloseFile(hTarger_);
	bool bResult = Open_Write(hTarger_,target_file);
	if (!bResult)
		return Create_File(hTarger_,target_file);
	return false;
}
void GatherByBlock::CloseFile(HANDLE & file_handle)
{
	if ( file_handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(file_handle);
		file_handle = INVALID_HANDLE_VALUE;
	}
}
bool GatherByBlock::ReadBlock(BYTE * data_buffer, const DWORD size_buffer, short block_number)
{
	if ( hSource_ == INVALID_HANDLE_VALUE)
		return false;

	if ( !data_buffer )
		return false;

	LARGE_INTEGER readOffset ;
	readOffset.QuadPart = size_buffer * block_number;
	
	DWORD BytesToRead = 0;

	::SetFilePointerEx(hSource_,readOffset,NULL,FILE_BEGIN);
	bool bResult = ::ReadFile(hSource_, data_buffer, size_buffer, &BytesToRead, NULL );
	if (BytesToRead == 0)
		return false;

	return (BytesToRead != 0) ? true : false;
}
void GatherByBlock::UpdateHeader(BYTE * data_buffer, short block_value)
{
	if (!data_buffer)
		return ;

	if (block_value > 255 )
	{
		int k =1 ;
		k = 2;
	}

	block_value /= 2;
	HeaderBlock * pHeader = (HeaderBlock *) data_buffer;
	BYTE high = ( block_value & 0xFF00 ) >> 8;
	BYTE low = ( block_value & 0x00FF );


	memset( pHeader->highBlockNumber, high, sizeof(pHeader->highBlockNumber) );
	memset( pHeader->lowBlockNumber, low, sizeof(pHeader->highBlockNumber) );

}
bool GatherByBlock::WriteBlock(BYTE * data_buffer, const DWORD size_buffer, LONGLONG offset)
{
	if ( hTarger_ == INVALID_HANDLE_VALUE)
		return false;

	if ( !data_buffer )
		return false;

	LARGE_INTEGER write_pos;
	write_pos.QuadPart = offset;
	HeaderBlock * pHeader = (HeaderBlock *) data_buffer;

	DWORD BytesWrite = 0;

	::SetFilePointerEx(hTarger_,write_pos,NULL,FILE_BEGIN);
	if ( !::WriteFile(hTarger_, pHeader, sizeof(HeaderBlock), &BytesWrite, NULL ) )
	{
		printf("Error to write #%d",::GetLastError());
		return false;
	}

	DWORD nextOffset = sizeof(HeaderBlock) + 16;
	write_pos.QuadPart += sizeof(HeaderBlock) + 16;

	::SetFilePointerEx(hTarger_,write_pos,NULL,FILE_BEGIN);
	if ( !::WriteFile(hTarger_, data_buffer + nextOffset, size_buffer - nextOffset, &BytesWrite, NULL ) )
	{
		printf("Error to write #%d",::GetLastError());
		return false;
	}

	return true;
}
bool GatherByBlock::WriteBlocks(BYTE * buffer1, BYTE * buffer2, const DWORD size_buffer, LONGLONG offset)
{
	if ( hTarger_ == INVALID_HANDLE_VALUE)
		return false;

	if ( !buffer1 )
		return false;

	LARGE_INTEGER write_pos;
	write_pos.QuadPart = offset;
	HeaderBlock * pHeader = (HeaderBlock *) buffer1;

	DWORD BytesWrite = 0;

	::SetFilePointerEx(hTarger_,write_pos,NULL,FILE_BEGIN);
	if ( !::WriteFile(hTarger_, pHeader, sizeof(HeaderBlock), &BytesWrite, NULL ) )
	{
		printf("Error to write #%d",::GetLastError());
		return false;
	}

	DWORD nextOffset = sizeof(HeaderBlock) + 16;
	BYTE * pFF = new BYTE[TargetSize - nextOffset];
	memset(pFF, 0xFF,TargetSize - nextOffset);
	write_pos.QuadPart += nextOffset;
	::SetFilePointerEx(hTarger_,write_pos,NULL,FILE_BEGIN);
	if ( !::WriteFile(hTarger_, pFF, TargetSize - nextOffset, &BytesWrite, NULL ) )
	{
		printf("Error to write #%d",::GetLastError());
		return false;
	}
	delete pFF;
	write_pos.QuadPart += TargetSize - nextOffset;

	::SetFilePointerEx(hTarger_,write_pos,NULL,FILE_BEGIN);
	if ( !::WriteFile(hTarger_, buffer1 + SourceSize, size_buffer - SourceSize, &BytesWrite, NULL ) )
	{
		printf("Error to write #%d",::GetLastError());
		return false;
	}

	write_pos.QuadPart += size_buffer - SourceSize;
	::SetFilePointerEx(hTarger_,write_pos,NULL,FILE_BEGIN);
	if ( !::WriteFile(hTarger_, buffer2 + SourceSize, size_buffer - SourceSize, &BytesWrite, NULL ) )
	{
		printf("Error to write #%d",::GetLastError());
		return false;
	}

	return true;
}




FileExtensions::~FileExtensions()
{
	map<wstring ,DWORD>::iterator it;
	if (m_Map.size() > 0)
	{
		while ((it = m_Map.begin()) != m_Map.end())
			it = m_Map.erase(it);
	}
}
BOOL FileExtensions::Add(wstring &_newExt,DWORD _extension)
{
	map<wstring,DWORD>::iterator itMap;
	itMap = m_Map.find(_newExt);
	if (itMap == m_Map.end())
	{
		m_Map.insert(ExtFiles(_newExt,_extension));
	}
	else
		return FALSE;
	return TRUE;
}
BOOL FileExtensions::AddFromFile(wchar_t * _pPath, DWORD _dwMaxFiles)
{
	HANDLE hFile = CreateFile(_pPath,
		GENERIC_READ,
		FILE_SHARE_READ,NULL,OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "Error Open File";
		return FALSE;
	}
	DWORD dwFileSize = GetFileSize(hFile,NULL);
	if ( dwFileSize <= 0 )
		return FALSE;

	BYTE *pBuffer = new BYTE[dwFileSize];
	DWORD dwBytesRead = 0;
	if ( ! ReadFile (hFile, pBuffer, dwFileSize, &dwBytesRead,NULL) )
	{
		cout << "Error Read File";
		return FALSE;		
	}
	DWORD iPos = 0;
	DWORD iStart = 0;
	while (iPos < dwBytesRead)
	{
		if (pBuffer[iPos] == '\n')
		{
			DWORD dwExtSize = iPos - iStart;
			if ( dwExtSize > 0)
			{	
				BYTE *pExt = new BYTE[dwExtSize];
				memset(pExt,0,dwExtSize);
				memcpy(pExt,pBuffer + iStart, dwExtSize-1);
				string sExt((const char *)pExt);

				delete pExt;

				//string strExt(
				DWORD dwWideSize = MultiByteToWideChar(CP_ACP, NULL, (LPCSTR)sExt.c_str(), -1 , NULL , 0);
				wchar_t *pWchar = new wchar_t[dwWideSize];
				MultiByteToWideChar(CP_ACP, NULL, (LPCSTR)sExt.c_str(), -1 , pWchar , dwWideSize);
				wstring str(pWchar);
				this->Add(str,_dwMaxFiles);
				delete pWchar;
				iStart = iPos + 1;
			}
		}
		++iPos;
	}

	delete pBuffer;
	CloseHandle(hFile);
	return TRUE;
}

BOOL FileExtensions::isPresent(wstring &_FileExt)
{
	map<wstring,DWORD>::iterator itMap;
	itMap = m_Map.find(_FileExt);
	if (itMap == m_Map.end())
		return FALSE;
	return TRUE;
}

BOOL FileExtensions::UpdateExt(wstring &_FileExt)
{
	map<wstring,DWORD>::iterator itMap;
	itMap = m_Map.find(_FileExt);
	if (itMap == m_Map.end())
		return FALSE;
	--itMap->second;
	if (itMap->second == 0)
	{
		m_Map.erase(itMap);
	}
	return TRUE;
}


bool FileExtensions::isEmpty() const
{
	return m_Map.empty();
}


BOOL FileSearcher::Execute(wchar_t *_FilePath, size_t _iNumber)
{
	HANDLE hFile = CreateFile(_FilePath,
							   GENERIC_READ,
							   FILE_SHARE_READ,NULL,OPEN_EXISTING,
							   FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << "Error Open File";
		return FALSE;
	}
	DWORD dwSize = 0;
	dwSize = ::GetFileSize(hFile,NULL);
	if (dwSize > 0)
	{
		DWORD dwBytesRead = 0;
		BYTE *pBuffer = new BYTE[dwSize];
		if (!ReadFile(hFile, pBuffer, dwSize, &dwBytesRead, NULL) )
		{
			std::cout << "Can't Read File";
			return -1;
		}
		string str((const char *)pBuffer);
		char DataComp[] = "Date: ";
		size_t iPosition = str.find(DataComp);
		size_t iNamePos = strlen(DataComp) + iPosition;
		iNamePos += 5;
		size_t iDataSize = 11;
		string strSub = str.substr(iNamePos,iDataSize);
		char buff[260];
		sprintf(buff,"%.4d ukr.net %s.eml",_iNumber,strSub.c_str());
		
		HANDLE hWriteFile = CreateFileA(buff,
							 GENERIC_WRITE,
							 FILE_SHARE_WRITE,
							 NULL,
							 OPEN_ALWAYS,
							 0,NULL);
	if (hWriteFile == INVALID_HANDLE_VALUE)
	{
		printf("Error Create File\r\n");
		return FALSE;
	}
	DWORD dwBytesWrite = 0;
	if (!WriteFile(hWriteFile, pBuffer, dwSize, &dwBytesWrite, NULL) )
	{
		std::cout << "Can't Write File";
		return -1;
	}
	CloseHandle(hWriteFile);
								
		delete pBuffer;
	}

	CloseHandle(hFile);

	return TRUE;
}
#define MAX_BYTE 256
BOOL FileSearcher::GetEntropy(wchar_t * _FilePath, double &_entropy)
{
	HANDLE hFile = CreateFile(_FilePath,
							   GENERIC_READ,
							   FILE_SHARE_READ,NULL,OPEN_EXISTING,
							   FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << "Error Open File";
		return FALSE;
	}

	DWORD dwSize = 0;
	dwSize = ::GetFileSize(hFile,NULL);
	double Log2 = log(2.0);

	const DWORD bufferSize = 256*512;
	BYTE pBuffer[bufferSize];
	_entropy = 0.0;
	double temp = 0.0;

	DWORD chunksCount = 0;
	if (dwSize > 0)
	{
		DWORD symbols[MAX_BYTE];
		DWORD dwBytesRead = 0;
		DWORD curPos = 0;
		while (true)
		{
			memset(symbols,0,MAX_BYTE*sizeof(DWORD));

			if ( curPos + bufferSize > dwSize )
			{
				DWORD lastSize = dwSize - curPos;
				BYTE * pBuffer2 = new BYTE[lastSize];
				if ( !ReadFile(hFile, pBuffer, lastSize, &dwBytesRead, NULL) )
				{
					cout << "Can't Read File";
					return FALSE;
				}
				if ( ::GetEntropy(pBuffer2,lastSize,temp) )
				{
					_entropy += temp;
					++chunksCount;
				}
				delete pBuffer2;

				break;

			}
			else
			{
				if ( !ReadFile(hFile, pBuffer, bufferSize, &dwBytesRead, NULL) )
				{
					cout << "Can't Read File";
					return FALSE;
				}
				if ( dwBytesRead == 0)
					break;
				if ( ::GetEntropy(pBuffer,dwBytesRead,temp) )
				{
					_entropy += temp;
					++chunksCount;
				}
				curPos += bufferSize;
			}
		}

		CloseHandle(hFile);
		_entropy /= chunksCount;
		return TRUE;
	}
	CloseHandle(hFile);
	return FALSE;
}


BOOL FileSearcher::GetEntropyWORD(wchar_t * _FilePath, double &_entropy)
{
	HANDLE hFile = CreateFile(_FilePath,
		GENERIC_READ,
		FILE_SHARE_READ,NULL,OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << "Error Open File";
		return FALSE;
	}

	DWORD dwSize = 0;
	dwSize = ::GetFileSize(hFile,NULL);
	double Log2 = log(2.0);

	_entropy = 0.0;
	double temp = 0.0;
	if (dwSize > 0)
	{
		
		DWORD symbols[MAX_WORD];
		ZeroMemory(symbols,MAX_WORD*sizeof(DWORD));
		DWORD dwBytesRead = 0;

		BYTE *pBuffer = new BYTE[dwSize];
		if ( !ReadFile(hFile, pBuffer, dwSize, &dwBytesRead, NULL) )
		{
			cout << "Can't Read File";
			return -1;
		}
		DWORD dwSumm = 0;
		WORD *pWord = NULL;
		WORD wVal = 0;
		int iNull = 0;
		DWORD valSumbol = 0;
		for (DWORD Index = 0; Index < dwSize - 1; ++Index )
		{
			pWord = (WORD *) &pBuffer[Index];
			wVal = *pWord;
			wVal = (wVal << 8) | (wVal >> 8);
			pWord = NULL;
			symbols[wVal]++;
			if (wVal == 0)
				printf("%d\r\n",Index);
			if (Index == 500)
			{
				int kk = 0;
			}
			++dwSumm;
		}
		double dwSumAll = 0.0;
		for (DWORD iByte = 0; iByte < MAX_WORD; ++iByte)
		{
			if (symbols[iByte] > 0)
			{
				temp = ((double)symbols[iByte])/((double)dwSumm);
				_entropy -= temp * log(temp)/Log2;
			}
		}

		delete pBuffer;

		CloseHandle(hFile);
		return TRUE;
	}
	CloseHandle(hFile);
	return FALSE;
}

BOOL FileSearcher::WriteToFile(wchar_t * _ExtName , double & entropy)
{
	if (_ExtName == NULL)
		return FALSE;

	wstring strFileName(_ExtName);
	strFileName.append(_T(".txt"));
	HANDLE hFile = CreateFile(strFileName.c_str(),
							 GENERIC_WRITE,
							 FILE_SHARE_WRITE,
							 NULL,
							 OPEN_ALWAYS,
							 0,NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("Error Create File\r\n");
		return FALSE;
	}

	char buffFormat[20];
	sprintf(buffFormat,"%2.7f",entropy);
	string strEntropy(buffFormat);
	strEntropy.append("\r\n");
	DWORD dwBytesWrite = 0;
	SetFilePointer(hFile,0,NULL,FILE_END);
	if (!WriteFile(hFile,strEntropy.c_str(),strEntropy.length(),&dwBytesWrite,NULL) )
	{
		printf("Error Write File\r\n");
		return FALSE;	
	}
	CloseHandle(hFile);
	return TRUE;
}
void FileSearcher::setFileExt(FileExtensions & _pFile)
{
	m_fileExt = &_pFile;
}

static size_t iNumber = 0;

BOOL FileSearcher::SearchFiles(wchar_t *_DirectoryPath)
{
	if (m_fileExt->isEmpty())
		return FALSE;
	HANDLE hFindFile = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA findData;

	TCHAR wFilePath[MAX_PATH];
	TCHAR wPath[MAX_PATH];
	TCHAR wDirPath[MAX_PATH];
	//if (GetFullPathName(_DirectoryPath,MAX_PATH,wPath,(LPTSTR*)&wFilePart) == 0)
	//	return FALSE;
	wcscpy(wDirPath,_DirectoryPath);
	wcscat(wDirPath,_T("\\*.*"));
	// First Check if Directory
	if ((hFindFile = FindFirstFile(wDirPath,&findData)) != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if (!wcsncmp(findData.cFileName,_T("."),1) || !wcsncmp(findData.cFileName,_T(".."),2))
				continue;

			// Get PAHT to Directory
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//if (GetFullPathName(_DirectoryPath,MAX_PATH,wPath,(LPTSTR*)&wFilePart) == 0)
				//	return FALSE;
				wcscpy(wPath,_DirectoryPath);
				wcscat(wPath,_T("\\"));
				wcscat(wPath,findData.cFileName);
				//wprintf(_T("%s   <DIR>\r\n"),wPath);
				SearchFiles(wPath);
			}				

			//SearchFiles(
		}while(FindNextFile(hFindFile, &findData) );

		FindClose(hFindFile);
			
	}

	if ((hFindFile = FindFirstFile(wDirPath,&findData)) != INVALID_HANDLE_VALUE)
	{
		do 
		{
			if (!wcsncmp(findData.cFileName,_T("."),1) || !wcsncmp(findData.cFileName,_T(".."),2))
				continue;

			// Get PAHT to Directory
			if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				
				wcscpy(wFilePath,_DirectoryPath);
				wcscat(wFilePath,_T("\\"));
				wcscat(wFilePath,findData.cFileName);
				//wprintf(_T("%s\r\n"),wFilePath);
				wstring str(wFilePath);
				size_t extPos = str.find_last_of(_T("."));
				size_t slashPos = str.find_last_of(_T("\\"));
				if (extPos > 0 && slashPos > 0)
				{
					size_t iNameSize = extPos - ++slashPos;
					wstring FileName = str.substr(slashPos,iNameSize);
					wstring sExt = str.substr( extPos , str.length() );
					transform(sExt.begin(),sExt.end(),sExt.begin(),::tolower);
					if ( m_fileExt->isPresent(sExt) )
					{
						double entropy = 0.0;
						GetEntropy(wFilePath,entropy);
						wprintf(_T("%s - Entropy = %f \r\n"),wFilePath,entropy);
						WriteToFile( (wchar_t*)sExt.c_str(),entropy );
					}
				}

			}				

			//SearchFiles(
		}while(FindNextFile(hFindFile, &findData) );

		FindClose(hFindFile);
	}

	return TRUE;
}



SonyVideoRecovery::SonyVideoRecovery( const wstring & fileToRecovery ) 
	: hReadFile_(INVALID_HANDLE_VALUE)
	, startBuffer_(nullptr)
	, endBuffer_(nullptr)
{
	Open_Read(hReadFile_,fileToRecovery);
}

SonyVideoRecovery::~SonyVideoRecovery()
{
	if ( hReadFile_ != INVALID_HANDLE_VALUE )
		CloseHandle(hReadFile_);
	deleteBuffer(startBuffer_);
	deleteBuffer(endBuffer_);
}

void SonyVideoRecovery::addSector( LONGLONG & offset )
{
	offset += SectorSize;
}

LONGLONG SonyVideoRecovery::findSignature( const LONGLONG offset, const BYTE * signature )
{
	LARGE_INTEGER liOffset;
	liOffset.QuadPart = offset;
	::SetFilePointerEx( hReadFile_ , liOffset , NULL , FILE_BEGIN );
	const int ReadSize = SectorSize * 256;
	BYTE block[ReadSize];
	DWORD byteToRead = 0;
	DWORD iSector = 0;
	while(true)
	{
		if ( ! ReadFile(hReadFile_, block, ReadSize,&byteToRead,NULL) )
		{
			printf("Error to read file");
			break;
		}
		if ( byteToRead == 0)
			break;

		iSector = 0;
		while ( iSector < byteToRead)
		{
			if ( memcmp(block+iSector , signature, mp4_signatureSize) == 0 )
			{
				liOffset.QuadPart += iSector;
				return liOffset.QuadPart;
			}
			iSector += SectorSize;
		}
		liOffset.QuadPart += byteToRead;
	}
	return -1;
}

void SonyVideoRecovery::save_MP4File( LONGLONG & offset , const BYTE * end_signature , DWORD fileNumber )
{
	wchar_t numberBuff[10];
	memset(numberBuff,0,10*sizeof(wchar_t));
	swprintf(numberBuff,10,L"%.3d",fileNumber);
	wstring writeName(L"D:\\incoming\\31868\\");
	writeName.append( numberBuff );
	writeName.append( L".mp4" );
	HANDLE hWriteFile = INVALID_HANDLE_VALUE;
	Create_File(hWriteFile,writeName);

	LARGE_INTEGER liOffset;
	liOffset.QuadPart = offset;
	::SetFilePointerEx(hReadFile_, liOffset, NULL, FILE_BEGIN);

	const DWORD ReadSize = FragmentSize + OtherSize;

	DWORD byteToRead = 0;
	DWORD byteToWrite = 0;
	BYTE block[ReadSize];
	DWORD iSector = 0;
	DWORD compareSize = 0;

	while (true)
	{
		if ( ! ReadFile(hReadFile_, block, ReadSize,&byteToRead,NULL) )
		{
			printf("Error to read file");
			break;
		}
		if (byteToRead == 0)
			break;

		iSector = 0;
		compareSize = ( byteToRead > FragmentSize ) ? FragmentSize : byteToRead;
		while (iSector < compareSize)
		{
			if ( memcmp(block + iSector, end_signature, mp4_signatureSize) == 0)
			{
				// Write last data.
				if ( ! WriteFile(hWriteFile, block , iSector , &byteToWrite , NULL) )
				{
					printf("Error to write file");
					break;
				}
				// Write 2 clusters to beginning of file.
				::SetFilePointer(hWriteFile,0,NULL,FILE_BEGIN);
				if ( ( iSector + 2*ClusterSize ) < compareSize )
				{
					::WriteFile(hWriteFile, block + iSector, 2*ClusterSize, &byteToWrite, NULL);
					offset += iSector + 2*ClusterSize;

					mp4_header * pMP4 =  ( mp4_header *) (block + iSector);
					
					DWORD moov_number = ntohl(pMP4->size)  / ClusterSize;

					for ( int iCluster = 2; iCluster < 4; ++iCluster)
					{
					BYTE * moov_cluster = block + iSector + iCluster*ClusterSize;
					DWORD curByte = 0;
					while ( curByte < ClusterSize - 4 )
					{
						if ( memcmp(moov_cluster + curByte, moov_signature, 4) == 0 )
						{
							liOffset.QuadPart = moov_number * ClusterSize;
							::SetFilePointerEx(hWriteFile,liOffset,NULL,FILE_BEGIN);
							if ( ! WriteFile(hWriteFile, moov_cluster , ClusterSize , &byteToWrite , NULL) )
							{
								printf("Error to write file");
								break;
							}
							CloseHandle(hWriteFile);
							return;
						}
						++curByte;
					}

					}
					CloseHandle(hWriteFile);
					return;
				}


			}

			iSector += SectorSize;
		}

		if ( ! WriteFile(hWriteFile, block, FragmentSize , &byteToWrite,NULL) )
		{
			printf("Error to read file");
			break;
		}

		offset += byteToRead;
	}
	CloseHandle(hWriteFile);

}
