#include "StdAfx.h"
#include "DiskDrive.h"




CDiskDrive::CDiskDrive(void)
:m_stDiskPath(_T(""))
,m_stDiskName(_T(""))
,m_iDiskNumber(0)
,m_iBytesPerSector(0)
,m_stSerialNumber(_T(""))
,m_llSectorCount(0)
//,m_liDiskSize(0)
{
	TRACE("Create... \r\n");
	//m_hDisk = new HANDLE();
}


CDiskDrive::~CDiskDrive(void)
{
	//if (m_hDisk != NULL)
	//{
	//	delete m_hDisk;
	//	m_hDisk = NULL;
	//}
}



void CDiskDrive::setDiskPath(CString _stDiskPath)
{
	m_stDiskPath = _stDiskPath;
}

void CDiskDrive::setDiskName(CString _stDiskName)
{
	m_stDiskName = _stDiskName;
}


void CDiskDrive::setDiskNumber(UINT _iDiskNumber)
{
	m_iDiskNumber = _iDiskNumber;
}

CString CDiskDrive::getDiskName() const
{
	return m_stDiskName;
}

UINT CDiskDrive::getDiskNumber() const
{
	return m_iDiskNumber;
}

CString CDiskDrive::getDiskPath() const
{
	return m_stDiskPath;
}


void CDiskDrive::setBytesPerSector(DWORD _iBytesPerSector)
{
	m_iBytesPerSector = _iBytesPerSector;
}


DWORD CDiskDrive::getBytesPerSector() const
{
	return m_iBytesPerSector;
}

DWORD CDiskDrive::getDiskSize() const
{
	return m_dwDiskSize;
}

void CDiskDrive::setSectorCount(LONGLONG _llDiskSize)
{
//	m_liDiskSize = _liDiskSize;
	m_llSectorCount = _llDiskSize;
	LONGLONG llDiskSize = 0;
	llDiskSize = _llDiskSize; // bytes
	llDiskSize /= 1024; // Kbytes
	llDiskSize /= 1024; // Mbytes
	llDiskSize /= 1024; // Gbytes

	m_dwDiskSize = (DWORD)llDiskSize;
	m_llSectorCount = _llDiskSize;
	m_llSectorCount /= m_iBytesPerSector;

}

void CDiskDrive::setSerialNumber(CString _stSerialNumber)
{
	_stSerialNumber.Trim(_T(" "));
	m_stSerialNumber = _stSerialNumber;
}

CString CDiskDrive::getSerialNumber() const
{
	return m_stSerialNumber;
}


LONGLONG CDiskDrive::getSectorCount() const
{
	return m_llSectorCount;
}


bool CDiskDrive::OpenPhysicalDisk()
{
	m_hDisk = CreateFile(m_stDiskPath,
					   GENERIC_READ | GENERIC_WRITE,
					   FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE  ,
					   NULL,
					   OPEN_EXISTING,
					   0,
					   NULL);


//	CM_Get_DevNode_Status

	if ( m_hDisk == INVALID_HANDLE_VALUE )
	{
	
		AfxMessageBox(_T("invalid Open Phisycal Disk"),MB_OK);
		exit(0);
	}

	return true;
		
}


void CDiskDrive::ClosePhysicalDisk()
{
	if ( m_hDisk != INVALID_HANDLE_VALUE )
	{
		CloseHandle(m_hDisk);
	}
}

void CDiskDrive::setHandle(HANDLE &_hDisk)
{
	m_hDisk = _hDisk;
}


bool CDiskDrive::ReadBytes(const WORD & _bytesPerSector,
				   DWORD *pdwBytesRead, 
				   BYTE * pBytes, 
				   LARGE_INTEGER &_pliDistMove,
				   PLARGE_INTEGER pliNewFilePointer)
{
	//memset(pBytes,1,_bytesPerSector);

	//SetFilePointerEx 
	if (_pliDistMove.QuadPart != 0 )
		SetFilePointerEx(m_hDisk,_pliDistMove,pliNewFilePointer,FILE_BEGIN);

	if (ReadFile(m_hDisk,pBytes,_bytesPerSector,pdwBytesRead,NULL))
		return true;
	return false;
}


HANDLE CDiskDrive::getHandle() 
{
	return m_hDisk;
}

ULONG CDiskDrive::getMaxTransferSize() const
{
	return m_ulMaxTransferSize;
}



void CDiskDrive::setMaxTransferSize(ULONG  _ulMaxTransferSize)
{
	m_ulMaxTransferSize = _ulMaxTransferSize;
}


CDiskDrive * CDiskDrive::getDiskDrive()
{
	return this;
}

bool CDiskDrive::operator() (CDiskDrive& _drive1,CDiskDrive& _drive2)
{
	return (_drive1.getDiskNumber() < _drive2.getDiskNumber());
}
