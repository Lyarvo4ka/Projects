#ifndef PARTITIONMODEL_H
#define PARTITIONMODEL_H

#include <QAbstractItemModel>
#include <QIcon>

#include <windows.h>

#include <memory>


#pragma pack(1)
struct partition_enty
{
	BYTE boot_flag;			// partition boot flag
	BYTE start_CHS[3];		// start address CHS
	BYTE partition_type;	// partition type
	BYTE end_CHS[3];		// end address CHS
	DWORD start_lba;		// start address lba
	DWORD sector_count;		// count in sectors
};
#pragma pack ()

class PartitionEntry
{
public:
	PartitionEntry(const DWORD start_sector, const DWORD sector_count , BYTE partition_type)
		: start_sector_(start_sector)
		, sector_count_(sector_count)
		, partition_type_( partition_type )
		, number_ ( -1 )
	{

	};
	void setData(const DWORD start_sector, const DWORD sector_count , BYTE partition_type)
	{
		setStartSector( start_sector );
		setSectorCount( sector_count );
		setPartitinType( partition_type );
	}
	void setStartSector(const DWORD start_sector)
	{
		start_sector_ = start_sector;
	}
	void setSectorCount(const DWORD sector_count)
	{
		sector_count_ = sector_count;
	}
	void setPartitinType( BYTE partition_type )
	{
		partition_type_ = partition_type;
	}
	DWORD getStartSector() const
	{
		return start_sector_;
	}
	DWORD getSectorCount() const
	{
		return sector_count_;
	}
	BYTE getPartitionType()
	{
		return partition_type_;
	}
	QString getPartitionTypeName() const
	{
		switch ( partition_type_ )
		{
		case 0x07 : return "NTFS";
		case 0x06: return "FAT16";
		};
		return "";		 
	}
	void setNumber( int number )
	{
		number_ = number;
	}
	int number() const
	{
		return number_;
	}
private:
	DWORD start_sector_;
	DWORD sector_count_;
	BYTE partition_type_;
	int number_;
};

typedef std::shared_ptr< PartitionEntry > PartitionEntryPtr;

inline bool isPartition( BYTE partition_type )
{
	switch ( partition_type )
	{
	case 0x07 : 
	case 0x06 : 
		return true;
	}
	return false;
}


class BaseItemIndex
{
public:
	BaseItemIndex()
		: parent_ ( nullptr )
		, checked_ ( Qt::Checked )

	{

	}
	virtual ~BaseItemIndex()
	{
		RemoveAll();
	}
	inline void Add( BaseItemIndex * new_item )
	{
		new_item->setParent( this );
		itemArray_.push_back(new_item);
	}
	void Remove( BaseItemIndex * delete_item )
	{
		//assert( delete_item != nullptr );
		int delPos = itemArray_.indexOf( delete_item );
		if ( delPos != -1 )
			itemArray_.remove( delPos );
		delete delete_item;
		delete_item = nullptr;
	}
	void RemoveAll( )
	{
		foreach ( auto pItem  , itemArray_ )
		{
			delete pItem;
		}
	}
	inline void setParent( BaseItemIndex * parent )
	{
		parent_ = parent ;
	}
	inline BaseItemIndex * parent() const
	{
		return parent_;
	}
	inline int childNumber( BaseItemIndex * child ) const
	{
		return itemArray_.indexOf( child );
	}
	inline BaseItemIndex * getChild(const int position) const 
	{
		return ( position < itemArray_.size()  ) ? itemArray_[ position ] : nullptr ;
	}
	inline bool hasChildrend() const
	{
		return !itemArray_.empty();
	}
	inline int count() const
	{
		return itemArray_.size();
	}
	inline const QString & name() const 
	{
		return name_;
	}
	void setName( const QString & name )
	{
		name_ = name;
	}
	inline QIcon getIcon() const
	{
		return icon_;
	}
	void setIcon( const QIcon & icon )
	{
		icon_ = icon;
	}
	void setChecked(const Qt::CheckState checked = Qt::Unchecked)
	{
		checked_ = checked;
	}
	Qt::CheckState getChecked() const
	{
		return checked_;
	}
private:
	QIcon icon_;
	Qt::CheckState checked_;
	QString name_;
	BaseItemIndex * parent_;
	QVector < BaseItemIndex * > itemArray_;
};

//struct Partition
//{
//	long number;
//	quint32 fs_type;
//	qlonglong offset;
//	qlonglong sectors;
//
//};

class PartitionItemIndex
	: public BaseItemIndex
{

public:
	PartitionItemIndex( PartitionEntry * partition_entry )
		: partition_( partition_entry )
	{

	}
	~PartitionItemIndex()
	{
		if ( partition_ )
		{
			delete partition_;
			partition_ = nullptr;
		}
	}
	
	PartitionEntry * getPartitionEntry() const 
	{
		return partition_;
	}
	void setPartitionEntry( PartitionEntry * new_entry )
	{
		partition_ = new_entry;
	}


private:
	PartitionEntry * partition_;

};

const QString sPartitionNumberText = QString::fromLocal8Bit("Partition number");
const QString sFileSystemText = QString::fromLocal8Bit("File system");
const QString sPartitinOffsetText = QString::fromLocal8Bit("Start");
const QString sPartitinSizeText = QString::fromLocal8Bit("Size");



class PartitionTreeModel : public QAbstractItemModel
{
	Q_OBJECT
public:

	static enum PartitionHeader
	{ 
		enNumber = 0, 
		//enFS , 
		enStart , 
		enSize,
		enHeaderSize
	};
	PartitionTreeModel(QObject *parent,  PartitionItemIndex * RootIndex )
		: RootIndex_( RootIndex )
	{

	}
	~PartitionTreeModel()
	{
		if ( RootIndex_ )
		{
			delete RootIndex_;
			RootIndex_ = nullptr;
		}
	}

	Qt::ItemFlags flags(const QModelIndex &index) const override
	{
		return (index.isValid()) ? ( QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable )
			: QAbstractItemModel::flags(index);
	}
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const override 
	{
		if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
			switch (section)
		{
			case enNumber: return sPartitionNumberText;
			//case enFS : return sFileSystemText;
			case enStart: return sPartitinOffsetText;
			case enSize: return sPartitinSizeText;
			default:
				return "never this text will be show.";
		}

		return QVariant();
	}
	int	columnCount ( const QModelIndex & parent = QModelIndex() ) const override
	{
		return (parent.isValid() && parent.column() != 0) ? 0 : enHeaderSize ;
	}
	int	rowCount ( const QModelIndex & parent = QModelIndex() ) const override
	{
		if ( parent.isValid() && parent.column() != 0)
			return 0;
		if (parent.column() > 0)
			return 0;

		auto * parent_index = fromIndex(parent);

		return (parent_index) ? parent_index->count() : 0 ;
	}
	QModelIndex	index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const override
	{
		if ( (RootIndex_ == nullptr) || row < 0 || column < 0 || row >= rowCount(parent) || column >= columnCount(parent) )
			return QModelIndex();

		if ( ! hasIndex(row,column, parent) )
			return QModelIndex();

		auto * parent_index = fromIndex(parent);

		auto * child_index  = parent_index->getChild(row);
		if (child_index)
			return createIndex( row ,column, child_index );

		return QModelIndex();
	}

	QModelIndex	parent ( const QModelIndex & index ) const override
	{
		if ( !index.isValid() )	
			return QModelIndex();

		if ( auto * child_index = static_cast < PartitionItemIndex *>	( index.internalPointer() )  )
		{
			if ( auto * parent_index = child_index->parent() )
			{
				if ( parent_index == RootIndex_)
					return QModelIndex();

				if ( auto * grandParent_index = parent_index->parent() )
					return createIndex( grandParent_index->childNumber(parent_index), 0 , parent_index);
			}
		}
		return QModelIndex();
	}
	QVariant data ( const QModelIndex & index, int role = Qt::DisplayRole ) const override
	{
		if (!index.isValid())
			return QVariant();

		if ( auto * model_index = static_cast < PartitionItemIndex *>	( index.internalPointer() ) )
		{
			if (role == Qt::DisplayRole)
			{
				switch ( index.column() )
				{
				case enNumber:
					return model_index->name();

				//case enFS :
				//	return model_index->getPartitionEntry()->getPartitionTypeName();

				case enStart:
					return QString::number( model_index->getPartitionEntry()->getStartSector() );

				case enSize:
					return QString::number( model_index->getPartitionEntry()->getSectorCount() );
				default:
					return "never this text will be show.";
				}
			}
			else
				if ( index.column() == 0 )
				{
					if ( role == Qt::CheckStateRole )
					{
						return static_cast<int>( model_index->getChecked() );
					}
					else
					if (role == Qt::DecorationRole)
					{
						//if (index.column() == DMTreeModel::header_device)
						//{
						//	return model_index->getIcon();
						//}
					}
				}
		}
				return QVariant();
	}
	bool setData(const QModelIndex &index, const QVariant &value, int role)
	{
		if ( !index.isValid() )
			return false;

		if ( auto * model_index = fromIndex(index))
		{
			if (role == Qt::CheckStateRole)
			{
				Qt::CheckState checkState =  (Qt::CheckState)value.toInt();
				model_index->setChecked(checkState);

			}
			emit dataChanged(index,index);
			return true;
		}
		return false;

	}
	PartitionItemIndex * getRootIndex() 
	{
		return RootIndex_;
	}

protected:
	PartitionItemIndex * fromIndex( const QModelIndex & qIndex) const
	{
		if ( qIndex.isValid() )
		{
			auto * model_index = static_cast < PartitionItemIndex *>
				( qIndex.internalPointer() ) ;
			if ( model_index)
				return model_index;
		}
		return RootIndex_;
	}
private:
	PartitionItemIndex * RootIndex_;
};




//class PartitionModel : public QAbstractItemModel
//{
//	Q_OBJECT
//
//public:
//	PartitionModel(QObject *parent);
//	~PartitionModel();
//
//private:
//	
//};

#endif // PARTITIONMODEL_H
