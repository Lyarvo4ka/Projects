#include "wselectfolder.h"
#include "ui_wselectfolder.h"

#include <QDir>
#include <QFileDialog>

WSelectFolder::WSelectFolder(QWidget *parent)
	: QWidget(parent)
{
	ui_ = new Ui::WSelectFolder();
	ui_->setupUi(this);
	this->setLabelText("Folder:");

	QString defaultPath = QDir::homePath();
	this->setFolderPathText(defaultPath);
	
	connect(ui_->openButton, SIGNAL(clicked()), this, SLOT(on_openbutton_clicked()));
}

WSelectFolder::~WSelectFolder()
{
	delete ui_;
}

void WSelectFolder::setLabelText(const QString & text)
{
	ui_->label->setText(text);
}

void WSelectFolder::setFolderPathText(const QString & pathText)
{
	ui_->lineEdit->setText(pathText);
}

QString WSelectFolder::getFolderPath() const
{
	return ui_->lineEdit->text();
}

void WSelectFolder::on_openbutton_clicked()
{
	QFileDialog folder_dialog;

	folder_dialog.setFileMode(QFileDialog::DirectoryOnly);
	folder_dialog.setOption(QFileDialog::ShowDirsOnly);
	folder_dialog.setViewMode(QFileDialog::List);

	int dialog_result = folder_dialog.exec();
	if (dialog_result)
	{
		QString path = folder_dialog.directory().absolutePath();
		setFolderPathText(path);
	}
}
