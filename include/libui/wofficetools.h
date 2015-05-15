#ifndef WOFFICETOOLS_H
#define WOFFICETOOLS_H

#include "libui_global.h"

#include <QWidget>
namespace Ui {class wOfficeTools;};

class LIBUI_EXPORT wOfficeTools : public QWidget
{
	Q_OBJECT

public:
	wOfficeTools(QWidget *parent = 0);
	~wOfficeTools();

private:
	Ui::wOfficeTools *ui;
};

#endif // WOFFICETOOLS_H
