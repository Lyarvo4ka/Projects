#ifndef PHYSICALDIALOG_H
#define PHYSICALDIALOG_H

#include <QDialog>
#include "ui_PhysicalDialog.h"

class PhysicalDialog : public QDialog
{
	Q_OBJECT

public:
	PhysicalDialog(QWidget *parent, Ui::PhysicalDialog * pPhysicalDialog);
	~PhysicalDialog();

	void SetSourceDevice(DevicePtr pSourceDevice);
	void SetSectorsCount(qlonglong sectorCount);
	void SetLogFolder(const QString & logFolder);
	void SetLogName(const QString & logName);
public slots:
	void OnChangeSectorsCount(QString ectorsCount);
	void OnSelectTarget(QModelIndex);
	void OnOpenLogFile();
private:
	Ui::PhysicalDialog * pPhysicalUi_;
	DevicePtr SourceDevice_;
	QString LogFolder_;
};

#endif // PHYSICALDIALOG_H


