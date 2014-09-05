#ifndef SECTORVIEW_H
#define SECTORVIEW_H

const int RectSize = 6;
const int MarginSector = 2;
const int SectorRectSize = RectSize + MarginSector;

#include "sectormodel.h"

#include <QtWidgets\QWidget>

#include <QtWidgets\QScrollBar>
#include <QtWidgets\QHBoxLayout>
#include <QDebug>
class WIDGETLIBRARY_EXPORT SectorView : public QWidget
{
	Q_OBJECT
public:
	SectorView(QWidget *parent);
	~SectorView();
	void setModel( AbsractSectorModel * model );
	bool isReady() const
	{
		return bReady;
	}
protected:
	void paintEvent(QPaintEvent *event) override;
	void resizeEvent ( QResizeEvent * event ) override;

signals:
	void RangeChanged( int );
	void ChangePosition ( int );
	public slots:
		void setCurrentNumber( int iNumber)
		{
			curNumber_ = iNumber;
			this->update();
		}
		void sector_updated( qlonglong sector) 
		{
			int iNumber = sector / objectCount;
			if ( iNumber != curNumber_ )
			{
				ChangePosition(iNumber);
				setCurrentNumber(iNumber);
			}
			else
				this->update();
		}
		void block_updated( qlonglong sector) 
		{
			sector_updated(sector);
		}
private:
	void DiscoverObject()
	{
		xCount = this->rect().width() /  SectorRectSize;
		yCount = this->rect().height() / SectorRectSize;
		objectCount = xCount * yCount;
		int maxRange = model_->total_sectors() / objectCount;
		bReady = true;
		emit RangeChanged( maxRange );
	}
private:
	AbsractSectorModel * model_;
	bool bReady ;
	int xCount;
	int yCount;
	int objectCount;
	int curNumber_;
};


#endif // SECTORVIEW_H
