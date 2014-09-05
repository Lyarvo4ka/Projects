#include <QString>
#include "windows.h"

#pragma once

class CExceptionEx
{
protected:
    const QString	m_where;
    const QString	m_message;
	const DWORD		m_error;

public:
	CExceptionEx(const QString &where, const QString &message);
	CExceptionEx(const QString &where, DWORD error);
	~CExceptionEx();
    QString GetWhere() const;
    QString GetMessage() const;
	DWORD GetError() const;
    void MessageBox(HWND hWnd = NULL) const;
};

//////////////////////////////////////////////////////////////////////////////////////////
// Static helper methods
//////////////////////////////////////////////////////////////////////////////////////////
static QString GetLastErrorMessage(DWORD last_error)
{
	QString			strError;
	static TCHAR	errorBuffer[512];
	if (!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, last_error, 0, errorBuffer, 511, NULL))
	{
		// if we fail, call ourself to find out why and return that error
		return GetLastErrorMessage(GetLastError());
	}
	return QString(QString::fromWCharArray(errorBuffer));
}
