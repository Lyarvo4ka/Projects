#include "ListDataModel.h"

#include <string>
using std::string;



CDeviceRowData::CDeviceRowData()
{
	//m_Number();
	//m_Name = _T("");
	//m_Size = _T("");
	//m_SerialNumber = _T("");
	//m_ConectionType = _T("");
}

BOOL CDeviceRowData::GetData(QString &_DataName , int _iTypeNumber)
{
	switch (_iTypeNumber)
	{
	case enDevNumber:
		_DataName = m_Number;
		break;
	case enDevName:
		_DataName = m_Name;
		break;
	case enDevSize:
		_DataName = m_Size;
		break;
	case enSerialNumber:
		_DataName = m_SerialNumber;
		break;
	case enConnType:
		_DataName = m_ConectionType;
		break;
	case enDescription:
		_DataName = m_Description;
		break;
	default:
		_DataName = "";
		return FALSE;
	}

	return TRUE;
}


CListDataModel::CListDataModel(const CDiviceList &_DeviceList)
	: m_DeviceList(_DeviceList)
{
	InitDataModel();
}


CListDataModel::~CListDataModel(void)
{
}

BOOL CListDataModel::InitDataModel()
{
	CreateHeaders();
	DevicePtr ptrDev;
	for (size_t iDev = 0; iDev < m_DeviceList.GetCount(); ++iDev)
	{
//		ptrDev = m_DeviceList.GetDevice(m_DeviceList.GetCount() - iDev - 1);
		ptrDev = m_DeviceList.GetDevice(iDev);
		if (ptrDev != NULL)
			if (!AddDeviceRow(ptrDev))
				return FALSE;
	}
	return TRUE;
}

BOOL CListDataModel::AddDeviceRow(DevicePtr &_devPtr)
{
	//QString sFormatString;
	
	CDeviceRowData DeviceData;


	// Device Number 
	DeviceData.m_Number = QString::number(_devPtr->GetNumber());

	// Device Name
	DeviceData.m_Name = QString(_devPtr->GetName());

	// Device Size
	DeviceData.m_Size = QString::number(_devPtr->GetCapacity(),'f',2) + ' ' + QString(_devPtr->GetSizeData());

	// Device SerialNumber
	DeviceData.m_SerialNumber = QString(_devPtr->GetSerialNumber());

	// Device Connection Type
	DeviceData.m_ConectionType = QString(_devPtr->GetBusTypeStr());

	// System Disk
	if (_devPtr->isSystemDisk())
		DeviceData.m_Description = SystemDevice;

	m_DeviceRowData.push_back(DeviceData);
	return TRUE;
}


void CListDataModel::CreateHeaders()
{
	//m_HeaderData.push_back(Languages::GetDeviceNumber());
	//m_OrderLabels.push_back(CDeviceRowData::enDevNumber);
	//m_HeaderData.push_back(Languages::GetDeviceName());
	//m_OrderLabels.push_back(CDeviceRowData::enDevName);
	//m_HeaderData.push_back(Languages::GetDeviceSize());
	//m_OrderLabels.push_back(CDeviceRowData::enDevSize);
	//m_HeaderData.push_back(Languages::GetSerialNumber());
	//m_OrderLabels.push_back(CDeviceRowData::enSerialNumber);
	//m_HeaderData.push_back(Languages::GetConnectionType());
	//m_OrderLabels.push_back(CDeviceRowData::enConnType);

	m_HeaderData.push_back("#");
	m_OrderLabels.push_back(CDeviceRowData::enDevNumber);
	m_HeaderData.push_back("Name");
	m_OrderLabels.push_back(CDeviceRowData::enDevName);
	m_HeaderData.push_back("Size");
	m_OrderLabels.push_back(CDeviceRowData::enDevSize);
	m_HeaderData.push_back("Serial Number");
	m_OrderLabels.push_back(CDeviceRowData::enSerialNumber);
	m_HeaderData.push_back("Bus");
	m_OrderLabels.push_back(CDeviceRowData::enConnType);
	m_HeaderData.push_back("Description");
	m_OrderLabels.push_back(CDeviceRowData::enDescription);
}

size_t CListDataModel::GetHeadersCount() const
{
	return m_HeaderData.size();
}
size_t CListDataModel::GetRowCount() const
{
	return m_DeviceRowData.size();
}
QString CListDataModel::GetHeader(size_t _iHeader) const 
{
	return (_iHeader < m_HeaderData.size()) ? m_HeaderData[_iHeader] : QString();
}

QString CListDataModel::GetCellText(int _iRow, int _iColunm)
{
	QString sCellString;
	if (_iRow < (int)m_DeviceRowData.size() && _iColunm < (int)m_OrderLabels.size())
	{
		CDeviceRowData DeviceRowData = m_DeviceRowData[_iRow];
		DeviceRowData.GetData(sCellString,_iColunm);
	}
	return sCellString;
}
bool CListDataModel::isSystem(size_t _Number) const
{
	if (m_DeviceList.GetCount() <= _Number)
		return false;

	return m_DeviceList.GetDevice(_Number)->isSystemDisk();
}