#ifndef SECTORMAPWIDGET_H
#define SECTORMAPWIDGET_H

#include <QtWidgets/QWidget>
#include <QPainter>

#include <QVector>
#include <QFile>

#include "assert.h"

#include "sectorview.h"

class WIDGETLIBRARY_EXPORT SectorMapWidget
	: public QWidget
{
	Q_OBJECT

public:
	SectorMapWidget(QWidget *parent)
		: QWidget(parent)
	{
		sectorWiew_ = new SectorView(this);
		srollBar_ = new QScrollBar( Qt::Vertical , this);
		mainLayout_ = new QHBoxLayout(this);
		mainLayout_->addWidget(sectorWiew_);
		mainLayout_->addWidget(srollBar_);
		mainLayout_->setMargin(0);
		mainLayout_->setSpacing(2);

		connect( sectorWiew_ , SIGNAL( RangeChanged( int ) ) , this, SLOT( setScrollRange( int ) ) );
		connect( srollBar_ , SIGNAL ( valueChanged ( int ) ) , sectorWiew_, SLOT ( setCurrentNumber( int ) ) );
		connect( sectorWiew_ , SIGNAL ( ChangePosition ( int ) ) , srollBar_, SLOT ( setValue( int ) ) );

	}
	~SectorMapWidget()
	{
		qDebug() << "dtor [\'SectorMapWidget\']";
	}
	SectorView * getView() 
	{
		return sectorWiew_;
	}
	protected slots:
		void setScrollRange( int iValue )
		{
			srollBar_->setRange(0,iValue);
			//qDebug() << "slider" << iValue;
		}
private:
	SectorView * sectorWiew_;
	QScrollBar * srollBar_;
	QHBoxLayout * mainLayout_;
};

#endif // SECTORMAPWIDGET_H
