#pragma once

#include "Imports.h"
#include "Concurrent.h"
#include "Solver.h"
#include "Writer.h"
#include "Definitions.h"
#include <Wincrypt.h>
#pragma comment(lib, "Advapi32.lib")

class CBuffer;


//////////////////////////////////////// MD5 (128 bit) //////////////////////////////////
class DllExport CMD5Hash
	: public IAbstractTask 
{
public:
	CMD5Hash();
	virtual ~CMD5Hash();
	virtual IAbstractTask * GetComposite() ;
	virtual void Execute(CBuffer * _pBuffer) ;
	virtual BOOL isReady() ;
	void toFinish();
protected:
	virtual DWORD StartThread();
private:
	BOOL CreateProvider();
	void ReleaseProvider();
	HCRYPTPROV m_hCryptProv;
	HCRYPTHASH m_hHash;
	BYTE *m_MD5Data;
	DWORD m_MD5Size;
};

//////////////////////////////////////// SHA1 (160 bit) //////////////////////////////////
class DllExport CSHA1Hash
	: public IAbstractTask 
{
public:
	CSHA1Hash();
	virtual ~CSHA1Hash();
	virtual IAbstractTask * GetComposite() ;
	virtual void Execute(CBuffer * _pBuffer) ;
	virtual BOOL isReady() ;
	void toFinish();
protected:
	virtual DWORD StartThread();
private:
	BOOL CreateProvider();
	void ReleaseProvider();
	HCRYPTPROV m_hCryptProv;
	HCRYPTHASH m_hHash;
	BYTE *m_SHA1Data;
	DWORD m_SHA1Size;
};

//////////////////////////////////////// SHA256 (256 bit) //////////////////////////////////
class DllExport CSHA256Hash
	: public IAbstractTask 
{
public:
	CSHA256Hash();
	virtual ~CSHA256Hash();
	virtual IAbstractTask * GetComposite() ;
	virtual void Execute(CBuffer * _pBuffer) ;
	virtual BOOL isReady() ;
	void toFinish();
protected:
	virtual DWORD StartThread();
private:
	BOOL CreateProvider();
	void ReleaseProvider();
	HCRYPTPROV m_hCryptProv;
	HCRYPTHASH m_hHash;
	BYTE *m_SHA256Data;
	DWORD m_SHA256Size;
};

