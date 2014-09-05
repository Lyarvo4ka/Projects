#pragma once

#include "Concurrent.h"
#include "Devices.h"

 #include <QString>
 #include <QLineEdit>
 #include <QPushButton>


QString DeviceToString(const DevicePtr & pDevice);

class PhysicalDialog;
//////////////////////	DeviceSubject	//////////////////////
class DeviceSubject
	: public CSubject
{
public:
	DeviceSubject(void);
	virtual ~DeviceSubject(void);
	virtual void SelectDevice(DevicePtr pDevice);
	DevicePtr GetDevice() const;
	bool isSelected();
	bool isEmpty();
private:
	DevicePtr Device_;

};


//////////////////////	TextObserver	//////////////////////
class TextObserver
	: public Observer
{
public:
	TextObserver(QLineEdit * DeviceText);
	virtual ~TextObserver();
	void Update(CSubject * pSubject);
private:
	QLineEdit * DeviceText_;
};
//////////////////////	TargetButtonObserver	//////////////////////
class TargetButtonObserver
	: public Observer
{
public:
	TargetButtonObserver(QAbstractButton * TargetButton);
	virtual ~TargetButtonObserver();
	void Update(CSubject * pSubject);
private:
	QAbstractButton *TargetButton_;
};
//////////////////////	PathToLogObserver	//////////////////////
class PathToLogObserver
	: public Observer
{
public:
	PathToLogObserver(QLineEdit * PathToLog);
	virtual ~PathToLogObserver();
	void Update(CSubject * pSubject);
private:
	QLineEdit * PathToLog_;
};


//////////////////////	PhysicalObserver	//////////////////////
class PhysicalObserver
	: public Observer
{
public:	
	PhysicalObserver( PhysicalDialog * pPhysicalDialog);
	void Update(CSubject * pSubject);
private:
	PhysicalDialog * PhysicalDialog_;
};


//////////////////////	CurrentLBAObserver	//////////////////////
class CurrentLBAObserver 
	: public QObject
	, public Observer
{
	Q_OBJECT

public:
	void Update(CSubject * pSubject);
signals:
	void ChangeLbaText(qlonglong CurrentLBA); 
};