#pragma once

// warning C4251: needs to have dll-interface to be used by clients of class
#pragma warning(disable : 4251)

#include "Concurrent.h"
#include <vector>
using std::vector;
#include <list>
using std::list;

class DllExport CBuffer 
{
public:
	CBuffer(const DWORD & _rBufferSize);
	virtual ~CBuffer(void);
	// Set Position in Bytes
	void SetPosition(const LONGLONG & _rPosition);
	LONGLONG GetPosition() const;
	void SetDiskNumber(const DWORD & _rDiskNumber);
	DWORD GetDiskNumber() const;
	void SetSize(DWORD _Size);
	DWORD GetSize() const;
	BYTE * GetBuffer() const;
	void AddBadSector(const LONGLONG & _rBadSector);
	BOOL isHasBadSector() const;
	const vector<LONGLONG> * GetBadSectors() const;
	void Clear();
private:
	BYTE * m_pBuffer;
	DWORD m_iSize;
	LONGLONG m_iLBA;
	DWORD m_iDiskNumber;
	BOOL m_bHasBadSector;
	vector<LONGLONG> m_BadSectorList;
};

class DllExport CAllocator
{
public:
	CAllocator(DWORD _iBufferSize, UINT _iSizeFree);
	virtual ~CAllocator();

	// S E T
	void setBuffersCount(UINT _iBuffersCount);
	void IncBufferCount();

	CBuffer *GetBuffer();
	void RemoveBuffer(CBuffer*);
protected:

	list<CBuffer*> m_FreeList;
	UINT m_iSize;
	const UINT m_iSizeFree;
private:
	DWORD m_TBlockSize;
	HANDLE m_hLockSize;
	HANDLE m_hUsedLock;
};