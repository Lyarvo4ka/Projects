#include "MainSubject.h"

#include "DeviceLibrary/Reader.h"
//#include "physicaldialog.h"


QString DeviceToString(const DevicePtr & pDevice)
{
	if (pDevice != NULL)
	{
		QString DeviceString;
		DeviceString = QString(QString::fromLocal8Bit("#: %1 %2 (%3) [%4 %5].")).arg(pDevice->GetNumber())
			.arg(pDevice->GetName())
			.arg(pDevice->GetSerialNumber())
			.arg(pDevice->GetCapacity())
			.arg(pDevice->GetSizeData());
		return DeviceString;
	}
	return QString::fromLocal8Bit("Диск не выбран...");
}
/************************************************************************/
/*                          DeviceSubject                               */
/************************************************************************/
DeviceSubject::DeviceSubject(void)
{
}


DeviceSubject::~DeviceSubject(void)
{
}

 void DeviceSubject::SelectDevice(DevicePtr pDevice)
 {
	 Device_ = pDevice;
	 this->Notify();
 }
 DevicePtr DeviceSubject::GetDevice() const
 {
	 return Device_;
 }
 bool DeviceSubject::isSelected()
 {
	 return (Device_) ? true : false;
 }
 bool DeviceSubject::isEmpty()
 {
	 return !isSelected();
 }

 /************************************************************************/
 /*                          TextObserver                                */
 /************************************************************************/
 TextObserver::TextObserver(QLineEdit * DeviceText)
	 : DeviceText_(DeviceText)
 {

 }
 TextObserver::~TextObserver()
 {

 }
 void TextObserver::Update(CSubject *pSubject)
 {
	DeviceSubject * pDeviceSubject = dynamic_cast<DeviceSubject *> (pSubject);
	if (pDeviceSubject)
	{
		DevicePtr pDevice(pDeviceSubject->GetDevice());
		DeviceText_->setText(DeviceToString(pDevice));

		qDebug("execute TextObserver...");
	}
 }
 /************************************************************************/
 /*                          TargetButtonObserver                        */
 /************************************************************************/
 TargetButtonObserver::TargetButtonObserver(QAbstractButton * TargetButton)
	 : TargetButton_(TargetButton)
 {

 }
 TargetButtonObserver::~TargetButtonObserver()
 {

 }
 void TargetButtonObserver::Update(CSubject * pSubject)
 {
	 DeviceSubject * pDeviceSubject = dynamic_cast<DeviceSubject *> (pSubject);
	 if (pDeviceSubject)
	 {
		 DevicePtr pDevice(pDeviceSubject->GetDevice());
		 if (pDevice == NULL)
			 TargetButton_->setDisabled(true);
		 else
			 TargetButton_->setEnabled(true);
	 }

 }
 /************************************************************************/
 /*                          PathToLogObserver                           */
 /************************************************************************/
 PathToLogObserver::PathToLogObserver(QLineEdit * PathToLog)
	 : PathToLog_(PathToLog)
 {

 }
 PathToLogObserver::~PathToLogObserver()
 {

 }
 void PathToLogObserver::Update(CSubject *pSubject)
 {
	 DeviceSubject * pDeviceSubject = dynamic_cast<DeviceSubject *> (pSubject);
	 if (pDeviceSubject)
	 {
		 DevicePtr pDevice(pDeviceSubject->GetDevice());
		 //DeviceText_->setText(DeviceToString(pDevice));

		 qDebug("execute TextObserver...");
	 }
 }
 ///************************************************************************/
 ///*                          PhysicalObserver                          */
 ///************************************************************************/
 //PhysicalObserver::PhysicalObserver( PhysicalDialog * pPhysicalDialog)
	// : PhysicalDialog_ ( pPhysicalDialog )
 //{

 //}
 //void PhysicalObserver::Update(CSubject * pSubject)
 //{
	// DeviceSubject * pDeviceSubject = dynamic_cast<DeviceSubject *> (pSubject);
	// if (pDeviceSubject)
	// {
	//	 PhysicalDialog_->SetSourceDevice( pDeviceSubject->GetDevice() );
	// }

 //}

 /************************************************************************/
 /*                          CurrentLBAObserver                          */
 /************************************************************************/
 void CurrentLBAObserver::Update(CSubject * pSubject)
 {
	 CReaderConsistent * pReaderConsistent = static_cast<CReaderConsistent*> (pSubject);
	 if (pReaderConsistent)
	 {
		 emit ChangeLbaText( pReaderConsistent->GetCurrentLBA() );
	 }
 }


