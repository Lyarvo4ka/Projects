
#include <QObject>
#include <QtTest>

//#include "dtm\DiskMaster.h"
#include "DiskMasterLib\dm_function.h"
#include "DiskMasterMock.h"

class Test_Functions
	: public QObject
{
	Q_OBJECT 

public:
	Test_Functions(QObject *parent = nullptr )
		: QObject( parent )
	{
	}
	~Test_Functions()
	{
	}

private slots:
	void isUsbSata_Test();
	void displayName_Test();
};

void Test_Functions::isUsbSata_Test()
{
	DiskDevicePtr diskUSB( new DiskDevice( CreatDiskMock( CreatePort( kUsb , kUsb1) , usb1SectorsCount ) ) );
	DiskDevicePtr diskSATA( new DiskDevice( CreatDiskMock( CreatePort( kSata , kSata1) , sata1SectorsCount ) ) );

	QCOMPARE(isUSB( diskUSB ) , true );
	QCOMPARE(isUSB( diskSATA ) , false );

	QCOMPARE(isSATA( diskSATA ) , true );
	QCOMPARE(isSATA( diskUSB ) , false );
}

void Test_Functions::displayName_Test()
{
	DiskDevicePtr diskUSB( new DiskDevice( CreatDiskMock( CreatePort( kUsb , kUsb1) , usb1SectorsCount ) ) );
	DiskDevicePtr diskSATA( new DiskDevice( CreatDiskMock( CreatePort( kSata , kSata1) , sata1SectorsCount ) ) );


	/*QCOMPARE( displayName( diskUSB ) , */
}

QTEST_MAIN(Test_Functions)

#include "DiskMasterUsbTest.moc"