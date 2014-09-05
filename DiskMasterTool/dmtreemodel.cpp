#include "dmtreemodel.h"

#include <QProgressBar>
#include <QApplication>

DMItemIdex::~DMItemIdex()
{
	auto deleteIter = ItemArray_.begin();
	while ( deleteIter != ItemArray_.end() )
	{
		DMItemIdex * pDiskMaster = *deleteIter;
		delete pDiskMaster;
		++deleteIter;
	}
	ItemArray_.clear();

}
int DMItemIdex::count() const
{ 
	return ItemArray_.size();
}

void DMItemIdex::Add( DMItemIdex * abstract_index )
{
	auto findIter = std::find (ItemArray_.begin(), ItemArray_.end(), abstract_index);
	if (findIter == ItemArray_.end() )
	{
		abstract_index->setParent(this);
		ItemArray_.push_back(abstract_index);
	}
}
void DMItemIdex::Remove( DMItemIdex * abstract_index )
{
	auto delIter = std::find (ItemArray_.begin(), ItemArray_.end() , abstract_index );
	if ( delIter != ItemArray_.end() )
		ItemArray_.erase(delIter);
	delete abstract_index;
	abstract_index = nullptr;
}
DMItemIdex * DMItemIdex::getChild(const int position) const
{
	return (position < ItemArray_.size()) ?
		ItemArray_[position] 
	: nullptr;
}
DMItemIdex * DMItemIdex::parent() const
{
	return parent_;
}
void DMItemIdex::setParent(DMItemIdex * parent)
{
	parent_ = parent;
}
void DMItemIdex::setState( DMTool::TASK_STATE itemState)
{
	item_state_ = itemState;
}
DMTool::TASK_STATE DMItemIdex::getState() const
{
	return item_state_;
}
QString DMItemIdex::getStateName() const
{
	if ( isDiskMaster() )
	{
		switch (item_state_)
		{
		case DMTool::NOT_STARTED:
			return TaskNotStartedText;
		case DMTool::STARTED:
			return TaskStartedText;
		case DMTool::COMPLETED:
			return TaskCompletedText;
		case DMTool::SUSPENDED:
			return TaskSuspenedText;
		case DMTool::ABORTED:
			return TaskAbortedText;
		default:
			return "never this text appears";
		}
	}
	return QString();
}
void DMItemIdex::setStatus( DMTool::TASK_STATUS item_status)
{
	item_status_ = item_status;
}
DMTool::TASK_STATUS DMItemIdex::getStatus() const 
{
	return item_status_;
}
QString DMItemIdex::getStatusName() const
{
	if ( isDiskMaster() )
	{
		switch (item_status_)
		{
		case DMTool::NOT_READY:
			return NotReadyStatusText;
		case DMTool::READY:
			return ReadyStatusText;
		case DMTool::COPYING:
			return CopyTaskText;
		case DMTool::VERIFYING:
			return VerifyTaskText;
		case DMTool::EARASING:
			return EraseTaskText;
		default:
			return TaskSwitchErrorText;
		}

	}
	return QString();
}
int DMItemIdex::row_index( DMItemIdex * pIndex)
{
	auto findIter = std::find(ItemArray_.begin(),ItemArray_.end(), pIndex);
	return (findIter != ItemArray_.end()) ? findIter - ItemArray_.begin() : -1;
}
void DMItemIdex::setPorgress( const int progress)
{
	progress_ = progress;
}
int DMItemIdex::getProgress() const
{
	return progress_;
}
void DMItemIdex::setIcon(const QIcon icon)
{
	icon_ = icon;
}
QIcon DMItemIdex::getIcon() const
{
	return icon_;
}
void DMItemIdex::setName(const QString & name)
{
	name_ = name;
}
QString DMItemIdex::name() const
{
	return name_;
}

/************************************************************************/
/*					        DelegateProgress							*/
/************************************************************************/
void DelegateProgress::paint(QPainter *painter, const QStyleOptionViewItem &option,
	const QModelIndex &index) const
{
	if (index.column() == DMTreeModel::header_progress) {

		DMItemIdex * pIndex = static_cast < DMItemIdex * > ( index.internalPointer() );
		if ( pIndex->isDiskMaster() )
		{
			if (pIndex->getState() == DMTool::STARTED)
			{
				int progress = index.data().toInt();

				QStyleOptionProgressBar progressBarOption;
				progressBarOption.minimum = 0;
				progressBarOption.maximum = 100;
				progressBarOption.progress = pIndex->getProgress();	
				progressBarOption.text = QString ("%1%").arg(progressBarOption.progress);
				progressBarOption.rect = option.rect;
				progressBarOption.rect.setRight(option.rect.right()-1);
				progressBarOption.rect.setHeight(option.rect.height()-1);
				progressBarOption.textVisible = true;
				progressBarOption.textAlignment = Qt::AlignCenter;

				QApplication::style()->drawControl(QStyle::CE_ProgressBar,
					&progressBarOption, painter);
			}
			else
				QStyledItemDelegate::paint(painter, option, index);
		}
	} else
		QStyledItemDelegate::paint(painter, option, index);
}
/************************************************************************/
/*						        DMTreeModel								*/
/************************************************************************/
DMTreeModel::DMTreeModel(QObject *parent, DMItemIdex * RootIndex)
	: QAbstractItemModel(parent)
	, RootIndex_(RootIndex)
	//, sort_order(Qt::AscendingOrder)
{

}

DMTreeModel::~DMTreeModel()
{
	if (RootIndex_)
	{
		delete RootIndex_;
		RootIndex_ = nullptr;
	}
}
Qt::ItemFlags DMTreeModel::flags(const QModelIndex &index) const
{
	return QAbstractItemModel::flags(index);
}
QVariant DMTreeModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		switch (section)
	{
		case header_device: return DeviceText;
		case header_status : return StatusText;
		case header_progress: return ProgressText;
		default:
			return QString("этот текст не должен выводится");
	}

	return QVariant();
}
int	DMTreeModel::columnCount ( const QModelIndex & parent ) const 
{
	return (parent.isValid() && parent.column() != 0) ? 0 : header_count ;
}
int	DMTreeModel::rowCount ( const QModelIndex & parent ) const
{
	if ( parent.isValid() && parent.column() != 0)
		return 0;
	if (parent.column() > 0)
		return 0;

	DMItemIdex * parent_index = fromIndex(parent);

	return (parent_index) ? parent_index->count() : 0 ;
}
QModelIndex	DMTreeModel::index ( int row, int column, const QModelIndex & parent ) const
{
	if ( (RootIndex_ == NULL) || row < 0 || column < 0 || row >= rowCount(parent) || column >= columnCount(parent) )
		return QModelIndex();

	if ( ! hasIndex(row,column, parent) )
		return QModelIndex();

	DMItemIdex * parent_index = fromIndex(parent);

	DMItemIdex * child_index  = parent_index->getChild(row);
	if (child_index)
		return createIndex( row ,column, child_index );

	return QModelIndex();
}
QModelIndex	DMTreeModel::parent ( const QModelIndex & index ) const 
{
	if ( !index.isValid() )	
		return QModelIndex();

	if ( DMItemIdex * child_index = fromIndex(index) )
	{
		if ( DMItemIdex * parent_index = child_index->parent() )
		{
			if ( parent_index == RootIndex_)
				return QModelIndex();

			if ( DMItemIdex * grandParent_index = parent_index->parent() )
				return createIndex( grandParent_index->row_index(parent_index), 0 , parent_index);
		}
	}
	return QModelIndex();
}
QVariant DMTreeModel::data ( const QModelIndex & index, int role ) const
{
	if (!index.isValid())
		return QVariant();

	if ( DMItemIdex * model_index = static_cast < DMItemIdex *>	( index.internalPointer() ) )
		if (role == Qt::DisplayRole)
		{
			switch ( index.column() )
			{
			case header_device:
				return model_index->name();

			case header_status:
				return model_index->getStatusName();

			case header_progress:
				return model_index->getStateName();

			default:
				return "never this text will be show.";
			}
		}
		else
			if (role == Qt::DecorationRole)
			{
				if (index.column() == DMTreeModel::header_device)
				{
					return model_index->getIcon();
				}
			}

			return QVariant();
}
//bool DMTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//	if ( !index.isValid() )
//		return false;
//
//	return false;
//
//}
DMItemIdex * DMTreeModel::fromIndex( const QModelIndex & qIndex) const
{
	if ( qIndex.isValid() )
	{
		DMItemIdex * model_index = static_cast < DMItemIdex *>
			( qIndex.internalPointer() ) ;
		if ( model_index)
			return model_index;
	}
	return RootIndex_;
}
void DMTreeModel::update_view()
{
	//this->reset();
}
//QModelIndex DMTreeModel::CreateRootIndex() const
//{
//	//if (DMItemIdex * child_index = RootIndex_->getChild(0) )
//		//return createIndex(RootIndex_->row_index(child_index),0,child_index);
//	return createIndex(0,0,RootIndex_);
//}
