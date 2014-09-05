#pragma once

#include <windows.h>
#include <string>
using std::string;
using std::wstring;

#include <list>
#include <cmath>
#include <algorithm>
#include <assert.h>

#include "Writer.h"

class CTranslator
{
public:
	CTranslator(void);
	virtual ~CTranslator(void);



};

#include <vector>
using std::vector;

class TableTranslator
{
public:
	TableTranslator();
	virtual ~TableTranslator();
	bool OpenDump( const wstring & dumpPath);
	bool OpenTable(const wstring & tablePath);

	void ReadTable();
	void SaveToFile(const wstring & outputStr, bool withService = false);

private:
	bool open_read(HANDLE & handle, const wstring & file_path);
	bool open_write(HANDLE & handle, const wstring & file_path);
private:
	HANDLE dumpHandle_;
	HANDLE tableHandle_;
	vector<WORD> vecTable_;
};

bool Open_Read(HANDLE & handle, const wstring & file_path);
bool Open_Read(HANDLE & handle, const string & file_path);
bool Open_Write(HANDLE & handle, const wstring & file_path);
bool Open_Write(HANDLE & handle, const string & file_path);
bool Create_File(HANDLE & handle, const wstring & file_path);
bool Create_File(HANDLE & handle, const string & file_path);
DWORD File_Size( HANDLE & hangle );


const int BlockCount = 256;
const int BlockSize = BlockCount * SectorSize;

inline bool ReadBlock( HANDLE & handle , BYTE * buffer , DWORD size , DWORD & bytesRead )
{
	assert ( handle != INVALID_HANDLE_VALUE );
	assert( handle != nullptr );
	assert( size != 0 );

	bytesRead = 0;
	return ::ReadFile(handle , buffer , size , &bytesRead , NULL );
}
inline bool WriteBlock( HANDLE & handle , BYTE * buffer , DWORD size , DWORD & bytesWritten )
{
	assert ( handle != INVALID_HANDLE_VALUE );
	assert( handle != nullptr );
	assert( size != 0 );

	bytesWritten = 0;
	return ::WriteFile(handle , buffer , size , &bytesWritten , NULL );
}
inline bool WriteDataToFile( const HANDLE & hRead , const LONGLONG offset , const DWORD size , HANDLE & hWriteFile )
{
	BYTE write_data[BlockSize];
	LARGE_INTEGER liTempPos;
	liTempPos.QuadPart = offset;

	DWORD tempBytesRead = 0;
	DWORD bytesWrite = 0;
	DWORD file_size = 0;


	while ( true)
	{
		::SetFilePointerEx(hRead, liTempPos , NULL , FILE_BEGIN );
		if ( ! ReadFile(hRead , write_data , BlockSize ,&tempBytesRead , NULL ) )
		{
			DWORD dwError = ::GetLastError();
			printf("error to read..");
			return false;
		}
		if ( tempBytesRead == 0)
			break;
		if ( file_size + tempBytesRead > size )
			tempBytesRead = size - file_size;
		file_size +=tempBytesRead;
		if ( ! WriteFile(hWriteFile  , write_data , tempBytesRead , &bytesWrite , NULL ) )
		{
			printf( "error to write... (# %d) ", ::GetLastError() );
			return false;
		}
		liTempPos.QuadPart += BlockSize;
		if ( file_size >= size)
			break;
	}

	return true;
}
inline bool AppendFile( const HANDLE & hRead , const LONGLONG offset , const DWORD size , HANDLE & hWriteFile)
{
	LARGE_INTEGER file_size;
	if ( ::GetFileSizeEx( hWriteFile, &file_size ) )
	{
		::SetFilePointerEx(hWriteFile , file_size  , NULL , FILE_BEGIN );
		return WriteDataToFile( hRead , offset , size , hWriteFile );
	}
	return false;
}


static enum OpenDriveMode
{ 
	OpenReadMode = 0,
	OpenWriteMode,
	OpenReadWriteMode
};

inline bool OpenDriveByNamber( DWORD drive_number , HANDLE & hDrive , OpenDriveMode open_mode = OpenReadMode )
{
	const std::string sPhysicalName = "\\\\.\\PhysicalDrive";
	std::string sDrivePath = sPhysicalName;
	char buff[10];

	memset(buff,0,10);
	sprintf_s(buff,10,"%d",drive_number);
	sDrivePath.append(buff);
	bool bOpenResult = false;
	switch ( open_mode )
	{
	case OpenReadMode:
		bOpenResult = Open_Read(hDrive, sDrivePath);
		break;
	case OpenWriteMode :
		bOpenResult = Open_Write(hDrive , sDrivePath );
		break;
	case OpenReadWriteMode:
		hDrive = CreateFileA( sDrivePath .c_str(),
			GENERIC_READ | GENERIC_WRITE ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		if ( hDrive	!= INVALID_HANDLE_VALUE )
			bOpenResult = true;
		break;
	default:
		bOpenResult = false;
	}

	if ( !bOpenResult)
	{
		printf( "Error to open drive %d" , drive_number );
	}
	return bOpenResult;
}


const int page_size = 32768;
const int page_size_sa = 34560;
const int block_size = 8388608;
const BYTE pages_count = 0xFF;

class AdditionConflicts
{
public:
	AdditionConflicts();
	void FindFiles(const wstring & folder_path);
	void writeToImage(const wstring & file_name, const wstring & image_name);
	void Execute(const wstring & image_name);
private:
	std::list< wstring > ListFiles_;
};

struct pagesTo
{
	BYTE number;
	BYTE pageOffset;
	WORD counter;
};

void setHalfClusterFF(const wstring & file_name, const DWORD cluster_size);

class XorCorrector
{
public:
	XorCorrector();
	~XorCorrector();


	void CorrectXor(const wstring & input_file, const wstring & output_file);
	void SetNull(const wstring & input_file, const wstring & output_file);
private:
	HANDLE hInput_;
	HANDLE hOutput_;

};

class PagePos
{
public:
	PagePos(const int offset, const int count)
		: offset_(offset)
		, count_(count)
	{

	}
	int offset() const
	{
		return offset_;
	}
	int count() const
	{
		return count_;
	}
private:
	int offset_;
	int count_;
};

class PageArray
{
public:
	void AddPage(const PagePos page_pos)
	{
		pageArray_.push_back(page_pos);
	}
	std::size_t count() const
	{
		return pageArray_.size();
	}
	const PagePos * getPage(std::size_t page_number) const
	{
		if ( page_number < pageArray_.size())
			return &pageArray_.at(page_number);

		return nullptr;
	}
private:
	vector<PagePos> pageArray_;
};
class BlockCutting
{
public:
	static const int Page_Size = 9184;
	static const int Page_Count = 258;
	static const int Block_Count = 4200;

	BlockCutting();
	~BlockCutting();

	bool OpenFiles(const wstring & filePath);
	void InitPagePos();
	void CutBlock(DWORD block_number, const BYTE * sourcePage, BYTE * targetPage);
	void Execute();

private:
	vector< PageArray > arrayBlock_;
	HANDLE hInput_;
	HANDLE hOutput_;
};

#pragma pack(1)
struct HeaderBlock
{
	const BYTE Header[4];
	const BYTE data1[12+16];
	BYTE highBlockNumber[4];
	BYTE lowBlockNumber[4];
	const BYTE MessageNumber[8];
	//const BYTE physicalNumber[16];
};
#pragma pack ()

class GatherByBlock
{
public:
	static const int SourceSize = 4096;
	static const int TargetSize = 8192;
	GatherByBlock();
	~GatherByBlock();
	bool OpenSource(const wstring & source_file);
	bool OpenTarget(const wstring & target_file);
	void CloseFile(HANDLE & file_handle);

	bool ReadBlock(BYTE * data_buffer, const DWORD size_buffer, short block_number);
	void UpdateHeader(BYTE * data_buffer, short block_value);
	bool WriteBlock(BYTE * data_buffer, const DWORD size_buffer, LONGLONG offset);
	bool WriteBlocks(BYTE * buffer1, BYTE * buffer2, const DWORD size_buffer, LONGLONG offset);
private:
	HANDLE hSource_;
	HANDLE hTarger_;
};

#include <iostream>
#include <map>
using std::cout;
using std::map;
using std::pair;
#include <string>
using std::wstring;
using std::string;
#include <algorithm>
using std::transform;

enum EnExtensions {jpg = 0,doc};
#define MAX_BYTE 256
typedef pair<wstring,DWORD> ExtFiles;

class FileExtensions
{
public:
	BOOL Add(wstring &_newExt,DWORD _extension);
	BOOL AddFromFile(wchar_t * _pPath, DWORD _dwMaxFiles);
	BOOL isPresent(wstring &_FileExt);
	BOOL UpdateExt(wstring &_FileExt);
	bool isEmpty() const;
	virtual ~FileExtensions();
private:
	map<wstring,DWORD> m_Map;
};

#define MAX_WORD (USHRT_MAX + 1)

inline BOOL GetEntropy( BYTE * data, DWORD size, double & entropy)
{
	if ( !data )
		return FALSE;


	double Log2 = log(2.0);

	entropy = 0.0;
	double temp = 0.0;
	if (size > 0)
	{
		DWORD symbols[MAX_BYTE];
		memset(symbols,0,MAX_BYTE*sizeof(DWORD));
		DWORD dwSumm = 0;
		for (DWORD Index = 0; Index < size; ++Index)
		{
			symbols[data[Index]]++;
			++dwSumm;
		}
		double dwSumAll = 0.0;
		for (size_t iByte = 0; iByte < MAX_BYTE; ++iByte)
		{
			if (symbols[iByte] > 0)
			{
				temp = ((double)symbols[iByte])/((double)dwSumm);
				entropy -= temp * log(temp)/Log2;
			}
		}

		return TRUE;
	}
	return FALSE;
}

class FileSearcher
{
public:
	FileSearcher(){};
	void setFileExt(FileExtensions & _pFile);
	virtual BOOL SearchFiles(wchar_t *_DirectoryPath);
	virtual BOOL Execute(wchar_t *_FilePath, size_t iNumber = 0);
	BOOL GetEntropy(wchar_t * _FilePath, double &_entropy);
	BOOL GetEntropyWORD(wchar_t * _FilePath, double &_entropy);
	BOOL WriteToFile(wchar_t * _ExtName , double & entropy);
private:
	wchar_t *m_pDirPath;
	FileExtensions *m_fileExt;
	double m_MinEntropy;
	double m_MaxEntropy;
};

#pragma pack(1)
struct mp4_header
{
	BYTE signature[15];
	BYTE value;
	BYTE other1[16];
	DWORD size;
};
#pragma pack ()


class ClusterMap
{
	static enum ClasterStatus { not_read , read};
public:
	ClusterMap( const DWORD array_size , BYTE default_value )
		: arrayMap_(nullptr)
		, arraySize_(array_size)
	{
		createArray(arrayMap_,array_size,default_value);
	}
	ClusterMap( const wstring & fileName )
	{
		Load(fileName);
	}
	~ClusterMap()
	{
		removeArray(arrayMap_);
	}
	void UpdateCluster( DWORD cluster_number , BYTE update_value)
	{
		arrayMap_[cluster_number] = update_value;
	}
	BYTE getCluster( DWORD cluster_number ) const
	{
		return arrayMap_[cluster_number];
	}
	bool Save(const wstring & fileName)
	{
		HANDLE hWrite = INVALID_HANDLE_VALUE;
		if ( Create_File(hWrite,fileName))
		{
			DWORD bytesWrite = 0;
			if ( !::WriteFile(hWrite, arrayMap_, arraySize_, &bytesWrite, NULL) )
			{
				printf("Error to save \"ClusterMap\" to file.\r\n");
				return false;
			}
			CloseHandle(hWrite);
			return true;
		}
		return false;
	}
	bool Load(const wstring & fileName)
	{
		HANDLE hRead = INVALID_HANDLE_VALUE;
		if ( Open_Read(hRead, fileName) )
		{
			arraySize_ = ::GetFileSize(hRead,NULL);
			if (arraySize_ == 0)
				return false;
			createArray(arrayMap_,arraySize_,not_read);
			DWORD bytesRead = 0;
			if ( ! ::ReadFile(hRead, arrayMap_, arraySize_ , &bytesRead, NULL ) )
			{
				printf("Error to load \"ClusterMap\" to file.\r\n");
				return false;
			}
			CloseHandle(hRead);
			return true;
		}
		return false;
	}
private:
	void removeArray( BYTE * pArray)
	{
		if (pArray)
		{
			delete [] pArray;
			pArray = nullptr;
		}
		arraySize_ = 0;

	}
	void createArray( BYTE * pArray, DWORD array_size, BYTE default_value)
	{
		if (array_size == 0 )
			return;
		
		removeArray(pArray);
		arrayMap_ = new BYTE[array_size];
		memset(arrayMap_,default_value,array_size);
	}

private:
	BYTE * arrayMap_;
	DWORD arraySize_;
};

#include "Buffer.h"

#pragma pack(1)
struct stsz_header
{
	BYTE STSZ_signature[12];
	DWORD recordCount;
};
#pragma pack ()
#pragma pack(1)
struct stco_header
{
	BYTE STSZ_signature[8];
	DWORD recordCount;
};
#pragma pack ()
struct TableSizes
{
	DWORD * pArray;
	DWORD count;
};

const DWORD AudioMarker = 0x000001B3;
const DWORD VideoMarker = 0x00000100;

class FrameOffset
{
public:
	enum FRAME_TYPE {audio_type, video_type};

	FrameOffset(DWORD offset, BYTE signType)
		: offset_(offset)
		, signType_(signType)
	{

	}
	DWORD getOffset() const
	{
		return offset_;
	}
	DWORD getType() const
	{
		return signType_;
	}
	DWORD getMarker() const
	{
		return (signType_ == video_type) ? VideoMarker : AudioMarker;
	}
private:
	DWORD offset_;
	BYTE signType_;
};

class TableOffset
{
public:
	void Add( DWORD offset, BYTE singType)
	{
		tableArray_.push_back(FrameOffset(offset,singType));
	}
	DWORD getSize() const
	{
		return tableArray_.size();
	}
	FrameOffset getFrameOffset(DWORD iNumber)
	{
		return tableArray_[iNumber];
	}
private:
	vector<FrameOffset> tableArray_;
};

const BYTE mp4_signature_0[16] = { 0x00 , 0x00 , 0x00, 0x18, 0x66, 0x74, 0x79, 0x70, 0x6D, 0x70, 0x34, 0x32, 0x00, 0x00, 0x00, 0x00};
const BYTE mp4_signature_1[16] = { 0x00 , 0x00 , 0x00, 0x18, 0x66, 0x74, 0x79, 0x70, 0x6D, 0x70, 0x34, 0x32, 0x00, 0x00, 0x00, 0x01};
const BYTE null_16[16] = { 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00, 0x00 };
const BYTE SLV[8] = {0x53, 0x4C, 0x56, 0x00, 0x00, 0x00, 0x00,0x00} ;
const BYTE STSZ_sign[12] = { 0x73, 0x74, 0x73, 0x7A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const BYTE STCO_sign[8] = { 0x73 , 0x74, 0x63, 0x6F, 0x00, 0x00, 0x00, 0x00};

const BYTE null_32[32] = {0};

const int RecordCount = 4;
const int mp4_signatureSize = 16;
static const char * moov_signature = "moov";
static const char * xml_end = "</NonRealTimeMeta>\r\n";
static const int xml_end_len = strlen(xml_end);
class SonyVideoRecovery
{
	static const int SectorSize = 512;
	static const DWORD FragmentSize = 0x7e0000;
	static const DWORD OtherSize = 0x20000;
	static const DWORD ClusterSize = 32768;
public:
	bool getOffsetTable( const CBuffer & buffer, TableOffset & offsetTable)
	{
		BYTE * pBuffer = buffer.GetBuffer();
		DWORD signPosition = 0;
		TableSizes STSZ_Table;
		TableSizes STCO_endTable;
		TableSizes STCO_startTable;
		if ( findSignaturePos( buffer , signPosition, STSZ_sign, 12 ) )
		{
			stsz_header * pSTSZ_Header = (stsz_header *) &pBuffer[signPosition];
			STSZ_Table.count = ntohl(pSTSZ_Header->recordCount);
			STSZ_Table.pArray = (DWORD *) &pBuffer[signPosition+sizeof(stsz_header)];
			signPosition += STSZ_Table.count * sizeof(DWORD);

			if (findSignaturePos( buffer , signPosition, STCO_sign, 8 ) )
			{
				stco_header * pSTCO_end = ( stco_header *) &pBuffer[signPosition];
				STCO_endTable.count = ntohl(pSTCO_end->recordCount);
				STCO_endTable.pArray = (DWORD *) &pBuffer[signPosition+sizeof(stco_header)];
				signPosition += STCO_endTable.count * sizeof(DWORD);

				if (findSignaturePos( buffer , signPosition, STCO_sign, 8 ) )
				{
					stco_header * pSTCO_start = ( stco_header *) &pBuffer[signPosition];
					STCO_startTable.count = ntohl(pSTCO_start->recordCount);
					STCO_startTable.pArray = (DWORD *) &pBuffer[signPosition+sizeof(stco_header)];

					DWORD start_offset = 0;
					DWORD next_offset = 0;
					DWORD video_size = 0;
					DWORD end_offset = 0;
					DWORD curVideoOffset = 0;
					
					for (DWORD iRecord = 0; iRecord < STCO_startTable.count -1 ; ++iRecord)
					{
						start_offset = ntohl(* ((DWORD*) &STCO_startTable.pArray[iRecord]) );

						next_offset = ntohl(* ((DWORD*) &STCO_startTable.pArray[iRecord + 1]) );
						end_offset = ntohl(* ((DWORD*) &STCO_endTable.pArray[iRecord]) );
						offsetTable.Add( end_offset , FrameOffset::audio_type );
						for ( curVideoOffset ; curVideoOffset < STSZ_Table.count; ++curVideoOffset)
						{
							video_size = ntohl(* ((DWORD*) &STSZ_Table.pArray[curVideoOffset]) );
							end_offset += video_size;
							if ( end_offset < next_offset )
								offsetTable.Add( end_offset , FrameOffset::video_type );
							else
							{
								++curVideoOffset;
								break;
							}
						}


					}
					return true;
				}
			}
		}
		return false;


	}

	bool isFileValid( const wstring & fileName)
	{
		HANDLE hRead = INVALID_HANDLE_VALUE;
		if ( !Open_Read(hRead, fileName) )
			return false;

		BYTE headerBuffer[sizeof(mp4_header)];
		DWORD bytesRead = 0;
		if ( !ReadFile(hRead,headerBuffer,sizeof(mp4_header),&bytesRead,NULL))
		{
			printf("error read file to check.\r\n");
			return false;
		}
		mp4_header * pHeader = ( mp4_header *) headerBuffer;
		DWORD size = ntohl(pHeader->size);
		if (size == 0)
		{
			printf("Incorrect file size..\r\n");
			return false;
		}
		CBuffer buffer(::GetFileSize(hRead,NULL) - size);
		::SetFilePointer(hRead,size,NULL,FILE_BEGIN);
		if ( !ReadFile(hRead,buffer.GetBuffer(),buffer.GetSize(),&bytesRead,NULL))
		{
			printf("error read file to check.\r\n");
			return false;
		}
		if (bytesRead != buffer.GetSize())
		{
			printf("file read isn't correct(CBuffer).\r\n");
			return false;
		}
		TableOffset offsetTable;
		if ( getOffsetTable(buffer , offsetTable) )
		{
			for (DWORD iRecord = 0; iRecord < offsetTable.getSize(); ++iRecord)
			{
				FrameOffset offsets = offsetTable.getFrameOffset(iRecord);
				::SetFilePointer(hRead,offsets.getOffset(), NULL, FILE_BEGIN);
				DWORD markerValue = 0;
				if ( !ReadFile(hRead,&markerValue,sizeof(DWORD),&bytesRead,NULL))
				{
					printf("error read file to check.\r\n");
					return false;
				}
				if ( ntohl(markerValue) != offsets.getMarker())
				{
					printf("Marker is incorrect offset = %d(bytes).\r\n", offsets.getOffset());
					return false;
				}
			}
			return true;
		}

		return false;
	}

	SonyVideoRecovery(const wstring & fileToRecovery);
	~SonyVideoRecovery();
	void addSector( LONGLONG & offset);
	LONGLONG findSignature(const LONGLONG offset, const BYTE * start_signature );
	void save_MP4File( LONGLONG & offset , const BYTE * end_signature , DWORD fileNumber );
	void Execute( )
	{
		LONGLONG nextOffset = 0/*3619749888*/;
		DWORD file_number = 0;
		LONGLONG startOffset = 0;
		while (true)
		{
		startOffset = this->findSignature(nextOffset,mp4_signature_0);
		nextOffset = startOffset;
		if (startOffset == -1)
		{
			printf("The end...");
			return;
		}
		LARGE_INTEGER liFileSize;
		::GetFileSizeEx(hReadFile_,&liFileSize);
		deleteBuffer(startBuffer_);
		startBuffer_ = new CBuffer(ClusterSize*2);
		// 1st Cluster
		BYTE cluster1[ClusterSize];
		if ( !ReadCluster(cluster1, nextOffset))
			return ;
		nextOffset += ClusterSize;
		memcpy(startBuffer_->GetBuffer(),cluster1,ClusterSize);

		// 2st Cluster
		BYTE cluster2[ClusterSize];
		if ( !ReadCluster(cluster2, nextOffset))
			return ;
		nextOffset += ClusterSize;
		memcpy(startBuffer_->GetBuffer()+ClusterSize,cluster2,ClusterSize);

		// End xml-file
		DWORD endSize = 0;
		findXml(nextOffset,endSize);
		if ( endSize != 0 )
		{
			deleteBuffer(endBuffer_);
			endBuffer_ = new CBuffer(endSize);
			if ( !ReadToBuffer(endBuffer_,nextOffset) )
				return;

			DWORD videoSize = getVideoSize(cluster1);
			if (videoSize < 104857600)
			{
				nextOffset += ClusterSize;
				continue;
			}
			DWORD sizeAlign = (videoSize/512) * 512;
			LONGLONG writefind = startOffset - sizeAlign;
			if ( writefind < 0 )
			{
				printf("Error offset is less than 0");
				return ;
			}
			//LONGLONG writeFileOffset = findStartFile(writefind,videoSize/3,mp4_signature_1);
			//if (writeFileOffset == -1)
			//{
			//	printf("Error not found start file signature");
			//	nextOffset += SectorSize;
			//}
			//else
			{
				writeMP4(0,liFileSize.QuadPart,videoSize,file_number);
				++file_number;
			}
		}

		}
	}
	void EraseSLV(const wstring & fromFile, const wstring & toFile)
	{
		HANDLE hWrite = INVALID_HANDLE_VALUE;
		CloseHandle(hReadFile_);
		if ( !Open_Read(hReadFile_,fromFile) )
		{
			printf("Error open to Read\r\n");
			return ;
		}			
		if ( !Create_File(hWrite,toFile))
		{
			printf("Error open to Write\r\n");
			return ;
		}	
		CBuffer buffer(ClusterSize);
		LONGLONG offset = 0;
		DWORD bytesWrite = 0;
		while (true)
		{

			if (!ReadCluster(buffer.GetBuffer(),offset) ) 
				break;

			if (isVideoCluster(buffer))
				if (!::WriteFile(hWrite,buffer.GetBuffer(), buffer.GetSize(),&bytesWrite, NULL))
					break;
			offset += ClusterSize;
		}
	}
	void writeMP4( LONGLONG startLba , LONGLONG maxLba , DWORD maxFileSize, DWORD number)
	{
		TableOffset offsetTable;
		if ( !getOffsetTable(*endBuffer_,offsetTable))
		{
			printf("Offset table has not found!\r\n");
			return;
		}

		wchar_t numberBuff[10];
		memset(numberBuff,0,10*sizeof(wchar_t));
		swprintf(numberBuff,10,L"%.3d",number);
		wstring writeName(L"D:\\incoming\\31868\\video\\");
		writeName.append( numberBuff );
		writeName.append( L".mp4" );
		HANDLE hWriteFile = INVALID_HANDLE_VALUE;
		Create_File(hWriteFile,writeName);

		LARGE_INTEGER liPos;
		liPos.QuadPart = 0;
		DWORD offset = 0;
		DWORD currOffset = 0;
		DWORD lastOffset = 0;
		DWORD markerValue = 0;
		DWORD bytesRead = 0;
		DWORD bytesWrite = 0;
		DWORD cluster_number = 0;
		DWORD count_clusters = 0;
		DWORD frame_size = 0;
		CBuffer clusterBuffer(ClusterSize);
		bool bFind = false;
		for (DWORD iRecord = 0; iRecord < offsetTable.getSize() - 1; ++iRecord)
		{
			offset = offsetTable.getFrameOffset(iRecord).getOffset();
			cluster_number = offset / ClusterSize;
			frame_size = offset - currOffset;
			count_clusters = frame_size / ClusterSize;
			CBuffer frameBuffer(frame_size+4);
			bFind = false;
			while (startLba < maxLba)
			{
				if ( ReadToBuffer(&frameBuffer,startLba) )
				{



					DWORD * pMarker = (DWORD *) &frameBuffer.GetBuffer()[frame_size];
					if ( ntohl(* pMarker) == offsetTable.getFrameOffset(iRecord).getMarker())

					{
					//	DWORD frameNextSize = offsetTable.getFrameOffset(iRecord+1).getOffset() - (currOffset + frameBuffer.GetSize());
					//	CBuffer frameBufferNext(frameNextSize+4);
					//	if ( ReadToBuffer(&frameBufferNext,startLba+frameBuffer.GetSize()) )
					//	{
					//		DWORD * pMarkerNext = (DWORD *) &frameBufferNext.GetBuffer()[frameNextSize];
					//		if (ntohl(* pMarkerNext) != offsetTable.getFrameOffset(iRecord+1).getMarker())
					//		{
					//			startLba += frameBuffer.GetSize();
					//			continue;
					//		}
					//}

						DWORD clusterPos = currOffset - (currOffset / ClusterSize) * ClusterSize;

						BYTE counter = 0;
						DWORD number = 0;
						CBuffer clusterBuffer(ClusterSize);
						BYTE * pFrameBuffer = frameBuffer.GetBuffer();
						for (DWORD iClust = 0 ; iClust < count_clusters; ++iClust)
						{
							
							memcpy( clusterBuffer.GetBuffer() , pFrameBuffer + clusterPos, ClusterSize );
							if ( !isVideoCluster(clusterBuffer) )
							{
								number = iClust;
								++counter;
							}
						}
						if ( counter > 0 )
						{
							for ( DWORD iWrite = 0; iWrite < counter; ++iWrite)
							{
								LONGLONG offsetPos = startLba - (counter)*ClusterSize - ClusterSize*iWrite;
								//offsetPos /= ClusterSize;
								//offsetPos *= ClusterSize;
								DWORD writePos =  (number)*ClusterSize ;
								
								ReadCluster(clusterBuffer.GetBuffer(), offsetPos );
								memcpy(pFrameBuffer + writePos, clusterBuffer.GetBuffer(),ClusterSize);
								--number;
							}
						}
						//while ( --iCluster != -1)
						//{
						//	BYTE * pClusterBuffer = clusterBuffer.GetBuffer();
						//	memcpy(pClusterBuffer, (BYTE*) &frameBuffer.GetBuffer()[iCluster*ClusterSize], ClusterSize);
						//	if ( !isVideoCluster(clusterBuffer) )
						//	{
						//		LONGLONG pos = startLba - (count_clusters-1)*ClusterSize - ClusterSize*(counter) ;
						//		if (ReadCluster(pClusterBuffer, pos ) )
						//			memcpy((BYTE*) &frameBuffer.GetBuffer()[iCluster*ClusterSize], pClusterBuffer, ClusterSize);
						//		++counter;
						//	}
						//}
						if (!WriteFile(hWriteFile,frameBuffer.GetBuffer(),frameBuffer.GetSize(),&bytesWrite,NULL))
						{
							printf("Error Write file.\r\n");
							return ;
						}
						startLba += frameBuffer.GetSize();
						currOffset += frameBuffer.GetSize();
						bFind = true;
						break;
					}
					else
						startLba += ClusterSize;
				}
				else
					break;

			}
			//if (!bFind)
			//	break;
			if (startLba > maxLba)
				break;
		}

		::SetFilePointer(hWriteFile,0,NULL,FILE_BEGIN);
		WriteFile(hWriteFile, startBuffer_->GetBuffer(), startBuffer_->GetSize(), &bytesWrite, NULL);
		startLba += ClusterSize*2;

		//CBuffer cluserBuffer(ClusterSize);
		//while ( startLba < maxLba )
		//{
		//	if ( ReadCluster(cluserBuffer.GetBuffer(),startLba) )
		//	{
		//		if ( isVideoCluster(cluserBuffer))
		//		{
		//			WriteFile(hWriteFile, cluserBuffer.GetBuffer(), cluserBuffer.GetSize(), &bytesWrite, NULL);
		//		}
		//	}

		//	startLba += ClusterSize;
		//}
		//DWORD moov_cluster = getMoovSignCluster(*endBuffer_);
		//if (moov_cluster == 0)
		maxFileSize = (maxFileSize/ClusterSize - getMoovSignCluster(*endBuffer_) ) * ClusterSize;
		::SetFilePointer(hWriteFile,maxFileSize,NULL,FILE_BEGIN);
		WriteFile(hWriteFile,endBuffer_->GetBuffer(), endBuffer_->GetSize(),&bytesWrite, NULL);
		::SetFilePointer(hWriteFile, maxFileSize + endBuffer_->GetSize(),NULL , FILE_BEGIN );
		::SetEndOfFile(hWriteFile);
		CloseHandle(hWriteFile);
	}
	bool findSignaturePos( const CBuffer & buffer, DWORD & pos, const BYTE * signature, DWORD signatureSize)
	{
		for ( ; pos < buffer.GetSize() - signatureSize; ++pos)
		{
			if ( memcmp(&buffer.GetBuffer()[pos],signature,signatureSize) == 0 )
				return true;
		}
		return false;
	}
	DWORD getMoovSignCluster( const CBuffer & buffer)
	{
		for (DWORD iPos = 0 ; iPos < buffer.GetSize() - 4; ++iPos)
		{
			if ( memcmp( &buffer.GetBuffer()[iPos] , moov_signature, 4) == 0)
				return iPos / ClusterSize;
		}
		return 0;
	}
	bool isVideoCluster(const CBuffer & buffer)
	{
		if (memcmp( buffer.GetBuffer(), SLV,8) == 0)
			return false;
		DWORD counter = 0;
		for ( DWORD iPos = 0; iPos < buffer.GetSize() - 32; iPos += 32 )
		{
			if ( memcmp( buffer.GetBuffer() + iPos, null_32, 32 ) == 0)
			{
				return false;
			}
			if ( buffer.GetBuffer()[iPos] == 0)
				++counter;

			if (counter > 9830)
				return false;
		}
		//double entropy = 0.0;
		//if ( ::GetEntropy(buffer.GetBuffer(),buffer.GetSize(), entropy) )
		//{
		//	if (entropy > 7.2 && entropy < 8.2 )
		//		return true;
		//}
		return true;
	}
	LONGLONG findStartFile(LONGLONG fromLBA , DWORD sizeToSearch, const BYTE * start_signature )
	{
		LONGLONG curSector = fromLBA;
		LONGLONG minLBA = fromLBA - sizeToSearch;
		if (minLBA < 0)
			return -1;

		curSector -= ClusterSize;
		BYTE buffer[ClusterSize];
		while ( curSector > minLBA )
		{
			if ( !ReadCluster(buffer,curSector) )
				return -1;
			for ( DWORD iSector = 0; iSector < ClusterSize; iSector += SectorSize )
			{
				if ( memcmp( &buffer[iSector], start_signature, mp4_signatureSize ) == 0 )
				if ( memcmp(  &buffer[iSector] + 48, startBuffer_->GetBuffer() + 48, 512 ) == 0)
					return curSector + iSector;
			}
			curSector -= ClusterSize;
		}
		return -1;
	}
	void findXml(LONGLONG offset, DWORD & endSize )
	{
		BYTE buffer[ClusterSize];
		DWORD cluster_number = 0;
		while (cluster_number < 10)
		{

			if ( !ReadCluster(buffer, offset))
			{
				endSize = 0;
				return ;
			}
			for (DWORD iPos = 0; iPos < ClusterSize - xml_end_len - 1; ++iPos)
			{
				if (memcmp(&buffer[iPos], xml_end, xml_end_len) == 0)
				{
					endSize += iPos + xml_end_len;
					return;
				}
			}
			offset += ClusterSize;
			++cluster_number;
			endSize += ClusterSize;
		}
	}
	bool ReadCluster( BYTE * buffer, LONGLONG offset)
	{
		DWORD bytesToRead = 0;
		LARGE_INTEGER liPos;
		liPos.QuadPart = offset;
		::SetFilePointerEx(hReadFile_,liPos,NULL,FILE_BEGIN);
		if ( ! ReadFile(hReadFile_, buffer, ClusterSize, &bytesToRead, NULL) )
		{
			printf("Error read cluster");
			return false;
		}
		if ( bytesToRead == 0)
			return false;
		return true;
	}
	bool ReadToBuffer( CBuffer * pBuffer , LONGLONG offset )
	{
		DWORD bytesToRead = 0;
		LARGE_INTEGER liPos;
		liPos.QuadPart = offset;
		::SetFilePointerEx(hReadFile_,liPos,NULL,FILE_BEGIN);
		if ( ! ReadFile(hReadFile_, pBuffer->GetBuffer() , pBuffer->GetSize(), &bytesToRead, NULL) )
		{
			printf("Error read cluster");
			return false;
		}
		if ( bytesToRead == 0)
			return false;
		return true;
	}
	DWORD getVideoSize(BYTE * buffer ) const
	{
		mp4_header * pMP4 = (mp4_header *) buffer;
		return ntohl(pMP4->size);
	}
private:
	void deleteBuffer(CBuffer * pBuffer)
	{
		if ( pBuffer )
		{
			delete pBuffer;
			pBuffer = nullptr;
		}
	}
private:
	HANDLE hReadFile_;
	CBuffer *startBuffer_;
	CBuffer *endBuffer_;
};

class GatherBySector
{
public:
	static const int BufferSize = 256*512;
	GatherBySector( const wstring & sourceFile, const wstring targetFile )
		: hRead(INVALID_HANDLE_VALUE)
		, hWrite(INVALID_HANDLE_VALUE)
	{
		Open_Read(hRead,sourceFile);
		Open_Write(hWrite, targetFile);
	}
	~GatherBySector()
	{
		CloseHandle(hRead);
		CloseHandle(hWrite);
	}
	void Execute()
	{
		DWORD bytesRead = 0;
		DWORD bytesWrite = 0;
		BYTE sourceBuffer[BufferSize];
		BYTE targetBuffer[BufferSize];
		LARGE_INTEGER liPos;
		liPos.QuadPart = 0;
		DWORD iSector = 0;
		bool isNull = false;
		int iByte = 0;
		while (true)
		{
			if ( !ReadFile(hRead,sourceBuffer,BufferSize,&bytesRead,NULL))
			{
				printf("Error read file.\r\n");
				break;
			}
			if (bytesRead == 0)
				break;

			::SetFilePointerEx(hWrite,liPos,NULL,FILE_BEGIN);
			if ( !ReadFile(hWrite,targetBuffer,BufferSize,&bytesRead,NULL))
			{
				printf("Error read file.\r\n");
				break;
			}
			iSector = 0;

			while (iSector < BufferSize)
			{
				isNull = false;
				for ( iByte = 0; iByte < 512; ++iByte)
				{
					if ( targetBuffer[iSector + iByte] != 0 )
						isNull = true;
				}
				if (!isNull)
					memcpy(targetBuffer + iSector,sourceBuffer + iSector,512);

				iSector += 512;
			}
			
			::SetFilePointerEx(hWrite,liPos,NULL,FILE_BEGIN);
			if ( !WriteFile(hWrite,targetBuffer,bytesRead,&bytesWrite,NULL))
			{
				printf("Error read file.\r\n");
				break;
			}
			liPos.QuadPart += BufferSize;
		}


	}
private:
	HANDLE hRead;
	HANDLE hWrite;
};
const int AVI_SignSize = 4;
const int FileSizeOffset = 4;
const BYTE AVI_Signature[ AVI_SignSize ] = { 0x52, 0x49, 0x46, 0x46 };

class SonyAviRaw
{
	static const int SectorsInBlock = 256;
	static const int SectorSize = 512;
	static const int HeaderCluster = 2;
public:
	SonyAviRaw( )
		: hSource_( INVALID_HANDLE_VALUE )
		, SourceName_( L"" )
		, hTarget_( INVALID_HANDLE_VALUE )
		, TargetName_( L"" )
		, ClusterCount_( 256 )
		, SkipCount_( 3 )
		, ClusterSize_( 64 )
	{

	}
	~SonyAviRaw()
	{

	}
	bool OpenSourceFile( const wstring & file_name )
	{
		SourceName_ = file_name;
		return Open_Read(hSource_ , SourceName_ );
	}
	bool OpenTargetFile( const wstring & file_name )
	{
		TargetName_ = file_name;
		return Create_File(hTarget_ , TargetName_ );
	}
	void Execute()
	{
		LONGLONG position = 0;
		LONGLONG file_sectors = 63404032;
		DWORD fileCounter = 0;
		

		while ( position < file_sectors)
		{

		position = findSignature( position );
		if ( position == -1)
		{
			printf( "Signature not found");
			return ;
		}
		DWORD block_size = ClusterCount_ * SectorSize * ClusterSize_;

		//	Reading 2 clusters
		BYTE * cluster_data = new BYTE[ block_size ];
		if ( ReadClusters( cluster_data , HeaderCluster, position) )
		{
			FileSize_ = getFileSize( cluster_data );
			if ( FileSize_ > 524288000)
			{
				int k = 1;
				k = 2;
			}
			if ( FileSize_ == 0 )
			{
				++position;
				continue;
			}
			wchar_t numberBuff[10];
			memset(numberBuff,0,10*sizeof(wchar_t));
			swprintf(numberBuff,10,L"%.5d",fileCounter);
			wstring writeName(L"D:\\PaboTa\\32659\\Result\\");
			writeName.append( numberBuff );
			writeName.append( L".avi" );
			if ( OpenTargetFile(writeName ) )
			{

			int chunk_count = getChunkCount( FileSize_ );
			LONGLONG back_sectors = position - chunk_count * ClusterCount_ * ClusterSize_;
			//back_sectors += 2 * ClusterSize_;
			DWORD clustersToRead = 0;
			DWORD valJump = 2;
			for ( int iChunk = 0 ; iChunk <= chunk_count ; ++iChunk )
			{
				clustersToRead = ClusterCount_;
				if ( iChunk == 0)
				{
					clustersToRead = ClusterCount_ - HeaderCluster;
					BYTE * next_data = ( BYTE * ) &cluster_data[ HeaderCluster * ClusterSize_ * SectorSize ];
					ReadClusters( next_data , clustersToRead , back_sectors + 2 * ClusterSize_ ) ;
				}
				else
				{
					ZeroMemory( cluster_data , block_size );
					ReadClusters( cluster_data , ClusterCount_ , back_sectors ) ;
				}

				WriteClusters( cluster_data, ClusterCount_ - valJump  , iChunk * ( ClusterCount_ - valJump ) * ClusterSize_ );
				back_sectors += ( ClusterCount_ )*ClusterSize_;
			}
			DWORD lastClusters = HeaderCluster*2;
			ReadClusters( cluster_data , lastClusters , position + valJump*ClusterSize_);
			DWORD lastCount = 0;
			// find xml end
			for ( DWORD iPos = 0; iPos < lastClusters*ClusterSize_*SectorSize - xml_end_len; ++ iPos)
			{
				if ( memcmp( &cluster_data[iPos] , xml_end , xml_end_len ) == 0 )
				{	
					lastCount = iPos / (ClusterSize_*SectorSize);
					break;
				}
			}
			if ( lastCount > 0 )
			{
				DWORD fileInClusters = FileSize_ / (ClusterSize_ * SectorSize);

				WriteClusters( cluster_data , lastCount + 1 , (fileInClusters - lastCount)*ClusterSize_  );
			}
			CloseHandle(hTarget_);
			int k = 1;
			k = 2;
			++fileCounter;
			position += HeaderCluster + HeaderCluster;
			}

		}
		delete [] cluster_data;
		cluster_data = nullptr;
		int k = 1;
		k = 2;
		}
	}
	DWORD getFileSize( BYTE * data )
	{
		DWORD * file_size = (DWORD *) & data[ FileSizeOffset ];
		return * file_size;
	}
	int getChunkCount( DWORD file_size )
	{
		double dChunks = (double) ( file_size / (double)( (ClusterCount_) * ClusterSize_ * SectorSize) );
		int iVal = (int)ceil( dChunks );
		return iVal ;
	}
	void ReadData( BYTE * data , const DWORD data_size , LONGLONG sector, DWORD & BytesRead)
	{
		LARGE_INTEGER liPos;
		liPos.QuadPart = sector * SectorSize;
		::SetFilePointerEx( hSource_ , liPos , NULL , FILE_BEGIN );

		if ( ! ReadFile(hSource_ , data , data_size , &BytesRead , NULL ) )
		{
			printf("Error to read block");
			return ;
		}
	}
	void WriteData( BYTE * data , const DWORD data_size , LONGLONG sector, DWORD & BytesWrite)
	{
		LARGE_INTEGER liPos;
		liPos.QuadPart = sector * SectorSize;
		::SetFilePointerEx( hTarget_ , liPos , NULL , FILE_BEGIN );

		if ( ! WriteFile(hTarget_ , data , data_size , &BytesWrite , NULL ) )
		{
			printf("Error to write block");
			return ;
		}
	}
	bool ReadCluster( BYTE * data, LONGLONG sector )
	{
		DWORD bytesRead = 0;
		ReadData( data , ClusterSize_ * SectorSize , sector , bytesRead );
		return ( bytesRead != 0 ) ? true : false;
	}
	bool ReadClusters( BYTE * data, DWORD cluster_count, LONGLONG sector )
	{
		DWORD bytesRead = 0;
		ReadData( data , cluster_count * ClusterSize_ * SectorSize , sector , bytesRead );
		return ( bytesRead != 0 ) ? true : false;
	}
	bool WriteClusters(BYTE * data, DWORD cluster_count, LONGLONG sector)
	{
		DWORD bytesWrite = 0;
		WriteData( data , cluster_count * ClusterSize_ * SectorSize , sector , bytesWrite );
		return ( bytesWrite != 0 ) ? true : false;
	}
	LONGLONG findSignature( LONGLONG start_sector )
	{
		DWORD block_size = SectorSize * SectorsInBlock;
		DWORD read_bytes = 0;
		BYTE * data_buffer = new BYTE[ block_size ];
		DWORD sector_offset = 0;
		bool bFound = false;
		DWORD sector_counter = 0;
		while ( true )
		{
			ReadData( data_buffer , block_size , start_sector , read_bytes);
			if ( read_bytes == 0 )
			{
				start_sector = -1;
				break;
			}
			sector_offset = 0;
			sector_counter = 0;
			while ( sector_offset < read_bytes)
			{
				BYTE * sign = ( BYTE * ) &data_buffer[ sector_offset ];
				if ( memcmp( sign , AVI_Signature , AVI_SignSize ) == 0 )
				{
					bFound = true;
					break;
				}
				sector_offset += SectorSize;
				++sector_counter;
			}
			start_sector += sector_counter;
			if ( bFound )
				break;
		}

		delete [] data_buffer;
		return start_sector;
	}
private:
	HANDLE hSource_ ;
	HANDLE hTarget_;
	wstring SourceName_;
	wstring TargetName_;
	WORD ClusterCount_;		// 256
	WORD SkipCount_;		// 3
	WORD ClusterSize_ ;		// 64
	DWORD FileSize_;

};


const int parse_matrix[5][6] = 
{
	{ 4 , 4 , 4 , 4 , 4 , 4 } ,		//0	other...
	{ 0 , 4 , 4 , 4 , 4 , 2 } ,		//1	'['
	{ 4 , 0 , 2 , 2 , 4 , 4 } ,		//2	digits
	{ 4 , 1 , 4 , 4 , 4 , 4 } ,		//3	','
	{ 4 , 4 , 4 , 3 , 4 , 4 } 		//4	']'
};
const int OTHER = 0;
const int OPEN_BRAKET = 1;
const int DIGIT = 2;
const int COMMA = 3;
const int CLOSE_BRAKET = 4;

#include <boost\lexical_cast.hpp>

struct ClusterChunk
{
	ClusterChunk( LONGLONG offset , DWORD size)
		: offset_( offset )
		, size_ ( size )
	{

	}
	ClusterChunk( LONGLONG offset )
		: offset_( offset )
		, size_ ( 0 )
	{

	}
	void setSize( DWORD size )
	{
		size_ = size;
	}
	LONGLONG offset_;
	DWORD size_;
};

typedef std::list< ClusterChunk > ChunkList;



class ParseVCN
{
public:
	ParseVCN( const wstring & file_name )
		: file_name_( file_name)
		, bOpen( false )
	{
		if ( Open_Read(hRead_ , file_name_ ) )
			bOpen = true;
		else
		{
			printf("Error to open file...");
			bOpen = false;
		}
	}
	~ParseVCN()
	{
		CloseHandle( hRead_ );
	}
	void ParseFile( )
	{
		DWORD file_size = File_Size( hRead_ );
		if ( file_size > 0)
		{
			DWORD bytesRead = 0;
			char * file_data = new char [ file_size ];

			if ( !ReadFile(hRead_ , file_data , file_size , &bytesRead , NULL) )
			{
				printf("Error to read the file...");
			}
			DWORD cur_pos = 0;
			int cur_state = OTHER;
			string digit_val("");
			DWORD cluster_summa = 0;

			while ( cur_pos < bytesRead )
			{
				switch ( file_data[ cur_pos ] )
				{
					case '[' :
						digit_val.clear();
						cur_state = OPEN_BRAKET;
					 break;

					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						if ( cur_state != OTHER)
						{
							digit_val.push_back( file_data[ cur_pos ] );
							cur_state = DIGIT;
						}
						break;

					case ',':
						if ( cur_state == DIGIT )
						{
							auto cluster_number = boost::lexical_cast<long long> ( digit_val.c_str() );
							chunkList_.push_back(ClusterChunk(cluster_number));
							printf("[%ld,",cluster_number);
						}
						cur_state = COMMA;
						digit_val.clear();
						break;

					case ']':
						if ( cur_state == DIGIT )
						{
							auto cluster_count = boost::lexical_cast<long> ( digit_val.c_str() );
							if ( !chunkList_.empty() )
							{
								chunkList_.back().setSize(cluster_count);
							}
							printf("%d]\r\n",cluster_count);
							cluster_summa += cluster_count;
						}
						cur_state = CLOSE_BRAKET;
						break;
					default:
						cur_state = OTHER;

				}
				++cur_pos;
			}

			printf("\r\n\r\n Total cluster count = %d",cluster_summa);
			delete [] file_data;
		}
	}
	const ChunkList & getChunks() const
	{
		return chunkList_;
	}
private:
	ChunkList chunkList_;
	wstring file_name_;
	HANDLE hRead_;
	bool bOpen;
};

class GatherChanks
{
	static const int ClusterSize = 4096;
public:
	GatherChanks( const ChunkList & chunkList, const std::wstring & target_file , DWORD sourceDrive )
		: chankList_ ( chunkList )
		, file_name_ ( target_file )
		, sourceDrive_ ( sourceDrive )

	{
		if ( Open_Write(hWrite_ , file_name_ ) )
			bOpen_ = true;
		else
		{
			printf("Error to open file...");
			bOpen_ = false;
		}
	}
	~GatherChanks()
	{
		CloseHandle( hWrite_ );
	}
	void SetOffset( LONGLONG offset )
	{
		offset_ = offset;
	}
	void WriteChanks()
	{
		wstring sDrivePath = L"\\\\.\\PhysicalDrive";
		WCHAR buff[10];
		memset(buff,0,10);
		swprintf_s(buff,10,L"%d",sourceDrive_);
		sDrivePath.append(buff);
		if ( !Open_Read(hDrive_, sDrivePath) )
		{
			printf("Error to open drive.");
			return;
		}
		
		DWORD bytesRead = 0;
		DWORD bytesWrite = 0;
		LARGE_INTEGER liPos;
		liPos.QuadPart = 0;
		auto listIter = chankList_.begin();
		::SetFilePointer( hWrite_ , 0, NULL , FILE_END );
		while ( listIter != chankList_.end() )
		{
			BYTE * data = new BYTE[ listIter->size_ * ClusterSize ];

			liPos.QuadPart = offset_;
			liPos.QuadPart += ( LONGLONG ) (listIter->offset_ * ClusterSize);
			::SetFilePointerEx( hDrive_ , liPos , NULL , FILE_BEGIN );

			if ( !::ReadFile( hDrive_ , data , listIter->size_* ClusterSize , &bytesRead, NULL ) )
			{
				DWORD dwErorr = GetLastError();
				printf("Error to read from drive.");
				break;
			}
			if ( bytesRead == 0)
				break;

			if ( !::WriteFile( hWrite_ , data , bytesRead , &bytesWrite , NULL ) )
			{
				DWORD dwErorr = GetLastError();
				printf("Error write to file.");
				break;
			}

			delete [] data;

			++listIter;
		}

	}
private: 
	ChunkList chankList_;
	std::wstring file_name_;
	DWORD sourceDrive_;
	bool bOpen_;
	LONGLONG offset_;
	HANDLE hDrive_;
	HANDLE hWrite_;
};

class RepairFile
{
	static const int SectorsCount = 128;
	static const int Sector = 512;
	static const int BlockSize = SectorsCount * Sector;

public:
	RepairFile( const wstring & file_name )
		: hFile_ ( INVALID_HANDLE_VALUE )
	{
		bReady_ = Open_Read( hFile_ , file_name );
		if ( !bReady_ )
			printf("Error to open file");
	}
	~RepairFile()
	{
		CloseHandle(hFile_);
	}
	bool isReady( ) const 
	{
		return bReady_;
	}
	void Repair( const wstring & file_name)
	{
		HANDLE hWrite_ = INVALID_HANDLE_VALUE;
		if ( Create_File( hWrite_ , file_name ) )
		{
			BYTE read_block[BlockSize];
			DWORD bytesRead = 0;
			DWORD bytesWrite = 0;

			while ( true )
			{
				if ( ! ReadFile(hFile_ , read_block , BlockSize , &bytesRead , NULL ) )
				{
					printf("Error to read file");
						break;
				}
				if ( bytesRead == 0 )
					break;

				//if ( bytesRead == BlockSize )
					bytesRead -= Sector;
				

				if ( ! WriteFile( hWrite_ , read_block + Sector , bytesRead , &bytesWrite , NULL ) )
				{
					printf("Error to write file");
					break;
				}			
			
			}
		}
		else
			printf("Error to create file");

		CloseHandle (hWrite_);
	}
private:
	HANDLE hFile_;
	bool bReady_;

};

const DWORD Riff_Signture = 0x46464952;
const int WaveSignSize = 10;
const char WaveSignature[10] = { 0x57 , 0x41 , 0x56 , 0x45 , 0x62 , 0x65 , 0x78 , 0x74 , 0x5A , 0x02 };
const int AviSignSize = 8;
const char AviSignature[AviSignSize] = { 0x41 , 0x56 , 0x49 , 0x20 , 0x4C , 0x49 , 0x53 , 0x54 };

const int QtSignSize = 4;
const char QtSignature[QtSignSize] = { 0x6D , 0x64 , 0x61 , 0x74 }; 
const char MoovSignature[QtSignSize] = { 0x6D , 0x6F , 0x6F , 0x76 }; 

#pragma pack( 1 )
struct WaveHeader
{
	DWORD signature;
	DWORD size;
	char next_signature[10];
	char reserved[322];
	char data[18];
	char nolik;
	
	bool isWaveHeader() const
	{
		return signature == Riff_Signture;
	}
	bool isNextSignature() const
	{
		return memcmp( next_signature , WaveSignature , WaveSignSize ) == 0;
	}
};
#pragma pack ()

#pragma pack( 1 )
struct AVIHeader
{
	DWORD signature;
	DWORD size;
	char next_signature[AviSignSize];
	char reserved[325];
	char data[18];
	char nolik;

	bool isRiffHeader() const
	{
		return signature == Riff_Signture;
	}
	bool isAviSignature() const
	{
		return memcmp( next_signature , AviSignature , AviSignSize ) == 0;
	}
};
#pragma pack ()

#pragma pack( 1 )
struct QuickTimetHeader
{
	DWORD size;
	char signature[QtSignSize];
	bool isQuickTime() const
	{
		return  memcmp( &signature , QtSignature , QtSignSize ) == 0;
	}
	bool isMoov() const
	{
		return  memcmp( &signature , MoovSignature , QtSignSize ) == 0;
	}
	void changeSize()
	{
		size = ntohl( size );
	}
};
#pragma pack ()



#include <Utilities.h>

class RiffRaw
{
	static const int SectorSize = 512;
	static const int BlockCount = 256;
	static const int BlockSize = BlockCount * SectorSize;
	

public:
	RiffRaw( DWORD drive_number, const std::string & output_folder )
		: hDrive_( INVALID_HANDLE_VALUE )
		, bReady_( false )
		, out_folder_( output_folder )
	{
		wstring sDrivePath = L"\\\\.\\PhysicalDrive";
		WCHAR buff[10];
		memset(buff,0,10);
		swprintf_s(buff,10,L"%d", drive_number );
		sDrivePath.append(buff);
		if ( !Open_Write(hDrive_, sDrivePath) )
		{
			DWORD lastError = ::GetLastError();
			printf("Error to open drive.");
			return;
		}
		else
			bReady_ = true;
	}

	void WriteDataToFile( const LONGLONG offset , const DWORD size , HANDLE & hWriteFile )
	{
		BYTE * write_data = new BYTE[BlockSize];
		LARGE_INTEGER liTempPos;
		liTempPos.QuadPart = offset;

		DWORD tempBytesRead = 0;
		DWORD bytesWrite = 0;
		DWORD file_size = 0;


		while ( true)
		{
			::SetFilePointerEx(hDrive_, liTempPos , NULL , FILE_BEGIN );
			if ( ! ReadFile(hDrive_ , write_data , BlockSize ,&tempBytesRead , NULL ) )
			{
				DWORD dwError = ::GetLastError();
				printf("error to read..");
				break;
			}
			if ( tempBytesRead == 0)
				break;
			if ( file_size + tempBytesRead > size )
				tempBytesRead = size - file_size;
			file_size +=tempBytesRead;
			if ( ! WriteFile(hWriteFile  , write_data , tempBytesRead , &bytesWrite , NULL ) )
			{
				printf( "error to write... (# %d) ", ::GetLastError() );
				break;
			}
			liTempPos.QuadPart += BlockSize;
			if ( file_size >= size)
				break;
		}

		delete [] write_data;


	}
	void AppendFile( const LONGLONG offset , const DWORD size , HANDLE & hWriteFile)
	{
		LARGE_INTEGER file_size;
		if ( ::GetFileSizeEx( hWriteFile, &file_size ) )
		{
			::SetFilePointerEx(hWriteFile , file_size, NULL , FILE_BEGIN );
			WriteDataToFile( offset , size , hWriteFile );
		}
	}
	bool CreateFileFromName( HANDLE & hFile , const std::string & folder , DWORD counter , const std::string & ext )
	{
		char buff[10];
		memset(buff,0,10);
		sprintf_s(buff,10,"%.5d", counter );
		++counter;
		string number( buff );
		string file_path( folder +  number + ext );
		hFile = INVALID_HANDLE_VALUE;
		if ( ! Create_File(hFile , file_path ))
		{
			DWORD dwError = ::GetLastError();
			printf("Error to open write file: %s.",file_path.c_str());
			return false;
		}
		return true;
	}

	void Execute( )
	{
		if ( !bReady_ )
		{
			printf("Error device is not ready.\r\n");
			return;
		}

		LONGLONG position = 0;
		LARGE_INTEGER liPos;
		liPos.QuadPart = position;
		BYTE * data = new BYTE[BlockSize];
		DWORD BytesRead  = 0;
		DWORD iBlockPos = 0;
		DWORD counter = 0;
		while ( true )
		{
			::SetFilePointerEx( hDrive_ , liPos , NULL , FILE_BEGIN );
			if ( ! ReadFile( hDrive_  , data , BlockSize , &BytesRead , NULL ) )
			{
				printf("Error to read..");
				break;
			}
			if ( BytesRead == 0 )
				break;

			iBlockPos = 0;
			while ( iBlockPos < BytesRead )
			{
				//AVIHeader * pAviHeader = (AVIHeader *)&data[iBlockPos];
				QuickTimetHeader * pQtHeader = ( QuickTimetHeader * ) &data[iBlockPos];
				//if ( pAviHeader->isRiffHeader() )
				//{
				//	if ( pAviHeader->isAviSignature() )
				//	{
				//		pAviHeader->size += 8;
				//		if ( pAviHeader->size < 2000*1024*1024)
				//		{
				//			pAviHeader->nolik = 0;
				//			string file_name( pAviHeader->data );
				//			std::replace_if(file_name.begin(), file_name.end() , []( char val) { return val == ':'; } , '-' );
				//			std::replace_if(file_name.begin(), file_name.end() , []( char val) { return val == ' '; } , '-' );
				//			string folder( out_folder_ );
				//			//folder.append(file_name.substr(0,10) + '\\');
				//			//if ( Utility::isDirectoryExist(folder.c_str()) )
				//			{
				//				char buff[10];
				//				memset(buff,0,10);
				//				sprintf_s(buff,10,"%.5d", counter );
				//				++counter;
				//				string number( buff );
				//			string file_path( folder + file_name + "_" + number + ".avi" );
				//			HANDLE hWrite_file = INVALID_HANDLE_VALUE;
				//			if ( ! Create_File(hWrite_file , file_path ))
				//			{
				//				DWORD dwError = ::GetLastError();
				//				printf("Error to open write file: %s.",file_path.c_str());
				//				break;
				//			}

				//			LARGE_INTEGER liTempPos = liPos;
				//			liTempPos.QuadPart += iBlockPos;
				//			WriteDataToFile( liTempPos.QuadPart , pAviHeader->size , hWrite_file );

				//			CloseHandle(hWrite_file);
				//			}
				//		}
				//	}
				//}
				//else
				if ( pQtHeader->isQuickTime() )
				{
					pQtHeader->changeSize();
					HANDLE hWriteFile = INVALID_HANDLE_VALUE;
					if ( this->CreateFileFromName( hWriteFile , out_folder_ , counter , ".mov") )
					{
						++counter;
						LARGE_INTEGER liTempPos = liPos;
						liTempPos.QuadPart += iBlockPos;
						WriteDataToFile( liTempPos.QuadPart , pQtHeader->size , hWriteFile );

						liTempPos.QuadPart += pQtHeader->size;
						::SetFilePointerEx( hDrive_ , liTempPos , NULL , FILE_BEGIN );
						BYTE sector[SectorSize];
						DWORD tempBytesRead = 0;
						if ( ! ReadFile( hDrive_  , sector , SectorSize , &tempBytesRead , NULL ) )
						{
							printf("Error to read..");
							break;
						}
						if ( tempBytesRead == 0 )
							break;

						 pQtHeader = ( QuickTimetHeader * ) &sector[0];
						 if ( pQtHeader->isMoov() )
						 {
							 pQtHeader->changeSize();
							 this->AppendFile( liTempPos.QuadPart , pQtHeader->size , hWriteFile );
						 }
						 CloseHandle(hWriteFile);
						 //liPos = liTempPos;
						// continue;
					}
				}


				iBlockPos += SectorSize;
			}
			

			liPos.QuadPart += BytesRead;
		}
		delete [] data;
	}
private:
	HANDLE hDrive_;
	bool bReady_;
	std::string out_folder_;
};

class AbstractRaw
{
public:
	AbstractRaw( DWORD drive_number, const std::string & output_folder )
		: hDrive_( INVALID_HANDLE_VALUE )
		, bReady_( false )
		, out_folder_( output_folder )
	{
		wstring sDrivePath = L"\\\\.\\PhysicalDrive";
		WCHAR buff[10];
		memset(buff,0,10);
		swprintf_s(buff,10,L"%d", drive_number );
		sDrivePath.append(buff);
		if ( !Open_Read(hDrive_, sDrivePath) )
		{
			DWORD lastError = ::GetLastError();
			printf("Error to open drive.");
			return;
		}
		else
			bReady_ = true;
	}
	AbstractRaw( const std::string & source_file, const std::string & output_folder )
		: hDrive_( INVALID_HANDLE_VALUE )
		, bReady_( false )
		, out_folder_( output_folder )
	{
		if ( !Open_Read(hDrive_, source_file) )
		{
			DWORD lastError = ::GetLastError();
			printf("Error to open drive.");
			return;
		}
		else
			bReady_ = true;
	}

	virtual ~AbstractRaw()
	{
		CloseHandle(hDrive_);
	}
	HANDLE & getDrive() 
	{
		return hDrive_;
	}
	bool isReady() const
	{
		return bReady_ ;
	}
	void setReady( bool bReady )
	{
		bReady_ = bReady;
	}
	std::string outputFolder() const
	{
		return out_folder_;
	}
	virtual void execute() = 0;
private:
	HANDLE hDrive_;
	bool bReady_;
	std::string out_folder_;
};

const int PdfSignSize = 7;
const char PdfSignature[PdfSignSize] = { 0x25 , 0x50 , 0x44 , 0x46 , 0x2D , 0x31 , 0x2E};

const int PdfFooterSize = 5;
const char PdfFooter[PdfFooterSize] = { 0x25 , 0x25 , 0x45 , 0x4F , 0x46};

const string startxrefSing = "startxref";

inline bool isDigit( char digit_symbol )
{
	switch ( digit_symbol )
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return true;
	}
	return false;
}

#include <Shlwapi.h>

class PdfRaw
	: public AbstractRaw
{
public:
	PdfRaw( DWORD drive_number, const std::string & output_folder )
		: AbstractRaw( drive_number , output_folder )
	{

	}

	void execute()
	{
		if ( !this->isReady() )
		{
			printf("Error device is not ready.\r\n");
			return;
		}

		LONGLONG position = 1741705216;
		LARGE_INTEGER liPos;
		liPos.QuadPart = position;
		const DWORD BlockSize = 256*512;
		BYTE * data = new BYTE[BlockSize];

		DWORD BytesRead  = 0;
		DWORD BytesWrite = 0;
		auto DriveHandle = this->getDrive();
		DWORD iBlockPos = 0;

		bool bFoundSignature = false;

		const DWORD MaxPdfSize = 200*1024*1024;
		DWORD iCurrSize = 0;
		DWORD counter = 0;
	
		HANDLE hWrite = INVALID_HANDLE_VALUE;

		while ( true )
		{
			::SetFilePointerEx( DriveHandle , liPos , NULL , FILE_BEGIN );
			if ( ! ReadFile( DriveHandle , data , BlockSize , &BytesRead , NULL ) )
			{
				printf("Error to read..");
				break;
			}

			if ( BytesRead == 0 )
				break;

			iBlockPos = 0;
			while ( iBlockPos < BytesRead - PdfSignSize )
			{
				if ( memcmp(data + iBlockPos , PdfSignature , PdfSignSize ) == 0 )
				{
					iCurrSize = 0;
					LONGLONG lShowPos = liPos.QuadPart;
					lShowPos += iBlockPos;
					printf("Found Pdf signature. Offset = %ld\r\n" , lShowPos );
					char buff[10];
					memset(buff,0,10);
					sprintf_s(buff,10,"%.5d", counter );
					++counter;
					std::string file_name(buff);
					file_name.append(".pdf");
					std::string full_path( outputFolder() + file_name );
					if ( !Create_File(hWrite , full_path ) )
					{
						printf( "Error to create target file: %s", full_path.c_str() );
						return;
					}
					bFoundSignature = true;
					break;

				}
				++iBlockPos;
			}
			if ( bFoundSignature )
			{
				DWORD tempPos = iBlockPos;
				iCurrSize = 0;
				while ( iCurrSize < MaxPdfSize)
				{
					while ( iBlockPos < BytesRead - PdfFooterSize )
					{
						if ( memcmp(data + iBlockPos , PdfFooter , PdfFooterSize ) == 0 )
						{
							for( DWORD iPos = iBlockPos - startxrefSing.size() ; iPos > tempPos ; --iPos )
							{
								// find 'startxref'
								if ( memcmp( data + iPos , startxrefSing.c_str() , startxrefSing.size() ) == 0 )
								{
									std::string digit_string;
									DWORD tempNewPos = iPos + startxrefSing.size();
									if ( data[tempNewPos] == 0x0D )
										++tempNewPos;
									if ( data[tempNewPos] == 0x0A)
										++tempNewPos;
									char temp_symbol = 0;
									while ( true )
									{
										temp_symbol = data[tempNewPos];
										if ( temp_symbol == 0xD)
											break;
										if ( isDigit(temp_symbol) )
											digit_string += temp_symbol;
										else
											break;
										++tempNewPos;
									}
									LONGLONG xRefSize = 0;
									if ( StrToInt64ExA(digit_string.c_str() , STIF_DEFAULT ,&xRefSize) )
									{
										if ( xRefSize != 0 )
										{
											printf("found Pdf end.");
											DWORD endPos = iBlockPos + PdfFooterSize;
											if ( !::WriteFile( hWrite , data + tempPos, endPos - tempPos, &BytesWrite, NULL ) )
											{
												printf("error to write");
												return;
											}
											iCurrSize += endPos - tempPos;
											bFoundSignature = false;
											break;
										}
										
									}

								}
							}

						}
						if ( !bFoundSignature )
							break;
						++iBlockPos;
					}

					if ( bFoundSignature )
					{
						if ( !::WriteFile( hWrite , data + tempPos , BytesRead - tempPos, &BytesWrite, NULL ) )
						{
							printf("error to write");
							return;
						}
						iCurrSize += BytesRead - tempPos;
						if ( iCurrSize >= MaxPdfSize )
						{
							bFoundSignature = false;
							break;
						}

						liPos.QuadPart += BytesRead;
						::SetFilePointerEx( DriveHandle , liPos , NULL , FILE_BEGIN );
						if ( ! ReadFile( DriveHandle , data , BlockSize , &BytesRead , NULL ) )
						{
							printf("Error to read..");
							break;
						}

						iBlockPos = 0;
						tempPos = 0;
					}
					else
						break;
				}

				CloseHandle(hWrite);
			}
			else
				liPos.QuadPart += BytesRead;
		}

		delete [] data;
		data = nullptr;

	}
};

struct struct_data1
{
	char s0[2];
	char d1[1660];
	char s1[2];
	char d2[502];
	char s2[2];
	char d3[1130];
	char s3[2];
	char d4[1130];
	char s4[2];
	char d5[824];
	char s5[2];
	char d6[306];
	char s6[2];
	char d7[1130];
	char s7[2];
	char d8[450];
	char s8[2];
	char d9[680];
	char s9[2];
	char d10[1130];
	char s10[2];
	char d11[114];
};

class WithoutService
{
	static const int ReadBlockSize = 9216;
	static const int WriteBlockSize = 9056;
public:
	WithoutService( const std::string & file_name )
		: bReady_( false )
		, hRead_ ( INVALID_HANDLE_VALUE )
		, hWrite_( INVALID_HANDLE_VALUE )
	{
		if ( Open_Read(hRead_ , file_name) )
		{
			if ( Create_File(hWrite_ , file_name + ".new" ) )
				bReady_ = true;
		}

	}

	bool isReady() const
	{
		return bReady_;
	}
	void Execute()
	{
		if ( !bReady_)
		{
			printf("Not ready...");
		}
		BYTE readData[ReadBlockSize];
		BYTE writeData[WriteBlockSize];
		DWORD bytesRead = 0 ;
		DWORD bytesWrite = 0;
		while ( true )
		{
			if ( ! ::ReadFile( hRead_ , readData , ReadBlockSize , &bytesRead , NULL) )
			{
				printf("Error read");
				break;
			}
			if ( bytesRead == 0 )
				break;
			ZeroMemory( writeData , WriteBlockSize );
			struct_data1 * pData1 = (struct_data1 *) readData;
			DWORD offset = 0;
			DWORD size = 0;

			size = sizeof(pData1->d1);
			memcpy( writeData + offset , pData1->d1 , size );
			offset += size;

			size = sizeof(pData1->d2);
			memcpy( writeData + offset , pData1->d2 , size );
			offset +=size;

			size = sizeof(pData1->d3);
			memcpy( writeData + offset , pData1->d3 , size );
			offset +=size;

			size = sizeof(pData1->d4);
			memcpy( writeData + offset , pData1->d4 , size );
			offset +=size;

			size = sizeof(pData1->d5);
			memcpy( writeData + offset , pData1->d5 , size );
			offset +=size;

			size = sizeof(pData1->d6);
			memcpy( writeData + offset , pData1->d6 , size );
			offset +=size;

			size = sizeof(pData1->d7);
			memcpy( writeData + offset , pData1->d7 , size );
			offset +=size;

			size = sizeof(pData1->d8);
			memcpy( writeData + offset , pData1->d8 , size );
			offset +=size;

			size = sizeof(pData1->d9);
			memcpy( writeData + offset , pData1->d9 , size );
			offset +=size;

			size = sizeof(pData1->d10);
			memcpy( writeData + offset , pData1->d10 , size );
			offset +=size;

			size = sizeof(pData1->d11);
			memcpy( writeData + offset , pData1->d11 , size );

			if ( ! ::WriteFile( hWrite_ , writeData , WriteBlockSize , &bytesWrite , NULL) )
			{
				printf("Error write..");
				break;
			}
			if ( bytesWrite == 0 )
				break;

		}
		
	}
private:
	HANDLE hRead_;
	HANDLE hWrite_;
	bool bReady_;
};

//struct ServiceCounter
//{
//	DWORD addr;
//	WORD count;
//};


inline bool CutService( const std::string & file_name )
{
	HANDLE hRead = INVALID_HANDLE_VALUE;
	if ( !Open_Read( hRead , file_name ) )
		return false;

	std::string write_name( file_name );
	write_name.insert(write_name.size(),"_SA");
	HANDLE hWrite = INVALID_HANDLE_VALUE;
	if ( !Create_File( hWrite , write_name ) )
		return false;


	const int PageReadSize = 2112;
	const int PageWriteSize = 2048;

	char read_data[ PageReadSize ] ;

	DWORD bytesRead = 0;
	DWORD bytesWrite = 0;

	while ( true )
	{
		if ( ! ::ReadFile(hRead , read_data , PageReadSize , &bytesRead, NULL ) )
		{
			printf("Error to read file.");
			break;
		}
		if ( bytesRead == 0 )
			break;

		if ( ! ::WriteFile(hWrite , read_data , PageWriteSize , &bytesWrite, NULL ) )
		{
			printf("Error to read file.");
			break;
		}
		if ( bytesWrite == 0 )
			break;
	}

	CloseHandle(hRead);
	CloseHandle(hWrite);

	return true;
}

class SamsungX820
{
public:
	SamsungX820( const std::string & file_name)
		: bReady_( false )
		, hRead_ ( INVALID_HANDLE_VALUE )
		, hWrite_( INVALID_HANDLE_VALUE )
	{
		if ( Open_Read(hRead_ , file_name) )
		{
			//if ( Create_File(hWrite_ , file_name + ".new" ) )
				bReady_ = true;
		}

	}
	bool isReady() const
	{
		return bReady_;
	}

	void execute( const std::string & target_name )
	{
		if ( !bReady_ )
		{
			printf("Source file not ready.");
			return;
		}

		if ( ! Create_File( hWrite_ , target_name ) )
		{
			printf("Target file not ready.");
			return;
		}

		table_.resize( 216027 , 0x0000 );
		const DWORD PageSize = 2112;
		const DWORD DataSize = 2048;
		const DWORD SectorPerPage = 4;
		const DWORD ServiceSize = 16;
		const DWORD SectorSize = 512;
		BYTE read_data[PageSize];
		DWORD bytesRead = 0;
		DWORD bytesWrite = 0;
		DWORD service_offset = 0;
		DWORD sector_offset = 0;
		DWORD target_offset = 0;
		DWORD source_offset = 0;

		DWORD file_size = ::GetFileSize( hRead_ , NULL );
		source_offset = file_size;
		source_offset -= PageSize;

		while ( source_offset > 0  )
		{
			::SetFilePointer(hRead_ , source_offset , NULL , FILE_BEGIN );
			if ( ! ::ReadFile(hRead_ , read_data , PageSize , &bytesRead, NULL ) )
			{
				printf("Error to read file.");
				break;
			}
			if ( bytesRead == 0 )
				break;

			for ( auto iSector = 0; iSector < SectorPerPage ; ++iSector )
			{
				service_offset = DataSize + iSector*ServiceSize + 2;
				BYTE * addr1 = (BYTE*)&read_data[service_offset];
				BYTE * addr2 = (BYTE*)&read_data[service_offset + 1];
				BYTE * addr3 = (BYTE*)&read_data[service_offset + 2];

				BYTE * pFD = (BYTE*)&read_data[service_offset + 3];

				sector_offset = *addr1 | (* addr2 << 8 ) | ( *addr3 << 16 ); 
				target_offset = sector_offset *SectorSize;
				if ( target_offset < 0x7380000 )
				{
					//if ( *pFD != 0xFC )
					{
					if ( table_[ sector_offset ] <= 4 )
					{
						::SetFilePointer(hWrite_, target_offset , NULL , FILE_BEGIN );
						if ( !::WriteFile(hWrite_ , read_data + iSector*SectorSize , SectorSize , &bytesWrite, NULL ) )
						{
							printf("Error to write file.");
							break;
						}
					


					}
					table_[ sector_offset ] += 1;
					}	
				}
			}
	
			source_offset -= PageSize;
		}

	}
private:
	std::vector< WORD > table_;
	bool bReady_;
	HANDLE hRead_;
	HANDLE hWrite_;
};


#define SIZEOF_ARRAY( a ) (sizeof( a ) / sizeof( a[ 0 ] ))

namespace Signautre
{
	const char Mov[] =  { 0x00 , 0x00 , 0x00 , 0x14 , 0x66 , 0x74 , 0x79 , 0x70 , 0x71 , 0x74 , 0x20 , 0x20 , 0x00 , 0x00 , 0x00 , 0x00};
	const char Canon_mov[] = { 0x00 , 0x00 , 0x00 , 0x18 , 0x66 , 0x74 , 0x79 , 0x70 , 0x71 , 0x74 , 0x20 , 0x20 , 0x20 , 0x07 , 0x09 , 0x00};
	const char qt_header[] = { 0x00 , 0x00 , 0x00 , 0x18 , 0x66 , 0x74 , 0x79 , 0x70 , 0x71 , 0x74 , 0x20 , 0x20 , 0x20 , 0x07 , 0x09 , 0x00};
	//const char Mov2[] =      { 0x00 , 0x00 , 0x00 , 0x18 , 0x66 , 0x74 , 0x79 , 0x70 , 0x71 , 0x74 , 0x20 , 0x20 , 0x20 , 0x07 , 0x09 , 0x00};
	const char mp4[] = { 0x00 , 0x00 , 0x00 , 0x1C , 0x66 , 0x74 , 0x79 , 0x70 , 0x4D , 0x53 , 0x4E , 0x56 , 0x01 , 0x29 , 0x00 , 0x46};
	const string mov_name = "moov";
	const char moov[] = { 0x6D , 0x6F , 0x6F , 0x76 };
	const char mdat[] = { 0x6D , 0x64 , 0x61 , 0x74 };
	const char MXF[] = { 0x06 , 0x0E , 0x2B , 0x34 , 0x02 , 0x05 , 0x01 , 0x01 , 0x0D , 0x01 , 0x02 , 0x01 , 0x01 , 0x02 , 0x04 , 0x00};
}

#pragma pack( 1 )
struct CannonMovData
{
	char header[ SIZEOF_ARRAY(Signautre::Canon_mov) ];
	void change_size()
	{
		size = ntohl(size );
	}
	char data[8];
	DWORD size;
	bool isCanonHeader( ) const
	{
		return ( memcmp ( header , Signautre::Canon_mov , SIZEOF_ARRAY( Signautre::Canon_mov ) ) == 0 );
	}
};
#pragma pack( )

#pragma pack( 1 )
struct mdatHeader
{
	DWORD size;
	char mdat_data[4];
	void change_size()
	{
		size = ntohl(size );
	}
	bool isMdatHeader() const
	{
		return ( memcmp ( mdat_data , Signautre::mdat , SIZEOF_ARRAY( Signautre::mdat ) ) == 0 );
	}
};
#pragma pack( )


struct MovHeader
{
	char header[ SIZEOF_ARRAY(Signautre::Mov) ];
	char header_next[8];
	DWORD data_size;
	char mdat[4];

	void change_size()
	{
		data_size = ntohl( data_size );
	}

	bool isMovHeader() const
	{
		return ( memcmp ( header , Signautre::Canon_mov , SIZEOF_ARRAY( Signautre::Canon_mov ) ) == 0 );
	}

	bool isMp4Header() const
	{
		return ( memcmp ( header , Signautre::Canon_mov , SIZEOF_ARRAY( Signautre::Canon_mov ) ) == 0 );
	}

	bool is_mdat() const
	{
		return ( memcmp( mdat  , Signautre::mdat , SIZEOF_ARRAY( Signautre::mdat ) ) == 0 );
	}
	bool is_moov() const
	{
		return ( memcmp( mdat  , Signautre::moov , SIZEOF_ARRAY( Signautre::moov ) ) == 0 );
	}

};

const int DefaulSectors = 256;
const int BufferSize = SectorSize * DefaulSectors;

inline bool WriteData( HANDLE & hDevice , LONGLONG position , DWORD size , HANDLE & hTarget , LONGLONG target_offset = 0 )
{
	if ( hDevice == INVALID_HANDLE_VALUE )
		return false;

	if ( hTarget == INVALID_HANDLE_VALUE )
		return false;

	
	BYTE buffer[ BufferSize ];

	DWORD bytesRead = 0;
	DWORD bytesWritten = 0;

	DWORD pos = 0;
	bool bReadResult = false;
	bool bWriteResult = false;
	LARGE_INTEGER read_pos;
	read_pos.QuadPart = position;
	::SetFilePointerEx( hDevice , read_pos, NULL , FILE_BEGIN );
	LARGE_INTEGER write_pos;
	write_pos.QuadPart = target_offset;
	::SetFilePointerEx( hTarget , write_pos, NULL , FILE_BEGIN );
	DWORD bytesToRead = 0;
	while ( pos < size )
	{
		if ( (pos + BufferSize) <= size )
			bytesToRead = BufferSize;
		else
		{
			bytesToRead = size - pos;
			bytesToRead /= SectorSize;
			++bytesToRead;
			bytesToRead *= SectorSize;
		}


		bReadResult = ReadBlock( hDevice , buffer , bytesToRead , bytesRead );

		if ( bytesRead == 0 )
			break;

		if ( !bReadResult )
			return false;

		
		bWriteResult = WriteBlock(hTarget , buffer , bytesToRead , bytesWritten );
		if ( !bWriteResult )
			return false;

		pos += bytesRead;
	}

	return true;
}


const char EncryptData[] = { 0xC1 , 0x88 , 0xD4 , 0xC6 , 0xC2 , 0xEA , 0x3A , 0x2D , 0x12 , 0x65 , 0xFA , 0x60 , 0xEF , 0x92 , 0x1B , 0x90 };
const char EncryptData2[] = { 0xF7 , 0x3E , 0x8F , 0xA2 , 0xD7 , 0x15 , 0xC9 , 0x71 , 0xB8 , 0xE5 , 0xFB , 0xDB , 0x1B , 0x9C , 0xC9 , 0x9A };

inline bool decrypt_data( BYTE *source , BYTE * target , DWORD size )
{
	if ( source == nullptr )
		return false;

	if ( target == nullptr )
		return false;

	if ( size == 0 )
		return false;

	for ( DWORD iData = 0; iData < size ; ++iData )
	{
		target[ iData ] = source[ iData ] ^ EncryptData[ iData % SIZEOF_ARRAY( EncryptData) ];
	}

	return true;
}

class DecryptDisk
	: public AbstractRaw
{
	static const int start_sector = 2048;
public:
	DecryptDisk( DWORD source_number, DWORD target_number )
		: AbstractRaw( source_number , "" )
	{
		if ( !OpenDriveByNamber(target_number , hTarget_ , OpenReadWriteMode ) )
			this->setReady( false );
	}
	void execute()
	{
		if ( !this->isReady() )
			return ;


		LARGE_INTEGER lOffset;
		lOffset.QuadPart = start_sector * SectorSize;

		DWORD bytesRead = 0;
		DWORD bytesWrite = 0;

		BYTE read_buffer[ BufferSize ];
		BYTE write_buffer[ BufferSize ];

		bool bResult = 0;

		while ( true )
		{
			::SetFilePointerEx( this->getDrive() , lOffset , NULL , FILE_BEGIN );
			bResult = ReadBlock(this->getDrive() , read_buffer , BufferSize , bytesRead );

			if ( !bResult )
				break;
			if( bytesRead == 0 )
				break;
			
			decrypt_data( read_buffer , write_buffer , bytesRead );

			::SetFilePointerEx( hTarget_ , lOffset , NULL , FILE_BEGIN );
			bResult = WriteBlock( hTarget_ , write_buffer , bytesRead , bytesWrite );

			if ( !bResult )
				break;

			if ( bytesWrite == 0 )
				break;

			
			//int k = 1;
			//k = 2;


		}
		
	}
private:
	HANDLE hTarget_;
};

class CanonFragmentMovRaw
	: public AbstractRaw
{
public:
	CanonFragmentMovRaw( const std::string & source_file, const std::string & output_folder )
		: AbstractRaw( source_file , output_folder )
	{

	}
	void execute( )
	{
		if ( !this->isReady() )
		{
			printf("Device isn't ready.");
			return;
		}

		BYTE buffer[BufferSize];
		BYTE buffer2[BufferSize ];

		bool bResult = false;
		DWORD bytesRead = 0;
		DWORD iSector = 0;

		LONGLONG mdat_pos = 0;
		LONGLONG header_pos = 0;

		LONGLONG pos = 0;

		bool bFoundMdat = false;
		mdatHeader * pMdat = nullptr;
		CannonMovData * pHeader = nullptr;
		//MovHeader * mov_header = nullptr;
		LARGE_INTEGER offset;
		offset.QuadPart = 0;

		int counter = 0;

		while ( true )
		{
			offset.QuadPart = pos;
			::SetFilePointerEx(this->getDrive() , offset , NULL , FILE_BEGIN );
			bResult = ReadBlock( this->getDrive() , buffer , BufferSize , bytesRead );

			if ( !bResult )
				break;
			if ( bytesRead == 0 )
				break;

			for ( iSector = 0 ; iSector < bytesRead ; iSector += SectorSize )
			{
				pMdat = ( mdatHeader * ) &buffer[ iSector ];

				if ( pMdat->isMdatHeader() )
				{
					pMdat->change_size();
					bFoundMdat = true;
					mdat_pos = pos;
					mdat_pos += iSector;

					DWORD headerSector = pMdat->size / SectorSize;
					headerSector *= SectorSize;

					pos += iSector;
					pos += headerSector;

					pMdat->size = headerSector;
					printf( "Found mdat...\r\n" );
					break;
				}
			}

			if ( bFoundMdat )
			{
				while ( true )
				{
					offset.QuadPart = pos;
					::SetFilePointerEx(this->getDrive() , offset , NULL , FILE_BEGIN );
					bResult = ReadBlock( this->getDrive() , buffer2 , BufferSize , bytesRead );
					if ( bytesRead == 0 )
						break;

					for ( iSector = 0 ; iSector < bytesRead ; iSector += SectorSize )
					{
						pHeader = ( CannonMovData * ) &buffer2[ iSector ];
						if ( pHeader->isCanonHeader() )
						{
							pHeader->change_size();
							pHeader->size += 24;
							char buff[10];
							memset(buff,0,10);
							sprintf_s(buff,10,"%.5d", counter++ );
							
							HANDLE hWrite = INVALID_HANDLE_VALUE;
							std::string write_file( this->outputFolder() );
							write_file.append(buff);
							write_file.append(".mov");
							if ( !Create_File(hWrite , write_file) )
							{
								printf("error to create new file...");
								exit(-1);
							}			
							pos += iSector;
							if ( ! WriteData( this->getDrive() , pos , pHeader->size , hWrite ) )
							{
								printf("error to write file...");
								exit(-1);
							}
							if ( ! WriteData( this->getDrive() , mdat_pos , pMdat->size , hWrite , pHeader->size ) )
							{
								printf("error to write file...");
								exit(-1);
							}

							CloseHandle( hWrite );
							bFoundMdat = false;

							DWORD next = pHeader->size / SectorSize;
							next *= SectorSize;
							pos += next;
							//pos /= SectorSize;
							//pos *= SectorSize;
							break;
						}
						
					}
					if ( !bFoundMdat )
						break;
				}

			}
			else
				pos += bytesRead;
		}
	}

};

class CanonMovRaw
	: public AbstractRaw
{
public:
	CanonMovRaw( DWORD number, const std::string & output_folder )
		: AbstractRaw( number , output_folder )
	{

	}
	CanonMovRaw( const std::string & file_name, const std::string & output_folder )
		: AbstractRaw( file_name , output_folder )
	{

	}
	void execute()
	{
		if ( !this->isReady() )
		{
			printf("Device isn't ready.");
			return;
		}

		BYTE buffer[BufferSize];
		BYTE buffer_mov[1024];


		bool bResult = false;
		DWORD bytesRead = 0;
		DWORD iSector = 0;
		bool bFound = false;
		LONGLONG pos = 0;
		LONGLONG header_pos = 0;
		LARGE_INTEGER lpos;
		lpos.QuadPart = 0;

		MovHeader * pMovHeader = nullptr;
		DWORD counter = 0;

		DWORD sizeHeader = 8 + 8 + 4 + 4;

		while ( true )
		{
			lpos.QuadPart = pos;
			::SetFilePointerEx( this->getDrive() , lpos , NULL , FILE_BEGIN );
			bResult = ReadBlock( this->getDrive() , buffer , BufferSize , bytesRead );

			if (  bytesRead == 0 )
				break;

			for ( iSector = 0 ; iSector < bytesRead ; iSector += SectorSize )
			{
				pMovHeader = ( MovHeader * ) &buffer[ iSector ];
				if ( pMovHeader->isMovHeader() )
				if ( pMovHeader->is_moov() )
				{
					pMovHeader->change_size();
					bFound = true;
					header_pos = pos;
					header_pos += iSector;
					printf("Found MOV header : %lld \r\n" , header_pos );
					break;
				}



			}

			if ( bFound )
			{
				bFound = false;
				LONGLONG mov_pos = header_pos;
				mov_pos += sizeHeader;
				mov_pos += pMovHeader->data_size;

				LONGLONG sector_pos = mov_pos;
				sector_pos /= SectorSize;
				sector_pos *= SectorSize;
				DWORD mov_offset = mov_pos - sector_pos ;
				DWORD bytesRead1 = 0;
				lpos.QuadPart = sector_pos;
				::SetFilePointerEx( this->getDrive() , lpos , NULL , FILE_BEGIN );
				bResult = ReadBlock( this->getDrive() , buffer_mov , 1024 , bytesRead1 );
				if ( bytesRead1 == 0 )
					break;

				if ( memcmp( buffer_mov + mov_offset + 4 , Signautre::mdat , SIZEOF_ARRAY( Signautre::mdat ) ) == 0)
				{
					DWORD * pMovSize = (DWORD * ) & buffer_mov[ mov_offset ];
					*pMovSize = ntohl( *pMovSize );

					DWORD full_file_size = pMovHeader->data_size + *pMovSize + 4 + sizeHeader;
					char buff[10];
					memset(buff,0,10);
					sprintf_s(buff,10,"%.5d", counter++ );

					HANDLE hWrite = INVALID_HANDLE_VALUE;
					std::string write_file( this->outputFolder() );
					write_file.append(buff);
					write_file.append(".mov");
					if ( !Create_File(hWrite , write_file) )
					{
						printf("error to create new file...");
						exit(-1);
					}

					bResult = WriteData( this->getDrive() , header_pos , full_file_size , hWrite );
					if ( !bResult )
						break;

					printf("File %s was written successfully.\r\n", write_file.c_str());

					CloseHandle( hWrite );

					DWORD next_pos = full_file_size / SectorSize;
					next_pos *= SectorSize;
					pos += next_pos;

				}
				else
				{
					pos = header_pos;
					pos += SectorSize;
				}

			}
			else
				pos += bytesRead;
		}


	}

};

class iPhoneVideoRaw
	: public AbstractRaw
{
	static const int SectorSize = 512;
	static const int BlockCount = 256;
	static const int BlockSize = BlockCount * SectorSize;

public:
	iPhoneVideoRaw( DWORD number , const std::string output_folder)
		: AbstractRaw( number , output_folder )
	{


	}
	iPhoneVideoRaw( const std::string & source_file, const std::string & output_folder )
		: AbstractRaw( source_file , output_folder )
	{

	}
	void execute( )
	{
		if ( !this->isReady() )
		{
			printf("Device isn't ready.");
			return;
		}
		BYTE read_buffer[BlockSize];

		LONGLONG offset = 4533125120;
		LONGLONG next_offset = 0;
		LONGLONG append_offset = 0;
		LARGE_INTEGER read_offset;
		read_offset.QuadPart = offset;
		DWORD bytesRead = 0;
		DWORD moov_offset = 0;
		int counter = 0;

		BYTE mov_data[1024];
		bool bFound = false;


		while ( true )
		{
			bytesRead = 0;
			read_offset.QuadPart = offset;
			::SetFilePointerEx( this->getDrive() , read_offset, NULL , FILE_BEGIN );
			if ( !ReadBlock(this->getDrive() , read_buffer , BlockSize , bytesRead ) )
				break;
			if ( bytesRead == 0 )
				break;

			for ( DWORD iSector = 0 ; iSector < bytesRead ; iSector += SectorSize )
			{
				MovHeader * header = ( MovHeader *) ( &read_buffer[iSector] );
			
				if ( header->isMp4Header() )
				{
					header->change_size();
					next_offset = offset;
					next_offset += iSector;

					char buff[10];
					memset(buff,0,10);
					sprintf_s(buff,10,"%.5d", counter );
					HANDLE hWrite = INVALID_HANDLE_VALUE;
					std::string write_file( this->outputFolder() );
					write_file.append(buff);
					write_file.append(".mov");
					if ( !Create_File(hWrite , write_file) )
					{
						printf("error to create new file...");
						exit(-1);
					}
					++counter;
					header->data_size += 4;
					if ( !WriteDataToFile( this->getDrive() , next_offset , header->data_size ,  hWrite ) )
						break;

					append_offset = next_offset;

					//DWORD file_sector = header->data_size / SectorSize;
					//file_sector *= SectorSize;
					DWORD newBytesRead = 0;
					LARGE_INTEGER mov_pos;
					mov_pos.QuadPart = append_offset;
					mov_pos.QuadPart += header->data_size;
					::SetFilePointerEx( this->getDrive() , mov_pos , NULL , FILE_BEGIN );
					::ReadBlock( this->getDrive() , mov_data , 1024 , newBytesRead);
					if ( newBytesRead == 0 )
						break;
					
					append_offset += header->data_size;
					//WORD sector_offset = (WORD) (header->data_size - file_sector);
					if ( memcmp( mov_data + 4, Signautre::mov_name.data() , Signautre::mov_name.size() ) == 0 )
					{
						DWORD * mov_size = (DWORD *) &mov_data[ 0 ];
						DWORD last_size = ntohl(*mov_size);
						last_size += 4;
						if ( !AppendFile( this->getDrive() , append_offset, last_size , hWrite ) )
						{
							break;
						}
						DWORD add_pos = header->data_size + last_size ;
						add_pos /= SectorSize;
						add_pos *= SectorSize;
						offset = next_offset ;
						offset += add_pos ;
						CloseHandle(hWrite);

						bFound = true;

						break;
					}

					CloseHandle(hWrite);
				}

			}
			if ( !bFound )
				offset += bytesRead;
			else
				bFound = false;
		}


		CloseHandle( this->getDrive() );
	}
};

class MXFVideoRaw
	: public AbstractRaw
{
	static const int SectorSize = 512;
	static const int BlockCount = 256;
	static const int BlockSize = BlockCount * SectorSize;
	static const int TailSize = 0x29BC;
public:
	MXFVideoRaw( const std::string & source_file, const std::string & output_folder )
		: AbstractRaw( source_file , output_folder )
	{

	}
	//MXFVideoRaw( const std::string & source_file, const std::string & output_folder )
	//	: AbstractRaw( source_file , output_folder )
	//{

	//}
	//v
	void execute( )
	{
		if ( !this->isReady() )
		{
			printf("Device isn't ready.");
			return;
		}
		BYTE read_buffer[BlockSize];
		LARGE_INTEGER read_offset;
		read_offset.QuadPart = 0;
		LONGLONG next_offset = 0;
		LONGLONG offset = 2206904913408;
		DWORD bytesRead = 0;
		int counter = 0;

		bool bFound = 0;

		while ( true )
		{
			bytesRead = 0;
			read_offset.QuadPart = offset;
			::SetFilePointerEx( this->getDrive() , read_offset, NULL , FILE_BEGIN );
			if ( !ReadBlock(this->getDrive() , read_buffer , BlockSize , bytesRead ) )
				break;
			if ( bytesRead == 0 )
				break;

			for ( DWORD iSector = 0 ; iSector < bytesRead ; iSector += SectorSize )
			{
				if ( memcmp( Signautre::MXF, &read_buffer[iSector], SIZEOF_ARRAY(Signautre::MXF) ) == 0 )
				{
					next_offset = offset;
					next_offset += iSector;					


					DWORD * file_size = (DWORD*) &read_buffer[iSector + 48];
					*file_size = ntohl(*file_size);
					*file_size += TailSize;
					char buff[10];
					memset(buff,0,10);
					sprintf_s(buff,10,"%.5d", counter );
					HANDLE hWrite = INVALID_HANDLE_VALUE;
					std::string write_file( this->outputFolder() );
					write_file.append(buff);
					write_file.append(".mxf");
					if ( !Create_File(hWrite , write_file) )
					{
						printf("error to create new file...");
						exit(-1);
					}
					++counter;
					if ( !WriteDataToFile( this->getDrive() , next_offset , * file_size ,  hWrite ) )
						break;

						DWORD add_pos = *file_size ;
						add_pos /= SectorSize;
						add_pos *= SectorSize;
						offset = next_offset ;
						offset += add_pos ;
						CloseHandle(hWrite);

						bFound = true;
						break;
				}

				

			}
			if ( !bFound )
				offset += bytesRead;
			else
				bFound = false;
		}


		CloseHandle( this->getDrive() );
	}

};

class GatherRaid
{
	static const DWORD DefaultBlockCount = 256;
	static const DWORD DefaultBlockSize = SectorSize * DefaultBlockCount;
public:
	GatherRaid( DWORD disk1 , DWORD disk2, DWORD target )
		: hDisk1_( INVALID_HANDLE_VALUE )
		, hDisk2_( INVALID_HANDLE_VALUE )
		, hTarget_ ( INVALID_HANDLE_VALUE )
		, bReady_ ( false )
	{
		if ( !OpenDriveByNamber( disk1 , hDisk1_ ))
			return;
		if ( !OpenDriveByNamber( disk2 , hDisk2_ ))
			return;
		if ( !OpenDriveByNamber( target , hTarget_ , OpenWriteMode ))
			return;

		bReady_ = true;

	}
	void Execute( )
	{
		if ( !bReady_ )
		{
			printf( "Devices are not ready. Sorry.");
			return ;
		}

		DWORD BytesRead1 = 0;
		DWORD BytesRead2 = 0;
		DWORD BytesWrite = 0;

		BYTE buffer1[ DefaultBlockSize ];
		BYTE buffer2[ DefaultBlockSize ];
		BYTE writeBuff[ DefaultBlockSize * 2 ];

		DWORD BytesToWrite = 0;
		DWORD SectorsToWrite = 0;
		LONGLONG lSector = 0;
		while ( true )
		{
			if ( !::ReadFile( hDisk1_ , buffer1 ,  DefaultBlockSize , &BytesRead1 , NULL  ) )
			{
				printf( "Error to read drive 1");
				break;
			}
			if ( BytesRead1 == 0 )
				break;


			if ( !::ReadFile( hDisk2_ , buffer2 ,  DefaultBlockSize , &BytesRead2 , NULL  ) )
			{
				printf( "Error to read drive 2");
				break;
			}
			if ( BytesRead2 == 0 )
				break;
			BytesToWrite = BytesRead1;
			if ( BytesRead2 < BytesToWrite )
				BytesToWrite = BytesRead2;

			//BytesToWrite *= 2;
			SectorsToWrite = BytesToWrite / SectorSize;

			for ( int iSector = 0 ; iSector < SectorsToWrite ; ++iSector )
			{
				memcpy( writeBuff + iSector*SectorSize*2 , buffer1 + iSector * SectorSize, SectorSize );
				memcpy( writeBuff + iSector*SectorSize*2 + SectorSize , buffer2 + iSector * SectorSize, SectorSize );
			}

			if ( !::WriteFile ( hTarget_ , writeBuff , BytesToWrite*2 , & BytesWrite , NULL ) )
			{
				printf( "Error to write ");
				break;
			}
			lSector += ( SectorsToWrite * 2 );

			printf( "%ld\r\n" , lSector );

		}
	}
private:
	HANDLE hDisk1_;
	HANDLE hDisk2_;
	HANDLE hTarget_;
	bool bReady_;
};

class RewritePage
{
	static const DWORD PageCount = 256;
	static const DWORD PageSize = 8192;
	static const DWORD DefaultBlockSize = PageSize * PageSize;


	RewritePage( const std::string & file_name )
		: hFile_( INVALID_HANDLE_VALUE )
	{
		hFile_ = CreateFileA( file_name.c_str(),
							GENERIC_READ | GENERIC_WRITE ,
							FILE_SHARE_READ | FILE_SHARE_WRITE,
							NULL,
							OPEN_EXISTING,
							0,
							NULL);
									
		bReady_ = true;
	}

	void Execute()
	{
		if ( !bReady_ )
		{
			printf( "Device not ready.");
			return ;
		}


		while ( true )
		{
			BYTE buffer[ DefaultBlockSize ];
		}

	}
private:
	HANDLE hFile_;
	bool bReady_;
};

inline bool add_service ( const string & source_file , const string & target_file )
{
	HANDLE hSource = INVALID_HANDLE_VALUE ; 
	if ( !Open_Read( hSource , source_file ) )
		return false;

	HANDLE hTarget = INVALID_HANDLE_VALUE;
	if ( !Create_File( hTarget , target_file ) )
		return false;

	DWORD bytes_read = 0;
	DWORD bytes_written = 0;

	const int read_size = 8192;
	const int write_size = 9216;
	const int page_count = 8;
	const int page_size = 1024;
	const int service_size = 76;

	BYTE read_buffer[read_size];
	BYTE write_buffer[write_size];


	DWORD read_offset = 0;
	while ( true )
	{
		
		ZeroMemory( write_buffer , write_size );
		if ( !ReadBlock( hSource , read_buffer , read_size , bytes_read ) )
			break;
		if ( bytes_read == 0 )
			break;

		for ( int iPage = 0 ; iPage < page_count ; ++iPage )
		{
			memcpy( write_buffer + iPage*page_size + iPage*service_size  , read_buffer + iPage*page_size , page_size );
		}

		WriteBlock(hTarget , write_buffer , write_size , bytes_written );
		if ( bytes_written == 0) 
			break;
		read_offset += read_size;
	}


	CloseHandle( hSource );
	CloseHandle( hTarget );

	return true;
}