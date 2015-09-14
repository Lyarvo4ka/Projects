#ifndef DRIVETABLEMODEL_H
#define DRIVETABLEMODEL_H

#include <QAbstractItemModel>

#include <vector>
#include "DeviceLibrary/Devices.h"

class DriveIndex
{
private:
	DevicePtr device_;
	DriveIndex * parent_;
	std::vector< DriveIndex *> drives_;
public:
	DriveIndex(const DevicePtr & device)
		: device_(device)
		, parent_(nullptr)
	{

	}
	~DriveIndex()
	{

	}
	void set_device(const DevicePtr & device)
	{
		device_ = device;
	}
	DevicePtr device() const
	{
		return device_;
	}
	void set_parent(DriveIndex * parent)
	{
		parent_ = parent;
	}
	DriveIndex * parent() const
	{
		return parent_;
	}
	int count() const
	{
		return drives_.size();

	}
	void insert(const DevicePtr & device)
	{
		DriveIndex * new_drive = new DriveIndex(device);
		new_drive->set_parent(this);
		drives_.push_back(new_drive);
	}
	DriveIndex * getDriveIndex( const int nNumber) const
	{
		if (drives_.size() < nNumber)
			return drives_.at(nNumber);
		else
			return nullptr;
	}
	int row_index(const DriveIndex * parent_index) const
	{
		auto findIter = drives_.begin();
		findIter = std::find(drives_.begin(), drives_.end(), parent_index);
		if (findIter != drives_.end())
			return std::distance(drives_.begin(), findIter);
		else
			return -1;
	}
};

class DriveTableModel
	: public QAbstractItemModel
{
	Q_OBJECT
private:
	DriveIndex * root_index_;
private:
	DriveIndex * from_ModelIndex(const QModelIndex & index) const
	{
		if (index.isValid)
		{
			DriveIndex * new_index = static_cast<DriveIndex*> (index.internalPointer());
			return new_index;
		}
		return root_index_;
	}
public:
	static enum DriveHeader { header_number = 0, header_drivename, header_serialnumber, header_sectorcount,  header_bps  };
	DriveTableModel(QObject * parent, DriveIndex *root_index)
		: QAbstractItemModel(parent)
		, root_index_( root_index )
	{

	}
	~DriveTableModel()
	{
		if (root_index_)
		{
			delete root_index_;
			root_index_ = nullptr;
		}
	}
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const override
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
	int	columnCount(const QModelIndex & parent) const override
	{
		return (parent.isValid() && parent.column() != 0) ? 0 : sizeof(DriveHeader) + 1;
	}
	int	rowCount(const QModelIndex & parent) const override
	{
		if (parent.isValid() && parent.column() != 0)
			return 0;
		if (parent.column() > 0)
			return 0;

		DriveIndex * parent_index = from_ModelIndex(parent);

		return (parent_index) ? parent_index->count() : 0;
	}

	QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const override
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
	QModelIndex	parent(const QModelIndex & index) const override
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
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override
	{

	}
};

#endif