#include "StdAfx.h"
#include "RawCreater.h"

#include "Utilities.h"
#include "Declaration.h"

#include <sstream>
#include <iomanip>

#include <vector>
using std::vector;

#include "Buffer.h"
#include "Writer.h"
#include "Devices.h"
#include "AbstractFactory.h"

#include "Updater.h"

CFinishObserver::CFinishObserver(const HWND & _hWnd)
	: m_hWnd(_hWnd)
{

}
void CFinishObserver::Update(CSubject * _pSubject)
{
	::PostMessage(m_hWnd, DefaultMsg::FinishMessage, NULL, NULL);
}
CCountFound::CCountFound(const HWND & _hWnd)
	: m_hWnd(_hWnd)
{

}
void CCountFound::Update(CSubject * _pSubject)
{
	CRawCreater * pRawCreater = (CRawCreater *) _pSubject;
	::SendMessage(m_hWnd, FoundCounts, NULL, (LPARAM) pRawCreater->GetCount());
}
