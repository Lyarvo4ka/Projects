#include "FT245R.h"

FT245R::FT245R()
//: m_iocp(0)
{
	m_hChipNotify = NULL;
	m_hOwner = NULL;
	//StartThread();
}

FT245R::~FT245R()
{
	StopNotification();
	PostRequest(NULL);
	WaitThreadShutdown();
}

BOOL FT245R::StartNotification(HWND hOwner, CString strSignature, BOOL bOnlyConnectEvent)
{
	DEV_BROADCAST_DEVICEINTERFACE	NotificationFilter;

	ASSERT(IsWindow(hOwner));
	m_hOwner = hOwner;
	ZeroMemory(&NotificationFilter, sizeof(NotificationFilter));
	NotificationFilter.dbcc_size =  sizeof(DEV_BROADCAST_DEVICEINTERFACE);
	NotificationFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	m_hChipNotify = ::RegisterDeviceNotification(m_hOwner, &NotificationFilter, DEVICE_NOTIFY_WINDOW_HANDLE|DEVICE_NOTIFY_ALL_INTERFACE_CLASSES);
//	if (m_hChipNotify) m_threadUpdateList.FirstStart(this, strSignature.MakeUpper(), bOnlyConnectEvent);
	return (m_hChipNotify != NULL);
}

void FT245R::StopNotification()
{
	m_hOwner = NULL;
	if (m_hChipNotify)
	{
		::UnregisterDeviceNotification(m_hChipNotify);
		m_hChipNotify = NULL;
	}
	m_threadUpdateList.Stop();
	m_mapUsedChips.RemoveAll();
}

void FT245R::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!m_hChipNotify) return;
	if (message != WM_DEVICECHANGE || m_hChipNotify == NULL) return;
	if (wParam != DBT_DEVICEARRIVAL && wParam != DBT_DEVICEREMOVECOMPLETE) return;
	if (lParam == NULL) return;

	PDEV_BROADCAST_DEVICEINTERFACE	pInterface = (PDEV_BROADCAST_DEVICEINTERFACE)lParam;
	CString							strDeviceDescription = pInterface->dbcc_name;

	strDeviceDescription.MakeUpper();
	if (strDeviceDescription.Find(VID_PID_STRING) == -1) return;
	m_threadUpdateList.Start();
}

int FT245R::Run()
{
	return 0;	
}
