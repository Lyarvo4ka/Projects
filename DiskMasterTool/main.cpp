#include "diskmasterui.h"
#include <QtWidgets/QApplication>
#include <QtCore>

#include "sectormapwidget.h"

void myMessageHandler(QtMsgType type, const char *msg)
{
	QString txt;
	switch (type) {
	case QtDebugMsg:
		txt = QString("Debug: %1").arg(msg);
		break;
	case QtWarningMsg:
		txt = QString("Warning: %1").arg(msg);
		break;
	case QtCriticalMsg:
		txt = QString("Critical: %1").arg(msg);
		break;
	case QtFatalMsg:
		txt = QString("Fatal: %1").arg(msg);
		abort();
	}
	QFile outFile("app_log.txt");
	outFile.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream ts(&outFile);
	ts << txt << endl;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//qInstallMsgHandler(myMessageHandler);	
	//a.addLibraryPath("c:\\Qt\\Qt5.1.0.x86\\5.1.0\\msvc2012\\plugins\\");
	DiskMasterUI w;
	w.show();
	//QTextCodec::setCodecForTr(QTextCodec::codecForName("Windows-1250"));
	//QTextCodec::setCodecForCStrings(QTextCodec::codecForName("CP1251"));
	return a.exec();
}


