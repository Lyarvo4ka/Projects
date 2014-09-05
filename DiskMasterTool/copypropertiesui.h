#ifndef COPYPROPERTIESUI_H
#define COPYPROPERTIESUI_H

#include <QWidget>
#include <QDialog>
#include "ui_CopyPropertiesUi.h"


#include "Functions.h"

class CopyPropertiesUi : public QWidget
{
	Q_OBJECT

public:
	CopyPropertiesUi(QWidget *parent);
	~CopyPropertiesUi();
	void setProperties( DWORD id )
	{
		id_ = id;
		this->setUiProperties();
	}

protected slots:
	void JumpSizeChanged( int size_value)
	{
		//DM_Settings::getSettings()->getCopySettings(id_).jump_size_ = size_value;
	}
	void DirectionChanged(int new_direction)
	{
		//DM_Settings::getSettings()->getCopySettings(id_).direction_ = new_direction;
	}
	void ReadUnReadChanged( int check_value )
	{
		//DM_Settings::getSettings()->getCopySettings(id_).isRead_unread = check_value;
	}
private:
	void setUiProperties( )
	{
		//auto copySettings = DM_Settings::getSettings()->getCopySettings(id_);
		//ui_.directionCombo->setCurrentIndex(copySettings.direction_);
		//ui_.jumpSizeBox->setValue( copySettings.jump_size_ );
		//ui_.readUnread->setCheckState( (Qt::CheckState) copySettings.isRead_unread );
	}
private:
	Ui::CopyPropertiesWidget ui_;
	DWORD id_;
};





#endif // COPYPROPERTIESUI_H
