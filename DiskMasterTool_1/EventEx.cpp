//#include "StdAfx.h"
#include "EventEx.h"
#include "ExceptionEx.h"

using namespace voidrealms::win32;


//////////////////////////////////////////////////////////////////////////////////////////
// QEventEx
//////////////////////////////////////////////////////////////////////////////////////////
QEventEx::QEventEx(bool bManualReset, bool bInitialState, const QString name)
: m_hEvent(::CreateEvent(NULL, bManualReset, bInitialState, (LPCTSTR)name.utf16()))
{
}

QEventEx::~QEventEx()
{
	::CloseHandle(m_hEvent);
}

HANDLE QEventEx::GetEvent() const
{
	return m_hEvent;
}

void QEventEx::ResetEvent()
{
	if (!::ResetEvent(m_hEvent))
	{
		throw CExceptionEx("ResetEvent()", ::GetLastError());
	}
}

void QEventEx::SetEvent()
{
	if (!::SetEvent(m_hEvent))
	{
		throw CExceptionEx("SetEvent()", ::GetLastError());
	}
}

void QEventEx::PulseEvent()
{
	if (!::PulseEvent(m_hEvent))
	{
		throw CExceptionEx("PulseEvent()", ::GetLastError());
	}
}

bool QEventEx::WaitEvent(DWORD timeoutMillis) const
{
	bool ret = false;
	switch (::WaitForSingleObject(m_hEvent, timeoutMillis))
	{
		case WAIT_OBJECT_0:
			ret = true;
			break;
		case WAIT_TIMEOUT:
			if (timeoutMillis == INFINITE)
			{
				throw CExceptionEx("WaitEvent()", "Timeout on infinite wait");
			}
			break;
		default:
			throw CExceptionEx("WaitEvent()", ::GetLastError());
			break;
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////
// QAutoResetEvent
//////////////////////////////////////////////////////////////////////////////////////////
QAutoResetEvent::QAutoResetEvent(bool initialState, const QString name)
: QEventEx(false, initialState, name)
{   
}

//////////////////////////////////////////////////////////////////////////////////////////
// QManualResetEvent
//////////////////////////////////////////////////////////////////////////////////////////
QManualResetEvent::QManualResetEvent(bool initialState, const QString name)
: QEventEx(true, initialState, name)
{   
}
