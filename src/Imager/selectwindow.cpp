
#include "selectwindow.h"
#include "devicetableview.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

SelectWindow::SelectWindow(QWidget *parent)
	: QDialog(parent)
{
	//this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

	//QVBoxLayout * mainLayout = new QVBoxLayout(this);
	//QVBoxLayout * tableLayout = new QVBoxLayout(this);
	//
	//TableDevice = new DeviceTableView(this);
	//tableLayout->addWidget(TableDevice);

	//mainLayout->addLayout(tableLayout);

	//QHBoxLayout * buttonLayout = new QHBoxLayout(this);

	//ButtonOK = new QPushButton("&Ok");
	//QSize SizeButtons(75,31);

	//ButtonOK->setMaximumSize(SizeButtons);
	//ButtonOK->setDefault(true);

	//buttonLayout->addWidget(ButtonOK);

	//ButtonCancel = new QPushButton("&Cancel",this);
	//ButtonCancel->setMaximumSize(SizeButtons);
	//ButtonCancel->setAutoDefault(false);
	//buttonLayout->addWidget(ButtonCancel);	

	//mainLayout->addLayout(buttonLayout);

	//setLayout(mainLayout);

	//connect( ButtonOK , SIGNAL(clicked()) , this , SLOT (accept()) );
	//connect( ButtonCancel , SIGNAL(clicked()) , this , SLOT (reject()) );
}

SelectWindow::~SelectWindow()
{
	qDebug("Close (Select Window)...");
}
