#pragma once

#include "Devices.h"
#include "Imports.h"
#include "Concurrent.h"
#include "Solver.h"


class CLog;

class IQueue;
class CBuffer;
class CAllocator;
class CThread;

#include <objidl.h>


#include <map>
using std::map;
using std::pair;

#include <list>
using std::list;

#include <string>
using std::wstring;

static string WStringToString(wstring &_WideStr)
{

	string strTo;
	if (_WideStr.length() > 0)
	{
		strTo.resize(_WideStr.length());
		WideCharToMultiByte(CP_ACP, 0, _WideStr.c_str(), -1, &strTo[0], strTo.size(), NULL, NULL);
	}
	return strTo;
}

template< class T, class T_Val>
class CSingletonMap
{
protected:
	CSingletonMap(){};
	virtual ~CSingletonMap(){};
	void operator = (const CSingletonMap &){};
	typedef pair<wstring, T_Val> FilePair;
public:
	static T * GetInstance()
	{
		if (m_pInstance == NULL)
			m_pInstance = new T();
		return m_pInstance;
	}
	void Release()
	{
		if (m_pInstance != NULL)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}
	bool Add(const wstring &_FileSizeName, T_Val _FileSize)
	{
		map<wstring,T_Val>::iterator it;
		it = m_FileSizeTable.find(_FileSizeName);
		if (it == m_FileSizeTable.end())
		{
			m_FileSizeTable.insert(FilePair(_FileSizeName,_FileSize));
			return true;
		}
		return false;
	}
	bool Remove(const wstring & _FileSizeName)
	{
		map<wstring,T_Val>::iterator it;
		it = m_FileSizeTable.find(_FileSizeName);
		if (it != m_FileSizeTable.end())
		{
			it = m_FileSizeTable.erase(it);
			return true;
		}
		return false;
	}
	T_Val GetData(const wstring & _FileSizeName)
	{
		map<wstring,T_Val>::iterator it;
		it = m_FileSizeTable.find(_FileSizeName);
		if (it == m_FileSizeTable.end())
			return -1;
		return it->second;
	}
	const list<wstring> & GetKeywords()
	{
		m_Keywords.clear();
		map<wstring,T_Val>::iterator it;
		it = m_FileSizeTable.begin();
		while ( it != m_FileSizeTable.end())
		{
			m_Keywords.push_back(it->first);
			++it;
		}
		return m_Keywords;
	}
	void RemoveAll()
	{
		m_Keywords.clear();
		m_FileSizeTable.clear();
	}
private:
	static T * m_pInstance;
	map<wstring , T_Val> m_FileSizeTable;
	list<wstring> m_Keywords;
};

class CImageFileSize;
typedef CSingletonMap<CImageFileSize,LONGLONG> TImageFileSize;

class DllExport CImageFileSize
	: public TImageFileSize
{
private:
	CImageFileSize(){};
	~CImageFileSize(){};
	friend class CSingletonMap<CImageFileSize,LONGLONG>;

};

class CEnCaseFileSize;
typedef CSingletonMap<CEnCaseFileSize,LONGLONG> TEnCaseFileSize;
class DllExport CEnCaseFileSize
	: public TEnCaseFileSize
{
private:
	CEnCaseFileSize(){};
	~CEnCaseFileSize(){};
	friend class CSingletonMap<CEnCaseFileSize,LONGLONG>;
};

class CCompressionLevel;
typedef CSingletonMap<CCompressionLevel,int> TCompressionLevel;
class DllExport CCompressionLevel
	: public TCompressionLevel
{
private:
	CCompressionLevel(){};
	~CCompressionLevel(){};
	friend class CSingletonMap<CCompressionLevel,int>;
};


class CHashingMap;
typedef CSingletonMap<CHashingMap,int> THashingMap;
class DllExport CHashingMap 
	: public THashingMap
{
private:
	CHashingMap(){};
	~CHashingMap(){};
	friend class CSingletonMap<CHashingMap,int>;
};
	

///////////////////// IWriter /////////////////////
class DllExport IWriter
{
public:
	IWriter();
	virtual ~IWriter() = 0;
	virtual BOOL Open() = 0;
	virtual BOOL isOpen() = 0;
	virtual void Close() = 0;
	virtual DWORD Write(BYTE * pBuffer, DWORD WriteSize, LONGLONG Position) = 0;
	virtual DWORD Write(CBuffer * pCBuffer) = 0;
	virtual DWORD GetErrorCode() const = 0;

};

///////////////////// CWriter /////////////////////
class DllExport CWriter :
	public IWriter
{
public:
	CWriter(const DevicePtr &_pDevice);
	~CWriter();
	BOOL Open();
	BOOL isOpen();	
	void Close();
	DWORD Write(BYTE * pBuffer, DWORD WriteSize, LONGLONG _Position);
	DWORD Write(CBuffer * pCBuffer);
	DWORD GetErrorCode() const;
private:
	DWORD m_iBytesWrite;
	DWORD m_dwErrorCode;
	LARGE_INTEGER m_iPosition;
	DevicePtr m_pDevice;
	HANDLE m_hWriteDevice;
	BOOL m_bOpen;
	LONGLONG m_lWritePos;
};

///////////////////// CPhysicalWriter /////////////////////
class DllExport CPhysicalWriter
	: public IAbstractTask 
{
public:
	CPhysicalWriter();
	CPhysicalWriter(IWriter * _pWriter, const DevicePtr & _pDevice);
	virtual ~CPhysicalWriter();
	void SetWriter(IWriter * _pWriter);
	void SetDevice(const DevicePtr & _pDevice);
	void Execute(CBuffer * _pBuffer);
	BOOL isReady();
	void toFinish();
	IAbstractTask * GetComposite();
	void SetStartSector(LONGLONG _StartSector);
	void SetSectorsCount(LONGLONG _SectorsCount);
protected:
	virtual DWORD StartThread();
private:
	LONGLONG m_lWritePos;
	LONGLONG m_lStartSector;
	LONGLONG m_lSectorsCount;
	DevicePtr m_pDevice;
	IWriter * m_pWriter;
};




///////////////////// CFileWriter /////////////////////
class DllExport CFileWriter :
	public IAbstractTask
{
public:
	CFileWriter();
	virtual ~CFileWriter(void);
	BOOL Init();
	void Execute(CBuffer * _pBuffer);
	BOOL isReady();
	void toFinish();
	IAbstractTask * GetComposite();
	void SetFileName(const wstring & _fileName);
	void SetDirectory(const wstring &_Directory);
	void SetMaxFileSize(LONGLONG _MaxFileSize);
protected:
	virtual DWORD StartThread();
private:
	// methods
	BOOL CreateWriter();
	// members
	DWORD m_iBytesWrite;
	int m_Counter;
	wstring m_sDirectory;
	wstring m_sFileName;
	wstring m_sFullPath;
	LONGLONG m_MaxFileSize;
	LONGLONG m_FileSize;
	LONGLONG m_WritePos;
	IWriter * m_pWriter;
	DevicePtr m_FileDevice;
};

class DllExport CFileFactoryWriter
{
public:
	CFileFactoryWriter();
	~CFileFactoryWriter();
	CFileWriter * CreateFileWriter();

};
//CFileWriter * CFileFactoryWriter::CreateFileWriter()
//{
//	return new CFileWriter();
//}


//
const DWORD SectorSize = 512;

const DWORD DefaultSectors = 255;
const DWORD DefaultBuffer = SectorSize * DefaultSectors;

typedef struct _SignatureArray
{
	BYTE * BufferArray;
	DWORD Size;
} SignatureArray, * PSignatureArray;

class IWriter;
///////////////////// CRawCreater ////////////////////
class DllExport CRawCreater
	: public IAbstractTask , public CSubject
{
public:
	CRawCreater(void);
	~CRawCreater(void);
	enum RawState {FindHeader = 0, NotFindHeader, WriteFooter , WRITE_TO_END};

	void SetHeaderOffset(const DWORD _HeaderOffset);
	void SetHeader(const string & _Header);
	void SetFooter(const string & _Footer);
	void SetFooterOffset(const DWORD _FooterOffset);
	void SetMinFileSize(const DWORD _MinFileSize);
	void SetMaxFileSize(const LONGLONG _iMaxFileSize);
	void SetExtension(const wstring &_Extension);
	void SetFolderPath(const wstring &_FolderPath);

	virtual IAbstractTask * GetComposite();
	virtual void Execute(CBuffer * _pBuffer);
	virtual BOOL isReady();
	virtual void toFinish();

	virtual void Init();
	DWORD GetCount() const;
protected:
	virtual DWORD StartThread();
private:
	string ToHexString(const string & SingString);
	BOOL CreateWriter(const DWORD _FileNumber);
	void ClearWriter();
private:
	DWORD m_HeaderOffset;
	string m_sHeader;
	SignatureArray * HeaderSignature_;
	string m_sFooter;
	SignatureArray * FooterSignature_;
	DWORD m_FooterOffset;
	DWORD m_MinFileSize;
	LONGLONG m_MaxFileSize;
	wstring m_sExtension;
	DWORD m_Counter;
	wstring m_sFolderPath;
	RawState m_RawState;
	LONGLONG m_Position;
	DWORD footer_remain_;

	IWriter * m_Writer;

	//		Jar 
	//DWORD m_WriteFileSize;
	//DWORD m_CurrentWrited;
};


