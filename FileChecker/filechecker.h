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
private slots:
	void on_office_2003();
private:
	Ui::FileCheckerClass ui_;
};

#endif // FILECHECKER_H
