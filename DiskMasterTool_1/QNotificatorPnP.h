#ifndef QNOTIFICATOTPNP_H
#define QNOTIFICATOTPNP_H

#include <windows.h>
#include <guiddef.h>
#include <QtGui>



class QNotificatorPnP : public QObject
{
	Q_OBJECT

public:
	enum NotificationEvent
	{
		EventDeviceArrival,
		EventDeviceQueryRemove,
		EventDeviceQueryRemoveFailed,
		EventDeviceRemovePending,
		EventDeviceRemoveComplete,
		EventDeviceTypeSpecific,
		EventDeviceCustom
	};

private:
	struct NotificationRecord
	{	// this object stores a device notification that has been registered
		GUID				InterfaceClassGuid;						// device interface class
		HDEVNOTIFY			hDevNotify;								// handle returned by RegisterDeviceNotification
		NotificationRecord() { ZeroMemory(this, sizeof(*this)); }	// constructor
	};
	CRITICAL_SECTION			m_CritSect;
	HANDLE						m_hThread;							// system thread object
	volatile HWND				m_hWnd;								// handle of hidden window
	volatile HANDLE				m_hThreadReadyEvent;				// event signaled by worker thread if initialization is finished
	bool						m_bInitialized;						// state 
	QList<NotificationRecord*>	m_listNotification;

public:
	QNotificatorPnP();
	~QNotificatorPnP();
	bool EnableDeviceNotifications(const GUID& InterfaceClassGuid);
	void DisableDeviceNotifications(const GUID& InterfaceClassGuid);
	//virtual void notifyEvent(int nType, GUID guidDevice, wchar_t* dbcc_name){};
signals:
	void notifyEvent(int nType, GUID guidDevice, QString strDeviceName);

protected:
	static unsigned int __stdcall BeginThread(void* pStartContext);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	unsigned int ThreadRoutine(void);
	virtual LRESULT WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	NotificationRecord* FindRecord(const GUID& InterfaceClassGuid);
	bool IsRegistered(const GUID& InterfaceClassGuid);
	bool RegisterNotification(NotificationRecord* pNotification);
	void UnregisterNotification(NotificationRecord* pNotification);
	void IssuePnPNotification(WPARAM wParam, LPARAM lParam);

private:
	
};



#endif // QNOTIFICATOTPNP_H
