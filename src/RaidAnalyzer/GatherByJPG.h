#pragma once
#include "InfoData.h"

class CDataBuffer
{
public:
	CDataBuffer();
	virtual ~CDataBuffer();
	void setData(BYTE *_pBufferData);
	void setSize(DWORD _dwSize);
	/*virtual*/ BYTE *GetData() const;
	DWORD GetSize() const;
	virtual BOOL Execute() = 0;
protected:
	BYTE * m_pBufferData;
	DWORD m_dwBufferSize;
};

class CDriveReader : public CDataBuffer
{
public:
	CDriveReader(void);
	CDriveReader(CDiskDrive & _diskDrive);
	CDriveReader(CDiskDrive & _diskDrive, LONGLONG _lPosition, DWORD _dwReadSize);
	void ClearBuffer();
	void setDiskDrive(CDiskDrive & _diskDrive);
	void setReadPosition(LONGLONG _lPosition);
	virtual BOOL Execute();
	virtual ~CDriveReader(void);
private:
	BOOL OpenDrive();
	void CloseDrive();

	LONGLONG m_lPosition;
	CDiskDrive m_DiskDrive;
	HANDLE m_hReadDevice;
};

class CFileCreater : public CDataBuffer
{
public:
	CFileCreater();
	CFileCreater(CString _strDirectoryPath);
	virtual ~CFileCreater();
	void setDirectoryPath(CString _strDirectoryPath);
	void setStep(UINT _iStep);
	void setFileNumber(UINT _iFileNumber);
	void AddWriteData(BYTE * _pBuffer, DWORD _dwSize);
	void AddFileName(CString _strAddFileName);
	CString GetFilePath() const;
	virtual BOOL Execute();
private:
	CString m_strDirectoryPath;
	CString m_strAddFileName;
	CString m_strFilePath;
	UINT m_iStep;
	UINT m_iFileNumber;
	BYTE *m_pAddData;
	DWORD m_dwAddSize;
};

enum PosUpDown {PosUP = 0,PosDown = 1};
class CDataBlock 
{
public:
	CDataBlock();
	virtual ~CDataBlock();
	void setDiskNumber(BYTE _iDiskNumber);
	void setPosUpDown(PosUpDown _posUpDown);
	void setSize(DWORD _dwSize);
	BYTE getDiskNumber() const;
	DWORD getBlockSize() const;
	PosUpDown getPosUpDown() const;
private:
	PosUpDown m_enPosUpDown;
	BYTE m_iDiskNumber;
	DWORD m_dwBlockSize;
};

class CMapBlocks
{
public:
	CMapBlocks();
	virtual ~CMapBlocks();
	void setVecDrives(vector<CDiskDrive> _vecDrives);
	void setPosition(LONGLONG _lPosition);
	void setBlockSize(DWORD _dwBlockSize);
	void ClearMap();
	void setDirectory(CString _strDirectory) ;
	void setBaseData(BYTE *_pBuffer, DWORD _dwSize);
	void DeterminateBlock(int iMinSector = 0);
	void CreateFiles(UINT & _iCurrentFile, DWORD _dwBlockSize, int _iDiskNumber = -1 );
	CDataBlock * getData(UINT _iNumber);
	UINT getCount() const;
	void setNextDisk(int _iNextDisk);
private:
	CMap<UINT , UINT, CDataBlock* , CDataBlock*> m_mapBlocks;
	vector<CDiskDrive> m_vecDrives;
	DWORD m_dwBlockSize;
	LONGLONG m_lPosition;
	CFileCreater *m_pFileCreater;
	CDriveReader *m_pDriveReader;
	CString m_strDirctoryPath;
	int m_iNextDisk;
};

class IDiskOrder
{
public:
	virtual ~IDiskOrder(){};
	virtual IDiskOrder * GetComposite() = 0;
	virtual CDiskDrive * GetDevice() = 0;
	//virtual BOOL Execute() = 0;
};

const CString csNewLine = _T("\r\n");

class CDiskNumber: public IDiskOrder
{
public:
	CDiskNumber();
	virtual ~CDiskNumber();
	virtual IDiskOrder * GetComposite();
	virtual CDiskDrive * GetDevice() ;
	void setDiskDrive(CDiskDrive _DiskDrive);
	//virtual BOOL Execute() ;
private:
	CDiskDrive *m_DiskDrive;
};
class CNewOrder : public IDiskOrder
{
public:
	CNewOrder();
	virtual ~CNewOrder();
	virtual IDiskOrder * GetComposite() ;
	virtual CDiskDrive * GetDevice() ;
	//virtual BOOL Execute() ;
};

class CDiskOrder : public IDiskOrder
{
public:
	CDiskOrder();
	void Add(IDiskOrder *_IDiskOrder);
	void Delete();
	virtual ~CDiskOrder();
	virtual IDiskOrder * GetComposite();
	virtual CDiskDrive * GetDevice() {return NULL;};
	CString GetDiskOrder() const;
	void MakeDiskOrder(CString _strSplit = _T("\r\n"));
	void Clear()
	{
	if (m_arOrder.GetCount() > 0)
	{
		for (INT_PTR iOrder = 0; iOrder < m_arOrder.GetCount(); ++iOrder)
		{
			IDiskOrder *pIDiskOrder = m_arOrder[iOrder];
			delete pIDiskOrder;
		}
		m_arOrder.RemoveAll();
	}
	}
	//virtual BOOL Execute() ;
private:
	CString m_strDiskOrder;
	CArray<IDiskOrder*,IDiskOrder*> m_arOrder;
};


///////////////////////////////////////////////////////////////////////////////
// --------------- JPG Singleton -------------------
///////////////////////////////////////////////////////////////////////////////

typedef struct _DiskNumber_Pos
{
	BYTE m_iDiskNumber;
	LONGLONG m_lLBAPosition;
} NUMBER_POS, *PNUMBER_POS;

typedef CMap<ULONGLONG,ULONGLONG,NUMBER_POS,NUMBER_POS> MapNumberPos;

class CSingletonJPGs
{
public:
	static CSingletonJPGs * GetInstance();
	void Add(BYTE _iDiskNumber, LONGLONG _lLBAPosition);
	BOOL GetNumberPos(UINT _iNumber,NUMBER_POS &_NumberPos);
	void setDirectory(CString _strDirectory);
	void setDrives(vector<CDiskDrive> _vecDrives);
	void RemoveInstance();
	void RemoveData();
protected:
	CSingletonJPGs();
	//~CSingletonJPGs();
private:
	vector<CDiskDrive> m_vecDrives;
	LONGLONG m_iCount;
	MapNumberPos m_mapNumberPos;
	HANDLE m_hMutex;
	CString m_strPath;
	static CSingletonJPGs *m_Instance;
};