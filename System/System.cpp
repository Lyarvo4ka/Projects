// System.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "System.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString System::CurTimeToStr()
{
	CTime cTime =  CTime::GetCurrentTime();
	CString sTime = _T("");
	sTime.Format(_T(" ( %i.%02i.%02i %02i:%02i:%02i  ) \r\n"),
		cTime.GetYear(),
		cTime.GetMonth(),
		cTime.GetDay(),
		cTime.GetHour(),
		cTime.GetMinute(),
		cTime.GetSecond()
		);
	return sTime;
}
string System::GetSystemDate()
{
	CTime cTime =  CTime::GetCurrentTime();
	CStringA sTime = "";
	sTime.Format("%i %02i %02i %02i %02i %02i",
		cTime.GetYear(),
		cTime.GetMonth(),
		cTime.GetDay(),
		cTime.GetHour(),
		cTime.GetMinute(),
		cTime.GetSecond()
		);
	string retStr = sTime.GetBuffer();
	return retStr;
}
string System::ToString(CString &_WideStr)
{

	string strTo;
	if (_WideStr.GetLength() > 0)
	{
		strTo.resize(_WideStr.GetLength());
		WideCharToMultiByte(CP_ACP, 0, _WideStr, -1, &strTo[0], strTo.size(), NULL, NULL);
	}
	return strTo;
}

string System::GetProgramVersion(DWORD _Version, DWORD _Subversion)
{
	string str;
	char buffer[10];
	sprintf_s(buffer,10,"%d.%d",_Version,_Subversion);
	str.append(buffer);
	return str;
}

CString System::GetCurrentDir()
{
	TCHAR lpCurrentDirectory[MAX_PATH];
	ZeroMemory(lpCurrentDirectory,MAX_PATH*sizeof(TCHAR));
	GetCurrentDirectory(MAX_PATH,lpCurrentDirectory);
	CString strCurrentDir(lpCurrentDirectory);
	return strCurrentDir;
}
CString System::PrepereDirectory(const CString &_Directory)
{
	CString sResult(_Directory);
	if (sResult.GetLength() > 0 )
	{
		if (sResult.GetAt(sResult.GetLength() - 1) != L'\\')
			sResult.Append(L"\\");
	}
	return sResult;
}
CString System::MakeFilePath(const CString &_Directory, const CString &_FileName, const CString &_Extesion)
{
	CString sResult( PrepereDirectory(_Directory) );
	sResult.Append(_FileName);
	sResult.Append(L".");
	sResult.Append(_Extesion);
	return sResult;
}
BOOL System::GetPlatformOS(LPTSTR pszOS)
{
	OSVERSIONINFOEX osvi;
	SYSTEM_INFO si;
	PGNSI pGNSI;
	PGPI pGPI;
	BOOL bOsVersionInfoEx;
	DWORD dwType;

	ZeroMemory(&si, sizeof(SYSTEM_INFO));
	ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*) &osvi);

	if(bOsVersionInfoEx == 0 ) 
	{
		DWORD dwError = GetLastError();

		return FALSE;
	}

	// Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.

	pGNSI = (PGNSI) GetProcAddress(
		GetModuleHandle(TEXT("kernel32.dll")), 
		"GetNativeSystemInfo");
	if(NULL != pGNSI)
		pGNSI(&si);
	else GetSystemInfo(&si);

	if ( VER_PLATFORM_WIN32_NT==osvi.dwPlatformId && 
		osvi.dwMajorVersion > 4 )
	{
		StringCchCopy(pszOS, BUFSIZE, TEXT("Microsoft "));

		// Test for the specific product.

		if ( osvi.dwMajorVersion == 6 )
		{
			if( osvi.dwMinorVersion == 0 )
			{
				if( osvi.wProductType == VER_NT_WORKSTATION )
					StringCchCat(pszOS, BUFSIZE, TEXT("Windows Vista "));
				else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2008 " ));
			}

			if ( osvi.dwMinorVersion == 1 )
			{
				if( osvi.wProductType == VER_NT_WORKSTATION )
					StringCchCat(pszOS, BUFSIZE, TEXT("Windows 7 "));
				else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2008 R2 " ));
			}

			pGPI = (PGPI) GetProcAddress(
				GetModuleHandle(TEXT("kernel32.dll")), 
				"GetProductInfo");

			pGPI( osvi.dwMajorVersion, osvi.dwMinorVersion, 0, 0, &dwType);

			switch( dwType )
			{
			case PRODUCT_ULTIMATE:
				StringCchCat(pszOS, BUFSIZE, TEXT("Ultimate Edition" ));
				break;
			case PRODUCT_PROFESSIONAL:
				StringCchCat(pszOS, BUFSIZE, TEXT("Professional" ));
				break;
			case PRODUCT_HOME_PREMIUM:
				StringCchCat(pszOS, BUFSIZE, TEXT("Home Premium Edition" ));
				break;
			case PRODUCT_HOME_BASIC:
				StringCchCat(pszOS, BUFSIZE, TEXT("Home Basic Edition" ));
				break;
			case PRODUCT_ENTERPRISE:
				StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition" ));
				break;
			case PRODUCT_BUSINESS:
				StringCchCat(pszOS, BUFSIZE, TEXT("Business Edition" ));
				break;
			case PRODUCT_STARTER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Starter Edition" ));
				break;
			case PRODUCT_CLUSTER_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Cluster Server Edition" ));
				break;
			case PRODUCT_DATACENTER_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Datacenter Edition" ));
				break;
			case PRODUCT_DATACENTER_SERVER_CORE:
				StringCchCat(pszOS, BUFSIZE, TEXT("Datacenter Edition (core installation)" ));
				break;
			case PRODUCT_ENTERPRISE_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition" ));
				break;
			case PRODUCT_ENTERPRISE_SERVER_CORE:
				StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition (core installation)" ));
				break;
			case PRODUCT_ENTERPRISE_SERVER_IA64:
				StringCchCat(pszOS, BUFSIZE, TEXT("Enterprise Edition for Itanium-based System" ));
				break;
			case PRODUCT_SMALLBUSINESS_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Small Business Server" ));
				break;
			case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
				StringCchCat(pszOS, BUFSIZE, TEXT("Small Business Server Premium Edition" ));
				break;
			case PRODUCT_STANDARD_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Standard Edition" ));
				break;
			case PRODUCT_STANDARD_SERVER_CORE:
				StringCchCat(pszOS, BUFSIZE, TEXT("Standard Edition (core installation)" ));
				break;
			case PRODUCT_WEB_SERVER:
				StringCchCat(pszOS, BUFSIZE, TEXT("Web Server Edition" ));
				break;
			}
		}

		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
		{
			if( GetSystemMetrics(SM_SERVERR2) )
				StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Server 2003 R2, "));
			else if ( osvi.wSuiteMask & VER_SUITE_STORAGE_SERVER )
				StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Storage Server 2003"));
			else if ( osvi.wSuiteMask & VER_SUITE_WH_SERVER )
				StringCchCat(pszOS, BUFSIZE, TEXT( "Windows Home Server"));
			else if( osvi.wProductType == VER_NT_WORKSTATION &&
				si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
			{
				StringCchCat(pszOS, BUFSIZE, TEXT( "Windows XP Professional x64 Edition"));
			}
			else StringCchCat(pszOS, BUFSIZE, TEXT("Windows Server 2003, "));

			// Test for the server type.
			if ( osvi.wProductType != VER_NT_WORKSTATION )
			{
				if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_IA64 )
				{
					if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Edition for Itanium-based System" ));
					else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise Edition for Itanium-based System" ));
				}

				else if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
				{
					if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter x64 Edition" ));
					else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise x64 Edition" ));
					else StringCchCat(pszOS, BUFSIZE, TEXT( "Standard x64 Edition" ));
				}

				else
				{
					if ( osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Compute Cluster Edition" ));
					else if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Edition" ));
					else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Enterprise Edition" ));
					else if ( osvi.wSuiteMask & VER_SUITE_BLADE )
						StringCchCat(pszOS, BUFSIZE, TEXT( "Web Edition" ));
					else StringCchCat(pszOS, BUFSIZE, TEXT( "Standard Edition" ));
				}
			}
		}

		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
		{
			StringCchCat(pszOS, BUFSIZE, TEXT("Windows XP "));
			if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
				StringCchCat(pszOS, BUFSIZE, TEXT( "Home Edition" ));
			else StringCchCat(pszOS, BUFSIZE, TEXT( "Professional" ));
		}

		if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
		{
			StringCchCat(pszOS, BUFSIZE, TEXT("Windows 2000 "));

			if ( osvi.wProductType == VER_NT_WORKSTATION )
			{
				StringCchCat(pszOS, BUFSIZE, TEXT( "Professional" ));
			}
			else 
			{
				if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
					StringCchCat(pszOS, BUFSIZE, TEXT( "Datacenter Server" ));
				else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
					StringCchCat(pszOS, BUFSIZE, TEXT( "Advanced Server" ));
				else StringCchCat(pszOS, BUFSIZE, TEXT( "Server" ));
			}
		}

		// Include service pack (if any) and build number.

		if( _tcslen(osvi.szCSDVersion) > 0 )
		{
			StringCchCat(pszOS, BUFSIZE, TEXT(" ") );
			StringCchCat(pszOS, BUFSIZE, osvi.szCSDVersion);
		}

		TCHAR buf[80];

		StringCchPrintf( buf, 80, TEXT(" (build %d)"), osvi.dwBuildNumber);
		StringCchCat(pszOS, BUFSIZE, buf);

		if ( osvi.dwMajorVersion >= 6 )
		{
			if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
				StringCchCat(pszOS, BUFSIZE, TEXT( ", 64-bit" ));
			else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
				StringCchCat(pszOS, BUFSIZE, TEXT(", 32-bit"));
		}

		return TRUE; 
	}

	else
	{  
		return FALSE;
	}
}

string System::GetPlatform()
{
	string str = "Windows";
	TCHAR szOS[BUFSIZE];
	if (System::GetPlatformOS(szOS))
	{
		CString strPlatform = szOS;
		str = ToString(strPlatform);
	}
	return str;
}
bool System::IsFileExists(const CString & sFileName)
{
	HANDLE hExistsFile = INVALID_HANDLE_VALUE;
	hExistsFile = ::CreateFile(
		sFileName, // file (or device) name
		0, // query access only
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, // share mode
		NULL, // security attributes
		OPEN_EXISTING, // disposition
		FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN, // flags & attributes
		NULL // template file
		);
	if (INVALID_HANDLE_VALUE != hExistsFile)
	{
		::CloseHandle(hExistsFile);
		return true;
	}
	return false;
}
System::CFileNames::CFileNames()
{

}
System::CFileNames::CFileNames(const CString & _FilePath)
	: m_FilePath(_FilePath)
{

}
System::CFileNames::~CFileNames(void)
{

}
void System::CFileNames::Parse(const CString & _FilePath)
{
	Clear();
	m_FilePath = _FilePath;
	Execute();
}
void System::CFileNames::Execute()
{
	int nFilePos= m_FilePath.ReverseFind('\\');
	if (nFilePos != -1)
	{
		++nFilePos;
		m_FolderName = m_FilePath.Left(nFilePos);

		CString sFileName( m_FilePath.Right(m_FilePath.GetLength() - nFilePos) );

		int nExtPos = sFileName.ReverseFind(L'.');
		if (nExtPos != -1)
		{
			m_FileName = sFileName.Left(nExtPos);
			m_Extension = sFileName.Right(sFileName.GetLength() - ++nExtPos);
		}
		else
		{
			m_FileName = sFileName;
			m_Extension = L"";
		}
		m_bCorrect = true;
	}
	else
		Clear();
}
bool System::CFileNames::isCorrect()
{
	return m_bCorrect;
}
void System::CFileNames::Clear()
{
	m_FilePath = L"";
	m_bCorrect = false;
	m_FileName = L"";
	m_FolderName = L"";
	m_Extension = L"";
}

CString System::CFileNames::GetFolder() const
{
	return m_FolderName;
}
CString System::CFileNames::GetName() const
{
	return m_FileName;
}
CString System::CFileNames::GetExtension() const
{
	return m_Extension;
}






CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
