#pragma once
#include <windows.h>

#include <string>
using std::string;
using std::wstring;

#include <algorithm>
using std::copy;

namespace Utility
{
	static BOOL isDirectoryExist(LPCTSTR _DirectoryPath)
	{
		if (!CreateDirectory(_DirectoryPath,NULL))
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_ALREADY_EXISTS)
			{
				return TRUE;
			}
			return FALSE;
		}
		return TRUE;
	}
	static BOOL isDirectoryExist(LPCSTR _DirectoryPath)
	{
		if (!CreateDirectoryA(_DirectoryPath,NULL))
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_ALREADY_EXISTS)
			{
				return TRUE;
			}
			return FALSE;
		}
		return TRUE;
	}
	static wstring DirectoryPath(const wstring &_Directory)
	{
		if (_Directory.empty())
			return L"";
		wstring sCheckDirectory(_Directory);
		if (_Directory.at(_Directory.size() -1 ) != L'\\')
		{
			sCheckDirectory += L"\\";
		}		
		return sCheckDirectory;
	}

	static wstring MakeFullPath(const wstring &_FileName,const wstring &_Directory)
	{
		if (_Directory.empty() || _FileName.empty())
		{
			return L"";
		}
		wstring sFullPath(DirectoryPath(_Directory));
		sFullPath.append(_FileName);
		return sFullPath;
	}

	static string ToString(const wstring & _String)
	{
		string strTo;
		if (_String.size() > 0)
		{
			strTo.resize(_String.size());
			//ANSI Cyrillic; Cyrillic (Windows)
			WideCharToMultiByte(1251, 0, _String.c_str(), -1, &strTo[0], strTo.size(), NULL, NULL);
		}
		return strTo;
	}

	static void PreperePath(const wstring &_Directory)
	{
		wstring sTreePath;
		size_t nPos = _Directory.find(L'\\');
		while (nPos != wstring::npos)
		{	
			sTreePath = _Directory.substr(0,++nPos);
			isDirectoryExist(sTreePath.c_str());
			nPos = _Directory.find(L'\\',nPos);
		}

	}
	static void PreperePath(const string &_Directory)
	{
		string sTreePath;
		size_t nPos = _Directory.find(L'\\');
		while (nPos != string::npos)
		{	
			sTreePath = _Directory.substr(0,++nPos);
			isDirectoryExist(sTreePath.c_str());
			nPos = _Directory.find(L'\\',nPos);
		}

	}
}