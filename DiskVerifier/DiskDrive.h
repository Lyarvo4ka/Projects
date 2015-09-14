#pragma once
#include <vector>
using std::vector;

typedef struct VerifyRange
{
	LONGLONG lFrom;
	LONGLONG lTo;
} VERIFY_RANGE, *PVERIFY_RANGE;

typedef struct TestNumbers
{
	BOOL bEasyTest;
	BOOL bRandomTest;
	BOOL bFullTest;
	BOOL isFirstMismatch;
} TESTNUMBERS, * PTESTNUMBERS;

typedef class CDiskDrive
{
public:
	CDiskDrive(void);
	~CDiskDrive(void);
	void setDiskPath(CString _stDiskPath);
	void setDiskName(CString _stDiskName);
	void setDiskNumber(UINT _iDiskNumber);
	void setBytesPerSector(DWORD _iBytesPerSector);
	void setSectorCount(LONGLONG _llDiskSize);
	void setSerialNumber(CString _stSerialNumber);
	void setHandle(HANDLE & _hDisk);
	void setMaxTransferSize(ULONG  _ulMaxTransferSize);

	bool OpenPhysicalDisk();
	void ClosePhysicalDisk();

	bool ReadBytes(const WORD & _bytesPerSector,
				   DWORD *pdwBytesRead, 
				   BYTE * pBytes, 
				   LARGE_INTEGER &_pliDistMove,
				   PLARGE_INTEGER pliNewFilePointer = 0);


	HANDLE getHandle();

	CString getDiskName() const;
	CString getDiskPath() const;
	CString getSerialNumber() const;
	UINT getDiskNumber() const;
	DWORD getBytesPerSector() const;
	DWORD getDiskSize() const;
	LONGLONG getSectorCount() const;
	ULONG getMaxTransferSize() const;
	CDiskDrive* getDiskDrive() ;

	bool operator() (CDiskDrive&,CDiskDrive&);

private:
	CString m_stDiskPath;
	CString m_stDiskName;
	CString m_stSerialNumber;
	UINT m_iDiskNumber;
	DWORD m_iBytesPerSector;
	DWORD m_dwDiskSize;
	LONGLONG m_llSectorCount;
	ULONG m_ulMaxTransferSize;
	HANDLE m_hDisk;
} CDISKDRIVE, *PCDISKDRIVE;

