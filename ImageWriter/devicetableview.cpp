#include "devicetableview.h"


#include <QHeaderView>
#include <QStandardItemModel>
#include "ListDataModel.h"

#include "DeviceLibrary/Devices.h"

DeviceTableView::DeviceTableView(QWidget *parent)
	: QTableView(parent)
	, TableWidth_(0)
{
	DeviceModel_ = new QStandardItemModel();

	this->setModel(DeviceModel_);

	this->verticalHeader()->setVisible(false);
	this->setAlternatingRowColors(true);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
DeviceTableView::~DeviceTableView()
{
	DeviceList_.RemoveAll();
}

void DeviceTableView::Init()
{
	
	InitDeviceList();

	CListDataModel ListDataModel(DeviceList_);

	DeviceModel_->setColumnCount(ListDataModel.GetHeadersCount());

	for (size_t iHeader = 0; iHeader < ListDataModel.GetHeadersCount(); ++iHeader)
		DeviceModel_->setHeaderData(iHeader, Qt::Horizontal, ListDataModel.GetHeader(iHeader) );


	for (size_t iRow = 0; iRow < ListDataModel.GetRowCount(); ++iRow)
	{
		auto iRowCount = DeviceModel_->rowCount();
		//auto iPosition = ListDataModel.GetRowCount() - iRow - 1;
		DeviceModel_->insertRow(iRowCount);

		for (int iCoulumn = 0; iCoulumn < ListDataModel.GetHeadersCount(); ++ iCoulumn)
		{
			DeviceModel_->setData(DeviceModel_->index(iRow, iCoulumn), ListDataModel.GetCellText(iRow, iCoulumn) );
			if (ListDataModel.isSystem(iRow))
				DeviceModel_->setData(DeviceModel_->index(iRow,iCoulumn), QColor(Qt::green), Qt::BackgroundColorRole);

		}
	}

	TableWidth_ = 0;

	this->resizeColumnsToContents();
	this->resizeRowsToContents();

	for (int iCoulumn = 0; iCoulumn < ListDataModel.GetHeadersCount(); ++ iCoulumn)
		TableWidth_ += this->columnWidth(iCoulumn);

}
void DeviceTableView::InitDeviceList()
{
	CPhysicalDevice PhysicalDevice;
	PhysicalDevice.GetDevices(DeviceList_);
	GetSerials();

	DeviceList_.SORT();
}
DevicePtr DeviceTableView::GetSelectedDevice()
{

	QItemSelectionModel *selectionModel = this->selectionModel();
	QModelIndexList selectList = selectionModel->selectedRows();
	QModelIndex index;

	bool bResult = false;
	foreach (index, selectList)
	{
		qDebug("Selected Device... #%d",index.row());
		return DeviceList_.GetDevice(index.row());
	}
	DevicePtr nullPtr;
	return nullPtr;
}
DevicePtr DeviceTableView::GetDevice(int nIndex)
{
	return DeviceList_.GetDevice(nIndex);
}
int DeviceTableView::GetTableWidth() const
{
	return TableWidth_;
}
void DeviceTableView::AddToList(DevicePtr pDevice)
{
	DeviceList_.AddDevice(pDevice);
}
void DeviceTableView::GetSerials()
{
	CPhysicalDevice PhysicalDevice;
	for ( size_t iDev = 0; iDev < DeviceList_.GetCount(); ++iDev)
		PhysicalDevice.GetSerialFromSmart(DeviceList_.GetDevice(iDev).get());

}
void DeviceTableView::RefreshDevices()
{
	RemoveTable();
	Init();
}
void DeviceTableView::RemoveTable()
{
	DeviceList_.RemoveAll();
	DeviceModel_->clear();
	TableWidth_ = 0;
}


TargetTableView::TargetTableView(QWidget *parent)
	: DeviceTableView(parent)
	, SourceNumber_(0)
	, EmptyDeviceList_(true)
{

}
TargetTableView::~TargetTableView()
{

}
void TargetTableView::InitDeviceList()
{
	CPhysicalDevice PhysicalDevice;
	CDiviceList tempList;
	PhysicalDevice.GetDevices(tempList);

	EmptyDeviceList_ = true;

	for ( DWORD iDev = 0 ; iDev < tempList.GetCount(); ++iDev)
	{
		DevicePtr tempDevice = tempList.GetDevice(iDev);
		
		if ( SourceNumber_ != tempDevice->GetNumber() ) 
		if (!tempDevice->isSystemDisk()  )
		{
			AddToList(tempDevice);
			EmptyDeviceList_ = false;
		}
	}
	GetSerials();
}
void TargetTableView::SetSourceNumber(DWORD SourceNumber)
{
	SourceNumber_ = SourceNumber;
}
bool TargetTableView::isEmptyDeviceList() const
{
	return EmptyDeviceList_;
}