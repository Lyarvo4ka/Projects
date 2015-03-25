#ifndef FILECHECKER_H
#define FILECHECKER_H

#include <QtWidgets/QMainWindow>
#include "ui_filechecker.h"

class FileChecker : public QMainWindow
{
	Q_OBJECT

public:
	FileChecker(QWidget *parent = 0);
	~FileChecker();

private:
	Ui::FileCheckerClass ui;
};

#endif // FILECHECKER_H
