#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	DriveIndex * root_index = new  DriveIndex(std::shared_ptr<IDevice>(new CFileDevice));
	//DriveIndex * main_index = new DriveIndex(std::shared_ptr<IDevice>(new CFileDevice));

	CPhysicalDevice physical_drives;
	physical_drives.GetDevices(drive_list_);
	for (auto iDrive = 0; iDrive < drive_list_.GetCount(); ++iDrive)
		root_index->insert(drive_list_.FindDevice(iDrive));


	drive_model_ = new DriveTableModel(this, root_index);
	ui.tableView->setModel(drive_model_);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	//ui.tableView->resizeRowsToContents();
	ui.tableView->resizeColumnsToContents();
	ui.tableView->setDragEnabled(true);
}

MainWindow::~MainWindow()
{
	if (drive_model_)
	{
		delete drive_model_;
		drive_model_ = nullptr;
	}
}
