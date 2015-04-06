#include "folderui.h"
#include <QDir>

FolderUI::FolderUI(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.textName->setText("Select Folder:");
	QString defaultPath = QDir::homePath();
	ui.folderPath->setText(defaultPath);
}

FolderUI::~FolderUI()
{

}
