#include "common.h"
#include <QtGui>

void TraceBuf(char* buf,int len)
{
	QString str;
	bool reminder=false;
	for(int i=0; i < len; i++)
	{				
		if(!(i%16)) 
		{
			if(!i)
				goto append_buf;
		//	str.Format(_T("\n             %02X"), buf[i]);
			qDebug() << str;
			reminder=false;
			str=QString(" 0x%1").arg((quint8)buf[i],2,16,QLatin1Char('0'));
		}
		else 
		{
append_buf:
			reminder=true;
			str+=QString(" 0x%1").arg((quint8)buf[i],2,16,QLatin1Char('0'));			
		}
	}

	if(reminder)
		qDebug() << str;
	
}

int CheckForZero(void* buf,size_t _size)
{
	int pos=0;
	for(int i=0; i<_size;i++)
	{
		char val = *((char*)buf+i);
		if(val)
		{
			pos++;
			return pos;
		}
	}
	return pos;
}



void ParseHddStrings(QByteArray* out_str, unsigned char* str,int len)
{
	int blank_pos=0;
	char chr;
	out_str->append((char*)str,len);
	*out_str = out_str->trimmed();
	if(out_str->size() % 2)
		len = out_str->size()-1;
	for(int i=0;i<len;i+=2)
	{
		chr = *(out_str->data()+i);
		*(out_str->data()+i)=*(out_str->data()+i+1);
		*(out_str->data()+i+1)=chr;
		/*temp=out_str[i];
		out_str[i]=out_str[i+1];
		out_str[i+1]=temp;*/
	/*	out_str->append(str[i+1]);
		out_str->append(str[i]);*/
	}
	
}


void DiskStringFromBuf(QString& str, quint8* buf, char length)
{
	str=QString((char*)buf).left(length);
	str=str.trimmed();	
}





ResizebleToolButton::ResizebleToolButton(QSize size,QWidget *parent)
	: QToolButton(parent)
{
	minSizeHint = size;
}

HoveredButton::HoveredButton(QWidget *parent)
	: QPushButton(parent)
{

}

HoveredButton::~HoveredButton()
{

}

void HoveredButton::enterEvent ( QEvent * event )
{
	//	QEasingCurve easing(QEasingCurve::OutExpo);
	//	for(qreal t = 0.0; t < 1.0; t+=0.1)
	//  qWarning() << "Effective progress" << t << " is
	//		           << easing.valueForProgress(t);
	if(isEnabled())
	{
		QPropertyAnimation *animation = new QPropertyAnimation(this, "iconSize");
		animation->setDuration(400);
		animation->setStartValue(QSize(32,32));
		animation->setEndValue(QSize(48,48));
		animation->setEasingCurve(QEasingCurve::OutSine);
		animation->start();
	}
}


void HoveredButton::leaveEvent ( QEvent * event )
{
	if(isEnabled())
	{
		QPropertyAnimation *animation = new QPropertyAnimation(this, "iconSize");
		animation->setDuration(400);
		animation->setStartValue(QSize(48,48));
		animation->setEndValue(QSize(32,32));
		animation->setEasingCurve(QEasingCurve::OutSine);
		animation->start();
	}
}


