#pragma once
#include <QWidget>

#include "ui_PartitionWidget.h"


class PartitionTreeWidget :
	public QWidget
{
public:
	PartitionTreeWidget(QWidget * parent = 0);
	~PartitionTreeWidget(void);
	QTreeView* getView() 
	{
		return ui_.treeView;
	}
private:
	Ui::PartitionForm ui_;
};
