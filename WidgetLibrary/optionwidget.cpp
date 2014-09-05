#include "optionwidget.h"



OptionWidget::OptionWidget(QWidget *parent)
	: QWidget(parent)
	, ui_( new Ui::OptionWidgetForm )
{
	ui_->setupUi( this );

	ui_->BadMarkerCmbBox->addItem("0000");
	ui_->BadMarkerCmbBox->addItem("BAD");

	connect( ui_->ChirpCheck , SIGNAL( stateChanged ( int ) ), this , SLOT(on_chirp_changed( int ) ) ); 
	connect( ui_->EndBeepCheck , SIGNAL( stateChanged ( int ) ), this , SLOT(on_EndBeep_changed( int ) ) ); 
	connect( ui_->CrcBeepCheck , SIGNAL( stateChanged ( int ) ), this , SLOT(on_CRCBeep_changed( int ) ) ); 


}

OptionWidget::~OptionWidget()
{

}
