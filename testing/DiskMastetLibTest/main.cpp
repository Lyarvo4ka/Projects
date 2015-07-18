
#include <QtCore/QCoreApplication>
#include <QTest>
#include "DiskMasterUsbTest.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//QTest::qExec(new Test_Functions, argc, argv);

	return a.exec();
}
