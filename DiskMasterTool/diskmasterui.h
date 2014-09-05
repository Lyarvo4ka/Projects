#ifndef DISKMASTERUI_H
#define DISKMASTERUI_H

#include <QtWidgets/QMainWindow>
#include "ui_diskmasterui.h"

 #include <QCloseEvent>


class DiskMasterUI : public QMainWindow
{
	Q_OBJECT

public:
	DiskMasterUI(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~DiskMasterUI();
protected:
	void closeEvent(QCloseEvent * close_event) override;
	//void EnableTaskActions( bool bEnable );
protected slots:
	void ItemIsSelected( const DMItemIdex *);
	void EnableTaskActions( bool bEnable );
private:
	Ui::DiskMasterUIClass ui;
};

#endif // DISKMASTERUI_H
