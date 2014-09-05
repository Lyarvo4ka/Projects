#ifndef SECTORMODEL_H
#define SECTORMODEL_H

#include <QtWidgets/QWidget>
#include <QPainter>

#include <QVector>
#include <QFile>

#include "assert.h"
#include "windows.h"
#include <QDebug>
#include <QReadWriteLock>
#include "widgetlibrary_global.h"

typedef QVector<qlonglong> ArrayBadSectors;


enum SECTOR_STATUS { NOT_READ = 0, READ_BAD = 0xF0, READ_GOOD , UNKNOWN_BAD };

class WIDGETLIBRARY_EXPORT SectorsInfo
{
public:
	SectorsInfo ( const qlonglong bad_sectors = 0 , const qlonglong read_sectors = 0, const qlonglong unread_sectors = 0 )
		: bads_( bad_sectors )
		, reads_ ( read_sectors )
		, unreads_ ( unread_sectors )
	{

	}
	void setBads( qlonglong bas_sectors )
	{
		QWriteLocker locker( & bads_locker_ );
		bads_ = bas_sectors;
	}
	void addBads( DWORD count )
	{
		QWriteLocker locker( & bads_locker_ );
		bads_ += count;
	}
	qlonglong getBads() const
	{
		QReadLocker locker( (QReadWriteLock*) & bads_locker_ );
		return bads_;
	}
	void setReads( qlonglong read_sectors )
	{
		QWriteLocker locker( & reads_locker_ );
		reads_ = read_sectors;
	}
	void addReads( qlonglong count )
	{
		QWriteLocker locker( & reads_locker_ );
		reads_ += count;
	}
	void reduceUnread( qlonglong count )
	{
		QWriteLocker locker( & unreads_locker_);
		unreads_ -= count;
	}
	qlonglong getReads() const
	{
		QReadLocker locker( (QReadWriteLock*) & reads_locker_ );
		return reads_;
	}
	void setUnReads( qlonglong unread_sectors )
	{
		QWriteLocker locker( & unreads_locker_ );
		unreads_ = unread_sectors;
	}
	void addUnReads( qlonglong count )
	{
		QWriteLocker locker( & unreads_locker_ );
		unreads_ += count;
	}
	qlonglong getUnReads() const
	{
		QReadLocker locker( (QReadWriteLock*) & unreads_locker_ );
		return unreads_;
	}
private:
	qlonglong bads_;
	qlonglong reads_;
	qlonglong unreads_;
	QReadWriteLock bads_locker_;
	QReadWriteLock reads_locker_;
	QReadWriteLock unreads_locker_;
};

class WIDGETLIBRARY_EXPORT BlockBuffer
{
public:
	BlockBuffer(qint32 buffer_size , const ArrayBadSectors & bads_array , qlonglong offset = 0 )
		: size_( buffer_size )
		, buffer_ ( nullptr )
	{
		assert(size_ > 0 && "ctor BlockBuffer size is 0.");
		buffer_ = new BYTE[ size_ ];
		memset(buffer_ , READ_GOOD , sizeof(BYTE)*size_);
		if ( ! bads_array.empty() )
		{
			qlonglong tempSector = 0;
			for ( auto Iter = bads_array.begin(); Iter != bads_array.end(); ++Iter)
			{
				tempSector = *Iter - offset;
				if ( tempSector <= buffer_size)
				{
					buffer_[tempSector] = READ_BAD;
				}
			}
		}
	}
	BlockBuffer( qint32 buffer_size, int initStatus = 0 )
		: size_( buffer_size )
		, buffer_ ( new BYTE[ size_ ] )
	{
		memset( buffer_, initStatus, sizeof(BYTE)*size_ );
	}
	BlockBuffer( std::vector<BYTE> data)
		: size_( data.size() )
		, buffer_ ( nullptr )
	{
		assert(size_ > 0 && "ctor BlockBuffer size is 0.");
		buffer_ = new BYTE[ size_ ];
		memcpy ( buffer_ , data.data(), size_ );
	}

	~BlockBuffer()
	{
		if ( buffer_ )
		{
			delete buffer_;
			buffer_ = nullptr;
		}
	}
	qint32 size() const
	{
		return size_;
	}
	BYTE * buffer() const
	{
		return buffer_;
	}
private:
	BlockBuffer(const BlockBuffer & );
private:
	qint32 size_;
	BYTE * buffer_;

};

class WIDGETLIBRARY_EXPORT AbsractSectorModel
	: public QObject
{
	Q_OBJECT
public:
	AbsractSectorModel()
		: total_sectors_(0)
		, bLoaded_( false )
	{

	}
	virtual ~AbsractSectorModel() = 0
	{

	}
	void setTotalSectors( qlonglong sectorsCount )
	{
		total_sectors_ = sectorsCount;
	}
	inline qlonglong total_sectors() const
	{
		return total_sectors_;
	}
	bool isLoaded() const
	{
		return bLoaded_;
	}
	void SetLoaded( bool loaded = true )
	{
		bLoaded_ = loaded;
	}
	virtual void createMap( qlonglong count, const QString & filePath ) = 0;
	virtual void loadMap( const QString & filePath ) = 0;

	virtual void updateBlock( qlonglong start, qint32 count, int initValue ) = 0;
	virtual void updateBlocks( qlonglong start, std::vector< BYTE > & block) = 0;
	virtual void updateBads( qlonglong start, qint32 count, const ArrayBadSectors & bads_array ) = 0;
	virtual void updateSector( qlonglong pos , int status ) = 0;

	virtual void getSectorsBlock( BlockBuffer & data_block, qlonglong pos ) = 0;
	virtual bool getUnReadSectors( qlonglong & startSector , qint32 & count ) = 0;
	virtual bool getBadSectors( qlonglong & startSector , qint32 & count ) = 0;
private:
	qlonglong total_sectors_;
	bool bLoaded_;

signals:
	void Block_Updated(qlonglong);
	void Sector_Updated(qlonglong);
};

class WIDGETLIBRARY_EXPORT SectorModel
	: public AbsractSectorModel
{
	Q_OBJECT

	static const DWORD DefaultReadSectors = 128;

public:
	SectorModel( )
	{

	}
	~SectorModel()
	{
		qDebug() << "dtor [\'SectorModel\']";
		file_.close();
		this->SetLoaded(false);

	}
	qlonglong getBadsCount() const
	{
		return sectorInfo_.getBads();
	}
	qlonglong getReadCount() const
	{
		return sectorInfo_.getReads();
	}
	qlonglong getUnreadCount() const
	{
		return sectorInfo_.getUnReads();
	}
	void createMap(qlonglong count, const QString & filePath) override
	{
		if (file_.isOpen())
			file_.close();
		setTotalSectors( count );
		file_.setFileName( filePath );
		if ( file_.open( QIODevice::ReadWrite | QIODevice::Unbuffered | QIODevice::Truncate) )
		{
			file_.setPermissions( QFile::ReadOwner | QFile::WriteOwner );
			//ResetFile( &file_ , NOT_READ, total_sectors() );
			file_.resize( filePath , total_sectors() );	// ???
			this->SetLoaded();
			sectorInfo_.setUnReads( count );
		}
	}
	void loadMap(const QString & filePath)
	{
		if (file_.isOpen())
			file_.close();
		file_.setFileName(filePath);
		if ( file_.open( QIODevice::ReadWrite ) )
		{
			setTotalSectors( file_.size() );
			this->SetLoaded();
		}
	}
	void updateBlock( qlonglong start, qint32 count, int initValue) override
	{
		if ( ( start + count ) <= total_sectors() )
		{
			BlockBuffer buffer(count,initValue);
			file_.seek(start);
			file_.write(( char *)buffer.buffer() , buffer.size() );
			start += count;
			sectorInfo_.addReads( count );
			sectorInfo_.reduceUnread( count );
			emit Block_Updated(start);
		}

	}
	void updateBlocks( qlonglong start, std::vector< BYTE > & block) override
	{
		if ( !block.empty() )
		if ( ( start + block.size() ) <= total_sectors() )
		{
			BlockBuffer buffer(block);
			file_.seek(start);
			file_.write(( char *)buffer.buffer() , buffer.size() );
			start += block.size();
			emit Block_Updated(start);
		}

	}
	void updateBads( qlonglong start, qint32 count, const ArrayBadSectors & bads_array) override
	{
		if ( ( start + count ) <= total_sectors() )
		{
			BlockBuffer buffer(count , bads_array , start );
			file_.seek(start);
			file_.write(( char *)buffer.buffer(),buffer.size());
			start += count;
			sectorInfo_.setBads( count );
			emit Block_Updated(start);
		}
	}
	void updateSector( qlonglong pos , int status ) override
	{
		if ( pos <= total_sectors() )
		{
			char val = status;
			if ( status == READ_BAD )
				sectorInfo_.addBads( 1 );
			else
				sectorInfo_.addReads( 1 );
			sectorInfo_.reduceUnread( 1 );
			file_.seek(pos);
			file_.write(&val,1);
			emit Sector_Updated(pos);
		}
	}
	void getSectorsBlock( BlockBuffer & data_block, qlonglong pos ) override
	{
		if ( (pos + data_block.size() ) <= total_sectors() )
		{
			file_.seek(pos);
			file_.read(( char *)data_block.buffer(), data_block.size() );
		}
	}
	bool getUnReadSectors( qlonglong & startSector , qint32 & count ) override 
	{
		count = 0;
		qint32 sectors = DefaultReadSectors;
		if ( startSector + sectors > total_sectors() )
			sectors = total_sectors() - startSector;

		if ( sectors <= 0 )
			return false;

		BYTE buffer[DefaultReadSectors];
		ZeroMemory( buffer , sizeof( BYTE ) * DefaultReadSectors );

		file_.seek(startSector);
		file_.read(( char *)buffer, sectors );
		qint32 iLBA = 0;
		for ( iLBA = 0 ; iLBA < sectors ; ++ iLBA)
			if ( buffer[ iLBA ] == SECTOR_STATUS::NOT_READ )
			{
				++count;
			}
			else
				if( count > 0 )
				{
					startSector += ( iLBA - count );
					return true;
				}

		if ( count == 0)
			return false;
		startSector += ( iLBA - count );
		return true;
	}
	bool getBadSectors( qlonglong & startSector , qint32 & count )
	{
		return false;
	}
	//BOOL getEndRegion();
private:
	bool ResetFile(QFile * file, char val , qlonglong size )
	{
		assert( file != nullptr );
		file_.resize( file->fileName() , total_sectors() );	// ???
		qlonglong curByte = 0;
		qlonglong tempPos = 0;
		const int BufferSize = 256*512;
		char buffer[BufferSize];
		memset( &buffer, val, sizeof(char) * BufferSize );
		int writeSize = BufferSize;
		qint64 bytesWritten = 0;
		while ( curByte < size )
		{
			tempPos = curByte + BufferSize;
			if (tempPos > size )
			{
				writeSize = size - curByte;
			}
			bytesWritten = file->write( buffer, writeSize );
			if ( bytesWritten != writeSize)	// error
				return false;

			curByte += bytesWritten;

		}
		return true;
	}
private:
	QFile file_;
	SectorsInfo sectorInfo_;
};

#endif // SECTORMODEL_H
