#include "filechecker.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	FileChecker w;
	w.show();
	return a.exec();
}
