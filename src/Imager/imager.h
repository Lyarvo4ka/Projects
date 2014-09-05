#ifndef IMAGER_H
#define IMAGER_H

#include <QMainWindow>
#include "ui_imager.h"


#include "Devices.h"
#include "Reader.h"
#include "Writer.h"
#include "MainSubject.h"

#include <memory>
#include <windows.h>

 #include <QDialog>
#include "ui_SelectionDialog.h"
#include "ui_PhysicalDialog.h"


typedef std::tr1::shared_ptr<IStreamReader> StreemReaderPtr;
typedef std::tr1::shared_ptr<IAbstractTask> AbstractTaskPtr;


class TaskHolder
{
public:

	TaskHolder();
	virtual ~TaskHolder();

	void AddStreamReader(StreemReaderPtr pStreamReader);
	void AddTaskManager(AbstractTaskPtr pTask);
	void StartThreads();
	bool isReady();
	string GetErrorString() const;
private:
	StreemReaderPtr PtrStreamReader_;
	AbstractTaskPtr PtrAbstractTask_;
	string ErrorString_;
};

class Imager : public QMainWindow
{
	Q_OBJECT

public:
	typedef std::tr1::shared_ptr<QDialog> DialogPtr;
	Imager(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~Imager();

	DialogPtr CreateSelectionDialog(Ui::SelectionDialog & selectionDialog);
	DialogPtr CreatePhysicalDialog(Ui::PhysicalDialog & physicalDialog);


	void ShowError(const string ErrorString);

private:
	Ui::ImagerClass ui;

	// Source Dialog
	Ui::SelectionDialog SelectionUi_;
	DialogPtr SelectionDilog_;
	// Physical Dialog
	Ui::PhysicalDialog physicalUi_;
	DialogPtr PhysicalDialog_;

	DeviceSubject SourceSubject_;
	DeviceSubject TargetSubject_;

	TaskHolder TaskHolder_;
private slots:
	void OnSourceSelect();
	void OnTargetSelect();
	void OnStartClicked();

	// From Threads
	void OnChangeCurrentLBA(qlonglong CurrentsLBA);

};

#endif // IMAGER_H
