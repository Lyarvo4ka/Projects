#include "imagewriter.h"
#include <QtWidgets/QApplication>

#include <QFile>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageWriter w;
	w.show();

	return a.exec();

	//QString device_name("\\\\.\\PhysicalDrive0");
	//QFile file(device_name);


	//bool bResult = file.open(QIODevice::WriteOnly);
	

	int k = 1;
	k = 1;

}
