#include "devicewidget.h"

 #include <QIcon>
 #include <QtWidgets\QComboBox>

DeviceWidget::DeviceWidget(QWidget *parent)
	: QWidget(parent)
{
	deviceWidgetUi_.setupUi(this);
	connect( deviceWidgetUi_.deviceComboBox, SIGNAL (currentIndexChanged ( int ) ) , this, SLOT( indexChanged(int) ) );
}
DeviceWidget::~DeviceWidget()
{

}

void DeviceWidget::indexChanged( int nIndex )
{
	emit deviceIndexChanged(nIndex);
}

void DeviceWidget::setWidgetName( const QString & nameWidget )
{
	deviceWidgetUi_.deviceGroupBox->setTitle(nameWidget);
}

void DeviceWidget::add_data( const QString & name, QIcon icon  )
{
	deviceWidgetUi_.deviceComboBox->addItem( icon , name );
}

void DeviceWidget::change_data( int nIndex , const QString & name, QIcon icon )
{
	if ( nIndex < deviceWidgetUi_.deviceComboBox->count() )
	{
		deviceWidgetUi_.deviceComboBox->setItemText( nIndex , name );
		deviceWidgetUi_.deviceComboBox->setItemIcon( nIndex , icon );
	}
}

int DeviceWidget::getCurrentIndex() const
{
	return deviceWidgetUi_.deviceComboBox->currentIndex();
}

void DeviceWidget::ChangeDevice( int nIndex )
{
	deviceWidgetUi_.deviceComboBox->setCurrentIndex(nIndex);
}

void DeviceWidget::setSerialNumberText( const QString & text )
{
	deviceWidgetUi_.serialNumberText->setText( text );
}

void DeviceWidget::setSectorCountText( const QString & text )
{
	deviceWidgetUi_.sectorsCountText->setText( text );
}

void DeviceWidget::setSectorSizeText( const QString & text )
{
	deviceWidgetUi_.sectorSizeText->setText( text );
}

void DeviceWidget::RefreshClicked()
{
	emit deviceDetect();
}
