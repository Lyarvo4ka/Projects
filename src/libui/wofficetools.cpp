#include "wofficetools.h"
#include "ui_wofficetools.h"
#include "wselectfolder.h"

wOfficeTools::wOfficeTools(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::wOfficeTools();
	ui->setupUi(this);
	auto source_widget = qobject_cast<WSelectFolder*>(ui->src_folderwidget);
	source_widget->setLabelText("Источник:");
	auto target_widget = qobject_cast<WSelectFolder*>(ui->dst_folderwidget);
	target_widget->setLabelText("Приемник:");
}

wOfficeTools::~wOfficeTools()
{
	delete ui;
}

