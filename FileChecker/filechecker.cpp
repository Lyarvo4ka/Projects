#include "filechecker.h"
#include <QDebug>


FileChecker::FileChecker(QWidget *parent)
	: QMainWindow(parent)
{
	ui_.setupUi(this);

	connect(ui_.actionOffice_2003, SIGNAL(triggered()), this, SLOT(on_office_2003()));

}

FileChecker::~FileChecker()
{

}

void FileChecker::on_office_2003()
{
	qDebug() << "Offide 2003 clicked";
}
