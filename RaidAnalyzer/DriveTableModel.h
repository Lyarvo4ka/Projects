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
	DriveIndex(const DevicePtr & device);
	~DriveIndex();
	void set_device(const DevicePtr & device);
	DevicePtr device() const;
	void set_parent(DriveIndex * parent);
	DriveIndex * parent() const;
	int count() const;
	void insert(const DevicePtr & device);
	void remove_all()
	{
		if (drives_.size() > 0)
		{
			auto iter = drives_.begin();
			while (iter != drives_.end())
			{
				delete *iter;
				++iter;
			}
			drives_.clear();
		}
	}
	DriveIndex * getDriveIndex( const int nNumber) const;
	int row_index(const DriveIndex * parent_index) const;
};

class DriveTableModel
	: public QAbstractItemModel
{
	Q_OBJECT
private:
	DriveIndex * root_index_;
private:
	DriveIndex * from_ModelIndex(const QModelIndex & index) const;
public:
	static enum DriveHeader { header_number = 0, header_drivename, header_serialnumber, header_sectorcount,  header_bps  };

	DriveTableModel(QObject * parent, DriveIndex *root_index);
	~DriveTableModel();
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	int	columnCount(const QModelIndex & parent) const override;
	int	rowCount(const QModelIndex & parent) const override;

	QModelIndex	index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
	QModelIndex	parent(const QModelIndex & index) const override;
	QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;

};

#endif