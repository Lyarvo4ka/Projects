#include "StdAfx.h"
#include "Log.h"

CLog * CLog::m_pLog = NULL;

CLog::CLog(void)
{
	m_hMonitor = INVALID_HANDLE_VALUE;
	m_LogFile = INVALID_HANDLE_VALUE;
	m_hMonitor = CreateMutex(NULL,FALSE,L"Log Monitor");
}


CLog::~CLog(void)
{
	if (m_hMonitor != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hMonitor);
		m_hMonitor = INVALID_HANDLE_VALUE;
	}
	Close();
}
CLog * CLog::GetInstance()
{
	if (m_pLog == NULL)
		m_pLog = new CLog();
	return m_pLog;
}
void CLog::Release()
{
	delete m_pLog;
	m_pLog = NULL;
}
void CLog::SetLogPath(WCHAR * _PathToLog)
{
	m_PathToLog = _PathToLog;
}
void CLog::WriteLog(string & _Text)
{
	::WaitForSingleObject(m_hMonitor,INFINITE);

	if (m_LogFile == INVALID_HANDLE_VALUE)
	{
		this->Open();
	}

	if (m_LogFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwBytesWrite = 0;
		m_sData = _Text;
		::SetFilePointer(m_LogFile,0,NULL,FILE_END);
		BOOL bResult = ::WriteFile(m_LogFile,m_sData.c_str(),m_sData.size(),&dwBytesWrite,NULL);
	}
	else
		m_sData = "Error Open Log file.\r\n";
	
	this->Notify();
	::ReleaseMutex(m_hMonitor);
}

bool CLog::Open()
{
	m_LogFile = CreateFile(m_PathToLog.c_str(),
							GENERIC_WRITE,
							FILE_SHARE_READ,
							NULL,
							OPEN_ALWAYS,
							NULL,
							NULL);
	return ( m_LogFile != INVALID_HANDLE_VALUE) ? true : false;
}
void CLog::Close()
{
	if (m_LogFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_LogFile);
		m_LogFile = INVALID_HANDLE_VALUE;
	}
}

void CLog::CreateDefaultFile()
{
	WCHAR *pCurretFolder =  GetCurrentFolder();
	m_PathToLog = pCurretFolder;
	delete pCurretFolder;
	pCurretFolder = NULL;

	if (m_PathToLog.size() > 0)
	{
		if (m_PathToLog.at(m_PathToLog.size() - 1) != L'\\' )
			m_PathToLog += L'\\';
		m_PathToLog.append(sLogName);
	}
}
const string * CLog::GetData() const
{
	return &m_sData;
}