#ifndef FILECHECKER_H
#define FILECHECKER_H

#include <QtWidgets/QMainWindow>
#include "ui_filechecker.h"
#include "folderui.h"

class FileChecker : public QMainWindow
{
	Q_OBJECT

public:
	FileChecker(QWidget *parent = 0);
	~FileChecker();

private:
	Ui::FileCheckerClass ui;
	FolderUI *folderUI_;
};

#endif // FILECHECKER_H
