 #ifndef VERIFYWINDOW_H
 #define VERIFYWINDOW_H

#include <QtGui>
#include <QtCore>

#include <QListView>

 class VerifyWindow : public QWidget
 {
     Q_OBJECT

 public:
     VerifyWindow(QWidget *parent = 0);

     void setWindowFlags(Qt::WindowFlags flags);
 
	QListView* defectListView;
	QStringListModel* defectListModel;
public slots:
	void updateDefectListView(const QModelIndex& topLeft, const QModelIndex& bottomRight);
	void updateDefectListView2( const QModelIndex & parent, int start, int end );
	void toggleErrorShow(bool isChecked);
	void toggleWarningShow(bool isChecked);
 private:
   
	QButtonGroup* topButtons;
	QPushButton* errorButton;
	QPushButton* warningButton;	 
	QPushButton* notReadyButton;
    QPushButton* closeButton;
 };


 class PreviewWindow : public QWidget
 {
     Q_OBJECT

 public:
     PreviewWindow(QWidget *parent = 0);

     void setWindowFlags(Qt::WindowFlags flags);

 private:
     QTextEdit *textEdit;
     QPushButton *closeButton;
 };

 #endif