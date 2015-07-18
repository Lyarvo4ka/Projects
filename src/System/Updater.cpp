// Updater.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Updater.h"
#include "Log.h"
#include "Reader.h"


/************************************************************************/
/*                       CProgressObserver                              */
/************************************************************************/
CProgressObserver::CProgressObserver(const HWND & _hWnd, const LONGLONG & _lProgressSize)
	: m_hWnd (_hWnd) , m_UpdateSize (_lProgressSize)
{
	m_Counter = 0;
}
CProgressObserver::~CProgressObserver()
{

}
void CProgressObserver::Update(CSubject *_pSubject)
{
	if (++m_Counter >= m_UpdateSize)
	{
		m_Counter = 0;
		::PostMessage(m_hWnd , DefaultMsg::UpdateProgress , NULL , NULL);
	}
}

/************************************************************************/
/*                        CSpeedObserver                                */
/************************************************************************/

CSpeedObserver::CSpeedObserver(const HWND & _hWnd, DWORD _UpdateRate)
	:m_hWnd(_hWnd), m_UpdateRate(_UpdateRate)
{
	m_Counter = 0;
	m_LastTime = ::GetCurrentTime();
}
CSpeedObserver::~CSpeedObserver()
{

}

void CSpeedObserver::Update(CSubject *_pSubject)
{
	if (++m_Counter >= m_UpdateRate)
	{
		m_Counter = 0;
		DWORD dwCurrentTime = ::GetCurrentTime();
		::PostMessage(m_hWnd , DefaultMsg::UpdateSpeed , (LPARAM) (dwCurrentTime - m_LastTime) , NULL);
		m_LastTime = dwCurrentTime;
	}
}
/************************************************************************/
/*                        CErrorObserver                                */
/************************************************************************/
CErrorObserver::CErrorObserver(const HWND & _hWnd)
	:m_hWnd(_hWnd)
{

}

CErrorObserver::~CErrorObserver()
{

}
void CErrorObserver::Update(CSubject *_pSubject)
{
	IAbstractTask * pAbstractTask = dynamic_cast<IAbstractTask *> (_pSubject );

	::SendMessage(m_hWnd , DefaultMsg::SendError , NULL , (LPARAM)pAbstractTask->GetErrorString());
}
/************************************************************************/
/*                        CEndObserver                                  */
/************************************************************************/
CEndObserver::CEndObserver(const HWND & _hWnd)
	:m_hWnd(_hWnd)
{

}

CEndObserver::~CEndObserver()
{

}
void CEndObserver::Update(CSubject *_pSubject)
{
	CTaskManager * pTaskManager = dynamic_cast<CTaskManager*>(_pSubject);
	EndResult EndRes;
	EndRes.SectorsCopied = *pTaskManager->GetCopiedSectors();
	EndRes.BadSectors = * pTaskManager->GetBadSectors();
	EndRes.BadSectors = *pTaskManager->GetBadSectors();
	if (!pTaskManager->GetForceExit())
		::SendMessage(m_hWnd , DefaultMsg::FinishMessage , NULL , (LPARAM)&EndRes);
}
/************************************************************************/
/*                        CLogObserver				                    */
/************************************************************************/

CLogObserver::CLogObserver(const HWND & _hWnd)
	: m_hWnd(_hWnd)
{

}
CLogObserver::~CLogObserver()
{

}
void CLogObserver::Update(CSubject * _pSubject)
{
	CLog * pLog = static_cast<CLog*> (_pSubject);
	::SendMessage(m_hWnd,DefaultMsg::SendLog,NULL,(LPARAM) pLog->GetData());
}

/************************************************************************/
/*                        CReaderObserver				                */
/************************************************************************/
CReaderObserver::CReaderObserver(const HWND & _hWnd)
	: m_hWnd(_hWnd)
{

}
CReaderObserver::~CReaderObserver()
{

}
void CReaderObserver::Update(CSubject *_pSubject)
{
	CReaderConsistent * pConsistentReader = static_cast<CReaderConsistent*>(_pSubject);
	::SendMessage(m_hWnd , DefaultMsg::UpdateLBA , NULL , (LPARAM) pConsistentReader->GetCurrentLBA());
}

/************************************************************************/
/*                        CReaderErrorObserver				            */
/************************************************************************/
CReaderErrorObserver::CReaderErrorObserver(const HWND & _hWnd)
	: m_hWnd(_hWnd)
{

}
CReaderErrorObserver::~CReaderErrorObserver()
{

}
void CReaderErrorObserver::Update(CSubject *_pSubject)
{
	CReaderConsistent * pConsistentReader = static_cast<CReaderConsistent*>(_pSubject);
	//string str(pConsistentReader->GetErrorString());
	::SendMessage(m_hWnd , DefaultMsg::ReadError , NULL , (LPARAM) pConsistentReader->GetErrorString().c_str());
}

