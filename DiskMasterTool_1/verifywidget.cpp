#include "verifywidget.h"

 VerifyWindow::VerifyWindow(QWidget *parent)
     : QWidget(parent)
{
	Qt::WindowFlags flags = 0;
	topButtons = new QButtonGroup;
	errorButton = new QPushButton(tr("Errors"));
	warningButton = new QPushButton(tr("Warnings"));
	notReadyButton = new QPushButton(tr("Not Ready"));

	closeButton = new QPushButton(tr("&Close"));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	topButtons->addButton(errorButton);
	topButtons->addButton(warningButton);
	topButtons->addButton(notReadyButton);
	topButtons->setExclusive(true);

	defectListView = new QListView;
	defectListModel = new QStringListModel;
	defectListView->setModel(defectListModel);
		
	//defectListView->setColumnCount(2);
	//defectListView->setRowCount(10);
	connect(defectListModel,SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
			this,SLOT(updateDefectListView(const QModelIndex&, const QModelIndex&)));

	connect(errorButton,SIGNAL(clicked(bool)),this,SLOT(toggleErrorShow(bool)));
	connect(warningButton,SIGNAL(clicked(bool)),this,SLOT(toggleWarningShow(bool)));


	connect(defectListModel,SIGNAL(rowsInserted(const QModelIndex& , int, int)),
			this,SLOT(updateDefectListView2(const QModelIndex& , int, int)));


	//listErrors->resizeRowsToContents(); 
	//listErrors->resizeColumnsToContents(); 
	//listErrors->horizontalHeader()->setStretchLastSection(true);
	//listErrors->horizontalHeader()->setResizeMode(QHeaderView::Interactive);//->setStretchLastSection(true);
	QVBoxLayout *layout = new QVBoxLayout;

	layout->addWidget(errorButton);
	layout->addWidget(warningButton);
    layout->addWidget(defectListView);
    layout->addWidget(closeButton);
    setLayout(layout);

    /* textEdit = new QTextEdit;
     textEdit->setReadOnly(true);
     textEdit->setLineWrapMode(QTextEdit::NoWrap);

 

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(textEdit);
     layout->addWidget(closeButton);
     setLayout(layout);*/
	flags = Qt::Window;
	QWidget::setWindowFlags(flags);
    setWindowTitle(tr("Preview"));
 }

void VerifyWindow::toggleErrorShow(bool isChecked)
{

}

void VerifyWindow::toggleWarningShow(bool isChecked)
{

}


 void  VerifyWindow::updateDefectListView( const QModelIndex & topLeft, const QModelIndex & bottomRight )
 {

 }

 void  VerifyWindow::updateDefectListView2( const QModelIndex & parent, int start, int end )  
 {

 }


 PreviewWindow::PreviewWindow(QWidget *parent)
     : QWidget(parent)
 {
     textEdit = new QTextEdit;
     textEdit->setReadOnly(true);
     textEdit->setLineWrapMode(QTextEdit::NoWrap);

     closeButton = new QPushButton(tr("&Close"));
     connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

     QVBoxLayout *layout = new QVBoxLayout;
     layout->addWidget(textEdit);
     layout->addWidget(closeButton);
     setLayout(layout);

     setWindowTitle(tr("Preview"));
 }

  void PreviewWindow::setWindowFlags(Qt::WindowFlags flags)
 {
     QWidget::setWindowFlags(flags);

     QString text;

     Qt::WindowFlags type = (flags & Qt::WindowType_Mask);
     if (type == Qt::Window) {
         text = "Qt::Window";
     } else if (type == Qt::Dialog) {
         text = "Qt::Dialog";
     } else if (type == Qt::Sheet) {
         text = "Qt::Sheet";
     } else if (type == Qt::Drawer) {
         text = "Qt::Drawer";
     } else if (type == Qt::Popup) {
         text = "Qt::Popup";
     } else if (type == Qt::Tool) {
         text = "Qt::Tool";
     } else if (type == Qt::ToolTip) {
         text = "Qt::ToolTip";
     } else if (type == Qt::SplashScreen) {
         text = "Qt::SplashScreen";
     }

     if (flags & Qt::MSWindowsFixedSizeDialogHint)
         text += "\n| Qt::MSWindowsFixedSizeDialogHint";
     if (flags & Qt::X11BypassWindowManagerHint)
         text += "\n| Qt::X11BypassWindowManagerHint";
     if (flags & Qt::FramelessWindowHint)
         text += "\n| Qt::FramelessWindowHint";
     if (flags & Qt::WindowTitleHint)
         text += "\n| Qt::WindowTitleHint";
     if (flags & Qt::WindowSystemMenuHint)
         text += "\n| Qt::WindowSystemMenuHint";
     if (flags & Qt::WindowMinimizeButtonHint)
         text += "\n| Qt::WindowMinimizeButtonHint";
     if (flags & Qt::WindowMaximizeButtonHint)
         text += "\n| Qt::WindowMaximizeButtonHint";
     if (flags & Qt::WindowCloseButtonHint)
         text += "\n| Qt::WindowCloseButtonHint";
     if (flags & Qt::WindowContextHelpButtonHint)
         text += "\n| Qt::WindowContextHelpButtonHint";
     if (flags & Qt::WindowShadeButtonHint)
         text += "\n| Qt::WindowShadeButtonHint";
     if (flags & Qt::WindowStaysOnTopHint)
         text += "\n| Qt::WindowStaysOnTopHint";
     if (flags & Qt::CustomizeWindowHint)
         text += "\n| Qt::CustomizeWindowHint";

     textEdit->setPlainText(text);
 }