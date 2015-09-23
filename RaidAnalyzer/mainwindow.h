#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include "DriveTableModel.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindowClass ui;
	DriveTableModel *drive_model_;
	CDiviceList drive_list_;

};

#endif // MAINWINDOW_H
