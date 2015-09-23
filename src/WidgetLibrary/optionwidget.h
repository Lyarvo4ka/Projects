#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include <QtWidgets/QWidget>

#include "IOptionsView.h"

#include "widgetlibrary_global.h"

#include "ui_OptionsWidget.h"

class WIDGETLIBRARY_EXPORT OptionWidget 
	: public QWidget
	, public IOptionsView
{
	Q_OBJECT

public:
	explicit OptionWidget(QWidget *parent);
	~OptionWidget();

	void setNumberReadBads( int repeat_count ) override
	{
		ui_->NumRepeatRdEdit->setValue( repeat_count );
	}

	void setChirp( int bChirp ) override
	{
		ui_->ChirpCheck->setCheckState( (Qt::CheckState) bChirp );
	}

	void setEndBeep(  int bBeep  ) override 
	{
		ui_->EndBeepCheck->setCheckState( (Qt::CheckState) bBeep );
	}

	void setCRCBeep( int bBeep ) override 
	{
		ui_->CrcBeepCheck->setCheckState( (Qt::CheckState) bBeep );
	}


signals:
	void ChirpChanged( int );
	void EndBeepChanged( int );
	void CRCBeepChanged( int );

private slots:
	void on_chirp_changed( int bChirp )
	{
		emit ChirpChanged( bChirp );
	}
	void on_EndBeep_changed( int bBeep )
	{
		emit EndBeepChanged( bBeep );
	}
	void on_CRCBeep_changed( int bBeep )
	{
		emit CRCBeepChanged( bBeep );
	}

private:
	Ui::OptionWidgetForm * ui_;
};

#endif // OPTIONWIDGET_H
