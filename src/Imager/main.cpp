#include "imager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Imager w;
	w.show();
	return a.exec();
}
