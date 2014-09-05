#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <QDialog>

class QPushButton;
class DeviceTableView;

class SelectWindow : public QDialog
{
	Q_OBJECT

public:
	SelectWindow(QWidget *parent);
	~SelectWindow();

private:
	QPushButton * ButtonOK;
	QPushButton * ButtonCancel;
	DeviceTableView * TableDevice; 
};

#endif // SELECTWINDOW_H
