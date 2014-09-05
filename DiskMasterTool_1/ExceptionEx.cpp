//#include "StdAfx.h"
#include "ExceptionEx.h"

///////////////////////////////////////////////////////////////////////////////
// CExceptionEx
///////////////////////////////////////////////////////////////////////////////
CExceptionEx::CExceptionEx(const QString &where, const QString &message)
: m_where(where), m_message(message), m_error(0)
{
}

CExceptionEx::CExceptionEx(const QString &where, DWORD error)
: m_where(where), m_message(GetLastErrorMessage(error)), m_error(error)
{
}
CExceptionEx::~CExceptionEx()
{
}

QString CExceptionEx::GetWhere() const 
{ 
	return m_where; 
}

QString CExceptionEx::GetMessage() const 
{ 
	return m_message; 
}

DWORD CExceptionEx::GetError() const 
{ 
	return m_error; 
}

void CExceptionEx::MessageBox(HWND hWnd) const 
{
	/*wchar_t* ptrMessage;	
	wchar_t* ptrWhere;
	LPCSTR
	QString str;
	str=GetWhere();
	str.toWCharArray(ptrWhere);		
	str=GetMessage();
	str.toWCharArray(ptrMessage);
*/
	::MessageBox(hWnd, (LPCTSTR)GetMessage().utf16(), (LPCTSTR)GetWhere().utf16(), MB_ICONSTOP); 
}
