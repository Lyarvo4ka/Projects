#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H


#include "widgetlibrary_global.h"
// warning C4482: nonstandard extension used: enum
#pragma warning(disable : 4482)

#include <QtWidgets/QWidget>
#include "ui_DeviceWidgetUi.h"
#include <windows.h>

class WIDGETLIBRARY_EXPORT DeviceWidget 
	: public QWidget
{
	Q_OBJECT

public:
	DeviceWidget(QWidget *parent);
	~DeviceWidget();

	void setWidgetName( const QString & nameWidget);
	int getCurrentIndex() const;
	void ChangeDevice( int nIndex );
	void setSerialNumberText( const QString & text );
	void setSectorCountText( const QString & text );
	void setSectorSizeText( const QString & text );
	void add_data( const QString & name, QIcon icon = QIcon());
	void change_data( int nIndex , const QString & name, QIcon icon = QIcon() );
private slots:
	void indexChanged(int nIndex);
	void RefreshClicked();

signals:
	void deviceIndexChanged(int);
	void deviceDetect();
private:
	Ui::deviceWidgetUi deviceWidgetUi_;
};
//
#include "ui_ErasePatternUi.h"



class WIDGETLIBRARY_EXPORT ErasePatternWidget
	: public QWidget
{
	Q_OBJECT
public:
	ErasePatternWidget( QWidget * parent )
		: QWidget(parent)
	{
		ui_.setupUi( this );
	}
	DWORD getPattern() const
	{
		//if ( ui_.button_00->isChecked() )
		//	return ErasePattern::dm_erase_00;
		//if ( ui_.button_FF->isChecked() )
		//	return ErasePattern::dm_erase_FF;
		//if ( ui_.button_RAND->isChecked() )
		//	return ErasePattern::dm_erase_rand;

		//return UnknownErasePattern;
		return 0;
	}
	void setPattern( const DWORD pattern )
	{
		//switch ( pattern )
		//{
		//case ErasePattern::dm_erase_00: 
		//	ui_.button_00->setChecked( true );
		//	break;
		//case ErasePattern::dm_erase_FF: 
		//	ui_.button_FF->setChecked( true );
		//	break;
		//case ErasePattern::dm_erase_rand: 
		//	ui_.button_RAND->setChecked( true );
		//	break;
		//default:
		//	ui_.button_00->setChecked( true );
		//}
	}
private:
	Ui::widget ui_;
};

#endif // DEVICEWIDGET_H
