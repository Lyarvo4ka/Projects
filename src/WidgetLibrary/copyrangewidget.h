#ifndef COPYRANGEWIDGET_H
#define COPYRANGEWIDGET_H

#include "widgetlibrary_global.h"

#include <QtWidgets/QWidget>
#include "windows.h"
#include "ui_CopyRangeWidgetUi.h"


class WIDGETLIBRARY_EXPORT CopyRangeData
	: public QObject
{
	Q_OBJECT

public:
	explicit CopyRangeData( QObject * parent = 0 )
		: sourceOffset_ ( 0 )
		, tartgetOffset_ ( 0 )
		, sectorCount_ ( 0 )
	{

	}
	void Initialize()
	{
		setSourceOffset( 0 );
		setTargetOffset( 0 );
		setSectorCount( 0 );
	}
	qlonglong getSourceOffset() const
	{
		return sourceOffset_;
	}
	qlonglong getTargetOffset() const
	{
		return tartgetOffset_;
	}
	qlonglong getSectorCount() const
	{
		return sectorCount_;
	}
	void setRange( qlonglong source_offset , qlonglong target_offset , qlonglong sector_count )
	{
		setSourceOffset( source_offset );
		setTargetOffset( target_offset );
		setSectorCount( sector_count );
	}
	bool validate( qlonglong source_size , qlonglong target_size , QString & error_str )
	{
		if ( sourceOffset_ < 0 )
		{
			error_str = "Ошибка. Смещение источника меньше 0.";
			return false;
		}
		if ( tartgetOffset_ < 0 )
		{
			error_str = "Ошибка. Смещение приемника меньше 0.";
			return false;
		}
		if ( sectorCount_ < 0 )
		{
			error_str = "Ошибка. Количество секторов меньше 0.";
			return false;
		}

		auto source_count = sourceOffset_ + sectorCount_;
		auto target_count = tartgetOffset_ + sectorCount_;

		if ( source_count > source_size )
		{
			error_str = "Ошибка. Введенные данные выходят за границу источнкика.";
			return false;
		}
		if ( target_count > target_size )
		{
			error_str = "Ошибка. Введенные данные выходят за границу приемника.";
			return false;
		}

		return true;
	}

public slots:
	void setSourceOffset( qlonglong souce_offset )
	{
		sourceOffset_ = souce_offset;
		emit sourceOffsetChanged( QString::number( sourceOffset_) );
	}
	void setTargetOffset( qlonglong target_offset )
	{
		tartgetOffset_ = target_offset;
		emit targetOffsetChanged( QString::number( tartgetOffset_) );
	}
	void setSectorCount( qlonglong sector_count )
	{
		sectorCount_ = sector_count ;
		emit sectorCountChanged( QString::number( sectorCount_) );
	}
	void setSourceOffset( const QString & souce_offset )
	{
		sourceOffset_ = souce_offset.toLongLong() ;
	}
	void setTargetOffset(const QString & target_offset )
	{
		tartgetOffset_ = target_offset.toLongLong() ;
	}
	void setSectorCount( const QString & sector_count )
	{
		sectorCount_ = sector_count.toLongLong() ;
	}

signals:
	void sourceOffsetChanged( const QString & );
	void targetOffsetChanged( const QString & );
	void sectorCountChanged( const QString & );
private:
	qlonglong sourceOffset_;
	qlonglong tartgetOffset_;
	qlonglong sectorCount_;
};


class  QLongLongValidator 
	: public QValidator
{
	Q_OBJECT
	Q_PROPERTY(qlonglong bottom READ bottom WRITE setBottom);
	Q_PROPERTY(qlonglong top READ top WRITE setTop);

public:
	explicit QLongLongValidator(QObject * parent);
	QLongLongValidator(qlonglong bottom, qlonglong top, QObject * parent);
	~QLongLongValidator();

	QValidator::State validate(QString &, int &) const;

	void setBottom(qlonglong);
	void setTop(qlonglong);
	virtual void setRange(qlonglong bottom, qlonglong top);

	qlonglong bottom() const { return b; }
	qlonglong top() const { return t; }

private:
	Q_DISABLE_COPY(QLongLongValidator)

	qlonglong b;
	qlonglong t;
};


///////////////////////////CopyRangeWidget/////////////////////////////
class WIDGETLIBRARY_EXPORT CopyRangeWidget : public QWidget
{
	Q_OBJECT

public:
	explicit CopyRangeWidget(QWidget *parent);
	~CopyRangeWidget();

	//void setSourceOffset( qlonglong sourceOffset );
	//void setTargetOffset( qlonglong targetOffset );
	//void setSectorCount( qlonglong sectorCount );

	//qlonglong getSourceOffset();
	//qlonglong getTargetOffset();
	//qlonglong getSectorsCount();

	//void setRange( qlonglong sourceOffset, qlonglong targetOffset, qlonglong sectorsCount );

	//bool validate( qlonglong source_size , qlonglong target_size , QString & strError );

	CopyRangeData * getRange();

private:
	CopyRangeData *range_data_;

	Ui::copyRangeWidget ui_;
};

//
//class RangeWidget
//	: public QWidget
//{
//	Q_OBJECT
//
//public:
//	RangeWidget(QWidget *parent);
//	~RangeWidget();
//	void setOffset( ULONGLONG offset);
//	ULONGLONG getOffset();
//	void setSectorsCount( ULONGLONG sectosCount);
//	ULONGLONG getSectorsCount();
//private:
//	ULONGLONG Offset_;
//	ULONGLONG sectorsCount_;
//
//	Ui::rangeWidget widget_;
//};
#endif // COPYRANGEWIDGET_H
