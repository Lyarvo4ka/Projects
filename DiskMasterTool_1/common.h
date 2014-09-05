#ifndef _COMMON_HEADER
#define _COMMON_HEADER

#include <QMessageBox>
#include <QPushButton>
#include <QToolButton>

#include "disk.h"
#include <dbt.h>


	void TraceBuf(char* buf,int len);
	int CheckForZero(void* buf,size_t _size);
	void DiskStringFromBuf(QString& str, quint8* buf, char length);


class HoveredButton : public QPushButton
{
	Q_OBJECT

public:
	HoveredButton(QWidget *parent = 0);
	~HoveredButton();

	void  enterEvent( QEvent * event );
	void  leaveEvent( QEvent * event );

	virtual QSize  minimumSizeHint() const
	{
		return QSize(60,60);
	}
};

class ResizebleToolButton : public QToolButton
{
	Q_OBJECT
public:
	ResizebleToolButton(QSize size=QSize(), QWidget *parent = 0);

private:
	QSize minSizeHint;

	virtual QSize  minimumSizeHint() const
	{
		return minSizeHint;
	}
};


class MyMessageBox : public QMessageBox 
{

public:
	int width;
	int height;

	void setSize(int w,int h)
	{
		width = w;
		height = h;

	}
protected:
	
	void showEvent(QShowEvent* event) 
	{
		QMessageBox::showEvent(event);
		setFixedSize(width, height);
	}
};

#endif