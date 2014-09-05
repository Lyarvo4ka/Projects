#include "StdAfx.h"
#include "Hashing.h"
#include "Buffer.h"
#include "Log.h"
#include <sstream>
#include <boost/lexical_cast.hpp>
using boost::lexical_cast;
#include <algorithm>
#include <iomanip>

/************************************************************************/
/*                            CMD5Hash				                    */
/************************************************************************/
CMD5Hash::CMD5Hash()
{
	m_hCryptProv = NULL;
	m_hHash = NULL;
	m_MD5Data = NULL;
	m_MD5Size = 0;
}
CMD5Hash::~CMD5Hash()
{
	if (m_MD5Data == NULL)
	{
		delete m_MD5Data;
		m_MD5Data = NULL;
	}
	m_MD5Size = 0;
	ReleaseProvider();
}

IAbstractTask * CMD5Hash::GetComposite()
{
	return NULL;
}

void CMD5Hash::Execute(CBuffer * _pBuffer)
{
	if (!CryptHashData(m_hHash,_pBuffer->GetBuffer(),_pBuffer->GetSize(),0))
	{
		m_dwResult = 0;
		return;
	}
}

BOOL CMD5Hash::isReady()
{
	if (!CreateProvider())
		return FALSE;
	return TRUE;
}
void CMD5Hash::toFinish()
{
	BOOL bResult = FALSE;
	// Get Length MD5
	DWORD Size = sizeof(DWORD);
	m_MD5Size = 0;
	bResult = CryptGetHashParam(
					m_hHash,
					HP_HASHSIZE,
					(BYTE*)&m_MD5Size,
					&Size,
					0);
	if (!bResult)
		return;

	if (m_MD5Size <= 0)
		return;

	m_MD5Data = new BYTE[m_MD5Size];
	ZeroMemory(m_MD5Data,m_MD5Size);
	bResult = FALSE;
	bResult = CryptGetHashParam(
						m_hHash,
						HP_HASHVAL,
						m_MD5Data,
						&m_MD5Size,
						0);
	CLog * pLog = CLog::GetInstance();
	string sText = "MD5 (128 bit) : ";

	std::stringstream HexStream;

	for (size_t iMd5 = 0; iMd5 < m_MD5Size; ++iMd5 )
		HexStream << std::setfill('0') <<std::setw (2) << std::hex << (int)m_MD5Data[iMd5];
	

	string sMD5(HexStream.str());
	std::transform(sMD5.begin(),sMD5.end(),sMD5.begin(),::toupper);

	sText += sMD5;
	sText += "\r\n";
	pLog->WriteLog(sText);
}
DWORD CMD5Hash::StartThread()
{
	return -1;
}

BOOL CMD5Hash::CreateProvider()
{
	ReleaseProvider();
	BOOL bResult = CryptAcquireContext(
					&m_hCryptProv,
					NULL,
					NULL,
					PROV_RSA_FULL,
					0);
	if (!bResult)
	{
		
		DWORD dwError = ::GetLastError();
		if (dwError == NTE_BAD_KEYSET)
		{
			bResult = CryptAcquireContext(
						&m_hCryptProv,
						NULL, 
						MS_DEF_PROV, 
						PROV_RSA_FULL, 
						CRYPT_NEWKEYSET);
		}

		if (!bResult)
		{
			char sErrorNumber[100];
			ZeroMemory(sErrorNumber,10*sizeof(char));
			sprintf_s(sErrorNumber,100,"%d",dwError);
			string sErrorString(sErrorNumber);
			m_sError = "Acquisition of context failed.\r\n";
			m_sError += "Error code(" + sErrorString + ").\r\n";
			return FALSE;
		}
	}

	bResult = CryptCreateHash( 
				m_hCryptProv,	// Дескриптор к CSP полученный ранее
				CALG_MD5,		// Алгоритм хэширования
				0, 
				0,				// Должен быть нулем!
				&m_hHash);		// Переменная для хранения дескриптора 
	

	if (!bResult)
	{
		m_sError = "Error during CryptBeginHash!\r\n";
		return FALSE;
	}

	return TRUE;
}

void CMD5Hash::ReleaseProvider()
{
	if(m_hHash) 
		CryptDestroyHash(m_hHash);
	if(m_hCryptProv) 
		CryptReleaseContext(m_hCryptProv,0);
}


/************************************************************************/
/*                            CSHA1Hash				                    */
/************************************************************************/

CSHA1Hash::CSHA1Hash()
{
	m_hCryptProv = NULL;
	m_hHash = NULL;
	m_SHA1Data = NULL;
	m_SHA1Size = 0;
}
CSHA1Hash::~CSHA1Hash()
{
	if (m_SHA1Data == NULL)
	{
		delete m_SHA1Data;
		m_SHA1Data = NULL;
	}
	m_SHA1Size = 0;
	ReleaseProvider();
}

IAbstractTask * CSHA1Hash::GetComposite()
{
	return NULL;
}

void CSHA1Hash::Execute(CBuffer * _pBuffer)
{
	if (!CryptHashData(m_hHash,_pBuffer->GetBuffer(),_pBuffer->GetSize(),0))
	{
		m_dwResult = 0;
		return;
	}
}

BOOL CSHA1Hash::isReady()
{
	if (!CreateProvider())
		return FALSE;
	return TRUE;
}
void CSHA1Hash::toFinish()
{
	BOOL bResult = FALSE;
	// Get Length MD5
	DWORD Size = sizeof(DWORD);
	m_SHA1Size = 0;
	bResult = CryptGetHashParam(
					m_hHash,
					HP_HASHSIZE,
					(BYTE*)&m_SHA1Size,
					&Size,
					0);
	if (!bResult)
		return;

	if (m_SHA1Size <= 0)
		return;

	m_SHA1Data = new BYTE[m_SHA1Size];
	ZeroMemory(m_SHA1Data,m_SHA1Size);
	bResult = FALSE;
	bResult = CryptGetHashParam(
					m_hHash,
					HP_HASHVAL,
					m_SHA1Data,
					&m_SHA1Size,
					0);
	CLog * pLog = CLog::GetInstance();
	string sText = "SHA1 (160 bit) : ";

	std::stringstream HexStream;

	for (size_t iSha1 = 0; iSha1 < m_SHA1Size; ++iSha1 )
		HexStream << std::setfill('0') << std::setw (2) << std::hex << (int)m_SHA1Data[iSha1];


	string sSha1(HexStream.str());
	std::transform(sSha1.begin(),sSha1.end(),sSha1.begin(),::toupper);
	sText += sSha1;
	sText += "\r\n";
	pLog->WriteLog(sText);


}
DWORD CSHA1Hash::StartThread()
{
	return -1;
}

BOOL CSHA1Hash::CreateProvider()
{
	ReleaseProvider();
	BOOL bResult = CryptAcquireContext(
		&m_hCryptProv,
		NULL,
		NULL,
		PROV_RSA_FULL,
		0);
	if (!bResult)
	{
		m_sError = "Acquisition of context failed.\r\n";
		return FALSE;
	}

	bResult = CryptCreateHash( 
		m_hCryptProv,	// Дескриптор к CSP полученный ранее
		CALG_SHA1,		// Алгоритм хэширования
		0, 
		0,				// Должен быть нулем!
		&m_hHash);		// Переменная для хранения дескриптора 


	if (!bResult)
	{
		m_sError = "Error during CryptBeginHash!\r\n";
		return FALSE;
	}

	return TRUE;
}

void CSHA1Hash::ReleaseProvider()
{
	if(m_hHash) 
		CryptDestroyHash(m_hHash);
	if(m_hCryptProv) 
		CryptReleaseContext(m_hCryptProv,0);
}

/************************************************************************/
/*                            CSHA256Hash				                    */
/************************************************************************/

CSHA256Hash::CSHA256Hash()
{
	m_hCryptProv = NULL;
	m_hHash = NULL;
	m_SHA256Data = NULL;
	m_SHA256Size = 0;
}
CSHA256Hash::~CSHA256Hash()
{
	if (m_SHA256Data == NULL)
	{
		delete m_SHA256Data;
		m_SHA256Data = NULL;
	}
	m_SHA256Size = 0;
	ReleaseProvider();
}

IAbstractTask * CSHA256Hash::GetComposite()
{
	return NULL;
}

void CSHA256Hash::Execute(CBuffer * _pBuffer)
{
	if (!CryptHashData(m_hHash,_pBuffer->GetBuffer(),_pBuffer->GetSize(),0))
	{
		m_dwResult = 0;
		return;
	}
}

BOOL CSHA256Hash::isReady()
{
	if (!CreateProvider())
		return FALSE;
	return TRUE;
}
void CSHA256Hash::toFinish()
{
	BOOL bResult = FALSE;
	// Get Length MD5
	DWORD Size = sizeof(DWORD);
	m_SHA256Size = 0;
	bResult = CryptGetHashParam(
		m_hHash,
		HP_HASHSIZE,
		(BYTE*)&m_SHA256Size,
		&Size,
		0);
	if (!bResult)
		return;

	if (m_SHA256Size <= 0)
		return;

	m_SHA256Data = new BYTE[m_SHA256Size];
	ZeroMemory(m_SHA256Data,m_SHA256Size);
	bResult = FALSE;
	bResult = CryptGetHashParam(
		m_hHash,
		HP_HASHVAL,
		m_SHA256Data,
		&m_SHA256Size,
		0);
	CLog * pLog = CLog::GetInstance();
	string sText = "SHA256 (256 bit) : ";

	std::stringstream HexStream;

	for (size_t iSha256 = 0; iSha256 < m_SHA256Size; ++iSha256 )
		HexStream << std::setfill('0') << std::setw (2) << std::hex << (int)m_SHA256Data[iSha256];


	string sSha256(HexStream.str());
	std::transform(sSha256.begin(),sSha256.end(),sSha256.begin(),::toupper);
	sText += sSha256;
	sText += "\r\n";
	pLog->WriteLog(sText);


}
DWORD CSHA256Hash::StartThread()
{
	return -1;
}

BOOL CSHA256Hash::CreateProvider()
{
	ReleaseProvider();
	BOOL bResult = CryptAcquireContext(
		&m_hCryptProv,
		NULL,
		NULL,
		PROV_RSA_AES,
		0);
	if (!bResult)
	{
		m_sError = "Acquisition of context failed.\r\n";
		return FALSE;
	}

	bResult = CryptCreateHash( 
		m_hCryptProv,	// Дескриптор к CSP полученный ранее
		CALG_SHA_256,		// Алгоритм хэширования
		0, 
		0,				// Должен быть нулем!
		&m_hHash);		// Переменная для хранения дескриптора 

 	if (!bResult)
	{
		DWORD dwError = ::GetLastError();
		//NTE_BAD_ALGID

		m_sError = "Error during CryptBeginHash!\r\n";
		return FALSE;
	}

	return TRUE;
}

void CSHA256Hash::ReleaseProvider()
{
	if(m_hHash) 
		CryptDestroyHash(m_hHash);
	if(m_hCryptProv) 
		CryptReleaseContext(m_hCryptProv,0);
}