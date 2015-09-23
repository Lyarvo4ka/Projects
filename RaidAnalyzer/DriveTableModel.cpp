#include "DriveTableModel.h"

DriveIndex::DriveIndex(const DevicePtr & device) 
: device_(device)
, parent_(nullptr)
{

}

DriveIndex::~DriveIndex()
{
	parent_ = nullptr;
}

void DriveIndex::set_device(const DevicePtr & device)
{
	device_ = device;
}

DevicePtr DriveIndex::device() const
{
	return device_;
}

void DriveIndex::set_parent(DriveIndex * parent)
{
	parent_ = parent;
}

DriveIndex * DriveIndex::parent() const
{
	return parent_;
}

int DriveIndex::count() const
{
	return drives_.size();
}

void DriveIndex::insert(const DevicePtr & device)
{
	DriveIndex * new_drive = new DriveIndex(device);
	new_drive->set_parent(this);
	drives_.push_back(new_drive);
}

DriveIndex * DriveIndex::getDriveIndex(const int nNumber) const
{
	if (nNumber < drives_.size())
		return drives_.at(nNumber);
	else
		return nullptr;
}


int DriveIndex::row_index(const DriveIndex * parent_index) const
{
	auto findIter = drives_.begin();
	findIter = std::find(drives_.begin(), drives_.end(), parent_index);
	if (findIter != drives_.end())
		return std::distance(drives_.begin(), findIter);
	else
		return -1;
}



DriveIndex * DriveTableModel::from_ModelIndex(const QModelIndex & index) const
{
	if (index.isValid())
	{
		DriveIndex * new_index = static_cast<DriveIndex*> (index.internalPointer());
		return new_index;
	}
	return root_index_;
}

DriveTableModel::DriveTableModel(QObject * parent, DriveIndex *root_index) : QAbstractItemModel(parent)
, root_index_(root_index)
{

}

DriveTableModel::~DriveTableModel()
{
	if (root_index_)
	{
		delete root_index_;
		root_index_ = nullptr;
	}
}

QVariant DriveTableModel::headerData(int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole*/) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		switch (section)
	{
		case header_number: return tr("#");
		case header_drivename: return tr("Name");
		case header_serialnumber: return tr("Serial Number");
		case header_sectorcount: return tr("Sector Count");
		case header_bps: return tr("BPS");
	}

	return QVariant();
}

int DriveTableModel::columnCount(const QModelIndex & parent) const
{
	return (parent.isValid() && parent.column() != 0) ? 0 : sizeof(DriveHeader) + 1;
}

int DriveTableModel::rowCount(const QModelIndex & parent) const
{
	if (parent.isValid() && parent.column() != 0)
		return 0;
	if (parent.column() > 0)
		return 0;

	DriveIndex * parent_index = from_ModelIndex(parent);

	return (parent_index) ? parent_index->count() : 0;
}

QModelIndex DriveTableModel::index(int row, int column, const QModelIndex & parent /*= QModelIndex()*/) const
{
	if ((root_index_ == nullptr) || row < 0 || column < 0 || row >= rowCount(parent) || column >= columnCount(parent))
		return QModelIndex();

	if (!hasIndex(row, column, parent))
		return QModelIndex();

	DriveIndex * parent_index = from_ModelIndex(parent);

	DriveIndex * child_index = parent_index->getDriveIndex(row);
	if (child_index)
		return createIndex(row, column, child_index);

	return QModelIndex();
}

QModelIndex DriveTableModel::parent(const QModelIndex & index) const
{
	if (!index.isValid())
		return QModelIndex();

	if (DriveIndex * child_index = from_ModelIndex(index))
	{
		if (DriveIndex * parent_index = child_index->parent())
		{
			if (parent_index == root_index_)
				return QModelIndex();

			if (DriveIndex * grandParent_index = parent_index->parent())
				return createIndex(grandParent_index->row_index(parent_index), 0, parent_index);
		}
	}
	return QModelIndex();
}

QVariant DriveTableModel::data(const QModelIndex & index, int role /*= Qt::DisplayRole*/) const
{
	if (!index.isValid())
		return QVariant();

	if (DriveIndex * drive_index = from_ModelIndex(index))
	{
		if (role == Qt::DisplayRole)
		{
			switch (index.column())
			{
			case header_number:
				return QString::number(drive_index->device()->GetNumber());
			case header_drivename:
				return QString::fromLocal8Bit(drive_index->device()->GetName());
			case header_serialnumber:
				return drive_index->device()->GetSerialNumber();
			case header_sectorcount:
				return QString::number(drive_index->device()->GetSectorCount());
			case header_bps:
				return QString::number(drive_index->device()->GetBytesPerSector());
			default:
				break;
			}
		}
	}
	return QVariant();
}
