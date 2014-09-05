#ifndef DEVICETABLEVIEW_H
#define DEVICETABLEVIEW_H

#include <QTableView>
class QStandardItemModel;

#include "DeviceLibrary/Devices.h"


class DeviceTableView 
	: public QTableView
{
	Q_OBJECT

public:
	DeviceTableView(QWidget *parent);
	virtual ~DeviceTableView();

	virtual void Init();
	virtual void InitDeviceList();
	void RefreshDevices();
	void RemoveTable();
	DevicePtr GetSelectedDevice();
	DevicePtr GetDevice(int nIndex);
	int GetTableWidth() const;
	void AddToList(DevicePtr pDevice);
	void GetSerials();

private:
	QStandardItemModel * DeviceModel_;
	CDiviceList DeviceList_;
	int TableWidth_;
};

class TargetTableView
	: public DeviceTableView
{
	Q_OBJECT 

public:
	TargetTableView(QWidget *parent);
	~TargetTableView();
	void InitDeviceList();
	void SetSourceNumber(DWORD SourceNumber);
	bool isEmptyDeviceList() const;
private:
	DWORD SourceNumber_;
	bool EmptyDeviceList_;
};

#endif // DEVICETABLEVIEW_H
