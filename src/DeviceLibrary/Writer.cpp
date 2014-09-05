#include "StdAfx.h"
#include "Writer.h"
#include "Buffer.h"
#include "Queue.h"
#include "Concurrent.h"
#include "Error.h"
#include "Declaration.h"
#include "Log.h"
#include "Definitions.h"
#include "Utilities.h"
#include "AbstractFactory.h"
#include <sstream>
#include <iomanip>



CImageFileSize * CImageFileSize::m_pInstance = NULL;
CEnCaseFileSize * CEnCaseFileSize::m_pInstance = NULL;
CCompressionLevel * CCompressionLevel::m_pInstance = NULL;
CHashingMap * CHashingMap::m_pInstance = NULL;
/************************************************************************/
/*                          CWriter                                     */
/************************************************************************/
IWriter::IWriter()
{

}
IWriter::~IWriter()
{

}

/************************************************************************/
/*                          CWriter                                     */
/************************************************************************/
CWriter::CWriter(const DevicePtr &_pDevice)
	:m_pDevice(_pDevice)
{
	m_hWriteDevice = INVALID_HANDLE_VALUE;
	m_bOpen = FALSE;
	m_iBytesWrite = 0;
	m_iPosition.QuadPart = 0;
}
CWriter::~CWriter()
{
	Close();
	m_iBytesWrite = 0;
	m_dwErrorCode = 0;
	m_iPosition.QuadPart = 0;
	m_bOpen = FALSE;
	m_lWritePos = 0;
}
BOOL CWriter::Open()
{
	return m_bOpen = m_pDevice->OpenWrite(m_hWriteDevice);
}
void CWriter::Close()
{
	if (m_hWriteDevice != INVALID_HANDLE_VALUE)
	{
		if (CloseHandle(m_hWriteDevice))
			m_hWriteDevice = INVALID_HANDLE_VALUE;
	}
}
BOOL CWriter::isOpen()
{
	return m_bOpen;
}
DWORD CWriter::Write(BYTE * pBuffer, DWORD WriteSize, LONGLONG _Position)
{
	m_iBytesWrite = 0;
	if (pBuffer == NULL || m_hWriteDevice == INVALID_HANDLE_VALUE)
		return m_iBytesWrite;

	m_iPosition.QuadPart = _Position;
	SetFilePointerEx(m_hWriteDevice,m_iPosition,NULL,FILE_BEGIN);
	if (!WriteFile(m_hWriteDevice,pBuffer,WriteSize,&m_iBytesWrite,NULL))
	{
		m_dwErrorCode = ::GetLastError();
		m_iBytesWrite = 0;
	}
	return m_iBytesWrite;
}
DWORD CWriter::Write(CBuffer * pCBuffer)
{
	m_iBytesWrite = 0;
	//if (!this->isOpen())
	//	this->Open();
	if (pCBuffer == NULL || m_hWriteDevice == INVALID_HANDLE_VALUE)
		return m_iBytesWrite;

	BYTE *pWriteBuffer = pCBuffer->GetBuffer();
	if (pWriteBuffer == NULL)
		return m_iBytesWrite;

	m_iPosition.QuadPart = pCBuffer->GetPosition();
	SetFilePointerEx(m_hWriteDevice,m_iPosition,NULL,FILE_BEGIN);
	if (!WriteFile(m_hWriteDevice,pWriteBuffer,pCBuffer->GetSize(),&m_iBytesWrite,NULL))
	{
		m_dwErrorCode = ::GetLastError();
		m_iBytesWrite = 0;
	}
	return m_iBytesWrite;
}
DWORD CWriter::GetErrorCode() const
{
	return m_dwErrorCode;
}


/************************************************************************/
/*                          CPhysicalWriter                             */
/************************************************************************/
CPhysicalWriter::CPhysicalWriter()
	: m_pWriter(NULL)
	, m_lStartSector(0)
	, m_lSectorsCount(0)
	, m_lWritePos(0)
{
	m_pDevice = DevicePtr();
}
CPhysicalWriter::CPhysicalWriter(IWriter * _pWriter, const DevicePtr & _pDevice)
	: m_pWriter(_pWriter)
	, m_pDevice(_pDevice)
	, m_lStartSector(0)
	, m_lSectorsCount(0)
	, m_lWritePos(0)
{
}
CPhysicalWriter::~CPhysicalWriter()
{
	delete m_pWriter;
}
void CPhysicalWriter::SetWriter(IWriter * _pWriter)
{
	m_pWriter = _pWriter;
}
void CPhysicalWriter::SetDevice(const DevicePtr & _pDevice)
{
	m_pDevice = _pDevice;
}

void CPhysicalWriter::Execute(CBuffer * _pBuffer)
{
	if (m_pWriter->Write(_pBuffer->GetBuffer(),_pBuffer->GetSize(),m_lWritePos) == 0)
	{
		m_dwResult = ::GetLastError();
	}
	m_lWritePos += _pBuffer->GetSize();
}
BOOL CPhysicalWriter::isReady()
{
	m_sError = "no error";
	if (m_pDevice == NULL)
	{
		m_sError = Declaration::ErrorNoSelectedDevice();
		return FALSE;
	}
	if (m_pWriter == NULL)
	{
		m_sError = "Writer parameter is incorrect";
		return FALSE;
	}
	if (m_lStartSector >= m_pDevice->GetSectorCount())
	{
		m_sError = Declaration::ErrorStartSectorMore();
		return FALSE;
	}
	LONGLONG lValidateRange = m_lStartSector + m_lSectorsCount;
	if (m_pDevice->GetSectorCount() < lValidateRange)
	{
		m_sError = Declaration::ErrorOutOffRange();
		return FALSE;
	}
	if (m_pDevice->GetBytesPerSector() == 0)
	{
		m_sError = Declaration::ErrorBPSNull();
		return FALSE;
	}
	if (!m_pWriter->isOpen())
	{
		m_sError = Declaration::ErrorOpenDevice();
		return FALSE;
	}
	return TRUE;
}
void CPhysicalWriter::toFinish()
{	
	/*		*/
}
IAbstractTask * CPhysicalWriter::GetComposite()
{
	return NULL;
}
void CPhysicalWriter::SetStartSector(LONGLONG _StartSector)
{
	m_lStartSector = _StartSector;
	m_lWritePos = m_lStartSector*m_pDevice->GetBytesPerSector();
}
void CPhysicalWriter::SetSectorsCount(LONGLONG _SectorsCount)
{
	m_lSectorsCount = _SectorsCount;
}
DWORD CPhysicalWriter::StartThread()
{
	// if Parameters is incorrect then exit
	if (!isReady())
	{
		return ErrorNumber;
	}
	//while (true)
	//{
	//	if (m_pBuffer != NULL)
	//	{
	//		if (m_pWriter->Write(m_pBuffer) == 0)
	//		{
	//			m_pUpdater->ShowError(::GetLastError());
	//			break;
	//		}
	//	}
	//	else
	//	{
	//		// Exit
	//		break;
	//	}
	//}

	return 0;
}

/*

/************************************************************************/
/*                          CFileWriter								    */
/************************************************************************/
CFileWriter::CFileWriter()
	: m_iBytesWrite(0)
	, m_Counter(1)
	, m_sDirectory(L"")
	, m_sFileName(L"")
	, m_sFullPath(L"")
	, m_MaxFileSize(0)
	, m_FileSize(0)
	, m_WritePos(0)
	, m_pWriter(NULL)
{
	m_FileDevice = DevicePtr();
}
CFileWriter::~CFileWriter(void)
{
	if (m_pWriter != NULL)
	{
		delete m_pWriter;
		m_pWriter = NULL;
	}
}
BOOL CFileWriter::Init()
{
	Utility::PreperePath(m_sDirectory);
	m_sFullPath = Utility::MakeFullPath(m_sFileName,m_sDirectory);
	if (m_pWriter == NULL)
	{
		if (!CreateWriter())
			return FALSE;
	}
	return TRUE;
}
void CFileWriter::Execute(CBuffer * _pBuffer)
{
	m_iBytesWrite = _pBuffer->GetSize();
	if (m_MaxFileSize != 0)
	{
		m_FileSize += m_iBytesWrite;
		if (m_FileSize > m_MaxFileSize)
		{
			if (m_pWriter != NULL)
			{
				delete m_pWriter;
				m_pWriter = NULL;
			}
			if (!CreateWriter())
			{
				m_dwResult = ErrorNumber;
				return;
			}
			m_FileSize = m_iBytesWrite;
			m_WritePos = 0;
		}
	}

	if (m_pWriter->Write(_pBuffer->GetBuffer(),m_iBytesWrite,m_WritePos) == 0)
	{
		m_dwResult = ::GetLastError();
	}
	m_WritePos += m_iBytesWrite;
}
BOOL CFileWriter::isReady()
{
	if ( !Init())
		return FALSE;

	return TRUE;
}
void CFileWriter::toFinish()
{	
	/*		*/
}
IAbstractTask * CFileWriter::GetComposite()
{
	return NULL;
}
void CFileWriter::SetFileName(const wstring & _fileName)
{
	m_sFileName = _fileName;
}
void CFileWriter::SetDirectory(const wstring &_Directory)
{
	m_sDirectory = _Directory;
}
void CFileWriter::SetMaxFileSize(LONGLONG _MaxFileSize)
{
	m_MaxFileSize = _MaxFileSize;
}

DWORD CFileWriter::StartThread()
{
	// if Parameters is incorrect then exit
	if (!isReady())
	{
		return ErrorNumber;
	}
	return 0;
}


BOOL CFileWriter::CreateWriter()
{
	CFileDevice * pFileDevice = new CFileDevice();
	wchar_t pStrCounter[10];
	memset(pStrCounter,0,10*sizeof(wchar_t));
	swprintf(pStrCounter,10,L"%.3d",m_Counter);
	wstring sFilePath = m_sFullPath + L'.' + pStrCounter;
	DevicePtr ptrDevice(pFileDevice);
	ptrDevice->SetPath((wchar_t*)sFilePath.c_str());
	m_pWriter = new CWriter(ptrDevice);
	if ( ! m_pWriter->Open() )
	{
		m_iBytesWrite = 0;
		m_sError = Declaration::ErrorOpenFileShow(Utility::ToString(sFilePath));
		return FALSE;
	}
	// Writing to Log
	CLog * pLog = CLog::GetInstance();
	string sFile ( WStringToString( sFilePath ) );
	string sLogMessage(Declaration::WrittingToFile(sFile));
	pLog->WriteLog(sLogMessage);

	++m_Counter;
	return TRUE;
}

CFileFactoryWriter::CFileFactoryWriter()
{

}
CFileFactoryWriter::~CFileFactoryWriter()
{

}
CFileWriter * CFileFactoryWriter::CreateFileWriter()
{
	return new CFileWriter();
}

/************************************************************************/
/*                          CRawCreater								    */
/************************************************************************/
CRawCreater::CRawCreater(void)
	: m_HeaderOffset ( 0 )
	, m_sHeader ( "" )
	, m_sFooter ( "" )
	, m_FooterOffset ( 0 )
	, m_MinFileSize ( 0 )
	, m_MaxFileSize ( 0 )
	, m_sExtension ( L"" )
	, m_sFolderPath ( L"" )
	//, HeaderSignature_ ( NULL )
	//, FooterSignature_ ( NULL )
	, m_Writer ( NULL )
	, m_Counter ( 0 )
	, m_RawState ( NotFindHeader )
	, m_Position ( 0 )
	, footer_remain_ ( 0 )
{

	//m_WriteFileSize = 0;
}
CRawCreater::~CRawCreater(void)
{
	//ClearHeaderData();
	//ClearFooterData();
	ClearWriter();
}
void CRawCreater::SetHeaderOffset(const DWORD _HeaderOffset)
{
	m_HeaderOffset = _HeaderOffset;
}
void CRawCreater::SetHeader(const string & _Header)
{
	m_sHeader = ToHexString(_Header);
}
void CRawCreater::SetFooter(const string & _Footer)
{
	m_sFooter = ToHexString(_Footer);
}
void CRawCreater::SetFooterOffset(const DWORD _FooterOffset)
{
	m_FooterOffset = _FooterOffset;
}
void CRawCreater::SetMinFileSize(const DWORD _MinFileSize)
{
	m_MinFileSize = _MinFileSize;
}
void CRawCreater::SetMaxFileSize(const LONGLONG _iMaxFileSize)
{
	m_MaxFileSize = _iMaxFileSize;
}
void CRawCreater::SetExtension(const wstring &_Extension)
{
	m_sExtension = _Extension;
}
void CRawCreater::SetFolderPath(const wstring &_FolderPath)
{
	m_sFolderPath = _FolderPath;
}

IAbstractTask * CRawCreater::GetComposite()
{
	return NULL;
}

//const int JarHeaderSize = 6;
//const int JarFileSizeOffset = 8;
//const int JarHeaderOffset = 14;
//const BYTE JarHeader[JarHeaderSize] = { 0x1A, 0x4A, 0x61, 0x72, 0x1B, 0x00 };
//const int JarStructureSize = 64;
void CRawCreater::Execute(CBuffer * _pBuffer)
{
	DWORD iSector = 0;
	DWORD iHeaderSector = 0;
	
	//const BYTE* buffCmp = (const BYTE*) m_sFooter.data();

	while (iSector < _pBuffer->GetSize())
	{
		// Find Header
		BYTE * pDataBuffer = _pBuffer->GetBuffer();

		if ( m_RawState == WriteFooter )
		{
			DWORD write_size = footer_remain_;
			if ( write_size > _pBuffer->GetSize() )
				write_size = _pBuffer->GetSize();
			else
				m_RawState = NotFindHeader;

			if ( m_Writer->Write(pDataBuffer , write_size , m_Position ) == 0)
			{
				m_dwResult = ::GetLastError();
				return;
			}

			if (m_RawState == WriteFooter)
			{
				footer_remain_ -= _pBuffer->GetSize();
				return;
			}
			iSector = footer_remain_ / SectorSize;
			footer_remain_ = 0;
		}
		if ( memcmp(pDataBuffer + iSector + m_HeaderOffset, m_sHeader.data(), m_sHeader.size() ) == 0)
		{
			if (m_RawState == FindHeader )
			{
				if (iSector > 0)
				{
					if ( m_Position > 0 )
						if (m_Writer->Write(pDataBuffer + iHeaderSector,iSector - iHeaderSector,m_Position) == 0 )
						{
							//m_dwResult = 0;
							m_dwResult = ::GetLastError();
							return;
						}
				}
			}
			//else
			//if ( m_RawState == NotFindHeader )
//			{
			if ( ! CreateWriter(m_Counter))
				return;

			iHeaderSector = iSector;
			iSector += SectorSize;
			++m_Counter;
			this->Notify();
			m_RawState = FindHeader;
			continue;
//			}
		}
		if (m_RawState == FindHeader)
		{
			if (m_sFooter.size() > 0)
				if (iSector + m_sFooter.size() < _pBuffer->GetSize())
				{
					LONGLONG lFooterPos = 0;
					for (DWORD iByte = 0; iByte < SectorSize - m_sFooter.size(); ++iByte)
					{
						lFooterPos = (LONGLONG)(m_Position + iSector + iByte);
						if (memcmp( pDataBuffer + iSector + iByte, m_sFooter.data() , m_sFooter.size() ) == 0)
						{
							if (lFooterPos > m_MinFileSize)
							{
								DWORD write_size = iSector - iHeaderSector + iByte + m_FooterOffset + m_sFooter.size();
								//bool bRemaining = false;
								if ( write_size > _pBuffer->GetSize() )
								{
									footer_remain_ = write_size - _pBuffer->GetSize() ;
									write_size = _pBuffer->GetSize() - iHeaderSector;
									m_RawState = WriteFooter;
								}
							
								if ( m_Writer->Write(pDataBuffer + iHeaderSector , write_size, m_Position ) == 0)
								{
									m_dwResult = ::GetLastError();
									return;
								}
								if ( m_RawState == WriteFooter )
									return;
								m_Position = 0;
								if ( ! CreateWriter(m_Counter))
									return;
								++m_Counter;
								m_RawState = NotFindHeader;
								break;
							}
						}
					}
				}
		}


		iSector += SectorSize;
	}
	if ( m_RawState == FindHeader )
	{
		/*if ( _pBuffer->GetSize() - iHeaderSector ) < 0 )*/
		BYTE * pDataBuffer = _pBuffer->GetBuffer();
		if ( m_Writer->Write(pDataBuffer + iHeaderSector ,_pBuffer->GetSize() - iHeaderSector, m_Position) == 0 )
		{
			m_dwResult = ::GetLastError();
			return;
		}
		m_Position += _pBuffer->GetSize() - iHeaderSector;
		if (m_Position > m_MaxFileSize)
		{
			ClearWriter();
			m_Position = 0;
			m_RawState = NotFindHeader;
		}
	}

}
/*				Jar archive RAW
while (iSector < _pBuffer->GetSize())
{
// Find Header
if (memcmp(pDataBuffer + iSector + JarHeaderOffset, JarHeader,JarHeaderSize) == 0)
{
DWORD *pWriteFileSize = (DWORD *) &pDataBuffer[iSector + JarFileSizeOffset];
m_WriteFileSize = *pWriteFileSize + JarStructureSize;
m_CurrentWrited = 0;

if (m_RawState == FindHeader )
{
if (iSector > 0)
{
if (m_Writer->Write(pDataBuffer + iSector - SectorSize,iSector,m_Position) == 0 )
{
m_dwResult = ::GetLastError();
return;
}
}
}
if ( ! CreateWriter(m_Counter))
return;

iHeaderSector = iSector;
iSector += SectorSize;
++m_Counter;
this->Notify();
m_RawState = FindHeader;
continue;
}

iSector += SectorSize;
}
if ( m_RawState == FindHeader )
{
DWORD WriteSize = _pBuffer->GetSize() - iHeaderSector;
if (( WriteSize + m_CurrentWrited ) > m_WriteFileSize )
WriteSize = m_WriteFileSize - m_CurrentWrited;

m_CurrentWrited += WriteSize;

if ( m_Writer->Write(pDataBuffer + iHeaderSector ,WriteSize, m_Position) == 0 )
{
m_dwResult = ::GetLastError();
return;
}
m_Position += _pBuffer->GetSize() - iHeaderSector;
if (m_CurrentWrited >= m_WriteFileSize)
{
ClearWriter();
m_Position = 0;
m_RawState = NotFindHeader;
}
}
*/
BOOL CRawCreater::isReady()
{
	m_sError = "no Error. RawCreater.";
	if ( m_sHeader.empty() /*|| m_sFooter.empty()*/ )
	{
		m_sError = "Ошибка. Не задана сигнатура.";
		return FALSE;
	}
	if (m_HeaderOffset >= DefaultBuffer )
	{
		std::stringstream sStream("");
		sStream << (unsigned long) DefaultBuffer;
		m_sError = "Ошибка. Смещение заголока больше чем допустимый ";
		m_sError += sStream.str();
		return FALSE;
	}
	if (m_MinFileSize >= m_MaxFileSize)
	{
		m_sError = "Ошибка. Минимальный размер файла больше чем максимальный.";
		return FALSE;
	}
#ifdef _DEBUG
	if (HeaderSignature_ == NULL || FooterSignature_ == NULL)
	{
		m_sError = "Ошибка. Не заданы данные ( HeaderSignature или FooterSignature ).";
		return FALSE;
	}
#endif
	return TRUE;
}
void CRawCreater::toFinish()
{

}

DWORD CRawCreater::StartThread()
{
	if (!isReady())
	{
		return ErrorNumber;
	}
	return 0;
}

void CRawCreater::Init()
{
	m_sFolderPath = Utility::DirectoryPath(m_sFolderPath);
	Utility::PreperePath(m_sFolderPath);
}
DWORD CRawCreater::GetCount() const
{
	return m_Counter;
}
string CRawCreater::ToHexString(const string & SingString)
{
	char *hexValue = new char[10];
	ZeroMemory(hexValue,10*sizeof(char));
	string hexString;
	for (size_t iSize = 0; iSize < SingString.size(); iSize += 2)
	{

		/*sprintf_s(&hexValue,1,"%x",SingString.substr(iSize,2).c_str() );*/
		sscanf_s(SingString.substr(iSize,2).c_str(),"%x", hexValue);
		hexString.push_back(*hexValue);
	}
	//hexString = "0000";
	delete hexValue;
	hexValue = NULL;
	return hexString;
}
BOOL CRawCreater::CreateWriter(const DWORD _FileNumber)
{
	ClearWriter();
	CFileFactory FileFactory;
	CWriterFactory WriterFactory;
	DevicePtr FileDevice(FileFactory.CreateDevice());
	WCHAR NumBuffer[10];
	ZeroMemory( NumBuffer , sizeof(WCHAR) * 10 );
	swprintf_s(NumBuffer , 10 , L"%.8d.", _FileNumber);
	wstring sFileName(NumBuffer);
	sFileName.append(m_sExtension);
	wstring sWriteFile(Utility::MakeFullPath(sFileName,m_sFolderPath));
	FileDevice->SetPath( (wchar_t *) sWriteFile.c_str());
	m_Writer = WriterFactory.CreateWriter(FileDevice);
	if ( !m_Writer->Open() )
	{
		m_dwResult = ErrorNumber;
		m_sError = Declaration::ErrorOpenFileShow(Utility::ToString(sWriteFile));
		return FALSE;
	}
	m_Position = 0;
	return TRUE;
}

void CRawCreater::ClearWriter()
{
	if (m_Writer != NULL)
	{
		delete m_Writer;
		m_Writer = NULL;
	}
}
