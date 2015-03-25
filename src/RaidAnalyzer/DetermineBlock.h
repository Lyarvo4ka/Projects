#pragma once
//#include "InfoData.h"
#include "GatherByJPG.h"
//class CDriveReader1
//{
//public:
//	CDriveReader();
//	CDriveReader(CDiskDrive & _diskDrive);
//	//DriveReader(CDiskDrive & _diskDrive,);
//	~CDriveReader(){};
//	void setDiskDrive(CDiskDrive & _diskDrive);
//	BOOL ReadSectors(BYTE *_pBuffer, LONGLONG &_SectorPosition, DWORD &_dwBufferSize);
//	BOOL ReadSector(BYTE *_pBuffer, LONGLONG &_SectorPosition, DWORD &_dwBufferSize);
//	DWORD getBytesPerSector() const;
//	BOOL OpenDrive();
//	void CloseDrive();
//private:
//	CDiskDrive m_DiskDrive;
//	HANDLE m_hDrive;
//
//};


class AbstractStep
{
public:
	virtual BOOL Execute() = 0;
	virtual AbstractStep* GetComposite() = 0;
	virtual DWORD GetSize() = 0;
	virtual BYTE * GetData() = 0;
	virtual LONGLONG GetPositiom() = 0;
	virtual ~AbstractStep(){};
};

class CompositeSTEP: public AbstractStep
{
public:
	CompositeSTEP();
	CompositeSTEP(UINT _iCurretStep);
	~CompositeSTEP();
	/*virtual */void AddSTEP(AbstractStep* _newStep) /*= 0*/;
	/*virtual */void RemoveSTEP(AbstractStep* _removeLastStep = NULL) /*= 0*/;
	void RemoveToOne();
	void setStep(UINT _iStep);
	virtual AbstractStep* GetComposite();
	virtual BOOL Execute();
	virtual DWORD GetSize();
	virtual BYTE * GetData();
	virtual LONGLONG GetPositiom();
	BOOL isFinishJPG() const;
	UINT getStep() {return m_iCurrentSTEP; };
protected :
	void IncStep();
	void DecStep();
private:
	CArray<AbstractStep*,AbstractStep*> m_arSteps;
	DWORD m_dwJPGSize;
	BYTE *m_pJPGBuffer;
	UINT m_iCurrentSTEP;
	BOOL m_bJpgFinish;
};

class CJPGChunk : public AbstractStep
{
public :
	CJPGChunk();
	~CJPGChunk();
	virtual AbstractStep* GetComposite();
	virtual BOOL Execute();
	virtual DWORD GetSize();
	virtual BYTE * GetData();
	virtual LONGLONG GetPositiom();
	void addJPGData(BYTE * _pBuffer);
	void removeJPGData();
	BYTE * getJPGData() const;
	void setDataSize(DWORD _dwDataSize);
	DWORD getDataSize() const;
	void setDiskNumber(BYTE _DiskNumber);
	BYTE getDiskNumber() const;
	void setDevice(CDiskDrive & _DiskDrive);
	void setShearPosition(LONGLONG _lShearPos);
	LONGLONG getShearPosition() const;
	void setBackPos(LONGLONG _lBackPos);
private:
	DWORD m_dwDataSize;
	BYTE m_iDiskNumber;
	LONGLONG m_lShearPos;
	LONGLONG m_lBackPos;
protected:
	CDriveReader m_DriveReader;
	BYTE * m_pJPGData;
};

class CJGShear : public CJPGChunk
{
public :
	CJGShear();
	~CJGShear();
	virtual AbstractStep* GetComposite();
	virtual BOOL Execute();
	virtual DWORD GetSize();
	virtual BYTE * GetData();
	virtual LONGLONG GetPositiom();
	void setJPGStartPostion(LONGLONG _lShearPos);
private:
	LONGLONG m_lShearPos;
	LONGLONG m_lJPGStartPos;
};

