#include "physicaldialog.h"

 #include <QFileDialog>
 #include <QString>

//#include "systemlibrary.h"

PhysicalDialog::PhysicalDialog(QWidget *parent,Ui::PhysicalDialog * pPhysicalDialog)
	: QDialog(parent)
	, pPhysicalUi_(pPhysicalDialog)
	, LogFolder_("")
{

}
PhysicalDialog::~PhysicalDialog()
{
	pPhysicalUi_ = NULL;
}
void PhysicalDialog::SetSourceDevice(DevicePtr pSourceDevice)
{
	SourceDevice_ = pSourceDevice;
	if ( SourceDevice_)
	{
		SetSectorsCount( SourceDevice_->GetSectorCount() );
		SetLogName( SourceDevice_->GetName() );
	}
}
void PhysicalDialog::SetSectorsCount(qlonglong sectorCount)
{
	pPhysicalUi_->SectorsCount->setText( QString::number(sectorCount) );
}
void PhysicalDialog::SetLogFolder(const QString & logFolder)
{
	LogFolder_ = logFolder;
}
void PhysicalDialog::SetLogName(const QString & logName)
{
	//QString tempStr = SysLib::MakeLogPath(LogFolder_,logName);
	//pPhysicalUi_->PathToLog->setText( SysLib::MakeLogPath(LogFolder_,logName));
}

void PhysicalDialog::OnChangeSectorsCount(QString SectorsCount)
{
	qDebug("Sectors change...");
}
void PhysicalDialog::OnSelectTarget(QModelIndex _SelectIndex)
{
	DevicePtr TargetDevice(pPhysicalUi_->DeviceTable->GetDevice(_SelectIndex.row()) );

	if (TargetDevice)
	{
		if (TargetDevice->GetSectorCount() < SourceDevice_->GetSectorCount() )
		{
			SetSectorsCount( TargetDevice->GetSectorCount() );
		}
		else
			SetSectorsCount( SourceDevice_->GetSectorCount() );
	}
	
}
void PhysicalDialog::OnOpenLogFile()
{
	QFileDialog LogDialog(this);

	LogDialog.setNameFilter("All txt files (*.txt)");
	LogDialog.setNameFilter("*.txt");

	LogDialog.setDirectory(pPhysicalUi_->PathToLog->text());

	LogDialog.exec() ;
	QString sLogFileName;
	LogDialog.selectFile(sLogFileName);
	pPhysicalUi_->PathToLog->setText(sLogFileName);

	//QString sLogFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
	//													LogFolder_,
	//													tr("txt (*.txt)"));
	//pPhysicalUi_->PathToLog->setText(sLogFileName);
}
