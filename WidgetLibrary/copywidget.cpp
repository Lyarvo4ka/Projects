#include "copywidget.h"

CopyWidget::CopyWidget(QWidget *parent)
	: QWidget(parent)
	, ui_ ( new Ui::CopyWidgetUi )
{
	ui_->setupUi( this );
}

CopyWidget::~CopyWidget()
{

}
