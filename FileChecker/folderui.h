#ifndef FOLDERUI_H
#define FOLDERUI_H

#include <QWidget>
#include "ui_folderui.h"

class FolderUI : public QWidget
{
	Q_OBJECT

public:
	FolderUI(QWidget *parent = 0);
	~FolderUI();

private:
	Ui::FolderUI ui;
};

#endif // FOLDERUI_H
