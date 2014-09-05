#ifndef DMTREEMODEL_H
#define DMTREEMODEL_H

#pragma warning( disable : 4482)

	#include <QWidget>
	#include <QAbstractItemModel>
	#include <QTableView>
	#include <QStyledItemDelegate>


#include <vector>

#include <algorithm>


//	Header names
const QString DeviceText = QString::fromUtf16(L"Device");
const QString StatusText = QString::fromUtf16(L"Status");
const QString ProgressText = QString::fromUtf16(L"Progress");

//	Task Status
const QString NotReadyStatusText = QString::fromUtf16(L"Not ready.");
const QString ReadyStatusText = QString::fromUtf16(L"Ready.");
const QString CopyTaskText = QString::fromUtf16(L"Copying");
const QString VerifyTaskText = QString::fromUtf16(L"Verification");
const QString EraseTaskText = QString::fromUtf16(L"Erasing");

//	Task Progress
const QString TaskNotStartedText = QString::fromUtf16(L"Task not started.");
const QString TaskStartedText = QString::fromUtf16(L"Task started.");
const QString TaskCompletedText = QString::fromUtf16(L"Task finished.");
const QString TaskSuspenedText = QString::fromUtf16(L"Task suspended.");
const QString TaskAbortedText = QString::fromUtf16(L"Task aborted.");
const QString TaskSwitchErrorText = "never this text appears";






#include "taskmanager.h"
#include "DiskMasterLib\dm_device.h"

/************************************************************************/
/*					        DMItemIdex									*/
/************************************************************************/

class DMItemIdex
{
public:
	static enum Item { 
			   RootItem = 0, 
			   DiskMasterItem, 
			   DiskDeviceItem,  
			   PartitionItem
					 };

	DMItemIdex () 
		: item_( RootItem )
		, number_id_( ULONG_MAX )
		, name_( "" )
		, item_state_( DMTool::NOT_STARTED )
		, item_status_( DMTool::NOT_READY )
		, parent_( nullptr )
		, icon_( QIcon() )
		, progress_ ( 0 )
	{

	}
	DMItemIdex ( DMItemIdex::Item dm_item, DWORD number_id)
		: item_( dm_item )
		, number_id_( number_id )
		, name_( "" )
		, item_state_( DMTool::NOT_STARTED )
		, item_status_( DMTool::NOT_READY )
		, parent_( nullptr )
		, icon_( QIcon() )	
		, progress_ ( 0 )
	{

	}
	~DMItemIdex();

	void update_params()
	{
		switch ( item_ )
		{
		case DiskMasterItem :
			icon_ = QIcon("icons//disk_master.png");
			name_ = QString("DiskMasterUsb id:0x") + QString("%1").arg( number_id_ , 0 , 16);

			if ( auto disk_master = DMTool::DMTaskManager::GetTaskManager()->Find(number_id_) )
				if (disk_master->isReady())
					setStatus( DMTool::READY );

			break;

		case DiskDeviceItem :
			icon_ = QIcon("icons//Hard_Drive.png");

			break;
		}
	}
	inline DMItemIdex * findIndex( DWORD number )
	{
		auto findIter = ItemArray_.begin();
		while ( findIter != ItemArray_.end() )
		{
			DMItemIdex * resIndex = *findIter;
			if ( number == resIndex->getID() )
				return resIndex;
			++findIter;
		}
		return nullptr;
	}
	int count() const ;
	void Add( DMItemIdex * abstract_index) ;
	void Remove ( DMItemIdex * abstract_index );
	bool hasChildrend() const
	{
		return !ItemArray_.empty();
	}
	DMItemIdex * getChild(const int position) const ;
	DMItemIdex * parent() const ;
	void setParent(DMItemIdex * parent) ;
	void setState(DMTool::TASK_STATE itemState) ;
	DMTool::TASK_STATE getState() const ;
	QString getStateName() const ;
	void setStatus(DMTool::TASK_STATUS item_status) ;
	DMTool::TASK_STATUS getStatus() const ; 
	QString getStatusName() const ; 
	int row_index( DMItemIdex * pIndex) ; 
	void setPorgress( const int progress) ; 
	int getProgress() const ; 
	void setIcon(const QIcon icon) ; 
	QIcon getIcon() const ; 
	void setName(const QString & name) ;
	QString name() const ;
	
	inline DWORD getID() const
	{
		return number_id_;
	}

	inline bool isRoot() const
	{
		return ( item_ == Item::RootItem );
	}
	inline bool isDiskMaster() const
	{
		return ( item_ == Item::DiskMasterItem );
	}
	inline bool isDiskDevice() const
	{
		return ( item_ == Item::DiskMasterItem );
	}
	inline bool isPartition() const
	{
		return ( item_ == Item::PartitionItem );
	}


private:

	Item item_;
	DWORD number_id_;
	QString name_;
	DMTool::TASK_STATE item_state_;
	DMTool::TASK_STATUS item_status_;
	DMItemIdex * parent_;
	int progress_;
	QIcon icon_;
	std::vector<DMItemIdex*> ItemArray_;
};

inline bool isItemIndexEqual( const DMItemIdex * index1 , const DMItemIdex * index2 )
{
	return (index2->getID() == index2->getID());
}


/************************************************************************/
/*					        DelegateProgress							*/
/************************************************************************/
class DelegateProgress
	: public QStyledItemDelegate
{
	Q_OBJECT

public:
	DelegateProgress(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

	void paint(QPainter *painter, const QStyleOptionViewItem &option,
		const QModelIndex &index) const;
};


/************************************************************************/
/*						        DMTreeModel								*/
/************************************************************************/
class DMTreeModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	static enum DMheader { header_device = 0, header_status, header_progress };
	static const int header_count = 3;

	DMTreeModel(QObject *parent,  DMItemIdex * RootIndex);
	~DMTreeModel();

	Qt::ItemFlags flags(const QModelIndex &index) const ;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const ;
	virtual int	columnCount ( const QModelIndex & parent = QModelIndex() ) const ;
	virtual int	rowCount ( const QModelIndex & parent = QModelIndex() ) const ;
	virtual QModelIndex	index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
	virtual QModelIndex	parent ( const QModelIndex & index ) const ;
	virtual QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;

	void update_view();
	//QModelIndex CreateRootIndex() const;

protected:
	DMItemIdex * fromIndex( const QModelIndex & qIndex) const;
private:
	DMItemIdex * RootIndex_;
};

#endif // DMTREEMODEL_H
