#ifndef COPYWIDGET_H
#define COPYWIDGET_H

#include <QtWidgets/QWidget>

#include "widgetlibrary_global.h"

#include "ui_CopyWidgetUi.h"

class WIDGETLIBRARY_EXPORT CopyWidget : public QWidget
{
	Q_OBJECT

public:
	CopyWidget(QWidget *parent);
	~CopyWidget();

public slots:
	void source_changed(int)
	{

	}
	void target_changed(int)
	{

	}


private:
	Ui::CopyWidgetUi * ui_;
};

#endif // COPYWIDGET_H
