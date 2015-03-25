
#ifndef UTILITY_H
#define UTILITY_H

#include <windows.h>
#include <string>
using std::string;
using std::wstring;
#include <sstream>
using std::wstringstream;
#include "io.h"
#include <wchar.h>
#include <sys/stat.h>

namespace Utility
{
	inline wstring IntToString( int val )
	{
		wstringstream sstream;
		sstream << val;
		return sstream.str();
	}

	inline BOOL IsDots(const WIN32_FIND_DATA * pfd) 
	{ 
		BOOL bIsDots = FALSE; 

		// If it's a file directory 
		if(pfd->dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) 
		{ 
			// If the first character is a dot 
			if(pfd->cFileName[0]=='.') 
			{ 
				// And it's followed by an end-of-string 
				if(pfd->cFileName[1]== 0) 
					bIsDots = TRUE; 
				// Or if the second character is also a dot 
				else if(pfd->cFileName[1]=='.') 
				{ 
					// And it's followed by an end-of-string 
					if(pfd->cFileName[2]== 0) 
						bIsDots = TRUE; 
				} 
			} 
		} 
		return bIsDots; 
	} 

	inline BOOL isDirectoryExist(LPCTSTR _DirectoryPath)
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
	inline BOOL isDirectoryExist(LPCSTR _DirectoryPath)
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

	inline void PreperePath(const wstring &_Directory)
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

	inline void PreperePath(const string &_Directory)
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
	inline BOOL DeleteDirectory(const TCHAR* sPath) 
	{
		HANDLE hFind;    // file handle
		WIN32_FIND_DATA FindFileData;

		TCHAR DirPath[MAX_PATH];
		TCHAR FileName[MAX_PATH];

		_tcscpy(DirPath,sPath);
		_tcscat(DirPath,_T("\\*"));    // searching all files
		_tcscpy(FileName,sPath);
		_tcscat(FileName,_T("\\"));

		// find the first file
		hFind = FindFirstFile(DirPath,&FindFileData);
		if(hFind == INVALID_HANDLE_VALUE) return FALSE;
		_tcscpy(DirPath,FileName);
		TCHAR chEnd = _T('\\0');
		bool bSearch = true;
		while(bSearch) 
		{    // until we find an entry
			if(FindNextFile(hFind,&FindFileData)) 
			{
				if( IsDots(&FindFileData) == TRUE) 
					continue;

				_tcscat(FileName,FindFileData.cFileName);

				if((FindFileData.dwFileAttributes &
					FILE_ATTRIBUTE_DIRECTORY)) 
				{
					DeleteDirectory(FileName);
					// we have found a directory, recurse
					//         if(!DeleteDirectory(FileName)) 
					//{
					//             FindClose(hFind);
					//             return FALSE;    // directory couldn't be deleted
					//         }
					// remove the empty directory
					RemoveDirectory(FileName);
					_tcscpy(FileName,DirPath);
				}
				else {
					if(FindFileData.dwFileAttributes &
						FILE_ATTRIBUTE_READONLY)
						// change read-only file mode
						_chmod((const char *) FileName, _S_IWRITE);
					if(!DeleteFile(FileName)) {    // delete the file
						FindClose(hFind);
						return FALSE;
					}
					_tcscpy(FileName,DirPath);
				}
			}
			else {
				// no more files there
				if(GetLastError() == ERROR_NO_MORE_FILES)
					bSearch = false;
				else {
					// some error occurred; close the handle and return FALSE
					FindClose(hFind);
					return FALSE;
				}

			}

		}
		FindClose(hFind);                  // close the file handle

		return RemoveDirectory(sPath);     // remove the empty directory

	}

	inline CString getDirectoryPath( CString & _strWorkDirectory , UINT _iDirNumber)
	{
		CString csDirName = _T("STEP");
		CString strDirPath;
		strDirPath.Format(_T("%s%s%d"),_strWorkDirectory,csDirName,_iDirNumber);
		return strDirPath;
	}
	inline BOOL CreateStepDirectory(CString &_strDirPath)
	{
		if (!CreateDirectory(_strDirPath,NULL))
		{
			DWORD dwError = GetLastError();
			if (dwError == ERROR_PATH_NOT_FOUND)
			{
				TRACE("One or more intermediate directories do not exist\r\n");
				return FALSE;
			}
			else
				if (dwError == ERROR_ALREADY_EXISTS)
				{
					TRACE("The specified directory already exists.\r\n");
				}
		}
		return TRUE;
	}

}

#endif
// UTILITY_H