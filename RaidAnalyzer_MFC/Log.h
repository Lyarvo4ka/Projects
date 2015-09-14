#pragma once
enum Command_ID {cmd_START = 0, cmd_FINISH};

class CLog
{
public:
	CLog(void);
	CLog(CString _strTestName);
	CLog(CString _strTestName, CEdit *_pEditReport);
	void AddEvent(Command_ID _commandId);
	void AddText(CString _strText);
	virtual ~CLog(void);
private:
	CString m_strTestName;
	CEdit *m_pEditReport;
	LONGLONG m_lFrom_To;
};

