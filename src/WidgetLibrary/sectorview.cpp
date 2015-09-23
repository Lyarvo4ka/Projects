#include "sectorview.h"




#include <QPaintEvent>
#include <QPainter>


SectorView::SectorView(QWidget *parent)
	: QWidget(parent)
	, model_(nullptr)
	, bReady( false )
	, xCount( 0 )
	, yCount( 0 )
	, objectCount( 0 )
	, curNumber_( 0 )
{
}

SectorView::~SectorView()
{
	qDebug() << "dtor [\'SectorView\']";

}

void SectorView::paintEvent(QPaintEvent *event)
{
	if (isReady())
	{
		//static int iCounter = 0;
		//qDebug() << "paintEvent" << ++iCounter;
		QPainter painter(this);
		painter.save();
		//painter.setRenderHint(QPainter::Antialiasing, true);
		QPen pen(Qt::darkGray);
		QPen pen_black( Qt::black );
		//pen.setWidth(2);
		painter.setPen(pen_black);
		int xPos = 0;
		int yPos = 0;
		int iValX = 0;
		int iValY = 0;
		int iSectorNumber = 0;
		qlonglong posValue = objectCount * curNumber_;
		qlonglong resValue = model_->total_sectors() - posValue;
		BlockBuffer * block = nullptr;
		if ( resValue >= objectCount )
			block = new BlockBuffer( objectCount );
		else
			block = new BlockBuffer( (int) resValue );
		if ( model_->isLoaded() )
		{
		model_->getSectorsBlock(*block , posValue);
		for ( yPos = 0; yPos < yCount ; ++yPos)
		{
			if ( iSectorNumber >= block->size() )
				break;
			iValX = 0;
			for ( xPos = 0; xPos < xCount; ++xPos)
			{
				switch ( block->buffer()[iSectorNumber] )
				{
				case SECTOR_STATUS::NOT_READ:
					painter.setPen(pen);
					painter.setBrush(Qt::white);	
					break;
				case SECTOR_STATUS::READ_GOOD:
					painter.setPen(pen_black);
					painter.setBrush(Qt::green);	
					break;
				case SECTOR_STATUS::READ_BAD:
					painter.setPen(pen_black);
					painter.setBrush(Qt::red);	
					break;
				case SECTOR_STATUS::UNKNOWN_BAD:
					painter.setPen(pen_black);
					painter.setBrush(Qt::blue);	
					break;
				}
				painter.drawRect(iValX , iValY, RectSize , RectSize );
				iValX += (SectorRectSize);
				++iSectorNumber;
			}
			iValY += (SectorRectSize);
		}

		}
		delete block;

		painter.restore();
	}
	//static int nNum = 0;
	//qDebug() << "paint Event" << ++nNum;
	else
	{
		QPainter painter(this);

		painter.drawText(event->rect().center(),QString( "Sector Map didn't load" ) );

	}
}
void SectorView::resizeEvent ( QResizeEvent * event )
{
	if (isReady())
	{
		int newXCount = this->rect().width() /  SectorRectSize;
		int newYCount = this->rect().height() / SectorRectSize;
		if ( ( newXCount != xCount ) || ( newYCount != yCount ) )
		{
			DiscoverObject();
		}
	}
	//QWidget::resizeEvent(event);
}
void SectorView::setModel( AbsractSectorModel * model )
{
	model_ = model;
	connect( model_ , SIGNAL( Sector_Updated( qlonglong ) ) , this , SLOT ( sector_updated( qlonglong ) ) );
	connect( model_ , SIGNAL( Block_Updated( qlonglong ) ) , this , SLOT ( block_updated( qlonglong ) ) );
	DiscoverObject();

}
