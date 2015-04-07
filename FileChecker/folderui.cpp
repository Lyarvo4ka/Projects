#include "folderui.h"
#include <QDir>
#include <QFileDialog>
#include <QTreeView>

FolderUI::FolderUI(QWidget *parent)
	: QWidget(parent)
	, ui_(new Ui::FolderUI)
{
	ui_->setupUi(this);
	this->setLableName("Select Folder:");
	QString defaultPath = QDir::homePath();
	this->setFolderPath(defaultPath);
	QObject::connect(ui_->openButton, SIGNAL(clicked()), this, SLOT(onFolderDialogClicked()));

}

FolderUI::~FolderUI()
{

}

void FolderUI::setLableName(const QString & newName)
{
	ui_->textName->setText(newName);
}

void FolderUI::setFolderPath(const QString & folderPath)
{
	ui_->folderPath->setText(folderPath);
}

void FolderUI::onFolderDialogClicked()
{
	QFileDialog folder_dialog;

	folder_dialog.setFileMode(QFileDialog::DirectoryOnly);
	folder_dialog.setOption(QFileDialog::ShowDirsOnly);
	folder_dialog.setViewMode(QFileDialog::List);

	int dialog_result = folder_dialog.exec();
	if (dialog_result)
	{
		QString path = folder_dialog.directory().absolutePath();
		setFolderPath(path);
	}

}
