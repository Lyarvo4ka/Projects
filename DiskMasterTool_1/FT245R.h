#include <QtCore>

#ifndef FT245R_H
#define FT245R_H



class FT245R : public QThread
{

private:
	HDEVNOTIFY			m_hChipNotify;
	HWND				m_hOwner;
	//CUpdateListThread	m_threadUpdateList;
	//CIOCompletionPort	m_iocp;
	//CMapUlongToChip		m_mapUsedChips;

public:

	FT245R();
	~FT245R();
		
	BOOL StartNotification(HWND hOwner, QString strSignature, BOOL bOnlyConnectEvent = FALSE);
	void StopNotification();
	void WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	int Run();
};

#endif