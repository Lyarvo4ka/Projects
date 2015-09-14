#include "StdAfx.h"
#include "DetermineBlock.h"
//
//CDriveReader::CDriveReader()
//{
//	m_hDrive = INVALID_HANDLE_VALUE;
//}
//CDriveReader::CDriveReader(CDiskDrive & _diskDrive)
//{
//	m_DiskDrive = _diskDrive;
//}
//void CDriveReader::setDiskDrive(CDiskDrive & _diskDrive)
//{
//	m_DiskDrive = _diskDrive;
//}
//DWORD CDriveReader::getBytesPerSector() const
//{
//	return m_DiskDrive.getBytesPerSector();
//}
//BOOL CDriveReader::ReadSectors(BYTE *_pBuffer, LONGLONG &_SectorPosition, DWORD &_dwBufferSize)
//{
//	if (_pBuffer == NULL)
//	{
//		TRACE("Error NULL buffer >>>>");
//		return FALSE;
//	}
//	DWORD dwBytesRead = 0;
//	DWORD dwBPS = m_DiskDrive.getBytesPerSector();
//	LARGE_INTEGER liPosition;
//	liPosition.QuadPart = _SectorPosition;
//	liPosition.QuadPart *= dwBPS;
//	SetFilePointerEx(m_hDrive,liPosition,NULL,FILE_BEGIN);
//	if (!ReadFile(m_hDrive,_pBuffer,_dwBufferSize,&dwBytesRead,NULL) )
//	{
//		TRACE("Error Read FILE >>>>");
//		return FALSE;
//	}
//	return TRUE;
//}
//BOOL CDriveReader::ReadSector(BYTE *_pBuffer, LONGLONG &_SectorPosition, DWORD &_dwBufferSize)
//{
//	if (!OpenDrive())
//		return FALSE;
//	ReadSectors(_pBuffer,_SectorPosition,_dwBufferSize);
//	CloseDrive();
//	return TRUE;
//}
//BOOL CDriveReader::OpenDrive()
//{
//	m_hDrive = CreateFile(m_DiskDrive.getDiskPath(),
//					   GENERIC_READ,
//					   FILE_SHARE_READ,
//					   NULL,
//					   OPEN_EXISTING,
//					   0 /*| FILE_FLAG_NOBUFFERING *//*NULL*/,
//					   NULL);
//	if (m_hDrive == INVALID_HANDLE_VALUE)
//	{
//		TRACE("ERROR OPEN PHYSICAL DRIVE");
//		return FALSE;
//	}
//	return TRUE;
//}
//void CDriveReader::CloseDrive()
//{
//	CloseHandle(m_hDrive);
//}

/////////////////////////////////////////
CompositeSTEP::CompositeSTEP()
	: m_dwJPGSize(0),m_pJPGBuffer(NULL),m_bJpgFinish(FALSE)

{
	setStep(0);
}
CompositeSTEP::CompositeSTEP(UINT _iCurretStep)
	:m_dwJPGSize(0),m_pJPGBuffer(NULL),m_bJpgFinish(FALSE)
{
	setStep(_iCurretStep);
}

void CompositeSTEP::IncStep()
{
	++m_iCurrentSTEP;
}

void CompositeSTEP::DecStep()
{
	if ( m_iCurrentSTEP > 0 )
		--m_iCurrentSTEP;
}

void CompositeSTEP::AddSTEP(AbstractStep* _newStep)
{
	m_arSteps.Add(_newStep);
	IncStep();

}

void CompositeSTEP::RemoveSTEP(AbstractStep* _removeLastStep)
{
	if (m_arSteps.GetCount() > 0)
	{
		UINT iDelPos = m_arSteps.GetCount() - 1;
		AbstractStep *pDelData = m_arSteps[iDelPos];
		delete pDelData;		
		m_arSteps.RemoveAt(iDelPos);
		DecStep();
	}
}

void CompositeSTEP::RemoveToOne()
{
	if (m_arSteps.GetCount() > 1)
	{
		while (m_arSteps.GetCount() == 1)
		{
			UINT iDelPos = m_arSteps.GetCount() - 1;
			AbstractStep *pDelData = m_arSteps[iDelPos];
			delete pDelData;		
			m_arSteps.RemoveAt(iDelPos);
			m_iCurrentSTEP = 1;
		
		}
	}

}

LONGLONG CompositeSTEP::GetPositiom()
{
	LONGLONG lPosition = 0;
	INT_PTR iCount = m_arSteps.GetCount();
	if (iCount > 0)
	{
		AbstractStep *pAbstractStep = NULL;
		pAbstractStep = m_arSteps.GetAt(iCount - 1);
		lPosition = pAbstractStep->GetPositiom();
	}
	return lPosition;
}

void CompositeSTEP::setStep(UINT _iStep)
{
	m_iCurrentSTEP = _iStep;
}

AbstractStep* CompositeSTEP::GetComposite()
{
	return this;
}

CompositeSTEP::~CompositeSTEP()
{
	if (m_arSteps.GetCount() > 0)
	{
		INT_PTR iCount = m_arSteps.GetCount();
		for (INT_PTR istep = 0; istep < m_arSteps.GetCount(); ++istep)
		{
			AbstractStep *pDelData = m_arSteps[istep];
			delete pDelData;
		}
		m_arSteps.RemoveAll();
	}
	delete m_pJPGBuffer;
	m_pJPGBuffer = NULL;
}
BOOL CompositeSTEP::Execute()
{
	m_dwJPGSize = 0;
	if (m_pJPGBuffer != NULL)
	{
		delete m_pJPGBuffer ;
		m_pJPGBuffer = NULL;
	}
	if (m_arSteps.GetCount() == 0 )
		return FALSE;
	CJPGChunk *pJPGChunk = NULL;
	for (INT_PTR istep = 0; istep < m_arSteps.GetCount(); ++istep)
		m_dwJPGSize += m_arSteps[istep]->GetSize();
	m_pJPGBuffer = new BYTE[m_dwJPGSize];
	DWORD dwLastPos = 0;
	for (INT_PTR istep = 0; istep < m_arSteps.GetCount(); ++istep)
	{
		memcpy(m_pJPGBuffer + dwLastPos,m_arSteps[istep]->GetData(),m_arSteps[istep]->GetSize());
		dwLastPos += m_arSteps[istep]->GetSize();
	}
	
	UINT iCounter = 0;
	for (DWORD iByte = 0; iByte < m_dwJPGSize - 1; ++iByte)
	{
		if (m_pJPGBuffer[iByte] == 0xFF)
			if (m_pJPGBuffer[iByte+1] == 0xD8)
				++iCounter;

		if (m_pJPGBuffer[iByte] == 0xFF)
			if (m_pJPGBuffer[iByte+1] == 0xD9)
				--iCounter;
		if (iCounter == 0)
			m_bJpgFinish = TRUE;
	}

	return TRUE;
}
DWORD CompositeSTEP::GetSize()
{
	return m_dwJPGSize;
}
BYTE * CompositeSTEP::GetData()
{
	return m_pJPGBuffer;
}
BOOL CompositeSTEP::isFinishJPG() const
{
	return m_bJpgFinish;
}

//////////////////////////// CJPGChunk ////////////////////////////
CJPGChunk::CJPGChunk()
	:m_pJPGData(NULL),m_dwDataSize(0),m_iDiskNumber(0)
{
}
CJPGChunk::~CJPGChunk()
{
	removeJPGData();
}
AbstractStep* CJPGChunk::GetComposite()
{
	return this;
}
void CJPGChunk::addJPGData(BYTE * _pBuffer)
{
	m_pJPGData = _pBuffer;
}
void CJPGChunk::removeJPGData()
{
	if (m_pJPGData != NULL)
	{
		delete m_pJPGData;
		m_pJPGData = NULL;
	}
}
BYTE * CJPGChunk::getJPGData() const
{
	return m_pJPGData;
}
void CJPGChunk::setDataSize(DWORD _dwDataSize)
{
	m_dwDataSize = _dwDataSize;
}
DWORD CJPGChunk::getDataSize() const
{
	return m_dwDataSize;
}
void CJPGChunk::setDiskNumber(BYTE _DiskNumber)
{
	m_iDiskNumber = _DiskNumber;
}
BYTE CJPGChunk::getDiskNumber() const
{
	return m_iDiskNumber;
}
void CJPGChunk::setDevice(CDiskDrive & _DiskDrive)
{
	m_DriveReader.setDiskDrive(_DiskDrive);
}
void CJPGChunk::setShearPosition(LONGLONG _lShearPosition)
{
	m_lShearPos = _lShearPosition;
}
LONGLONG CJPGChunk::getShearPosition() const
{
	return m_lShearPos;
}
DWORD CJPGChunk::GetSize()
{
	return m_dwDataSize;
}
BYTE * CJPGChunk::GetData()
{
	return m_pJPGData;
}
LONGLONG CJPGChunk::GetPositiom()
{
	return m_lBackPos;
}
void CJPGChunk::setBackPos(LONGLONG _lBackPos)
{
	m_lBackPos = _lBackPos;
}

BOOL CJPGChunk::Execute()
{
	if (  m_dwDataSize == 0)
		return FALSE;
	m_DriveReader.setSize(m_dwDataSize);
	m_DriveReader.setReadPosition(m_lShearPos);
	if (m_DriveReader.Execute() == FALSE)
		return FALSE;
	m_pJPGData = new BYTE[m_dwDataSize];
	memcpy(m_pJPGData,m_DriveReader.GetData(),m_dwDataSize);

	return TRUE;
}
//////////////////////////// CJGShear ////////////////////////////
CJGShear::CJGShear()
	:CJPGChunk(),m_lShearPos(0)
{

}
CJGShear::~CJGShear()
{
	removeJPGData();
}
AbstractStep* CJGShear::GetComposite()
{
	return this;
}
void CJGShear::setJPGStartPostion(LONGLONG _lJPGStartPosition)
{
	m_lJPGStartPos = _lJPGStartPosition;
}
LONGLONG CJGShear::GetPositiom()
{
	return m_lShearPos;
}
BOOL CJGShear::Execute()
{
	DWORD dwBlockSize = getDataSize();
	if ( dwBlockSize == 0)
		return FALSE;
	m_pJPGData = new BYTE[dwBlockSize];
	m_DriveReader.setSize(dwBlockSize);
	m_DriveReader.setReadPosition(m_lJPGStartPos);
	if (m_DriveReader.Execute() == FALSE)
		return FALSE;
	memcpy(m_pJPGData,m_DriveReader.GetData(),dwBlockSize);
	return TRUE;
}
DWORD CJGShear::GetSize()
{
	return getDataSize();
}
BYTE * CJGShear::GetData()
{
	return m_pJPGData;
}
