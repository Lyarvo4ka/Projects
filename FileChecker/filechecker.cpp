#include "filechecker.h"
#include <QDebug>

#include "libui/wofficetools.h"


FileChecker::FileChecker(QWidget *parent)
	: QMainWindow(parent)
{
	ui_.setupUi(this);

	connect(ui_.actionOffice_2003, SIGNAL(triggered()), this, SLOT(on_office_2003()));
	//ui_.centralWidget->tabWidget->addWidget
	ui_.tabWidget->addTab(new wOfficeTools(ui_.tabWidget), "Office 2003");
	//ui_.widget = new wOfficeTools(this);
}

FileChecker::~FileChecker()
{

}

void FileChecker::on_office_2003()
{
	qDebug() << "Offide 2003 clicked";
}
