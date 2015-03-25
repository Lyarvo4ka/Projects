
///////////////////////////////////////////////////////////////////////////////
// --------------- CAllocator -------------------
///////////////////////////////////////////////////////////////////////////////
template <class TypeBuffer>
class CAllocator/*:public CBuffer*/
{
public:
	CAllocator();
	CAllocator(DWORD _iBufferSize, UINT _iSizeFree);
	virtual ~CAllocator();

	/*virtual */TypeBuffer *CreateBuffer();
	// S E T
	void setBuffersCount(UINT _iBuffersCount);
	void IncBufferCount();

	TypeBuffer *GetBuffer();
	void RemoveBuffer(TypeBuffer*);

	void setToDefault(TypeBuffer );

protected:

///////////////////////////////////////////////////////////////////////////////
	// CBuffer
	CList<TypeBuffer*,TypeBuffer*> m_FreeList;
	CRITICAL_SECTION *csFreeAccess;
	UINT m_iSize;
	const UINT m_iSizeFree;
private:
	DWORD m_TBlockSize;

};

///////////////////////////////////////////////////////////////////////////////
// --------------- CAllocator -------------------
///////////////////////////////////////////////////////////////////////////////

template <class TypeBuffer>
CAllocator<TypeBuffer>::CAllocator()
	:m_TBlockSize(0),m_iSize(0),m_iSizeFree(0)
{
	csFreeAccess = new CRITICAL_SECTION;
	::InitializeCriticalSection(csFreeAccess);
}


template <class TypeBuffer>
CAllocator<TypeBuffer>::CAllocator(DWORD _iBufferSize, UINT _iSizeFree)
	:m_TBlockSize(_iBufferSize),m_iSize(0),m_iSizeFree(_iSizeFree)
{
	csFreeAccess = new CRITICAL_SECTION;
	::InitializeCriticalSection(csFreeAccess);
}

template <class TypeBuffer>
CAllocator<TypeBuffer>::~CAllocator()
{
	while (!m_FreeList.IsEmpty())
	{
		TypeBuffer *pBufferDelete = m_FreeList.RemoveHead();
		delete pBufferDelete;
	}

	::DeleteCriticalSection(csFreeAccess);
	delete csFreeAccess;
}


template <class TypeBuffer>
void CAllocator<TypeBuffer>::setBuffersCount(UINT _iBuffersCount)
{
	m_iSize = _iBuffersCount;
}


template <class TypeBuffer>
void CAllocator<TypeBuffer>::setToDefault(TypeBuffer  _pBuffer)
{
	//_pBuffer->m_iDiskNumber = UCHAR_MAX;
}


template <class TypeBuffer>
TypeBuffer* CAllocator<TypeBuffer>::CreateBuffer()
{
	TypeBuffer *_pBuffer = new TypeBuffer(m_TBlockSize);
	return _pBuffer;
}

template <class TypeBuffer>
TypeBuffer *CAllocator<TypeBuffer>::GetBuffer()
{
	TypeBuffer *pBuffer = NULL;

	// if in ListFree is Present CBuffer then return this pointer 
	// and remove from list
	::EnterCriticalSection(csFreeAccess);
	if (!m_FreeList.IsEmpty() )
	{
		// get Data From buffer
		pBuffer = m_FreeList.RemoveHead();
		::LeaveCriticalSection(csFreeAccess);
		return pBuffer;
	}
	else
	{
		pBuffer = new TypeBuffer(m_TBlockSize);
		IncBufferCount();
		return pBuffer;
	}

}
template <class TypeBuffer>
void CAllocator<TypeBuffer>::RemoveBuffer(TypeBuffer *_pBuffer)
{
	::EnterCriticalSection(csFreeAccess);
	if (m_iSize == 0)
	{
		::AfxMessageBox(_T("Error Buffers Count Don't equal = 0"),MB_OK);
	}
	if (m_FreeList.GetSize() <= m_iSizeFree)
	{
		m_FreeList.AddTail(_pBuffer);
	}
	else
	{
		delete _pBuffer;
		::InterlockedDecrement(&m_iSize);
	}
	::LeaveCriticalSection(csFreeAccess);
}



template <class TypeBuffer>
void CAllocator<TypeBuffer>::IncBufferCount()
{
	::InterlockedIncrement(&m_iSize);
}


