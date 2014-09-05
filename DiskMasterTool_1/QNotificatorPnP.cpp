//#include "stdafx.h"
#include "QNotificatorPnP.h"
#include <process.h>
#include <dbt.h>

#define INTERNAL_WAIT_TIMEOUT	10000

static const WCHAR strWndClass[] = L"QNotificatorPnP_WndClass";
static const WCHAR strWndTitle[] = L"QNotificatorPnP_WndTitle";
//static const GUID GUID_FT245R = {0x219D0508, 0x57A8, 0x4FF5, {0x97, 0xA1, 0xBD, 0x86, 0x58, 0x7C, 0x6C, 0x7E}};
QNotificatorPnP::QNotificatorPnP()
{
	m_bInitialized = false;
	m_hWnd = NULL;
	::InitializeCriticalSection(&m_CritSect);
	::EnterCriticalSection(&m_CritSect);
	m_hThreadReadyEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);	// create manual reset event
	// create our worker thread
	unsigned int tid;
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, BeginThread, this, 0, &tid );
	if (m_hThread != NULL)
	{	// wait until worker thread has finished initialization we use a timeout of 10 seconds
		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hThreadReadyEvent, INTERNAL_WAIT_TIMEOUT)) m_bInitialized = true;
	}
	::CloseHandle(m_hThreadReadyEvent);	// destroy event, it's no longer needed
	m_hThreadReadyEvent = NULL;
	::LeaveCriticalSection(&m_CritSect);
}

QNotificatorPnP::~QNotificatorPnP()
{
	::EnterCriticalSection(&m_CritSect);
	if (m_bInitialized && (m_hThread != NULL))
	{	// terminate worker thread
		if (m_hWnd != NULL) ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
		::WaitForSingleObject(m_hThread, INTERNAL_WAIT_TIMEOUT);
		::CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	// Delete All Notification Records
	while (!m_listNotification.isEmpty())
	{
		UnregisterNotification(m_listNotification.takeFirst());
	}
	::LeaveCriticalSection(&m_CritSect);
	::DeleteCriticalSection(&m_CritSect);
}

// thread routine called by C runtime, static
unsigned int __stdcall QNotificatorPnP::BeginThread(void* pStartContext)
{
	QNotificatorPnP* pThis = (QNotificatorPnP*)pStartContext;
	return pThis->ThreadRoutine();	// call member function, returning from there terminates the thread
}

// worker thread main routine
unsigned int QNotificatorPnP::ThreadRoutine()
{
	// Register window class and create our hidden window. This needs to be done in the context of the worker thread.
	WNDCLASSEX	wcex;
	ATOM		atomClass;
	MSG			msg;
	int			nRet;

	ZeroMemory(&wcex, sizeof(wcex));
	wcex.cbSize = sizeof(wcex);
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.hInstance = (HINSTANCE)HWND_MESSAGE;
	wcex.lpszClassName = strWndClass;
	atomClass = ::RegisterClassEx(&wcex);
	if (atomClass != 0)
	{	// create window, is initially hidden
		m_hWnd = ::CreateWindow(strWndClass, strWndTitle, WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, (HINSTANCE)HWND_MESSAGE, NULL);
		if (m_hWnd)
		{	// The window has been successfully created, attach this object
			::SetWindowLong(m_hWnd, GWL_USERDATA, (LONG)this);
		}
	}
	::SetEvent(m_hThreadReadyEvent);	// tell the main thread that initialization is done
	if (m_hWnd)
	{
		while (true)
		{	// retrieve and process messages until WM_QUIT is encountered
			nRet = ::GetMessage(&msg, NULL, 0, 0);
			if ((nRet == 0) || (nRet == -1)) break;	// WM_QUIT (0) or ERROR (-1) is detected
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		m_hWnd = NULL;								// window is already destroyed by DefWindowProc
	}
	if (atomClass != 0) ::UnregisterClass(strWndClass, (HINSTANCE)HWND_MESSAGE);
	return 0;
}

// window proc routine, static
LRESULT CALLBACK QNotificatorPnP::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// retrieve the pointer to our QNotificatorPnP instance
	QNotificatorPnP* pThis = (QNotificatorPnP*)::GetWindowLong(hWnd, GWL_USERDATA);
	return (pThis != NULL) ? pThis->WindowProc(hWnd, uMsg, wParam, lParam) : ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// window proc implementation
LRESULT QNotificatorPnP::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT retcode = 0;
	switch (uMsg)
	{
	case WM_DESTROY:		// post WM_QUIT to the window's message loop, this will terminate the worker thread
		::PostQuitMessage(0);
		break;
	case WM_DEVICECHANGE:	// this is a device PnP notification message, issue notification to handler
		IssuePnPNotification(wParam, lParam);
		break;
	default:				// let DefWindowProc handle the message, it handles standard messages like WM_CLOSE, WM_QUIT...
		retcode = ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return retcode;
}

QNotificatorPnP::NotificationRecord* QNotificatorPnP::FindRecord(const GUID& InterfaceClassGuid)
{
	NotificationRecord* pNotification;
	for (int i = 0; i < m_listNotification.size(); i++)
	{
		pNotification = m_listNotification.at(i);
		if (0 == memcmp(&pNotification->InterfaceClassGuid, &InterfaceClassGuid, sizeof(GUID)))
		{
			return pNotification;
		}
	}
	return NULL;
}

bool QNotificatorPnP::IsRegistered(const GUID& InterfaceClassGuid)
{
	return (FindRecord(InterfaceClassGuid) != NULL);
}

// Enable notifications for a particular class of device interfaces.
bool QNotificatorPnP::EnableDeviceNotifications(const GUID& InterfaceClassGuid)
{
	bool bSucc = true;
	::EnterCriticalSection(&m_CritSect);
	if (!IsRegistered(InterfaceClassGuid))
	{
		NotificationRecord* pNotification = new NotificationRecord;
		pNotification->InterfaceClassGuid = InterfaceClassGuid;  // struct copy
		bSucc = RegisterNotification(pNotification);
		bSucc ? m_listNotification.append(pNotification) : delete pNotification;
	}
	::LeaveCriticalSection(&m_CritSect);
	return bSucc;
}

// Disable notifications for a particular class of device interfaces.
void QNotificatorPnP::DisableDeviceNotifications(const GUID& InterfaceClassGuid)
{
	::EnterCriticalSection(&m_CritSect);
	UnregisterNotification(FindRecord(InterfaceClassGuid));
	::LeaveCriticalSection(&m_CritSect);
}

// Register the device interface type identified by Notification->InterfaceClassGuid so that our internal hidden window will receive notifications.
bool QNotificatorPnP::RegisterNotification(NotificationRecord* pNotification)
{
	if (m_hWnd == NULL) return false;
	// register the window for receiving device change notifications
	DEV_BROADCAST_DEVICEINTERFACE sFilter;
	ZeroMemory(&sFilter, sizeof(sFilter));
	sFilter.dbcc_size = sizeof(sFilter);
	sFilter.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;
	sFilter.dbcc_classguid = pNotification->InterfaceClassGuid; // struct copy
	pNotification->hDevNotify = ::RegisterDeviceNotification(m_hWnd, &sFilter, DEVICE_NOTIFY_WINDOW_HANDLE/*|DEVICE_NOTIFY_ALL_INTERFACE_CLASSES*/);
	return (pNotification->hDevNotify != NULL);
}

// Unregister the specified interface type
void QNotificatorPnP::UnregisterNotification(NotificationRecord* pNotification)
{
	if (!pNotification) return;
	::UnregisterDeviceNotification(pNotification->hDevNotify);
	m_listNotification.removeOne(pNotification);
	delete pNotification;
}

// issue a PnP notification
void QNotificatorPnP::IssuePnPNotification(WPARAM wParam, LPARAM lParam)
{
	DEV_BROADCAST_DEVICEINTERFACE*	pDeviceInterface = (DEV_BROADCAST_DEVICEINTERFACE*)lParam;
	if (pDeviceInterface == NULL) return;
	if (pDeviceInterface->dbcc_devicetype != DBT_DEVTYP_DEVICEINTERFACE) return;
	if (pDeviceInterface->dbcc_name == NULL || wcslen(pDeviceInterface->dbcc_name) == 0) return;
	if (!IsRegistered(pDeviceInterface->dbcc_classguid)) return;
	
	//notifyEvent(wParam & DBT_CONFIGMGPRIVATE, pDeviceInterface->dbcc_classguid, pDeviceInterface->dbcc_name);
	qDebug() << QString::fromStdWString(pDeviceInterface->dbcc_name);
	qDebug() << (wParam & DBT_CONFIGMGPRIVATE);
	emit notifyEvent(wParam & DBT_CONFIGMGPRIVATE, pDeviceInterface->dbcc_classguid, QString::fromStdWString(pDeviceInterface->dbcc_name));
}
