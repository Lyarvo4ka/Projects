#ifndef CAMTEST_H
#define CAMTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_camtest.h"

class CamTest : public QMainWindow
{
	Q_OBJECT

public:
	CamTest(QWidget *parent = 0);
	~CamTest();

private:
	Ui::CamTestClass ui;
};

#endif // CAMTEST_H
