#include "copyrangewidget.h"

#include <QtWidgets\QMessageBox>


QLongLongValidator::QLongLongValidator(QObject * parent)
	: QValidator(parent),
	b(Q_UINT64_C(0x8000000000000000)), t(Q_UINT64_C(0x7FFFFFFFFFFFFFFF))
{
}
QLongLongValidator::QLongLongValidator(qlonglong minimum, qlonglong maximum,
	QObject * parent)
	: QValidator(parent), b(minimum), t(maximum)
{
}
QLongLongValidator::~QLongLongValidator()
{
	// nothing
}
QValidator::State QLongLongValidator::validate(QString & input, int &) const
{
	if (input.contains(' '))
		return Invalid;
	if (input.isEmpty() || (b < 0 && input == "-"))
		return Intermediate;
	bool ok;
	qlonglong entered = input.toLongLong(&ok);
	if (!ok || (entered < 0 && b >= 0)) 
	{
		return Invalid;
	} 
	else if (entered >= b && entered <= t) 
	{
		return Acceptable;
	} 
	else 
	{
		if (entered >= 0)
			return (entered > t) ? Invalid : Intermediate;
		else
			return (entered < b) ? Invalid : Intermediate;
	}
}
void QLongLongValidator::setRange(qlonglong bottom, qlonglong top)
{
	b = bottom;
	t = top;
}

void QLongLongValidator::setBottom(qlonglong bottom)
{
	setRange(bottom, top());
}

void QLongLongValidator::setTop(qlonglong top)
{
	setRange(bottom(), top);
}

/************************************************************************/
/*                           CopyRangeWidget                            */
/************************************************************************/
CopyRangeWidget::CopyRangeWidget(QWidget *parent)
	: QWidget(parent)
	, range_data_( nullptr )
{
	ui_.setupUi(this);
	range_data_ = new CopyRangeData( this );

	QObject::connect( range_data_ , 
					  SIGNAL( sourceOffsetChanged( const QString & ) ),
					  ui_.sourceOffset, 
					  SLOT( setText ( const QString & ) ) 
	);

	QObject::connect( range_data_ , 
				 	  SIGNAL( targetOffsetChanged( const QString & ) ),
					  ui_.targetOffset, 
					  SLOT( setText ( const QString & ) ) 
	);

	QObject::connect( range_data_ , 
					  SIGNAL( sectorCountChanged ( const QString & ) ),
					  ui_.sectorsCount, 
					  SLOT( setText ( const QString & ) ) 
	);


	QObject::connect( ui_.sourceOffset , 
					  SIGNAL( textChanged ( const QString & ) ),
					  range_data_,
					  SLOT( setSourceOffset ( const QString & ) ) 
	);
	QObject::connect( ui_.targetOffset , 
					  SIGNAL( textChanged ( const QString & ) ),
					  range_data_,
					  SLOT( setTargetOffset ( const QString & ) ) 
	);
	QObject::connect( ui_.sectorsCount , 
					  SIGNAL( textChanged ( const QString & ) ),
					  range_data_,
					  SLOT( setSectorCount ( const QString & ) ) 
	);

}

CopyRangeWidget::~CopyRangeWidget()
{

}

CopyRangeData * CopyRangeWidget::getRange()
{
	return range_data_;
}

//
//void CopyRangeWidget::setSourceOffset( qlonglong sourceOffset )
//{
//	range_data_.setSourceOffset( sourceOffset );
//	widget_.sourceOffset->setText( QString::number( range_data_.getSourceOffset() ) );
//}
//
//void CopyRangeWidget::setTargetOffset( qlonglong targetOffset )
//{
//	range_data_.setTargetOffset( targetOffset );
//	widget_.targetOffset->setText( QString::number( range_data_.getTargetOffset() ) );
//}
//
//void CopyRangeWidget::setSectorCount( qlonglong sectorCount )
//{
//	range_data_.setSectorCount( sectorCount );
//	widget_.sectorsCount->setText( QString::number( range_data_.getSectorCount() ) );
//}
//
//qlonglong CopyRangeWidget::getSourceOffset()
//{
//	range_data_.setSourceOffset( widget_.sourceOffset->text().toLongLong() );
//	return range_data_.getSourceOffset();
//}
//
//qlonglong CopyRangeWidget::getTargetOffset()
//{
//	range_data_.setTargetOffset( widget_.targetOffset->text().toLongLong() );
//	return range_data_.getTargetOffset() ;
//}
//
//qlonglong CopyRangeWidget::getSectorsCount()
//{
//	range_data_.setSectorCount( widget_.sectorsCount->text().toLongLong() );
//	return range_data_.getSectorCount() ;
//}
//
//void CopyRangeWidget::setRange( qlonglong sourceOffset, qlonglong targetOffset, qlonglong sectorsCount )
//{
//	//range_data_.setRange( sourceOffset , targetOffset , sectorsCount );
//	this->setSourceOffset( sourceOffset );
//	this->setTargetOffset( targetOffset );
//	this->setSectorCount( sectorsCount );
//}
//bool CopyRangeWidget::validate( qlonglong source_size , qlonglong target_size , QString & strError )
//{
//	return range_data_.validate( source_size , target_size , strError );
//}
//
//RangeWidget::RangeWidget( QWidget *parent ) : Offset_( 0 )
//	, sectorsCount_( 0 )
//	, disk_ ( nullptr )
//{
//	widget_.setupUi(this);
//	connect( widget_.groupBox, SIGNAL( clicked(bool) ), SLOT( check_clicked(bool) ) );
//}
//
//RangeWidget::~RangeWidget()
//{
//	disk_ = nullptr;
//}
//
//void RangeWidget::setOffset( ULONGLONG offset )
//{
//	Offset_ = offset;
//	widget_.offsetEdit->setText( QString::number(Offset_) );
//}
//
//ULONGLONG RangeWidget::getOffset()
//{
//	Offset_ = widget_.offsetEdit->text().toLongLong();
//	return Offset_;
//}
//
//void RangeWidget::setSectorsCount( ULONGLONG sectosCount )
//{
//	sectorsCount_ = sectosCount;
//	widget_.sectorsCountEdit->setText( QString::number(sectorsCount_) );
//}
//
//ULONGLONG RangeWidget::getSectorsCount()
//{
//	sectorsCount_ = widget_.sectorsCountEdit->text().toLongLong();
//	return sectorsCount_;
//}
//
//void RangeWidget::check_clicked( bool bCkicked )
//{
//	if ( widget_.groupBox->isChecked() )
//	{
//		if ( disk_)
//			if ( !disk_->isDetected() )
//			{
//				PortArray portArray ;
//				portArray.push_back( disk_->getPort() );
//				QString outputText =  QString::fromLocal8Bit("<B>Утройство было не определено.</B>");
//				QString infoText = QString::fromLocal8Bit("Определить утройство?");
//				QMessageBox msgBox;
//				msgBox.setText(outputText);
//				msgBox.setInformativeText(infoText);
//				msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
//				msgBox.setDefaultButton(QMessageBox::Ok);
//				msgBox.setIcon(QMessageBox::Question);
//				int nResult = msgBox.exec();
//
//				if ( nResult == QMessageBox::Ok)
//				{
//					emit DetectDevicePressed( portArray );
//				}
//				else
//					if (nResult == QMessageBox::Cancel)
//					{
//						widget_.groupBox->setChecked(false);
//					}
//
//			}
//	}
//}
