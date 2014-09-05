/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "printview.h"
#include <QDebug>
#include <QPrinter>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QDateTime>


PrintView::PrintView(QString headerStr,QString str)
{
	layout = new QVBoxLayout(this);
	table = new QTableView(this);
	table->setEnabled(true);
	if(!headerString.isEmpty())
		headerString = headerStr+"\n";
	//str += " ----------------------------------------------------------------------------- \n";
	label = new QLabel(/*headerString+"\n"+*/str,this);
	//label->setTextFormat(Qt::RichText);
	label->setEnabled(true);
	layout->addWidget(label);
	layout->addWidget(table);
	setLayout(layout);
//	show();
	listSizes = 0;
	rowCount = 0;
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void PrintView::print(QPrinter *printer)
{
#ifndef QT_NO_PRINTER
	qreal left;
	qreal top;
	qreal right;
	qreal bottom;
	printer->getPageMargins(&left,&top,&right,&bottom, QPrinter::Point); 
	QRect rectPage = printer->pageRect();
	//rectPage = printer->paperRect();

	QDateTime date = QDateTime::currentDateTime();
	QString timeStr = date.toString(Qt::DefaultLocaleShortDate);	

	if(listSizes)
	{
		int offset=0;
		qDebug() << "Height: "<< rowCount*table->rowHeight(0);
		
		QPainter painter;
	
		if(printer->paintingActive())
			qWarning("painting is active!");

	
		if (! painter.begin(printer)) { // failed to open file
		    qWarning("failed to open file, is it writable?");
		    return;
		}
		resize(printer->width(), printer->height());
		rowCount++;

		qDebug() << label->sizeHint().height();
		int rowsPerLabel = label->sizeHint().height()/table->rowHeight(0)+1;
	
		resize(width(),table->rowHeight(0)*rowCount+(rowsPerLabel+1)*table->rowHeight(0));
		int rowPerPage = rectPage.height()/table->rowHeight(0)-3;
		int pageHeight = table->rowHeight(0)*rowPerPage;
		int page=0;
		int maxPage=1;
		int topOffset;
		if(rowCount+1 > rowPerPage)
			maxPage = (rowCount+1)/rowPerPage;

		for(int i = 0;i<rowCount+1;i+=rowPerPage)
		{
			int fontSize = font().pointSize();
			
			if(!headerString.isEmpty())
				topOffset = 50;
			else
				topOffset = 10;

			render(&painter,QPoint(rectPage.x(),topOffset),QRegion (0, i*table->rowHeight(0), rectPage.width(),pageHeight));
			
			if(!headerString.isEmpty())
			{
				painter.drawText(10,4*fontSize,headerString);
				painter.drawLine(10,5*fontSize,rectPage.width()-10,5*fontSize);
			}
			painter.drawText(10,rectPage.height()-2*fontSize,QString("Page %1 / %2").arg(page).arg(maxPage));
			painter.drawText(rectPage.width()-120,rectPage.height()-2*fontSize,timeStr);
	
			if((i+rowPerPage)<rowCount+1)
			{		
				if (!printer->newPage()) 
				{
					qWarning("failed in flushing page to disk, disk full?");
					return;
				}
			}
			page++;
		}
			/*if(i+rowPerPage<rowCount)
					i+=rowPerPage;
				else
					i+=(rowCount-rowPerPage);*/
		//if(rowCount*table->rowHeight(0) > printer->height()/*printer->fullPage()*/)
		//{
		//	offset+= row*table->rowHeight(0);
		//	if (!printer->newPage()) 
		//	{
		//		qWarning("failed in flushing page to disk, disk full?");
		//		return;
		//	}
		//	//render(&painter,QPoint(),QRegion (0, offset ,printer->width(),printer->height()));
		//	
		//}
		painter.end();
	}
#endif
}

void PrintView::setTableColumnSizes()
{
	if(listSizes)
	{
		for(int i=0;i<listSizes->count();i++)
			table->setColumnWidth(i,(*listSizes)[i]);
	}
}
