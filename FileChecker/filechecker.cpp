#include "filechecker.h"


FileChecker::FileChecker(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	folderUI_ = new FolderUI(parent);
	folderUI_->show();


}

FileChecker::~FileChecker()
{

}
