#ifndef WSELECTFOLDER_H
#define WSELECTFOLDER_H

#include "libui_global.h"

#include <QWidget>
namespace Ui {class WSelectFolder;};

class LIBUI_EXPORT WSelectFolder
	: public QWidget
{
	Q_OBJECT

public:
	WSelectFolder(QWidget *parent = 0);
	~WSelectFolder();
	void setLabelText(const QString & text);
	void setFolderPathText(const QString & pathText);
	QString getFolderPath() const;

private slots:
	void on_openbutton_clicked();

private:
	Ui::WSelectFolder *ui_;
};

#endif // WSELECTFOLDER_H
