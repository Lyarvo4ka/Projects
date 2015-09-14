#include "StdAfx.h"
#include "GatherByJPG.h"

#include "Settings.h"

CDataBuffer::CDataBuffer()
	:m_pBufferData(NULL)
{

}
CDataBuffer::~CDataBuffer()
{

}
void CDataBuffer::setData(BYTE *_pBufferData)
{
	m_pBufferData = _pBufferData;
}
BYTE * CDataBuffer::GetData() const
{
	return m_pBufferData;
}
void CDataBuffer::setSize(DWORD _dwSize)
{
	m_dwBufferSize = _dwSize;
}
DWORD CDataBuffer::GetSize() const
{
	return m_dwBufferSize;
}


CDriveReader::CDriveReader(void)
	:m_lPosition(0)
{
	m_hReadDevice = INVALID_HANDLE_VALUE;
	m_pBufferData = NULL;
	m_dwBufferSize = 0;
}
CDriveReader::CDriveReader(CDiskDrive & _diskDrive)
	:m_lPosition(0),m_DiskDrive(_diskDrive)
{
	m_hReadDevice = INVALID_HANDLE_VALUE;
	m_pBufferData = NULL;
	m_dwBufferSize = 0;
}
CDriveReader::CDriveReader(CDiskDrive & _diskDrive, LONGLONG _lPosition, DWORD _dwReadSize)
	:m_lPosition(_lPosition),m_DiskDrive(_diskDrive)
{
	m_hReadDevice = INVALID_HANDLE_VALUE;
	m_pBufferData = NULL;
	m_dwBufferSize = _dwReadSize;
}
CDriveReader::~CDriveReader(void)
{
	ClearBuffer();
}
void CDriveReader::setDiskDrive(CDiskDrive & _diskDrive)
{
	m_DiskDrive = _diskDrive;
}

void CDriveReader::ClearBuffer()
{
	if (m_pBufferData != NULL)
	{
		delete m_pBufferData;
		m_pBufferData = NULL;
	}	
}
void CDriveReader::setReadPosition(LONGLONG _lPosition)
{
	m_lPosition = _lPosition;
}
BOOL CDriveReader::OpenDrive()
{
	m_hReadDevice = CreateFile(m_DiskDrive.getDiskPath(),
					   GENERIC_READ,
					   FILE_SHARE_READ,
					   NULL,
					   OPEN_EXISTING,
					   0 ,
					   NULL);
	if (m_hReadDevice == INVALID_HANDLE_VALUE)
	{
		DWORD dwError = GetLastError();
		TRACE("ERROR OPEN PHYSICAL DRIVE (Error #%d)",dwError);
		return FALSE;
	}
	return TRUE;
}
void CDriveReader::CloseDrive()
{
	CloseHandle(m_hReadDevice);
}
BOOL CDriveReader::Execute()
{
	if ( (m_dwBufferSize == 0) || ( OpenDrive() == FALSE ) )
		return FALSE;
	m_pBufferData = new BYTE[m_dwBufferSize];
	LARGE_INTEGER liPosition;
	liPosition.QuadPart = m_lPosition;
	liPosition.QuadPart *= m_DiskDrive.getBytesPerSector();
	::SetFilePointerEx(m_hReadDevice,liPosition,NULL,FILE_BEGIN);
	DWORD dwReadBytes = 0;
	if ( !ReadFile(m_hReadDevice , m_pBufferData, m_dwBufferSize, &dwReadBytes, NULL) )
	{
		DWORD dwError = GetLastError();
		TRACE("ERROR READ DRIVE (Error #%d)",dwError);
	}
	CloseDrive();
	return TRUE;
}

///////////////**********[ CFileCreater ]**********///////////////
CFileCreater::CFileCreater()
	:m_strDirectoryPath(_T("")),m_iFileNumber(0),m_strAddFileName(_T("")),m_strFilePath(_T(""))
{
	setStep(0);
	m_pBufferData = NULL;
	m_dwBufferSize = 0;
	m_pAddData = NULL;
	m_dwAddSize = 0;
}
CFileCreater::CFileCreater(CString _strDirectoryPath)
	:m_iFileNumber(0),m_strAddFileName(_T("")),m_strFilePath(_T(""))
{
	setDirectoryPath(_strDirectoryPath);
	setStep(0);
	m_pBufferData = NULL;
	m_dwBufferSize = 0;
	m_pAddData = NULL;
	m_dwAddSize = 0;
}
CFileCreater::~CFileCreater()
{
	//delete m_pAddData;
}
void CFileCreater::setDirectoryPath(CString _strDirectoryPath)
{
	m_strDirectoryPath = _strDirectoryPath;
}

void CFileCreater::setStep(UINT _iStep)
{
	m_iStep = _iStep;
}

void CFileCreater::setFileNumber(UINT _iFileNumber)
{
	m_iFileNumber = _iFileNumber;
}

void CFileCreater::AddWriteData(BYTE * _pBuffer, DWORD _dwSize)
{
	m_pAddData = _pBuffer;
	m_dwAddSize = _dwSize;
}
void CFileCreater::AddFileName(CString _strAddFileName)
{
	m_strAddFileName = _strAddFileName;
}
	CString CFileCreater::GetFilePath() const
	{
		return m_strFilePath;
	}
BOOL CFileCreater::Execute()
{
	if (m_pBufferData == NULL )
	{
		TRACE("CFileCreater: (buffer == NULL)");
		return FALSE;
	}
	if ( m_dwBufferSize == 0)
	{
		TRACE("CFileCreater: (File size to write == 0)");
		return FALSE;
	}

	CString strFileNumber = _T("");
	strFileNumber.Format(_T("%.5d"),m_iFileNumber);
	m_strFilePath = _T("");
	m_strFilePath.Format(_T("%s\\%s%s.jpg"),m_strDirectoryPath,strFileNumber,m_strAddFileName);


	HANDLE hWriteFile = INVALID_HANDLE_VALUE;
	hWriteFile = CreateFile(m_strFilePath,
					   GENERIC_WRITE,
					   FILE_SHARE_WRITE,
					   NULL,
					   CREATE_ALWAYS,
					   0 ,
					   NULL);

	if (hWriteFile == INVALID_HANDLE_VALUE)
	{
		DWORD dwError = GetLastError();
		TRACE("CFileCreater: Error Create File (Error #%d)\r\n",dwError);
		return FALSE;
	}

	DWORD dwWriteSize = 0;
	dwWriteSize += m_dwBufferSize;
	if (m_dwAddSize != 0)
		dwWriteSize += m_dwAddSize;
	BYTE *pBuffer = new BYTE[dwWriteSize];
	memcpy(pBuffer,m_pBufferData,m_dwBufferSize);
	if (m_pAddData != NULL)
		memcpy(pBuffer + m_dwBufferSize,m_pAddData, m_dwAddSize);

	DWORD dwBytesWrite = 0;
	if ( !WriteFile(hWriteFile,pBuffer,dwWriteSize,&dwBytesWrite,NULL) )
	{
		DWORD dwError = GetLastError();
		TRACE("CFileCreater: Error Write File (Error #%d)\r\n",dwError);
		return FALSE;
	}
	CloseHandle(hWriteFile);
	delete pBuffer;
	return TRUE;
}

CDataBlock::CDataBlock()
{
	m_enPosUpDown = PosUP;
	m_iDiskNumber = 0;
}
CDataBlock::~CDataBlock()
{

}
void CDataBlock::setDiskNumber(BYTE _iDiskNumber)
{
	m_iDiskNumber = _iDiskNumber;
}	
void CDataBlock::setPosUpDown(PosUpDown _posUpDown)
{
	m_enPosUpDown = _posUpDown;
}
void CDataBlock::setSize(DWORD _dwSize)
{
	m_dwBlockSize = _dwSize;
}
BYTE CDataBlock::getDiskNumber() const
{
	return m_iDiskNumber;
}
DWORD CDataBlock::getBlockSize() const
{
	return m_dwBlockSize;
}
PosUpDown CDataBlock::getPosUpDown() const
{
	return m_enPosUpDown;
}


CMapBlocks::CMapBlocks()
{
	m_pFileCreater = new CFileCreater();
	m_pDriveReader = new CDriveReader();
	m_iNextDisk = -1;
}
CMapBlocks::~CMapBlocks()
{
	ClearMap();
	if (m_pFileCreater != NULL)
	{
		delete m_pFileCreater;
		m_pFileCreater = NULL;
	}
	if (m_pDriveReader != NULL)
	{
		delete m_pDriveReader;
		m_pDriveReader = NULL;
	}
}
void CMapBlocks::ClearMap()
{
	if (!m_mapBlocks.IsEmpty())
	{
		POSITION mapPos;
		UINT iFileNumber = 0;
		CDataBlock *pRemoveBuffer = NULL;
		for (;mapPos = m_mapBlocks.GetStartPosition(); mapPos != NULL) 
		{
			m_mapBlocks.GetNextAssoc(mapPos,iFileNumber,(CDataBlock*&)pRemoveBuffer);
			if (pRemoveBuffer != NULL)
			{
				delete pRemoveBuffer;
				pRemoveBuffer = NULL;
			}
			m_mapBlocks.RemoveKey(iFileNumber);
		}
		
	}
}
void CMapBlocks::setBaseData(BYTE *_pBuffer, DWORD _dwSize)
{
	m_pFileCreater->setData(_pBuffer);
	m_pFileCreater->setSize(_dwSize);
}
void CMapBlocks::setVecDrives(vector<CDiskDrive> _vecDrives)
{
	m_vecDrives = _vecDrives;
}
void CMapBlocks::setPosition(LONGLONG _lPosition)
{
	m_lPosition = _lPosition;
}
void CMapBlocks::setBlockSize(DWORD _dwBlockSize)
{
	m_dwBlockSize = _dwBlockSize;
}
void CMapBlocks::setNextDisk(int _iNextDisk)
{
	m_iNextDisk = _iNextDisk;
}

void CMapBlocks::CreateFiles(UINT & _iCurrentFile, DWORD _dwBlockSize, int _iDiskNumber )
{
	CDataBlock *pDataBlock = NULL;
	if (_iDiskNumber == -1)
	{
		for (size_t iDisk = 0; iDisk < m_vecDrives.size(); ++iDisk)
		{
			m_pDriveReader->setDiskDrive(m_vecDrives.at(iDisk) );
			m_pDriveReader->setSize(_dwBlockSize);
			m_pDriveReader->setReadPosition(m_lPosition);
			m_pDriveReader->Execute();
			pDataBlock = new CDataBlock();
			pDataBlock->setDiskNumber(m_vecDrives.at(iDisk).getDiskNumber());
			pDataBlock->setSize(_dwBlockSize);
			pDataBlock->setPosUpDown(PosDown);
			m_mapBlocks.SetAt(_iCurrentFile,pDataBlock);
			m_pFileCreater->AddWriteData(m_pDriveReader->GetData(),m_pDriveReader->GetSize());
			m_pFileCreater->setFileNumber(_iCurrentFile);
			m_pFileCreater->Execute();
			m_pDriveReader->ClearBuffer();

			pDataBlock = new CDataBlock();
			DWORD dwSectorsCount = _dwBlockSize / m_vecDrives.at(iDisk).getBytesPerSector();
			LONGLONG lBackPos = m_lPosition;
			lBackPos -= dwSectorsCount;
			m_pDriveReader->setReadPosition(lBackPos);
			m_pDriveReader->Execute();
			++_iCurrentFile;
			pDataBlock->setPosUpDown(PosUP);
			pDataBlock->setSize(_dwBlockSize);
			pDataBlock->setDiskNumber(m_vecDrives.at(iDisk).getDiskNumber());
			m_mapBlocks.SetAt(_iCurrentFile,pDataBlock);
			m_pFileCreater->AddWriteData(m_pDriveReader->GetData(),m_pDriveReader->GetSize());
			m_pFileCreater->setFileNumber(_iCurrentFile);
			m_pFileCreater->Execute();
			m_pDriveReader->ClearBuffer();
			++_iCurrentFile;
		}
	}
	else
	{
			m_pDriveReader->setDiskDrive(m_vecDrives.at(_iDiskNumber) );
			m_pDriveReader->setSize(_dwBlockSize);
			m_pDriveReader->setReadPosition(m_lPosition);
			m_pDriveReader->Execute();
			pDataBlock = new CDataBlock();
			pDataBlock->setDiskNumber(m_vecDrives.at(_iDiskNumber).getDiskNumber());
			pDataBlock->setSize(_dwBlockSize);
			pDataBlock->setPosUpDown(PosDown);
			m_mapBlocks.SetAt(_iCurrentFile,pDataBlock);
			m_pFileCreater->AddWriteData(m_pDriveReader->GetData(),m_pDriveReader->GetSize());
			m_pFileCreater->setFileNumber(_iCurrentFile);
			m_pFileCreater->Execute();
			m_pDriveReader->ClearBuffer();

			pDataBlock = new CDataBlock();
			DWORD dwSectorsCount = _dwBlockSize / m_vecDrives.at(_iDiskNumber).getBytesPerSector();
			LONGLONG lBackPos = m_lPosition;
			lBackPos -= dwSectorsCount;
			m_pDriveReader->setReadPosition(lBackPos);
			m_pDriveReader->Execute();
			++_iCurrentFile;
			pDataBlock->setPosUpDown(PosUP);
			pDataBlock->setSize(_dwBlockSize);
			pDataBlock->setDiskNumber(m_vecDrives.at(_iDiskNumber).getDiskNumber());
			m_mapBlocks.SetAt(_iCurrentFile,pDataBlock);
			m_pFileCreater->AddWriteData(m_pDriveReader->GetData(),m_pDriveReader->GetSize());
			m_pFileCreater->setFileNumber(_iCurrentFile);
			m_pFileCreater->Execute();
			m_pDriveReader->ClearBuffer();
			++_iCurrentFile;
			/*m_iNextDisk = -1;*/
		
	}
}
//#define MAX_SECTORS_COUNT 4096
//#define MAX_BLOCK_SIZE MAX_SECTORS_COUNT * 1024
void CMapBlocks::DeterminateBlock(int iMinSector)
{
	m_pFileCreater->setDirectoryPath(m_strDirctoryPath);
	UINT iCurrentFile = 1;
	auto setting = settings::CSettings::getSetting();
	DWORD max_sector_count = setting->getMaxBlock() / m_vecDrives.at(0).getBytesPerSector();//???
	if (m_dwBlockSize == 0)
	{
		//int iMinBlock
		int iStartBlock = 1;
		for (UINT iBlock = 1 ; iBlock <= max_sector_count; iBlock *= 2 )
		{
			if ( (iMinSector / iBlock) <= 1 )
			{
				iStartBlock = iBlock;
				break;
			}
		}
		DWORD blockSize = iStartBlock*m_vecDrives.at(0).getBytesPerSector();//???
		while ( blockSize <= setting->getMaxBlock() )
		{
			CreateFiles(iCurrentFile,blockSize,m_iNextDisk);
			blockSize *= 2;
		}
	}
	else
		CreateFiles(iCurrentFile,m_dwBlockSize);
}
UINT CMapBlocks::getCount() const
{
	return m_mapBlocks.GetCount();
}


void CMapBlocks::setDirectory(CString _strDirectory)
{
	m_strDirctoryPath = _strDirectory;
}
CDataBlock * CMapBlocks::getData(UINT _iNumber)
{
	CDataBlock *pDataBlock = NULL;
	if ( m_mapBlocks.Lookup(_iNumber,pDataBlock) )
		return pDataBlock;
	return NULL;
}

//////////////////////////////////////////
CDiskNumber::CDiskNumber()
{
	m_DiskDrive = new CDiskDrive();
}
CDiskNumber::~CDiskNumber()
{
	if (m_DiskDrive != NULL)
	{
		delete m_DiskDrive;
		m_DiskDrive = NULL;
	}
}
void CDiskNumber::setDiskDrive(CDiskDrive _DiskDrive)
{
	*m_DiskDrive = _DiskDrive;
}

IDiskOrder * CDiskNumber::GetComposite()
{
	return this;
}

CDiskDrive * CDiskNumber::GetDevice() 
{
	return m_DiskDrive;
}


//////////////////////////////////////////
CNewOrder::CNewOrder()
{

}

CNewOrder::~CNewOrder()
{

}

IDiskOrder * CNewOrder::GetComposite()
{
	return this;
}

CDiskDrive * CNewOrder::GetDevice() 
{
	return NULL;
}
/////////////////////////////////////////
CDiskOrder::CDiskOrder()
{

}

CDiskOrder::~CDiskOrder()
{
	this->Clear();
}

IDiskOrder * CDiskOrder::GetComposite()
{
	return this;
}

void CDiskOrder::Add(IDiskOrder *_IDiskOrder)
{
	m_arOrder.Add(_IDiskOrder);
}

void CDiskOrder::Delete()
{
	INT_PTR iCount = m_arOrder.GetCount();
	if (iCount > 0 )
	{
		IDiskOrder *pDiskOrder = NULL;
		--iCount;
		pDiskOrder = m_arOrder.GetAt(iCount);
		delete pDiskOrder;
		m_arOrder.RemoveAt(iCount);

		iCount = m_arOrder.GetCount();
		if (iCount > 0)
		{
			--iCount;
			pDiskOrder = m_arOrder.GetAt(iCount);
			if (pDiskOrder->GetDevice() == NULL)
			{
				delete pDiskOrder;
				m_arOrder.RemoveAt(iCount);
			}
		}
	}
}

CString CDiskOrder::GetDiskOrder() const
{
	return m_strDiskOrder;
}
void CDiskOrder::MakeDiskOrder(CString _strSplit)
{
	m_strDiskOrder = _T("");
	CString strText = _T("");
	CDiskDrive *pDiskDrive = NULL;
	vector<vector<UINT>> OrderMatrix;
	vector<UINT> OrderVector;
	if ( m_arOrder.GetCount() > 0 )
	{
		m_strDiskOrder = _T("\r\nDisk Order : \r\n");

		for (UINT iDisk = 0; iDisk < m_arOrder.GetCount(); ++iDisk)
		{
			pDiskDrive = m_arOrder.GetAt(iDisk)->GetDevice();
			if (pDiskDrive != NULL)
			{
				OrderVector.push_back(pDiskDrive->getDiskNumber());
			}
			else
			{
				OrderMatrix.push_back(OrderVector);
				OrderVector.clear();
			}
			if ( iDisk == m_arOrder.GetCount() - 1 )
				OrderMatrix.push_back(OrderVector);

		}
		//UINT iDiskCount = 2;
		//UINT iCounts = iDiskCount - OrderMatrix.size();
		//if (iCounts > 0)
		//for (size_t iNum = 0; iNum < iCounts; ++iNum)
		//		m_strDiskOrder += _T("Disk X + ");


		for (size_t iRow = 0; iRow < OrderMatrix.size(); ++iRow)
		{
			if (!OrderMatrix.at(iRow).empty())
				for (size_t iColum = 0; iColum < OrderMatrix.at(iRow).size(); ++iColum)
				{
					strText.Format(_T("D %d"),OrderMatrix.at(iRow).at(iColum));
					m_strDiskOrder += strText;
					if (iColum != OrderMatrix.at(iRow).size() - 1)
						m_strDiskOrder += _T(" + ");
				}

			//if (iRow != 0)
			//	m_strDiskOrder += _T("Disk P");
			m_strDiskOrder += csNewLine;
		}
		m_strDiskOrder += csNewLine;
	}
}

///////////////////////////////////////////////////////////////////////////////
// --------------- JPG Singleton -------------------
///////////////////////////////////////////////////////////////////////////////

CSingletonJPGs::CSingletonJPGs()
{
	m_Instance = NULL;
	m_iCount = 0;
	m_hMutex = CreateMutex(NULL,FALSE,_T("Mutex to access MAP"));
	m_strPath = _T("");
}
//~CSingletonJPGs()
//{}

void CSingletonJPGs::setDrives(vector<CDiskDrive> _vecDrives)
{
	m_vecDrives = _vecDrives;
}
void CSingletonJPGs::RemoveInstance()
{
	RemoveData();
	CloseHandle(m_hMutex);
	delete m_Instance;
	m_Instance = NULL;
}
void CSingletonJPGs::RemoveData()
{
	m_mapNumberPos.RemoveAll();
	m_iCount = 0;
	m_vecDrives.clear();
	m_strPath = _T("");

}
CSingletonJPGs * CSingletonJPGs::GetInstance()
{
	if (m_Instance == NULL)
		return m_Instance = new CSingletonJPGs();

	return m_Instance;
}

#define ONE_MBYTE 1*1024*1024
void CSingletonJPGs::Add(BYTE _iDiskNumber, LONGLONG _lLBAPosition)
{
	::WaitForSingleObject(m_hMutex,INFINITE);
	CDriveReader *pDriveReader = new CDriveReader(m_vecDrives.at(_iDiskNumber),_lLBAPosition,ONE_MBYTE);
	pDriveReader->Execute();

	CString file_name;
	file_name.Format( L"-%I64d-%d" , _lLBAPosition , m_vecDrives.at(_iDiskNumber).getDiskNumber() );

	CFileCreater *pFileCreater = new CFileCreater(m_strPath);
	pFileCreater->setData(pDriveReader->GetData());
	pFileCreater->setSize(ONE_MBYTE);
	pFileCreater->setFileNumber(m_iCount);
	pFileCreater->AddFileName( file_name );

	pFileCreater->Execute();
	delete pDriveReader;
	delete pFileCreater;
	NUMBER_POS vNumberPosition;
	vNumberPosition.m_iDiskNumber = _iDiskNumber;
	vNumberPosition.m_lLBAPosition = _lLBAPosition;
	m_mapNumberPos.SetAt(m_iCount,vNumberPosition);
	++m_iCount;
	::ReleaseMutex(m_hMutex);
}

BOOL CSingletonJPGs::GetNumberPos(UINT _iNumber,NUMBER_POS &_NumberPos)
{
	BOOL bResult = FALSE;
	::WaitForSingleObject(m_hMutex,INFINITE);
	UINT iCount = m_mapNumberPos.GetCount();
	if ( iCount == 0 )
		return FALSE;
	bResult = m_mapNumberPos.Lookup(_iNumber,_NumberPos) ;

	::ReleaseMutex(m_hMutex);

	return bResult;
}

void CSingletonJPGs::setDirectory(CString _strDirectory)
{
	m_strPath = _strDirectory;
}

	//CompositeSTEP *pComposite = new CompositeSTEP(iCurrentStep);

	//// 1 - Нарезка файлов по секторам ...
	//CuttingForSection *pShear = new CuttingForSection();
	//pShear->setNumberDisk(pDiskInfoData->m_iDiskNumber);
	//pShear->setPosition(pDiskInf oData->m_LBAPosition,pDiskInfoData->m_dwStartSector);
	//pShear->setDiskDrive( m_vecSelDrives.at(pDiskInfoData->m_iDiskNumber) );
	//pShear->setAllSectors(1000);
	//pShear->Execute();
	//delete pShear;
	//// Show Directory
	////system("explorer.exe c:\\JPG\\");

	//// T E X T 
	//CString strText = _T("");
	//strText.Format(_T("Введите последний Нормальный Файл на Ваш взгляд")); 

	//CCuttingSectorsDlg *pCuttingDialog = new CCuttingSectorsDlg(this,pComposite->getStep());
	//pCuttingDialog->setTextData(strText);
	//pCuttingDialog->setEditStyle(EDIT_STYLE::DIGIT_STYLE);
	//pCuttingDialog->setDefaultData(defaultString);
	//INT_PTR iDlgResult = pCuttingDialog->DoModal();

	//// Get Number of Sectors ( Shear Size)
	//strText = pCuttingDialog->getStringData();
	//DWORD dwSectorNumbers = _ttoi(strText);
	//delete pCuttingDialog;
	//pCuttingDialog = NULL;
	//if (iDlgResult == ID_ABORD )
	//{	
	//	delete pComposite;
	//	pResultCutting->m_ButtonResult = iResABORT;
	//	return (LRESULT)pResultCutting;
	//}
	//if ( iDlgResult == ID_NO)
	//{	
	//	delete pComposite;
	//	pResultCutting->m_ButtonResult = iResNEXT;
	//	return (LRESULT)pResultCutting;
	//}
	//DWORD dwBPS = m_vecSelDrives.at(pDiskInfoData->m_iDiskNumber).getBytesPerSector();
	//LONGLONG lShearPos = pDiskInfoData->m_LBAPosition;
	//lShearPos += pDiskInfoData->m_dwStartSector;
	//CJGShear *pJpgShear = new CJGShear();
	//pJpgShear->setDataSize(dwSectorNumbers*dwBPS); // set Data Buffer size
	//pJpgShear->setDiskNumber( (BYTE)m_vecSelDrives.at(pDiskInfoData->m_iDiskNumber).getDiskNumber() ); // Set Disk Number
	//pJpgShear->setJPGStartPostion(lShearPos);
	//lShearPos += dwSectorNumbers /*+ 1*/;
	//pJpgShear->setShearPosition(lShearPos); // set Position of Shear
	//pJpgShear->setDevice(m_vecSelDrives.at(pDiskInfoData->m_iDiskNumber));
	//pJpgShear->Execute();
	//pComposite->AddSTEP(pJpgShear);
	////
	//// Нужно исключить Диск где "СРЕЗ"
	//RaidDrives.erase(RaidDrives.begin()+pDiskInfoData->m_iDiskNumber);
	//DWORD dwBlockSize = 64*1024;
	//// 
	//while (dwBlockSize  <  (2* 1024*1024 ))
	//{
	//	vector<CDiskDrive> copyRaidDrives = RaidDrives;
	//	
	//	while(copyRaidDrives.size() > 0)
	//	{
	//		pComposite->Execute();
	//		CFileCreater *pFileCreater = new CFileCreater();
	//		BYTE *pBUFFER = pComposite->GetData();
	//		DWORD dwJPGSize = pComposite->GetSize();
	//		pFileCreater->setJPGData(pBUFFER);
	//		pFileCreater->setJPGSize(dwJPGSize);
	//		pFileCreater->setBlockSize(dwBlockSize);
	//		pFileCreater->setSetDrives(copyRaidDrives);
	//		pFileCreater->setShearPosition(lShearPos);
	//		pFileCreater->CreateFiles();
	//		delete pFileCreater;
	//		// Вывести файлы и задать вопрос...
	//		CCuttingSectorsDlg *pCuttingDialog = new CCuttingSectorsDlg(this,pComposite->getStep());
	//		pCuttingDialog->setTextData(strText);
	//		pCuttingDialog->setEditStyle(EDIT_STYLE::DIGIT_STYLE);
	//		pCuttingDialog->setDefaultData(defaultString);
	//		iDlgResult = pCuttingDialog->DoModal();
	//		if (iDlgResult == ID_NO)
	//		{
	//			copyRaidDrives.clear();
	//			break;
	//		}
	//		
	//		if (iDlgResult == ID_ABORD)
	//		{	
	//			copyRaidDrives.clear();
	//			delete pComposite;
	//			pResultCutting->m_ButtonResult = iResABORT;
	//			return (LRESULT)pResultCutting;
	//		}

	//		strText = pCuttingDialog->getStringData();
	//		DWORD iDiskNumber = _ttoi(strText);
	//		BYTE iDiskPos = 0;
	//		for (size_t iNumDisk = 0; iNumDisk < copyRaidDrives.size();++iNumDisk)
	//		{
	//			if (iDiskNumber == copyRaidDrives.at(iNumDisk).getDiskNumber())
	//			{
	//				iDiskPos = iNumDisk;
	//				break;
	//			}
	//		}
	//		delete pCuttingDialog;		

	//		CJPGChunk *pJPGChunk = new CJPGChunk();
	//		pJPGChunk->setDataSize(dwBlockSize);
	//		pJPGChunk->setDiskNumber(iDiskNumber);
	//		pJPGChunk->setDevice(copyRaidDrives.at(iDiskPos));
	//		LONGLONG lBackShearPos = lShearPos - dwBlockSize/512;
	//		pJPGChunk->setShearPosition(lBackShearPos);
	//		pJPGChunk->Execute();
	//		pComposite->AddSTEP(pJPGChunk);
	//		// delete drive;
	//		if (copyRaidDrives.size() == 1)
	//			copyRaidDrives.erase(copyRaidDrives.begin());
	//		else
	//			copyRaidDrives.erase(copyRaidDrives.begin()+iDiskPos);
	//	}
	//	dwBlockSize *= 2;
	//}
	//delete pComposite;