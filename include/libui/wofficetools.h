#ifndef WOFFICETOOLS_H
#define WOFFICETOOLS_H

#include <QWidget>
namespace Ui {class wOfficeTools;};

class wOfficeTools : public QWidget
{
	Q_OBJECT

public:
	wOfficeTools(QWidget *parent = 0);
	~wOfficeTools();

private:
	Ui::wOfficeTools *ui;
};

#endif // WOFFICETOOLS_H
