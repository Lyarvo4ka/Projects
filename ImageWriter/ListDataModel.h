#pragma once

#include "DeviceLibrary/Devices.h"

#include <QString>

const QString SystemDevice = "System device";

struct CDeviceRowData
{
	CDeviceRowData();
	static enum enDataHeaders {enDevNumber = 0, enDevName = 1, enDevSize = 2, enSerialNumber = 3, enConnType = 4, enDescription = 5};

	BOOL GetData(QString &_DataName , int _iTypeNumber);
	QString m_Number;
	QString m_Name;
	QString m_Size;
	QString m_SerialNumber;
	QString m_ConectionType;
	QString m_Description;
};

class CListDataModel
{
public:
	CListDataModel(const CDiviceList &_DeviceList);
	virtual ~CListDataModel(void);

	virtual BOOL InitDataModel();
	virtual BOOL AddDeviceRow(DevicePtr &_devPtr);
	virtual void CreateHeaders();
	size_t GetHeadersCount() const;
	size_t GetRowCount() const;
	QString GetHeader(size_t _iHeader) const ;
	QString GetCellText(int _iRow, int _iColunm);
	bool isSystem(size_t _Number) const;
private:
	CDiviceList m_DeviceList;
	vector<CDeviceRowData> m_DeviceRowData;
	vector<QString> m_HeaderData;
	vector<int> m_OrderLabels;

};