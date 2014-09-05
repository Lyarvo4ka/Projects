#pragma once
//#include "Imports.h"
#include <string>
using std::string;
using std::wstring;
#include <windows.h>
#include <list>
using std::list;
#include "Solver.h"

static const WCHAR * sLogName = L"Log.txt";

static WCHAR * GetCurrentFolder()
{
	TCHAR *lpCurrentDirectory = new TCHAR[MAX_PATH];
	ZeroMemory(lpCurrentDirectory,MAX_PATH*sizeof(TCHAR));
	GetCurrentDirectory(MAX_PATH,lpCurrentDirectory);
	return lpCurrentDirectory;
}

static wstring AddExtension(const WCHAR *_FileName,const WCHAR * _Extension)
{
	wstring sPath = _FileName;
	sPath.append(L".");
	sPath.append(_Extension);
	return sPath;
}

class DllExport CLog
	: public CSubject
{
protected:
	CLog(void);
	virtual ~CLog(void);
public:
	static CLog * GetInstance();
	void Release();
	void SetLogPath(WCHAR * _PathToLog);
	void WriteLog(string & _Text);
	bool Open();
	void Close();
	void CreateDefaultFile();
	const string * GetData() const;
private:
	static CLog * m_pLog;
	string m_sData;
	wstring m_PathToLog;
	HANDLE m_hMonitor;
	HANDLE m_LogFile;
};

