#include "copypropertiesui.h"


CopyPropertiesUi::CopyPropertiesUi(QWidget *parent)
	: QWidget(parent)
	, id_ ( -1 )
{
	ui_.setupUi( this );
	ui_.directionCombo->addItem( QIcon ( "icons\\forward.png" ) , QString::fromLocal8Bit("Forward") );
	ui_.directionCombo->addItem( QIcon ( "icons\\backward.png" ) , QString::fromLocal8Bit("Backward") );
	//this->setUiProperties();
}

CopyPropertiesUi::~CopyPropertiesUi()
{
	qDebug() << "dtor [CopyPropertiesUi]";
}


