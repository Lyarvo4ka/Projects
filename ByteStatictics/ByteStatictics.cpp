// ByteStatictics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <atlstr.h>
#include <Windows.h>
#include <iostream>
using std::cout;
using std::cin;
using std::wcin;
using std::endl;

#include <string>
using std::string;
using std::wstring;
#include <conio.h>
#include "ByteCounts.h"
#include <ostream>
using std::ofstream;

#include "Devices.h"
#include "AbstractFactory.h"
#include "Reader.h"
#include "Buffer.h"
#include "Writer.h"


#include "BlockByte.h"
// E:\Flash\01_01.dump.bin 
// 16384
bool OpenFileRead(const char * _pFilePath, HANDLE & _hFile );
bool SaveToFile(ByteCounts * _pByteCounts, int _Size);
bool WriteToFile(CString _strPath, BYTE *_pData, int _Size);
BOOL CreateDir(CString _DirPath);

void AnalizeXor(BYTE *_pBuffer, int _iPageNumber, int _iBlockSize , BYTE *_pBuffWrite);


const size_t BlockFounds = 48-1;

#define KEY_QUIT 113

#include "Translator.h"


#include <string>
using std::wstring;
#include <algorithm>






int main(int argc, char* argv[])
{
	int dwBlockSize = 0;
	char buffInput[100];
	memset(buffInput, 0 , 100);
	cout << "File Path : ";
	cin >> buffInput;

	// Set Path to File
	HANDLE hFile;
	if (OpenFileRead(buffInput,hFile) == false)
	{
		cout << endl << "Press any key to Exit";
		_getch();
		exit(-1);
	}

	cout << "Block size (bytes) : ";
	cin >> dwBlockSize;


	// Set Block Size
	if (dwBlockSize <= 0 )
	{
		cout << "Block size must more then 0" << endl;
		cout << endl << "Press any key to Exit";
		_getch();
		exit (-1);
	}
	try
	{
		ByteCounts *pByteCounts = new ByteCounts[dwBlockSize];

		BOOL bFullBlock = FALSE;
		lReadPos
		cout << "Wait for Executing" << endl;
		while (lReadPos < lMaxFileSize)
		{
			dwBytesRead = pReader->Read(pBuffer, lReadPos);
			if (dwBytesRead == 0)
				break;

			tempSize = dwBytesRead;

			bFullBlock = FALSE;
			for (DWORD dwIndex = 0; dwIndex < tempSize; ++dwIndex)
			{
				if (pDataBuffer[dwIndex] != 0xFF && pDataBuffer[dwIndex] != 0)
				{
					bFullBlock = TRUE;
					break;
				}
			}
			if (bFullBlock == TRUE)
				for (DWORD dwIndex = 0; dwIndex < dwBlockSize; ++dwIndex)
				{
					pByteCounts[dwIndex].Add(pDataBuffer[dwIndex]);
				}
			lReadPos += dwBytesRead;

		}
		//CloseHandle(hFile);
		delete pBuffer;
		delete pReader;
		for (DWORD dwIndex = 0; dwIndex < dwBlockSize; ++dwIndex)
		{
			pByteCounts[dwIndex].Show();
		}
		pByteCounts[0].ShowStatictics();

		_getch();



		int iCode = 0;
		while (iCode != KEY_QUIT)
		{
			cout << "Enter byte to show statistics : ";
			scanf_s("%d", &iCode);
			cout << " Entered #(" << iCode << ")" << endl;
			if (iCode >= 0 && iCode < dwBlockSize)
			{
				pByteCounts[iCode].ShowStatictics();
			}
			cout << "Press any key to continue. (Q) Quit.";
			iCode = _getch();
			cout << endl;
		}

		SaveToFile(pByteCounts, dwBlockSize);
		delete[] pByteCounts;

	}
	catch (const std::exception& e)
	{
		printf("Error. Allocation memory failed. \r\n(%s)" ,e.what());
		_getch();
		exit(-3);
	}


	

	//setlocale(LC_ALL,"Russian");

	//add_service("d:\\Public\\34370\\xor_34370.bin" , "d:\\Public\\34370\\xor_34370_SA.bin" );

	//CanonMovRaw video_raw( 2 , "D:\\PaboTa\\34099\\raw\\");
	//CanonFragmentMovRaw video_files( "d:\\Public\\34281\\34281.bin" , "D:\\Public\\34281\\result\\");
	//video_files.execute();
/*
	char ImagePath[260]; 
	ZeroMemory(ImagePath,260*sizeof(char));
	printf("Image file:");	
	scanf("%s",ImagePath);

	char Output_folder[260]; 
	ZeroMemory(Output_folder,260*sizeof(char));
	printf("Output folder:");	
	scanf("%s",Output_folder)*/;

	//DecryptDisk decryp_disk( 4 , 2 );
	//decryp_disk.execute();

	//std::string Output_folder("d:\\Public\\ENTAR\\result\\");
	//CanonMovRaw canon_raw( "d:\\Public\\ENTAR\\image.img" , Output_folder );
	//canon_raw.execute();

	//iPhoneVideoRaw mp4Raw( "d:\\PaboTa\\33485\\33485.bin" , "D:\\PaboTa\\33485\\result\\" );
	//if ( mp4Raw.isReady() )
	//	mp4Raw.execute() ;

	//GatherRaid raid0( 3 , 2 , 4 );
	//raid0.Execute();

//if ( argc == 3 )
//{
//	char chars[] = "\"";
//
//	std::string sInputFile( argv[1] );
//	for (unsigned int i = 0; i < strlen(chars); ++i)
//		sInputFile.erase (std::remove(sInputFile.begin(), sInputFile.end(), chars[i]), sInputFile.end());
//
//	std::string sOutputFile( argv[2] );
//	for (unsigned int i = 0; i < strlen(chars); ++i)
//		sOutputFile.erase (std::remove(sOutputFile.begin(), sOutputFile.end(), chars[i]), sOutputFile.end());
//
//	iPhoneVideoRaw iPhoneMovie(sInputFile , sOutputFile );
//	iPhoneMovie.execute();
//}
//else
//	printf("argc != 3");
	//SamsungX820 samsung( "d:\\PaboTa\\33001\\Physical Samsung GSM SGH-X820 2013_01_24 (002)\\CTS(29080000-30400000).bin" );
	//samsung.execute("d:\\PaboTa\\33001\\Image.bin");

	//SamsungX820 samsung( "d:\\PaboTa\\33001\\Dump\\dump.bin" );
	//samsung.execute( "d:\\PaboTa\\33001\\Dump\\result.bin" );

	//CutService("d:\\PaboTa\\33001\\Dump\\4201_new\\1.dump ");

	//PdfRaw wavRaw( 2 , "D:\\PaboTa\\32938\\pdf\\");
	//wavRaw.execute();
	//BYTE addr1 = 0xF4;
	//BYTE addr2 = 0x6D;
	//BYTE addr3 = 0x02;

	//DWORD sector_offset = addr1 | ( addr2 << 8 ) | ( addr3 << 16 ); 
	//int k = 1;
	//k = 1;

	//WithoutService noService( "d:\\incoming\\01_01_1,3.dump" );
	//WithoutService noService( "d:\\incoming\\test.file" );
	//noService.Execute();

	//RepairFile repair_file(L"c:\\Users\\ssavchenko\\Desktop\\noname");
	//if ( repair_file.isReady() )
	//{
	//	repair_file.Repair(L"c:\\Users\\ssavchenko\\Desktop\\result.zip");
	//}

	//int i = 1 / 512;
	//int j = 513 / 512;

	//SonyAviRaw avi_raw;
	//if ( avi_raw.OpenSourceFile(L"d:\\PaboTa\\32659\\32659.img") )
	//	avi_raw.Execute();

	//ParseVCN vcn(L"d:\\PaboTa\\32789\\chunk_3.txt");
	//vcn.ParseFile();

	//GatherChanks chunks( vcn.getChunks() , L"d:\\PaboTa\\32789\\buh\\1Cv8.1CD", 3 ) ;
	//chunks.SetOffset( (LONGLONG)(172615758336) );
	//chunks.WriteChanks();
	//GatherBySector sectors(L"d:\\Backup\\B52_test.mdf",L"d:\\Backup\\B52_Data.MDF");
	//sectors.Execute();

	/*SonyVideoRecovery sonyRec(L"e:\\31868.bin");*/
	//if ( sonyRec.isFileValid(L"e:\\video\\034.mp4" ) )
	//{
	//	printf("File is valid");
	//}
	//else
	//	printf("File isn't valid");



	//sonyRec.Execute();
	//sonyRec.EraseSLV(L"d:\\incoming\\31868\\31868.bin",L"E:\\31868.bin");

	//FileExtensions fileExt;
	//fileExt.AddFromFile(L"d:\\incoming\\31868\\ext.txt", 10);

	//FileSearcher searcer;
	//searcer.setFileExt(fileExt);
	//searcer.SearchFiles(L"D:\\incoming\\31868\\example");
	//XorCorrector xorNull;
	//xorNull.SetNull(L"d:\\incoming\\31822\\1.txt", L"d:\\incoming\\31822\\result.txt");

	//GatherByBlock gatherBlock;
	//gatherBlock.OpenTarget(L"d:\\PaboTa\\result.bin");

	//const int SourceBlock = GatherByBlock::SourceSize * 128;
	//const int TargetBlock = GatherByBlock::TargetSize * 128;

	//BYTE * pBuffer1 = new BYTE[SourceBlock];
	//BYTE * pBuffer2 = new BYTE[TargetBlock];

	//short counter = 0;

	//LONGLONG nextOffset = 0;
	//while (gatherBlock.ReadBlock(pBuffer1,SourceBlock,counter))
	//{
	//	++counter;
	//	if ( ! gatherBlock.ReadBlock(pBuffer2,SourceBlock,counter))
	//	{
	//		delete pBuffer2;
	//		pBuffer2 = nullptr;
	//	}
	//	gatherBlock.UpdateHeader(pBuffer1,counter-1);
	//	gatherBlock.WriteBlocks(pBuffer1,pBuffer2,SourceBlock,nextOffset);
	//	nextOffset += TargetBlock;
	//	++counter;

	//}
	//if (pBuffer1)
	//{
	//	delete pBuffer1;
	//	pBuffer1 = nullptr;
	//}
	//if (pBuffer2)
	//{
	//	delete pBuffer2;
	//	pBuffer2 = nullptr;
	//}
	//printf("File to xor:");
	//wchar_t FolderPath[260]; 
	//ZeroMemory(FolderPath,260*sizeof(wchar_t));
	//wscanf(L"%s",FolderPath);
	//wstring sFile(FolderPath);
	//XorCorrector xorCorrector;
	//xorCorrector.SetNull(sFile,sFile + L".result");

	//BlockCutting blockCutting;
	//blockCutting.InitPagePos();
	//wstring sFile(L"e:\\Public\\31351\\MultiLevel_Rd_9184_86_4200.dat");
	//blockCutting.OpenFiles(sFile);
	//blockCutting.Execute();

	//setHalfClusterFF(L"e:\\Public\\CONTENTS\\VIDEO\\0003GP.MXF",32*1024);

	//AdditionConflicts Conflicts;
	//printf("Folder:");
	//wchar_t FolderPath[260]; 
	//ZeroMemory(FolderPath,260*sizeof(wchar_t));
	////wscanf(L"%s",FolderPath);
	//wstring folder_path(L"E:\\Public\\31320\\");
	//Conflicts.FindFiles(folder_path);

	//wchar_t ImagePath[260]; 
	//ZeroMemory(ImagePath,260*sizeof(wchar_t));
	//printf("Image file:");	
	////wscanf(L"%s",ImagePath);
	///*ImagePath*/
	//wstring image_path = L"E:\\Public\\31320\\";
	//Conflicts.Execute(L"e:\\Public\\31320\\result\\Disk.image "/*image_path*/);

/*
	wstring dumpPath(L"e:\\Public\\01_01.dump_old");
	wstring tablePath(L"e:\\Public\\table_4.bin");
	wstring output_file(L"E:\\Public\\Result_4.dump");

	bool bResult = false;
	TableTranslator tableTranslator;
	bResult = tableTranslator.OpenDump(dumpPath);

	if (!bResult)
	{
		wprintf(L"Error open file (%s)\r\n",dumpPath.c_str());
		_getch();
		return - 1;		
	}

	bResult = tableTranslator.OpenTable(tablePath);

	if (!bResult)
	{
		wprintf(L"Error open file: (%s)\r\n",tablePath.c_str());
		_getch();
		return - 1;		
	}

	tableTranslator.ReadTable();
	tableTranslator.SaveToFile(output_file);
*/
	//FILE *fTxt = NULL;
	//fTxt = fopen( "Report.txt" , "a" );
	//if ( fTxt != NULL)
	//{
	//	cout << "Open Report.txt OK" << endl;
	//	fclose(fTxt);
	//}
	//else
	//{
	//	cout << " Error Open File " << endl;
	//	exit ( -3 );
	//}


/*
	wstring sFilePath = L"d:\\xor\\01_true_xor.dat";
	//cout << "File Path : ";
	//std::getline(std::wcin, sFilePath); 
	//wcin >> sFilePath;

	CFileFactory FileFactory;
	CReaderFactory ReaderFactory;
	IDevice * pFileDev = (CFileDevice *) FileFactory.CreateDevice();
	DevicePtr pFileDevice(pFileDev);
	pFileDevice->SetPath((wchar_t *)sFilePath.c_str());
	IReader * pReader = ReaderFactory.CreateReader(pFileDevice);
	if (!pReader->Open())
	{
		cout << "Невозможно открить файл...\r\nПроверте правильность пути к файлу.\r\n";
		_getch();
		exit(-1);
	}

	CWriterFactory WriterFactory;
	IDevice * pWriteDev = FileFactory.CreateDevice();
	pWriteDev->SetPath(L"d:\\xor\\Result.bin");
	DevicePtr ptrWriteDev(pWriteDev);
	IWriter * pWriter = WriterFactory.CreateWriter(ptrWriteDev);
	if (!pWriter->Open())
	{
		cout << "Невозможно открить файл для записи Result.bin\r\n";
		_getch();
		exit(-1);
	}


	const DWORD BufferSize = (DWORD) pFileDevice->GetSize();
	CBuffer buffer(BufferSize);

	LONGLONG lPosition = 0;
	DWORD bytesRead = pReader->Read(&buffer,lPosition);

	if (bytesRead == 0)
	{
		cout << "Невозможно прочитать файл.\r\n";
		_getch();
		exit(-1);		
	}

	buffer.SetSize(bytesRead);
	system("cls");

	BlockByte byteBlock(BlockSize);
	byteBlock.FindOffsets(&buffer);

	byteBlock.CorrectXor(&buffer);

	DWORD Count = byteBlock.GetCount();
	byteBlock.ShowFounds();
*/

	cout << endl << "Press any key to Exit";
	_getch();
	return 0;
}

bool OpenFileRead(const char * _pFilePath, HANDLE & _hFile )
{
	TCHAR *pFilePath = NULL;
	size_t iSize = 0;
	// Get Size of Buffer

	iSize = MultiByteToWideChar( CP_ACP,
						0,
						_pFilePath,
						-1,
						pFilePath,
						0);


	if (iSize > 0)
	{
		pFilePath = new TCHAR[iSize];
		memset(pFilePath,0,iSize);
	}
	else
	{
		cout << "Error Input File Path" << endl << "Exit >>";
		cout << endl << "Press any key to Exit";
		_getch();
		exit(-1);
	}
	size_t iResult  = MultiByteToWideChar( CP_ACP,
											0,
											_pFilePath,
											-1,
											pFilePath,
											iSize);
						

	//size_t iResult = mbstowcs(pFilePath,_pFilePath,strlen(_pFilePath));
	if (iResult <= 0)
	{
		cout << "Error Input File Path" << endl << "Exit >>";
		cout << endl << "Press any key to Exit";
		_getch();
		exit(-1);
	}
	_hFile = CreateFile(pFilePath,GENERIC_READ,
							FILE_SHARE_READ,NULL,OPEN_EXISTING,
							FILE_ATTRIBUTE_NORMAL,NULL);
	delete pFilePath;

	if ( _hFile == INVALID_HANDLE_VALUE )
	{
		DWORD dwError = GetLastError();
		cout << "Error Open File" << endl 
			<< "Error Code [" << dwError << "]" << endl;
		return false;
	}
	else
		cout << "Open File OK" << endl; 

	return true;
}

bool SaveToFile(ByteCounts * _pByteCounts, int _Size)
{
	HANDLE hFileWrite ;
	hFileWrite = CreateFile(_T("file.txt"),
							GENERIC_WRITE,
							FILE_SHARE_WRITE,NULL,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,NULL);
	if ( hFileWrite == INVALID_HANDLE_VALUE )
	{
		DWORD dwError = GetLastError();
		cout << "Error Open File to WRITE!!!!" << endl 
			<< "Error Code [" << dwError << "]" << endl;
		return false;
	}

	BYTE *pWriteBuff = new BYTE[_Size];
	for ( int dwIndex = 0; dwIndex < _Size; ++dwIndex)
		pWriteBuff[dwIndex] = (BYTE)_pByteCounts[dwIndex].GetMax();

	DWORD dwBytesWrite = 0;
	if ( ! WriteFile (hFileWrite, pWriteBuff, _Size , &dwBytesWrite, NULL) )
	{
			DWORD dwError = GetLastError();
			cout << "Error Write File " << endl 
			<< "Error Code [" << dwError << "]" << endl;
	}
	//else
	//	cout << "Write OK!"<< endl;
	delete pWriteBuff;

	CloseHandle(hFileWrite);
	return true;
}
bool WriteToFile(CString _strPath, BYTE *_pData, int _Size)
{
	HANDLE hFileWrite ;
	hFileWrite = CreateFile(_strPath,
							GENERIC_WRITE,
							FILE_SHARE_WRITE,NULL,
							CREATE_ALWAYS,
							FILE_ATTRIBUTE_NORMAL,NULL);
	if ( hFileWrite == INVALID_HANDLE_VALUE )
	{
		DWORD dwError = GetLastError();
		cout << "Error Open File to WRITE!!!!" << endl 
			<< "Error Code [" << dwError << "]" << endl;
		return false;
	}
	DWORD dwBytesWrite = 0;
	if ( ! WriteFile (hFileWrite, _pData, _Size , &dwBytesWrite, NULL) )
	{
			DWORD dwError = GetLastError();
			cout << "Error Write File " << endl 
			<< "Error Code [" << dwError << "]" << endl;
	}
	//else
	//	cout << "Wrute OK!"<< endl;

	CloseHandle(hFileWrite);
	return true;
}


void AnalizeXor(BYTE *_pBuffer, int _iPageNumber, int _iBlockSize, BYTE *_pBuffWrite)
{
/*	int iDataSize = 1024;
	int iServiceSize = 42;
	int iSectorSize = iDataSize + iServiceSize;
	int iSectorCount = _iBlockSize / iSectorSize;

	BYTE **pSectors = new BYTE*[iSectorCount];
	for ( int i = 0; i < iSectorCount; ++i)
		pSectors[i] = new BYTE[iDataSize];

	
	CString strDir = _T("Page");
	CString strIns = _T("");
	strIns.Format(_T("%.2d"),_iPageNumber);
	strDir.Insert(strDir.GetLength() , strIns);

	CString strText = _T("/.bin");
	CString strFile = strText;
	CString strFullPath = strDir;
	strIns = _T("");
	BOOL bResult = FALSE;
	bResult = CreateDir(strDir);

	// Write to File
	for ( int i = 0; i < iSectorCount; ++i)
	{
		strFullPath = strDir;
		memcpy(	pSectors[i] , _pBuffer + i*iSectorSize, iDataSize);
		strIns.Format(_T("%.2d"),i);
		strFile = strText;
		strFile.Insert(1,strIns);
		strFullPath += strFile;
		//_itow(i,pNumber,10);
		//_itow(i,&pNumber[2] ,10);
		WriteToFile(strFullPath,pSectors[i],iDataSize);

	}
	memset(_pBuffWrite,0,_iBlockSize);
	for ( int i = 0; i < iSectorCount; ++i)
		memcpy(_pBuffWrite + i * iSectorSize,  pSectors[i] , iDataSize);

	//File pFile
	// Check to Equal
	
	for ( int i = 1; i < iSectorCount; ++i)
	{
		if (memcmp(pSectors[0],pSectors[i],iDataSize) )
		{
			FILE *fTxt = NULL;
			fTxt = fopen( "Report.txt" , "a" );
			if ( fTxt == NULL )
				cout << "Error open Report file" << endl;
			else
			{
				CString strReport;
				strReport.Format(_T("Page not Equal : %d\r\n"),_iPageNumber);
				fputws(strReport.GetBuffer(),fTxt);
				cout << "Page not Equal" << _iPageNumber << endl;
				strReport.Format(_T("Sector : %d\r\n"),i);
				fputws(strReport.GetBuffer(),fTxt);
				cout << "Sector # " << i << endl<<endl;
				fclose(fTxt);
			}
			break;
		}
	}

	for ( int i = 0; i < iSectorCount; ++i)
		delete pSectors[i];

	delete pSectors;
*/
}
BOOL CreateDir(CString _DirPath)
{
	if (!CreateDirectory(_DirPath,NULL))
	{
		DWORD dwError = GetLastError();
		return FALSE;
	}
	return TRUE;
}
/*
	int dwBlockSize = 0;
	char buffInput[100];
	memset(buffInput, 0 , 100);
	cout << "File Path : ";
	cin >> buffInput;


	// Set Path to File
	HANDLE hFile;
	if (OpenFileRead(buffInput,hFile) == false)
	{
		cout << endl << "Press any key to Exit";
		_getch();
		exit(-1);
	}

	cout << "Block size (bytes) : ";
	cin >> dwBlockSize;
	

	// Set Block Size
	if (dwBlockSize <= 0 )
	{
		cout << "Block size must more then 0" << endl;
		cout << endl << "Press any key to Exit";
		_getch();
		exit (-1);
	}

	// Read File and Keep statistics
	DWORD dwBytesRead = 0;
	BYTE *pBuffer = new BYTE[dwBlockSize];
	BOOL bFullBlock = FALSE;
	ByteCounts *pByteCounts = new ByteCounts[dwBlockSize];
	BYTE *pWriteBuff = new BYTE[dwBlockSize];
	cout << "Wait for Executing"<< endl;
	while (true)
	{
		if ( !ReadFile(hFile, pBuffer, dwBlockSize,&dwBytesRead,NULL) )
		{
			DWORD dwError = GetLastError();
			cout << "Error Read File " << endl 
			<< "Error Code [" << dwError << "]" << endl;
			break;
		}
		if (dwBytesRead == 0)
			break;

		bFullBlock = FALSE;
		for ( int dwIndex = 0; dwIndex < dwBlockSize; ++dwIndex)
		{
			if ( pBuffer[dwIndex] != 0xFF && pBuffer[dwIndex] != 0 )
			{
				bFullBlock = TRUE;
				break;
			}
		}
		if (bFullBlock == TRUE)
		for ( int dwIndex = 0; dwIndex < dwBlockSize; ++dwIndex)
		{
			pByteCounts[dwIndex].Add(pBuffer[dwIndex]);
		}

	}
	CloseHandle(hFile);
	delete pBuffer;
	//for ( DWORD dwIndex = 0; dwIndex < dwBlockSize; ++dwIndex)
	//{	
	//	pByteCounts[dwIndex].Show();
	//}
	//pByteCounts[0].ShowStatictics();

	//_getch();
	system("cls");
	int iCode = 0;
	while (iCode != KEY_QUIT)
	{
		cout << "Enter byte to show statictis : ";
		scanf("%d",&iCode);
		cout << " Entered #(" << iCode << ")"<<endl;
		if ( iCode >= 0 && iCode < dwBlockSize)
		{
			pByteCounts[iCode].ShowStatictics();
		}
		cout << "Press any key to continue. (Q) Quit.";
		iCode = _getch();
		cout << endl;
	}

	SaveToFile(pByteCounts,dwBlockSize);
	delete [] pByteCounts;


	//cout << endl << "Press any key to Exit";
	_getch();

*/

//int dwBlockSize = 0;
//char buffInput[100];
//memset(buffInput, 0 , 100);
//cout << "File Path : ";
//cin >> buffInput;

//// Set Path to File
//HANDLE hFile;
//if (OpenFileRead(buffInput,hFile) == false)
//{
//	cout << endl << "Press any key to Exit";
//	_getch();
//	exit(-1);
//}
//HANDLE hFileWrite;
//hFileWrite = CreateFile(_T("Dump.dat"),
//						GENERIC_WRITE,
//						FILE_SHARE_WRITE,NULL,
//						CREATE_ALWAYS,
//						FILE_ATTRIBUTE_NORMAL,NULL);
//if ( hFileWrite == INVALID_HANDLE_VALUE )
//{
//	DWORD dwError = GetLastError();
//	cout << "Error Open File to WRITE!!!!" << endl 
//		<< "Error Code [" << dwError << "]" << endl;
//	return -3;
//}
//								

////dwBlockSize = 8640;
//cout << "Block size (bytes) : ";
//cin >> dwBlockSize;
//

//// Set Block Size
//if (dwBlockSize <= 0 )
//{
//	cout << "Block size must more then 0" << endl;
//	cout << endl << "Press any key to Exit";
//	_getch();
//	exit (-1);
//}

//// Read File and Keep statistics
//DWORD dwBytesRead = 0;
//DWORD dwBytesWrite = 0;

//BYTE *pBuffer = new BYTE[dwBlockSize];
//BYTE *pWriteBuff = new BYTE[dwBlockSize];
//cout << "Wait for Executing"<< endl;
//int iPageNumber = 0;
//while (true)
//{
//	if ( !ReadFile(hFile, pBuffer, dwBlockSize,&dwBytesRead,NULL) )
//	{
//		DWORD dwError = GetLastError();
//		cout << "Error Read File " << endl 
//		<< "Error Code [" << dwError << "]" << endl;
//		break;
//	}

//	if (dwBytesRead == 0)
//		break;
//	AnalizeXor(pBuffer,iPageNumber,dwBlockSize,pWriteBuff);
//	if ( ! WriteFile (hFileWrite, pWriteBuff, dwBlockSize , &dwBytesWrite, NULL) )
//	{
//			DWORD dwError = GetLastError();
//			cout << "Error Write File " << endl 
//			<< "Error Code [" << dwError << "]" << endl;
//	}
//	 // Write to File
//	++iPageNumber;
//}
//CloseHandle(hFile);
//CloseHandle(hFileWrite);
//delete pBuffer;
//delete pWriteBuff;

//cout << endl << "Press any key to Exit";
//_getch();
//int dwBlockSize = 0;
//char buffInput[MAX_PATH];
//memset(buffInput, 0 , MAX_PATH);
//WCHAR buffInput[MAX_PATH];
//ZeroMemory( buffInput , sizeof(WCHAR) * MAX_PATH ); 	//int dwBlockSize = 0;
//char buffInput[100];
//memset(buffInput, 0 , 100);
//cout << "File Path : ";
//cin >> buffInput;

//// Set Path to File
//HANDLE hFile;
//if (OpenFileRead(buffInput,hFile) == false)
//{
//	cout << endl << "Press any key to Exit";
//	_getch();
//	exit(-1);
//}
//HANDLE hFileWrite;
//hFileWrite = CreateFile(_T("Dump.dat"),
//						GENERIC_WRITE,
//						FILE_SHARE_WRITE,NULL,
//						CREATE_ALWAYS,
//						FILE_ATTRIBUTE_NORMAL,NULL);
//if ( hFileWrite == INVALID_HANDLE_VALUE )
//{
//	DWORD dwError = GetLastError();
//	cout << "Error Open File to WRITE!!!!" << endl 
//		<< "Error Code [" << dwError << "]" << endl;
//	return -3;
//}
//								

////dwBlockSize = 8640;
//cout << "Block size (bytes) : ";
//cin >> dwBlockSize;
//

//// Set Block Size
//if (dwBlockSize <= 0 )
//{
//	cout << "Block size must more then 0" << endl;
//	cout << endl << "Press any key to Exit";
//	_getch();
//	exit (-1);
//}

//// Read File and Keep statistics
//DWORD dwBytesRead = 0;
//DWORD dwBytesWrite = 0;

//BYTE *pBuffer = new BYTE[dwBlockSize];
//BYTE *pWriteBuff = new BYTE[dwBlockSize];
//cout << "Wait for Executing"<< endl;
//int iPageNumber = 0;
//while (true)
//{
//	if ( !ReadFile(hFile, pBuffer, dwBlockSize,&dwBytesRead,NULL) )
//	{
//		DWORD dwError = GetLastError();
//		cout << "Error Read File " << endl 
//		<< "Error Code [" << dwError << "]" << endl;
//		break;
//	}

//	if (dwBytesRead == 0)
//		break;
//	AnalizeXor(pBuffer,iPageNumber,dwBlockSize,pWriteBuff);
//	if ( ! WriteFile (hFileWrite, pWriteBuff, dwBlockSize , &dwBytesWrite, NULL) )
//	{
//			DWORD dwError = GetLastError();
//			cout << "Error Write File " << endl 
//			<< "Error Code [" << dwError << "]" << endl;
//	}
//	 // Write to File
//	++iPageNumber;
//}
//CloseHandle(hFile);
//CloseHandle(hFileWrite);
//delete pBuffer;
//delete pWriteBuff;

//cout << endl << "Press any key to Exit";
//_getch();
//int dwBlockSize = 0;
//char buffInput[MAX_PATH];
//memset(buffInput, 0 , MAX_PATH);
//WCHAR buffInput[MAX_PATH];
//ZeroMemory( buffInput , sizeof(WCHAR) * MAX_PATH ); 



// Set Path to File
//HANDLE hFile;
//if (OpenFileRead(buffInput,hFile) == false)
//{
//	cout << endl << "Press any key to Exit";
//	_getch();
//	exit(-1);
//}

//cout << "Block size (bytes) : ";
//cin >> dwBlockSize;
//

//// Set Block Size
//if (dwBlockSize <= 0 )
//{
//	cout << "Block size must more then 0" << endl;
//	cout << endl << "Press any key to Exit";
//	_getch();
//	exit (-1);
//}
