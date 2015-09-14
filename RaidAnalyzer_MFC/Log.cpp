#include "StdAfx.h"
#include "Log.h"


CLog::CLog(void)
	:m_pEditReport(NULL),m_strTestName(_T("")),m_lFrom_To(0)
{
}

CLog::CLog(CString _strTestName)
	:m_strTestName(_strTestName)
{
}
CLog::CLog(CString _strTestName, CEdit *_pEditReport)
	:m_strTestName(_strTestName), m_pEditReport(_pEditReport)
{
}

CLog::~CLog(void)
{
}

void CLog::AddEvent(Command_ID _commandId)
{
	CString strText = _T("");
	if (m_pEditReport != NULL)
	{
	switch (_commandId)
	{
	case cmd_START:
		strText.Format(_T("Starting (%s) ...\r\n"),m_strTestName);
		m_pEditReport->ReplaceSel(strText);
		break;
	case cmd_FINISH:
		strText.Format(_T("\r\nFinish (%s)...\r\n"),m_strTestName);
		m_pEditReport->ReplaceSel(strText);
		break;
	};
	}
	else
		TRACE(_T("Error Address pointer CEdit in CLog (func AddEvent"));
}

void CLog::AddText(CString _strText)
{
	if (m_pEditReport != NULL)
		m_pEditReport->ReplaceSel(_strText);
}
