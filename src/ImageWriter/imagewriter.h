#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include <QtWidgets/QMainWindow>
#include "ui_imagewriter.h"

#include "ui_SelectionDialog.h"
#include "memory"

#include <QThread>

class CopyThread;

enum state { start = 0 , stop };

class ImageWriter : public QMainWindow
{
	Q_OBJECT

public:
	ImageWriter(QWidget *parent = 0);
	~ImageWriter();

public slots :
	void FileOpenCliced();
	void HddOpenCliced();
	void StartButtonClicked();

	void OnErrorName( const QString & error_text );
	void OnFinishError( const QString & error_text );
	void OnFinishOk();
	void OnUpdateLba( qlonglong sector );
private:
	std::shared_ptr< QDialog > targetDialog_;
	Ui::ImageWriterClass ui;
	Ui::SelectionDialog uiSelectionDialog;
	QString file_;
	DevicePtr selected_device_;
	CopyThread * copy_thread;
	DWORD max_file_size;
	state state_;

};

class CopyThread
	: public QThread
{
	Q_OBJECT

public:
	CopyThread( QObject * parent = nullptr);
	~CopyThread();

	void setParams( const QString & file , const DevicePtr & hdd );
protected:
	virtual void run();

signals:
	void error_name( const QString & );
	void finish_error( const QString &  );
	void finish_ok();
	void update_lba( qlonglong );

private:
	QString file_;
	DevicePtr hdd_;

};

#endif // IMAGEWRITER_H
