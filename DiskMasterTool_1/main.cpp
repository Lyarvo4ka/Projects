#include "DiskMasterTool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(DiskMasterTool);
	QApplication a(argc, argv);
	
	QTextCodec *codec = QTextCodec::codecForName("CP1251");
    QTextCodec::setCodecForTr(codec);

	DiskMasterTool w;

	w.show();
	return a.exec();
}
