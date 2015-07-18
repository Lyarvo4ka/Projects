#include "StdAfx.h"
#include "AppHistory.h"


IAppHistory::IAppHistory(void)
{
}


IAppHistory::~IAppHistory(void)
{
}

BOOL IAppHistory::ReadFromFile(CString _FileName)
{
	CStdioFile readFile;
	try 
	{
	if (readFile.Open(_FileName,CFile::modeRead))
	{
		CString ReadString = _T("");
		CString KeywordString = _T("");
		CString ValueString = _T("");
		int iPosition = 0;
		while (readFile.ReadString(ReadString))
		{
			// Skip empty line
			if (ReadString.GetLength() == 0)
				continue;

			iPosition = ReadString.Find(L"=");
			if (iPosition != -1)
			{
				KeywordString = ReadString.Left(iPosition);
				++iPosition;
				int iValuePos = ReadString.GetLength() - iPosition;
				if ( iValuePos > 0 )
					ValueString = ReadString.Right(ReadString.GetLength() - iPosition);
				else
					ValueString = L"";

				Set(KeywordString,ValueString);
			}

		}
		readFile.Close();
	}
	else
		SetDefaults();

	}
	catch (...)
	{
		TRACE("Error Read from file...\r\n");
	}
	return TRUE;
}
CString IAppHistory::PrepereString(const CString & _Keyword, const CString & _Value)
{
	CString sReturn;
	sReturn = _Keyword + L"=" + _Value + L"\n";
	return sReturn;
}
void IAppHistory::Add(const CString &_Keyword, const CString &_Value)
{
	MapKeyword::iterator it = m_Keywords.find(_Keyword);
	if ( it != m_Keywords.end() )
		it->second = _Value;
	else
		m_Keywords.insert(PairKeyword(_Keyword,_Value));
}
void IAppHistory::Set(const CString &_Keyword, const CString &_Value)
{
	Add(_Keyword,_Value);
}
CString IAppHistory::GetValue(const CString & _Keywrod) const
{
	MapKeyword::const_iterator m_constIter = m_Keywords.find(_Keywrod);
	return (m_constIter != m_Keywords.end()) ? m_constIter->second : L"";
}
