#include "DiskMasterTool.h"
#include <QtGui>
#include "QNotificatorPnP.h"
//#include <QtDebug>
#include <QPropertyAnimation>


char Buf1[200]	={ID_COUNTER_BADS,0x00,0x00,0x00,0x00,0x00,0x00,
					ID_COUNTER_SOFTS,0x00,0x00,0x00,0x00,0x00,0x00,
					ID_COUNTER_SLOWS,0x00,0x00,0x00,0x00,0x00,0x00,
					ID_CURR_LBA,0x03,0x00,0x2A,0x10,0x00,0x40,
					ID_CURR_PROCESS,0x03,
					ID_CURR_SUB_PROCESS,0x07,
					ID_DESTINATION_MODEL,'S','A','M','S','U','N','G',' ','S','P','0','8','0','2','N','1',
					ID_DESTINATION_SERIAL,'S','4','5','7','0','9','2','3','4','5','0','8','0','2','N','5','9','2','1','2',
					ID_SOURCE_MODEL,'S','E','A','G','A','T','E',' ','3','1','2','8','0','2','N',' ',
					ID_SOURCE_SERIAL,'6','1','3','5','2','4','1','1','3','7','2','8','0','2','9','3','9','E','F','5','2',
					ID_TOTAL_TIME,0x30,0x02,0x13,0x43,
					ID_END_PROCESS_CODE,0x00,0x00,
					ID_END_OF_RECORD
	};

char Buf2[200]	={ID_COUNTER_BADS,0x00,0x74,0x6A,127,128,0x10,
					ID_COUNTER_SOFTS,0x00,0xa2,0x01,0x00,0x00,0x00,
					ID_COUNTER_SLOWS,0x02,0x00,0x00,0x00,0x00,0x00,
					ID_CURR_LBA,0x03,0x00,0x6A,0x10,0x20,0x40,
					ID_CURR_PROCESS,0x04,
					ID_CURR_SUB_PROCESS,0x08,
					ID_DESTINATION_MODEL,'S','A','M','S','U','N','G',' ','S','P','0','8','0','3','N','1',
					ID_DESTINATION_SERIAL,'S','5','5','7','0','9','2','3','4','5','0','8','0','2','N','5','9','2','1','2',
					ID_SOURCE_MODEL,'S','E','A','G','A','T','E',' ','3','2','2','8','0','2','N',' ',
					ID_SOURCE_SERIAL,'6','1','3','5','2','4','1','1','3','7','2','8','0','2','9','3','9','E','F','5','2',
					ID_TOTAL_TIME,0x30,0x02,0x13,0x43,
					ID_END_PROCESS_CODE,0xFF,HDD1_NOT_READY,
					ID_END_OF_RECORD
	};

char Buf3[200]	={ID_COUNTER_BADS,0x00,0x00,0x00,0x00,0x00,0x00,
					ID_COUNTER_SOFTS,0x00,0xa2,0x01,0x00,0x00,0x00,
					ID_COUNTER_SLOWS,0x02,0x00,0x00,0x00,0x00,0x00,
					ID_CURR_LBA,0x03,0x00,0x6A,0x10,0x20,0x40,
					ID_CURR_PROCESS,0x04,
					ID_CURR_SUB_PROCESS,0x08,
					ID_DESTINATION_MODEL,'S','A','M','S','U','N','G',' ','S','P','0','8','0','3','N','1',
					ID_DESTINATION_SERIAL,'S','5','5','7','0','9','2','3','4','5','0','8','0','2','N','5','9','2','1','2',
					ID_SOURCE_MODEL,'S','E','A','G','A','T','E',' ','3','2','2','8','0','2','N',' ',
					ID_SOURCE_SERIAL,'6','1','3','5','2','4','1','1','3','7','2','8','0','2','9','3','9','E','F','5','2',
					ID_TOTAL_TIME,0x30,0x02,0x13,0x43,
					ID_END_PROCESS_CODE,0x00,0x00,
					ID_END_OF_RECORD
	};

quint8 pc3000_list_head[] = {0x01,0x00,0x01,0x8A,0x00,0x00,0x00,0x56,0x00,0x00,0x00,0x78,0xDA,0x63,0x61,0x60,
							0x60,0x28,0xCA,0xCF,0x2F,0x61,0x61,0x80,0x00,0x76,0x20,0x76,0x2C,0x29,0x29,0xCA,0x4C,
							0x2A,0x66,0x40,0x12,0x0A,0x28,0xCA,0x4F,0xCB,0xCC,0x49,0x45,0x16,0x72,0x4F,0xCD,0x4B,
							0x2D,0x4A,0xCC,0x01,0x71,0x99,0x80,0x18,0x64,0x80,0x77,0x66,0x5E,0x0A,0x33,0x5C,0x41,
							0x58,0x6A,0x51,0x71,0x66,0x7E,0x1E,0x33,0x58,0x1A,0x49,0x00,0x24,0xCF,0x08,0xC4,0xAC,0x20,
							0xA1,0xC4,0x9C,0xD2,0x54,0x88,0x0A,0x00,0x5E,0x85,0x13,0xC0};

	QStringList mainButtonIconPath;
	QStringList mainButtonToolTips;
	QStringList registrationButtonIconPath;
	QStringList registrationButtonToolTips;

	QStringList listStringsCopy;
	QStringList listStringsErase; 
	QStringList listStringsVerify; 
	QStringList listStringsTestWrite;
	QStringList listStringsTestRead;
	QStringList listStringsTestWriteVerify;
	QStringList nvramLogStrings;
	QStringList defectLogStrings;
	QStringList nvramLogToolTips;

static const GUID GUID_FT245R = {0x219D0508, 0x57A8, 0x4FF5, {0x97, 0xA1, 0xBD, 0x86, 0x58, 0x7C, 0x6C, 0x7E}};

//mainButtonProc << &refreshDeviceList;
//ptrMainButtonProc mainButtonProc[]= {&DiskMasterTool::refreshDeviceList,
//									 &DiskMasterTool::downloadLog,
//									 &DiskMasterTool::saveLog,
//									 &DiskMasterTool::printLog,
//									 &DiskMasterTool::clearLog};
//
DiskMasterTool::DiskMasterTool(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	qRegisterMetaType<GUID>("GUID");
	showMaximized();

	setWindowFilePath(QString());

	int rowCount=0;
	int columnCount=0;
	bool ret;
	int val=0x45;
	isOnlyRegistration = false;
	isRunningProcess=false;
	isBreakProcess = false;
	isStopProcess = false;
	isAlreadyIdentify=false;
	cntSlowings = 0;
	cntBads = 0;
	cntNotReady = 0;

	pFtdiChip=NULL;
	
	


//	printString = " ----------------------------------------------------------------------------- \n";

	/*listStringsCopy << tr("Current Process") << "Destination" << "Source" << "Size/Done" << "Time Elaps" << "Total time" << "Bads" << "Softs" << "NRDY1" << "Finish Code";
	listStringsErase << "Current Process" << "Destination" << "Size/Done" << "Time Elaps" << "Total time" << "Bads" << "NRDY2" << "Finish Code";
	listStringsVerify << tr("Current Process") << "Destination" << "Size/Done" << "Time Elaps" << "Total time" << "Bads" << "Slows" << "NRDY2" << "Time average" << "Time max" << "Finish Code";
	listStringsTestWrite << "Current Process" << "Destination" << "Size/Done" << "Time Elaps" << "Total time" << "Bads" << "Softs" << "Finish Code";
	listStringsTestRead << "Current Process" << "Destination" << "Size/Done" << "Time Elaps" << "Total time" << "Bads" << "Finish Code";
	listStringsTestWriteVerify << "Current Process" << "Destination" << "Size/Done" << "Time Elaps" << "Total time" << "Bads" << "Finish Code";*/

	mainButtonIconPath << QString(":/DiskMaster/new.png") << 
						QString(":/DiskMaster/open.png") << 
						QString(":/DiskMaster/save.png") << 
						QString(":/DiskMaster/print.png") <<
						QString(":/DiskMaster/refresh.png") <<
						QString(":/DiskMaster/download.png") <<
						QString(":/DiskMaster/clear.png");   /*<< QString(":/DiskMasterTool/DiskVerify.png")*/

	mainButtonToolTips << QString(" Clear all controls and reinit all lists") <<  
						QString("Open NVRAM log or defect list ") <<
						QString("Save To File") <<
						QString("Print log") <<
						QString("Refresh USB device list") <<
						QString("Download NVRAM Log") << 
						QString("Clear NVRAM Log");						


	registrationButtonIconPath << /*QString(":/DiskMaster/resume.png") <<*/
								QString(":/DiskMaster/run.png") <<
								QString(":/DiskMaster/pause.png") << 
								QString(":/DiskMaster/stop.png") <<
								QString(":/DiskMaster/Goodshield.png") /*<< 
								QString(":/DiskMaster/Error.png")*/;

	registrationButtonToolTips << /*QString("Resume Process") << */
								QString("Start defect registration") << 
								QString("Break Process") <<
								QString("Stop Process")  << 
								QString("OTHER") /*<< 
								QString("Toggle Errors")*/;

	nvramLogStrings << " " << 
					"Current Process" << 
					"Destination" << 
					/*"Source" << */
					"Done(Size)" << 
					"Bads" << 
					"UNCR/Slows" << 
					"NRDY1(2)" << 
					"Time mid" << 
					"Time max" << 
					"Time Elaps(Time Colaps)" /*<< 
					"Finish Code"*/;

	nvramLogToolTips << QString(" ") <<  
						tr(" Название режима ") <<
						tr(" модель и серийный номер приемника/источника(для режима копирования)") <<
						tr(" выполненный обьем(максимальный обьем), если выполненный обьем меньше,\n значит роцесс не был полностью завершен") <<
						tr("количество бедов") << 
						tr("количество замедлений(порог на время доступа к сектору = 30мс)") << 
						tr("количество потерь готовности HDD2 или HDD1 (при наведении на значение показывается детальная информация)") << 
						tr("среднее время доступа(считается только в процессе теста верификации)") << 
						tr("максимальное время доступа(считается только в процессе теста верификации)") << 
						tr("общее время выполнения теста");			


	defectLogStrings <<" "<<"LBA" << "Type" << "Code" << "Time Op";

	mainButtonProc << &DiskMasterTool::refreshDeviceList;
	//mainButtonProc << pFunc;

	//resize(1024,600);
	QList<int> listSizes;
	////qDebug()<<rect().width();
	listSizes.append(rect().width());
	listSizes.append(rect().width());


	//listNvramLogs = new QListWidget;
	deviceTree = new MyTreeWidget;
	
	//deviceTree->setHeaderHidden(true);
	//deviceTree->setSelectionMode(QAbstractItemView::SingleSelection); 
	//deviceTree->clearSelection();

	processTextLog = new QTextBrowser;
	processTextLog->setFont(QFont("Courier New"));
	processTextLog->setWhatsThis(QString("DiskMasterTool system messages"));
	//deviceTree->setMaximumHeight(40);
	nvramLog = new MultiLineTableWidget;
	nvramLog->setSortingEnabled(true);
	nvramLog->setWordWrap(true);
	nvramLog->setWhatsThis(QString("NVRAM Log downloaded from DiskMaster, click 'download' to show NVRAM content"));
	defectLog = new QTableWidget;
	defectLog->setSortingEnabled(true);
	defectLog->setWhatsThis(QString("Defect list, fill during verify process"));
//	connect(defectLog,SIGNAL(cellClicked ( int , int  )),this,SLOT(sortColumn ( int , int )));
//	connect(nvramLog,SIGNAL(cellClicked ( int , int )),this,SLOT(sortColumn ( int , int)));

	pFtdiChip=NULL;

    fontDeviceTree.setFamily("Lucida Console");
    fontDeviceTree.setFixedPitch(true);
	fontDeviceTree.setPointSize(8);
	fontDeviceTree.setPixelSize(10);
	
	deviceTree->setIconSize(QSize (40,40));
	deviceTree->setWhatsThis(QString("FTDI usb device tree, to update click 'refresh' "));
	
	topLeftLayout = new QGridLayout;
	mainLeftGroup = new QGroupBox;
	mainLeftGroup->setFlat(true);
	topLeftLayout->setMargin(0);
	mainLeftGroup->setLayout(topLeftLayout);
	topLeftLayout->addWidget(processTextLog,0,0);

	//topLeftLayout->addWidget(deviceTree,0,1);


	//mainButtonLayout->setGeometry(QRect(0,0,rect().width(),50));
	//listDevices = new QComboBox;
	//mainButtonLayout->addWidget(listDevices);
	//mainButtonLayout->addWidget(deviceTree);
	menuButtonLayout = new QGridLayout;
	menuButtonLayout->setAlignment(Qt::AlignLeft);
	menuButtonLayout->setMargin(0);

	mainButtonLayout = new QHBoxLayout;
	mainButtonLayout->setAlignment(Qt::AlignLeft);
	mainButtonLayout->setMargin(0);

	registrationButtonLayout = new QHBoxLayout;
	registrationButtonLayout->setAlignment(Qt::AlignLeft);
	registrationButtonLayout->setMargin(0);
	
	
	mainButtonBox = new QGroupBox;
	mainButtonBox->setFlat(true);
	mainButtonBox->setLayout(menuButtonLayout);
	//mainButtonBox->setMinimumHeight(80);
	//mainButtonBox->setMinimumHeight(80);
	mainButtonBox->setAlignment(Qt::AlignLeft);

	registrationButtonBox = new QGroupBox;
	registrationButtonBox->setFlat(true);
	//registrationButtonBox->setMargin(0);
	//registrationButtonBox->setMinimumHeight(80);
	registrationButtonBox->setAlignment(Qt::AlignLeft);

	//registrationButtonBox->setLayout(mainButtonLayout);
	//registrationButtonBox->show();

	menuButtonLayout->addLayout(mainButtonLayout,0,0);
	menuButtonLayout->addLayout(registrationButtonLayout,0,1);


	mainSplitter = new QSplitter(Qt::Vertical);
	QList<int> splitterSizes;
	splitterSizes.append(20);
	splitterSizes.append(100);
	headerSplitter = new QSplitter;
	headerSplitter->addWidget(deviceTree);
	headerSplitter->addWidget(mainLeftGroup);
	headerSplitter->setSizes(splitterSizes);

	mainSplitter->setSizes(splitterSizes);
	mainSplitter->addWidget(headerSplitter);
	//mainSplitter->addWidget(mainButtonBox);
	//mainSplitter->addWidget(registrationButtonBox);
	mainSplitter->addWidget(nvramLog);
	mainSplitter->addWidget(defectLog);
	
	
	mainToolBar = new QToolBar("Main Menu",this);
	mainToolBar->setWindowTitle("Main Menu"); 
	mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	mainToolBar->setIconSize(QSize(32,32));

	nvramToolBar = new QToolBar("NVRAM Tools",this);
	nvramToolBar->setWindowTitle("NVRAM Tools"); 
	nvramToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	nvramToolBar->setIconSize(QSize(32,32));

	registrationToolBar = new QToolBar("Registration Tools",this);
	registrationToolBar->setWindowTitle("Registration Tools"); 
	registrationToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	registrationToolBar->setIconSize(QSize(32,32));

	createMainButtons();
	createRegistrationButtons();
	
	addToolBar(Qt::TopToolBarArea,mainToolBar);
	addToolBar(Qt::TopToolBarArea,nvramToolBar);
	//addToolBar(Qt::TopToolBarArea,registrationToolBar);

	mainLayout = new QVBoxLayout;
	mainLayout->setAlignment(Qt::AlignTop);
	mainLayout->setSpacing(0);
	mainLayout->setMargin(0);
	mainLayout->addWidget(mainButtonBox);
	mainLayout->addWidget(mainSplitter);
	setLayout(mainLayout);
	setCentralWidget(mainSplitter);
	//nvramLog->resize(rect().width(),100);
	//nvramLog->setMinimumHeight(600);
	nvramLog->setColumnCount(nvramLogStrings.count()); 
	nvramLog->setHorizontalHeaderLabels(nvramLogStrings);
	nvramLog->resizeColumnsToContents();
	nvramLog->setColumnWidth (0,20);
	setNvramLogColumnSizes(&nvramLogColumnSizes);
	setNvramLogToolTips();

	//registrationtLogTable->resize(rect().width(),400);
	defectLog->setColumnCount(defectLogStrings.count()); 
	defectLog->setHorizontalHeaderLabels(defectLogStrings);
	defectLog->setColumnWidth (0,20);
	for(int i=1;i<nvramLogStrings.count();i++)
		defectLog->setColumnWidth (i,150);

	defectLog->hide();
	nvramLog->show();
	setNvramLogColumnSizes(&nvramLogColumnSizes);

	errorIco.addPixmap(QPixmap(":/DiskMaster/Error.png"));
	okIco.addPixmap(QPixmap(":/DiskMaster/Goodshield.png"));
	warningIco.addPixmap(QPixmap(":/DiskMaster/Warning.png"));
	
	//QMessageBox* msgBox = new QMessageBox(QMessageBox::Information,QString("Device Notification"),QString("  Process finished!  "),QMessageBox::Ok,this);

	PnpNotificator.EnableDeviceNotifications(GUID_FT245R);

	//ret=QObject::connect(&PnpNotificator,SIGNAL(notifyEvent(int, GUID, QString)),this,SLOT(updateTree(int , GUID , QString )));	
	
	// обновление списка устройств и обновление дерева на экране
	connect(&PnpNotificator,SIGNAL(notifyEvent(int, GUID, QString)),&DeviceListThread,SLOT(updateDeviceTree(int , GUID , QString )));
	connect(&DeviceListThread,SIGNAL(changeDevice(int, ChipFT245R*, unsigned long, QString)),this,SLOT(updateTree(int, ChipFT245R*, unsigned long, QString)));
	connect(&DeviceListThread,SIGNAL(removeOpenedDevice()),this,SLOT(updateRemoveOpenedDevice()));
	connect(deviceTree,SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),this,SLOT(openDev(QTreeWidgetItem*,int)));

	
	DeviceListThread.start();

	//AddItemToDeviceTree();
	
	//addLogItem(Buf1,200);

	//addItemToList(Buf1,200);
	//AddItemToList(Buf2,200);
	//AddItemToList(Buf3,200);

	/*PreviewWindow* previewWindow = new PreviewWindow(this);
	flags = Qt::SplashScreen;
	previewWindow->setWindowFlags(flags);
	QPoint pos = previewWindow->pos();
    pos.setX(width()/2);
    pos.setY(height()/2);
    previewWindow->move(pos);
    previewWindow->show();*/

	//QWidget window(this);
	/*QPalette palette;
    palette.setBrush(QPalette::Window, Qt::black);
    window.setPalette(palette);*/
	
	//verifyWindow = new VerifyWindow(this);
	//verifyWindow->hide();

}


DiskMasterTool::~DiskMasterTool()
{
	
	if(pFtdiChip)
	{
		pFtdiChip->close();
	//	disconnect(pFtdiChip->recieveThread,SIGNAL(updateTableLogs(char*,unsigned short)),this,SLOT(addNvramLogRow(char* ,unsigned short)));
	//	disconnect(pFtdiChip->outputThread,SIGNAL(updateBufList(char*,unsigned char)),this,SLOT(parseBufList(char*,unsigned char)));

		/*if(pFtdiChip->recieveThread->isFinished())
			pFtdiChip->recieveThread->quit();
		if(pFtdiChip->outputThread->isFinished())
			pFtdiChip->outputThread->quit();

		delete pFtdiChip;*/
	}
	
	delete actionErase0;
	delete actionErase1;
	delete actionEraseRand;
	delete actionVerify;
	delete actionTestRead;

	delete actionTestWriteCompare;
	delete actionCopy;
	delete actionTraceEnable;
	delete actionTraceDisable;
	delete actionOnlyRegistration;

	//delete printPopupMenu;
	delete startRegistrationPopup;
//	delete printer;

	delete deviceTree;
	delete nvramLog;
	
	for(int i=0;i<registrationButtonIconPath.count();i++)
		registrationButtonLayout->removeWidget(registrationButtons[i]);

	for(int i=0;i<mainButtonIconPath.count();i++)
		mainButtonLayout->removeWidget(mainButtons[i]);

	menuButtonLayout->removeWidget(mainButtonBox);
	menuButtonLayout->removeItem(registrationButtonLayout);
	menuButtonLayout->removeItem(mainButtonLayout);

	delete registrationButtonLayout;
	delete mainButtonLayout;
	delete menuButtonLayout;

	delete registrationButtonBox;
	
	mainButtons.clear();
	registrationButtons.clear();
	
	mainLayout->removeWidget(mainButtonBox);
	mainLayout->removeWidget(mainSplitter);

	topLeftLayout->removeWidget(processTextLog);
	delete processTextLog;
	delete topLeftLayout;
	delete mainLeftGroup;

	delete mainButtonBox;
	delete headerSplitter;


	delete mainSplitter;
	delete mainLayout;
}

void DiskMasterTool::sortColumn( int row, int column )
{

}

void DiskMasterTool::setNvramLogToolTips(void)
{
	QTableWidgetItem * item = new QTableWidgetItem;
	for(int i=0;i<nvramLogStrings.count();i++)
	{
		
		item = nvramLog->horizontalHeaderItem(i);
		item->setToolTip(nvramLogToolTips[i]);
	}
}

void DiskMasterTool::createMainButtons(void)
{
	/*ptrMainButtonProc pFunc=mainButtonProc[0];	
	(this->*pFunc)(true);*/

	for(quint8 i=0;i<mainButtonIconPath.count();i++)
	{
		mainButtons << new ResizebleToolButton(QSize(50,50));
		mainButtonLayout->addWidget(mainButtons[i]);
		mainButtons[i]->setToolTip(mainButtonToolTips[i]);
		//mainButtons[i]->setIconSize(QSize(32,32));
		mainButtons[i]->setIcon(QPixmap(mainButtonIconPath[i]));
		//mainButtons[i]->setFlat(true);
		mainButtons[i]->setEnabled(false);
		//mainButtonIcons[i].addPixmap();
	//	connect(mainButtons[i],SIGNAL(clicked(bool)),this,SLOT((this->*mainButtonProc[i])(bool)));
	}
	refreshButton->show();	
	newButton->setEnabled(true);	
	openButton->setEnabled(true);	
	refreshButton->setEnabled(false);
	printButton->setEnabled(true);	

	mainToolBar->addWidget(newButton);
	mainToolBar->addWidget(openButton);
	mainToolBar->addWidget(saveButton);
	mainToolBar->addWidget(printButton);
	mainToolBar->addWidget(refreshButton);

	nvramToolBar->addWidget(downloadButton);
	nvramToolBar->addWidget(clearButton);

	//mainButtons[5]->setCheckable(true);

	/*printPopupMenu = new QMenu(tr("Print Menu"));
	actPrint = new QAction(printPopupMenu);
	actPrint = printPopupMenu->addAction(tr("Print..."));
	actPreview = new QAction(printPopupMenu);
	actPreview = printPopupMenu->addAction(tr("Print Preview"));*/
	//connect(actPreview,SIGNAL(triggered()),this,SLOT(print()));
	/*connect(actPrint,SIGNAL(triggered()),this,SLOT(printLog()));*/

	//printButton->setMenu(printPopupMenu); 
	//printer = new QPrinter;

	connect(newButton,SIGNAL(clicked(bool)),this,SLOT(newDocument(bool)));
	connect(openButton,SIGNAL(clicked(bool)),this,SLOT(openDataFile(bool)));
	connect(saveButton,SIGNAL(clicked(bool)),this,SLOT(saveDataFile(bool)));
	connect(refreshButton,SIGNAL(clicked(bool)),this,SLOT(refreshDeviceList(bool)));
	connect(downloadButton,SIGNAL(clicked(bool)),this,SLOT(downloadLog(bool)));
	connect(clearButton,SIGNAL(clicked(bool)),this,SLOT(clearLog(bool)));
	connect(printButton,SIGNAL(clicked(bool)),this,SLOT(print(bool)));

	//connect(printButton,SIGNAL(clicked(bool)),this,SLOT(printLog(bool)));
}


void DiskMasterTool::createRegistrationButtons(void)
{
	for(int i=0;i<registrationButtonIconPath.count();i++)
	{
		registrationButtons << new ResizebleToolButton(QSize(50,50));
		registrationButtonLayout->addWidget(registrationButtons[i]);
		registrationButtons[i]->setToolTip(registrationButtonToolTips[i]);
		//registrationButtons[i]->setIconSize(QSize(32,32));
		//registrationButtons[i]->setMinimumSize(QSize(40,40)) ;
		registrationButtons[i]->setIcon(QPixmap(registrationButtonIconPath[i]));
		//registrationButtons[i]->setFlat(true);
		registrationButtons[i]->setEnabled(false);
		registrationToolBar->addWidget(registrationButtons[i]);
		//registrationButtons[i]->setGeometry(QRect(1+i*50, 105, 51, 51));
		//registrationButtons[i]->show();
	}
	
	////resumeButton->hide();
	/*registrationButtonLayout->setEnabled(false);
	registrationButtonBox->setEnabled(false);*/
	//registrationButtonBox->setLayout(registrationButtonLayout);
	pauseButton->hide();
	// start registration popUp Menu
	startRegistrationPopup = new QMenu(tr("Start Process & Registration Menu"));
	actionErase0 = new QAction(tr("  ERASE MODE 0x00  "),startRegistrationPopup);
	actionErase1 = new QAction(tr("  ERASE MODE 0xFF  "),startRegistrationPopup);
	actionEraseRand = new QAction(tr("  ERASE MODE RAND  "),startRegistrationPopup);
	actionVerify = new QAction(tr("  VERIFY MODE  "),startRegistrationPopup);
	actionCopy = new QAction(tr("  COPY MODE  "),startRegistrationPopup);
	actionTestRead = new QAction(tr("  TEST READ MODE  "),startRegistrationPopup);
	actionTestWriteCompare = new QAction(tr("  TEST WRITE/COMPARE MODE  "),startRegistrationPopup);

	actionOnlyRegistration = new QAction(tr("Only registration"),startRegistrationPopup);
	actionOnlyRegistration->setCheckable(true);
	connect(actionOnlyRegistration, SIGNAL(triggered(bool)), this, SLOT(toggleOnlyRegFlag(bool)));

	actionTraceEnable = new QAction(tr("  TRACE ENABLE  "),startRegistrationPopup);
	actionTraceDisable = new QAction(tr("  TRACE DISABLE  "),startRegistrationPopup);

    //actionOnlyRegistration->setShortcut(QKeySequence::Italic);
    //actionOnlyRegistration->setStatusTip(tr("Make the text italic"));

///// MY BUTTON
//	registrationButtons << new ResizebleToolButton(QSize(50,50));
//	registrationButtonLayout->addWidget(registrationButtons[3]);
//	registrationButtons[3]->setEnabled(true);
//	registrationToolBar->addWidget(registrationButtons[3]);

	
	startRegistrationPopup->addAction(actionCopy);
	startRegistrationPopup->addSeparator();
	startRegistrationPopup->addAction(actionVerify);
	startRegistrationPopup->addAction(actionTestRead);
	startRegistrationPopup->addAction(actionTestWriteCompare);
	startRegistrationPopup->addSeparator();
	startRegistrationPopup->addAction(actionErase0);
	startRegistrationPopup->addAction(actionErase1);
	startRegistrationPopup->addAction(actionEraseRand);
	startRegistrationPopup->addSeparator();
	startRegistrationPopup->addAction(actionOnlyRegistration);
	startRegistrationPopup->addSeparator();
	startRegistrationPopup->addAction(actionTraceDisable);
	


//	connect(startRegistrationPopup, SIGNAL(triggered(QAction*)), this, SLOT(switchTask(QAction*)));

	//runButton->setMenu(startRegistrationPopup); 

	//connect(//resumeButton,SIGNAL(clicked(bool)),this,SLOT(resumeProcess(bool)));
	connect(runButton,SIGNAL(clicked(bool)),this,SLOT(switchTask(bool)));
	connect(pauseButton,SIGNAL(clicked(bool)),this,SLOT(breakProcess(bool)));
	connect(stopButton,SIGNAL(clicked(bool)),this,SLOT(stopProcess(bool)));
	/*connect(errorButton,SIGNAL(clicked(bool)),this,SLOT(toggleWarning(bool)));
	connect(warningButton,SIGNAL(clicked(bool)),this,SLOT(toggleError(bool)));*/
}



void DiskMasterTool::setNvramLogColumnSizes(QList<int>* listSizes)
{
	listSizes->clear();
	for(int i=0;i<nvramLogStrings.count();i++)
	{
		nvramLog->setColumnWidth (i,70);
	
	}

	nvramLog->setColumnWidth (nvramLogStrings.indexOf(QString(" ")),25);

	nvramLog->setColumnWidth (nvramLogStrings.indexOf(QString("Current Process")),100);
	nvramLog->setColumnWidth (nvramLogStrings.indexOf(QString("Destination")),250);
	//nvramLog->setColumnWidth (nvramLogStrings.indexOf(QString("Source")),170);
	nvramLog->setColumnWidth (nvramLogStrings.indexOf(QString("Done(Size)")),140);
	nvramLog->setColumnWidth (nvramLogStrings.indexOf(QString("Bads")),70);
	nvramLog->setColumnWidth (nvramLogStrings.indexOf(QString("NRDY1(2)")),60);
	nvramLog->setColumnWidth (nvramLogStrings.indexOf(QString("UNCR/Slows")),80);
	nvramLog->setColumnWidth (nvramLogStrings.indexOf(QString("Time Elaps(Time Colaps)")),160);

	for(int i=0;i<nvramLogStrings.count();i++)
		listSizes->append(nvramLog->columnWidth(i));

}

void DiskMasterTool::openDev(QTreeWidgetItem* item, int column)
{
	//	QTreeWidgetItem *currItem = listUsbDevices->currentItem();
	//	QTextEdit* textEdit=currItem->data(0,Qt::UserRole+1).value<QTextEdit*>();

	ChipFT245R* pChip = item->data(0,Qt::UserRole).value<ChipFT245R*>();
	if(!pChip) return;

	pFtdiChip=pChip;

	if(pChip->open(DeviceListThread.isOpenedDevice))
	{
		if(DeviceListThread.isOpenedDevice) 
			return;
		isAlreadyIdentify=false;
		isRunningProcess=false;
		isBreakProcess=false;
		isStopProcess=false;

		DeviceListThread.isOpenedDevice=true;
		connect(pChip->recieveThread,SIGNAL(updateTableLogs(char*,unsigned short)),this,SLOT(addNvramLogRow(char* ,unsigned short)));
		//connect(pFtdiChip,SIGNAL(defectDetected(void)),this,SLOT(updateDefectList(void)));
		connect(pChip->outputThread,SIGNAL(updateBufList(char*,quint16)),this,SLOT(parseBufList(char*,quint16)));

		item->setIcon(0,QIcon(":/DiskMaster/ChipOpenOk.png"));
		downloadButton->setEnabled(true);
		clearButton->setEnabled(true);
		runButton->setEnabled(true);
		pauseButton->setEnabled(false);
		////resumeButton->setEnabled(true);
		//fadeInWidget(mainButtons,NUMBER_MAIN_BUTTONS);
	}
	else
	{
		DeviceListThread.isOpenedDevice=false;
		item->setIcon(0,QIcon(":/DiskMaster/chip.png"));
		pChip->close();	

		downloadButton->setEnabled(false);
		clearButton->setEnabled(false);

		for(int i=0;i<registrationButtons.count();i++)
			registrationButtons[i]->setEnabled(false);
 
		//memset(ListNVRAMItems,0x00,sizeof(NVRAM_LOG_ITEM)*1000);
		nvramList.clear();
		disconnect(pChip->recieveThread,SIGNAL(updateTableLogs(char*,unsigned short)),this,SLOT(addNvramLogRow(char* ,unsigned short)));
		disconnect(pChip->outputThread,SIGNAL(updateBufList(char*,quint16)),this,SLOT(parseBufList(char*,quint16)));
	}
}



void DiskMasterTool::updateControls(int state)
{
	switch(state)
	{
	case OnAllDevicesRemove:
		DeviceListThread.isOpenedDevice=false;
		deviceTree->clear();
		deviceTree->setHeaderLabel(QString("no any FTDI USB device")); 
		runButton->setEnabled(false);
		pauseButton->setEnabled(false);
		stopButton->setEnabled(false);
		downloadButton->setEnabled(false);
		clearButton->setEnabled(false);
		break;

	case OnUsbRequest:
		if(!isAlreadyIdentify && !isRunningProcess && !isBreakProcess)
		{
			runButton->setEnabled(true);
			pauseButton->setEnabled(false);
			stopButton->setEnabled(false);
			break;
		}
		if(isBreakProcess)
			pauseButton->setEnabled(false);
		if(isStopProcess)
		{
			stopButton->setEnabled(false);
			pauseButton->setEnabled(false);
		}

		if(isAlreadyIdentify && !isRunningProcess && !isBreakProcess && !isStopProcess)
		{
			runButton->setEnabled(true);
			pauseButton->setEnabled(false);
			stopButton->setEnabled(false);
		}
		else
		{
			if(isAlreadyIdentify && !isRunningProcess && (isBreakProcess || isStopProcess))
			{
				runButton->setEnabled(true);
				pauseButton->setEnabled(false);
				stopButton->setEnabled(false);
			}
			else
			{
				if(isAlreadyIdentify && isRunningProcess && isBreakProcess)
				{
					runButton->setEnabled(true);
					pauseButton->setEnabled(false);
				}
				else
				{
					if(isAlreadyIdentify && isRunningProcess && isStopProcess)
					{
						runButton->setEnabled(true);
						pauseButton->setEnabled(false);
						stopButton->setEnabled(false);

					}
					else
					{
						if(isAlreadyIdentify && isRunningProcess && !isBreakProcess && !isStopProcess)
						{
							runButton->setEnabled(false);
							pauseButton->setEnabled(true);
							stopButton->setEnabled(true);
						}
						else
						{
							
						}
					}
				}
			}
		}
		break;
	}
}

void DiskMasterTool::updateRemoveOpenedDevice(void)
{
	
	updateControls(OnAllDevicesRemove);
}

void DiskMasterTool::updateTree(int nType, ChipFT245R* pChip,unsigned long nChipID, QString serial)
{
	QTreeWidgetItem *deviceItem;
	QList<QTreeWidgetItem*> list;
	QModelIndex index;
	QString str;
	//qDebug()<<"nType:"<< nType;
	//qDebug()<<"pChip:"<< pChip;

	if(nType == (0x00FF & DBT_DEVICEARRIVAL))
	{
		if(pChip)
		{
			
			deviceItem = new QTreeWidgetItem(deviceTree);
			deviceItem->setFont(0,fontDeviceTree);
			deviceItem->setText(0,	"\nDescription: " + QString(pChip->ftInfo.Description)+ "\n" +
									"     Serial: " + QString(pChip->ftInfo.SerialNumber) + "\n" + 
									"    Chip ID: " + QString::number(nChipID)+"\n"/*+
									"    Chip ID2: " + QString::number(pChip->ftInfo.ID)+ "\n"*/);

			deviceItem->setIcon(0,QIcon(":/DiskMaster/chip.png"));	
			deviceItem->setData(0,Qt::UserRole,qVariantFromValue(pChip));
		}
		else
		{
			if(!DeviceListThread.isOpenedDevice)
			{
				deviceItem = new QTreeWidgetItem(deviceTree);
				deviceItem->setFont(0,fontDeviceTree);
				deviceItem->setText(0,  "\nSerial: " + serial + "\n"+
								QString("Device still enumerates or busy by another task")+"\n"+
								QString("try refresh list later ! "));
				deviceItem->setIcon(0,QIcon(":/DiskMaster/chip_hide.png"));	
			}
		}
	}
	else
	{
		if(nType == (0x00FF & DBT_DEVICEREMOVECOMPLETE))
		{
			//bool ok = deviceTree->model()->hasIndex (0,0);
			int rows = deviceTree->model()->rowCount();
			for(int i=0; i<rows;i++)
			{
				index = deviceTree->model()->index(i, 0, QModelIndex());
				deviceItem = deviceTree->itmFromIndex(index);
				QString str = deviceItem->data (0, Qt::DisplayRole ).toString();
				if(str.contains(serial, Qt::CaseInsensitive))
				{
					deviceTree->model()->removeRow(i);
				}
			if(!(rows = deviceTree->model()->rowCount()))
				updateControls(OnAllDevicesRemove);
			}

			/*  indexes = deviceTree->model()->match(deviceTree->model()->index(0, 0, QModelIndex()),
                                               Qt::DisplayRole, serial, -1, Qt::MatchContains);*/
			//QString str = deviceTree->model()->data( const QModelIndex & index, int role = Qt::DisplayRole );
			//indexes.clear();
		//	for (int i = 0; i < indexes.size(); ++i)
	//			list.append(deviceTree->model()->indexWidget  (indexes.at(i)));

			//deviceTree->findItems (serial, Qt::MatchContains);
		
		//	deviceTree->removeItemWidget(deviceTree->itmFromIndex(indexes[0]) ,0);
		}
	}

	if(!deviceTree->model()->rowCount())
		deviceTree->setHeaderLabel(QString("no any FTDI USB device")); 
	else
		deviceTree->setHeaderLabel(QString("FTDI USB device list (%1)").arg(deviceTree->model()->rowCount())); 

	//deviceItem->setData(0,Qt::UserRole+1,qVariantFromValue(textEdit));
}


void DiskMasterTool::SendCommand(USB_HEADER header)
{
	pFtdiChip->WriteHeader(header);
}


void DiskMasterTool::switchTask(bool ok)
{
	USB_HEADER cmdPkt;
	memset(&cmdPkt,0x00,sizeof(USB_HEADER));	
	
	runButton->setEnabled(false);
	
	if(isBreakProcess && isRunningProcess)
	{
		qDebug() << "resume process";
		isBreakProcess = false;
		//resumeButton->hide();
		pauseButton->setEnabled(true);
		stopButton->setEnabled(true);

		cmdPkt.code =USB_REQ_START_REGISTRATION;
		cmdPkt.sub_code[0] =LO_RESUME_PROCESS;
		SendCommand(cmdPkt);
	}
	else
	{
		qDebug() << "->run process";
		nvramLog->hide();
		defectLog->show();
		setDefectLogColumnSizes(&defectLogColumnSizes);
		/////// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		QAction* currentTask = actionVerify;
		/////// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

		if(currentTask==actionVerify)
		{
			currentProcess = MODE_TEST_VERIFY;
			SET_HI_THETRADE(cmdPkt.sub_code[0],MODE_TEST_VERIFY);
			MessageToLog("> VERIFY started");
		}
		else
		{
			if(currentTask==actionErase0)
			{
				currentProcess = MODE_USB_ERASE0;
				MessageToLog("> ERASE 0x00 started");
				SET_HI_THETRADE(cmdPkt.sub_code[0],MODE_USB_ERASE0);
			}
			else
			{
				if(currentTask==actionErase1)
				{
					currentProcess = MODE_USB_ERASE1;
					MessageToLog("> ERASE 0xFF started");
					SET_HI_THETRADE(cmdPkt.sub_code[0],MODE_USB_ERASE1);
				}
				else
				{
					if(currentTask==actionEraseRand)
					{
						currentProcess = MODE_USB_ERASE_RAND;
						MessageToLog("> ERASE Rand started");
						SET_HI_THETRADE(cmdPkt.sub_code[0],MODE_USB_ERASE_RAND);
					}
					else
					{
						if(currentTask==actionCopy)
						{
							currentProcess = MODE_COPY;
							MessageToLog("> COPY started");
							SET_HI_THETRADE(cmdPkt.sub_code[0],MODE_COPY);
						}
						else
						{
							if(currentTask==actionTestRead)
							{
								currentProcess = MODE_TEST_READ;
								MessageToLog("> TEST READ started");
								SET_HI_THETRADE(cmdPkt.sub_code[0],MODE_TEST_READ);
							}
							else
							{
								if(currentTask==actionTestWriteCompare)
								{
									currentProcess = MODE_WRITE_COMPARE;
									MessageToLog("> TEST WRITE/COMPARE started");
									SET_HI_THETRADE(cmdPkt.sub_code[0],MODE_WRITE_COMPARE);
								}
								else
								{
									if(currentTask==actionTraceDisable)
									{

										MessageToLog("> trace disable...");
										cmdPkt.code =USB_REQ_TRACE_ENABLE;
										cmdPkt.sub_code[0] = ONLY_DISABLE;
									}
								}
							}
						}
					}
				}
			}
		}
		MessageToLog("> wait identify...");
		runProcess(cmdPkt);
	}
}


void DiskMasterTool::toggleOnlyRegFlag(bool changed)
{
	isOnlyRegistration = changed;
}



void DiskMasterTool::runProcess(USB_HEADER cmdPkt)
{
	Qt::WindowFlags flags = 0;
	QDialog* window = new QDialog;
	 QGraphicsScene* scene = new QGraphicsScene(0, 0, 300, 300,window);
	 scene->setBackgroundBrush(Qt::blue);

	// a blue background
 //

 // a gradient background
 //QRadialGradient* gradient = new QRadialGradient(0, 0, 10);
 //gradient->setSpread(QGradient::LinearGradient);
 //scene->setBackgroundBrush(*gradient);
     //QGraphicsView*  window = new QGraphicsView(scene);
    /* window->setFrameStyle(0);
     window->setAlignment(Qt::AlignLeft | Qt::AlignTop);
     window->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
     window->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);*/
	
	/*QPainterPath* path = new  QPainterPath;
 path->addRect(20, 20, 60, 60);

 path->moveTo(0, 0);
 path->cubicTo(99, 0,  50, 50,  99, 99);
 path->cubicTo(0, 99,  50, 50,  0, 0);

 QPainter* painter = new QPainter(window);
 painter->fillRect(0, 0, 100, 100, Qt::blue);
 painter->setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine,
                     Qt::FlatCap, Qt::MiterJoin));
 painter->setBrush(QColor(122, 163, 39));

 painter->drawPath(*path);

	 flags = Qt::Dialog;
	 flags |= Qt::FramelessWindowHint;
	window->setWindowFlags(flags);
	QPoint pos = window->pos();
	window->setModal(true);
    pos.setX(width()/2);
    pos.setY(height()/2);
    window->move(pos);
QGraphicsRectItem *button1 = new QGraphicsRectItem(QRect(100, 0, 50, 50));
	scene->addItem(button1);
	
	  window->resize(300, 300);
     window->show();*/

	/*QMessageBox*  msgBox = new QMessageBox;
	msgBox->setText("The document has been modified.");
	msgBox->exec();*/
	memset(&disk1Object.identify,0x00,sizeof(CUSTOM_INFO_SIZE));
	memset(&disk2Object.identify,0x00,sizeof(CUSTOM_INFO_SIZE));

	printString="";
	nvramList.clear();

	defectList.clear();
	defectLog->clearContents();
	defectLog->setRowCount(0);

	isStopProcess = false;
	isBreakProcess = false;
	isAlreadyIdentify=false;
	isRunningProcess=false;
	
	runButton->hide();
	runButton->setEnabled(false);
	// кнопка Pause неактивна на период подачи питания (~2сек)
	
	pauseButton->setEnabled(false);
	
	stopButton->setEnabled(false);
	QTimer::singleShot(3000, this, SLOT(updatePauseButton()));
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(2000);

	cmdPkt.code =USB_REQ_START_REGISTRATION;
	cmdPkt.sub_code[0] |= (unsigned char)isOnlyRegistration;
	SendCommand(cmdPkt);
	//registrationButtons[0]->setIcon(QIcon(":/DiskMasterTool/pause.png"));
}



void DiskMasterTool::updatePauseButton(void)
{
	pauseButton->setEnabled(true);
}

void DiskMasterTool::breakProcess(bool ok)
{
	USB_HEADER cmdPkt;
	memset(&cmdPkt,0x00,sizeof(USB_HEADER));
	
	qDebug() << "break process";
	isBreakProcess = true;
	//if(isRunningProcess)
	{
		////resumeButton->show();
	//	pauseButton->hide();
	//	runButton->show();
	}
	runButton->setEnabled(true);
	pauseButton->setEnabled(false);
	cmdPkt.code =USB_REQ_STOP_REGISTRATION;
	SendCommand(cmdPkt);

}

void DiskMasterTool::resumeProcess(bool ok)
{
	USB_HEADER cmdPkt;
	memset(&cmdPkt,0x00,sizeof(USB_HEADER));

	//resumeButton->hide();
	pauseButton->setEnabled(true);
	stopButton->setEnabled(true);

	cmdPkt.code =USB_REQ_START_REGISTRATION;
	cmdPkt.sub_code[0] =LO_RESUME_PROCESS;
	SendCommand(cmdPkt);

}

void DiskMasterTool::stopProcess(bool ok)
{
	USB_HEADER cmdPkt;
	memset(&cmdPkt,0x00,sizeof(USB_HEADER));
	
	stopButton->setEnabled(false);
	isStopProcess = true;
	isRunningProcess=false;
	isBreakProcess=false;
	cmdPkt.code =USB_REQ_STOP_REGISTRATION;
	SendCommand(cmdPkt);
}

void DiskMasterTool::toggleWarning(bool ok)
{
}

void DiskMasterTool::toggleError(bool ok)
{
}

//////////////////////////////////////////////////////////////////////////////////
// main button[0]
//////////////////////////////////////////////////////////////////////////////////
void DiskMasterTool::refreshDeviceList(bool checked)
{
	deviceTree->clear();
	DeviceListThread.run();
}

//////////////////////////////////////////////////////////////////////////////////
// main button[1]
//////////////////////////////////////////////////////////////////////////////////
void DiskMasterTool::downloadLog(bool checked)
{
	USB_HEADER cmdPkt;
	memset(&cmdPkt,0x00,sizeof(USB_HEADER));
		
	nvramLog->show();
	defectLog->hide();
	nvramLog->setRowCount(0);
	nvramList.clear();
	defectList.clear();
	printString="";
	pFtdiChip->state = STATE_READ_NVRAM_LOG;
	cmdPkt.code = USB_REQ_NVRAM_READ_LOG;
	//NumberRecordsNVRAM=0;
	//PREPARE_HEADER(0,USB_REQUEST_NVRAM_READ_LOG,0);
	MessageToLog("> Download Log...");
	SendCommand(cmdPkt);
	
}

//////////////////////////////////////////////////////////////////////////////////
// main button[1]
//////////////////////////////////////////////////////////////////////////////////
void DiskMasterTool::clearLog(bool checked)
{
	USB_HEADER cmdPkt;
	memset(&cmdPkt,0x00,sizeof(USB_HEADER));
	MessageToLog("> Clear Log...");
	this->nvramLog->setRowCount(0);

	cmdPkt.code = USB_REQ_NVRAM_CLEAR_LOG;
	//NumberRecordsNVRAM=0;
	SendCommand(cmdPkt);
}




//////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////
void DiskMasterTool::newDocument(bool checked)
{
	nvramList.clear();
	defectList.clear();
	pc3000List.clear();
	nvramLog->clearContents();
	defectLog->clearContents();
	nvramLog->setRowCount(0);
	defectLog->setRowCount(0);
	saveButton->setEnabled(false);
	printButton->setEnabled(false);
	
	runButton->setEnabled(false);
	pauseButton->setEnabled(false);
	stopButton->setEnabled(false);

	processTextLog->clear();

	cntBads=0;
	cntSlowings=0;
	cntNotReady=0;
	isAlreadyIdentify = false;
	isStopProcess = false;
	isRunningProcess = false;
	isOnlyRegistration = false;
	memset(&disk1Object.identify,0x00,sizeof(CUSTOM_IDENTIFY));
	memset(&disk2Object.identify,0x00,sizeof(CUSTOM_IDENTIFY));
}


template <class T>
void DiskMasterTool::openFile(const QString& filename,QList<T>* list,char*& buf,char* buf_len/* NVRAM or DEFECT list */)
{
	QFile data(filename);
	QDataStream in(&data);
	quint64 count_rec;
	char len;
	if (data.open(QFile::ReadOnly)) 
	{
		in.readRawData  ((char*)&count_rec,8);
		in.readRawData (&len,1);
		if(len)
		{
			*buf_len=len;
			buf = new char[len];
			in.readRawData (buf,len);
		}
	/*	in.readRawData  ((char*)&cntBads,8);
		in.readRawData  ((char*)&cntSlowings,8);
		in.readRawData  ((char*)&cntNotReady,8);*/

		T* nvram_item = new T;
		for(quint64 i=0; i<count_rec;i++)
		{
			in.readRawData  ((char*)nvram_item, sizeof(T));
			list->append(*nvram_item);
		}

		//QTextStream out(&data);
		//out << "Result: " << qSetFieldWidth(10) << left << 3.14 << 2.7;
     // writes "Result: 3.14      2.7       "
	}
	fileString = filename;
	MessageToLog(QString("> Open:")+filename);
}


template <class T>
void DiskMasterTool::saveFile(const QString& filename, const QList<T> & list,char* buf,char buf_len/* NVRAM or DEFECT list */)
{
	QFile data(filename);
	QDataStream out(&data);
	quint64 count_rec = list.count();
	
	if (data.open(QFile::WriteOnly)) 
	{
		out.writeRawData((char*)&count_rec,8);	
		out.writeRawData(&buf_len,1);
		if(buf_len)
			out.writeRawData(buf,buf_len);
		/*out.writeRawData((char*)&cntBads,8);
		out.writeRawData((char*)&cntSlowings,8);
		out.writeRawData((char*)&cntNotReady,8);*/

		for(quint64 i=0; i<count_rec;i++)
			out.writeRawData ((const char*)&list[i],sizeof(T));
		
		data.close();
		MessageToLog(QString("> Save: ")+filename);
	}
	else
		MessageToLog("> Error open file!");
}


//////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////
void DiskMasterTool::openDataFile(bool checked)
{
	int num_records=0;
	char* buf;
	char len=0;
	QString str;
	
	QProgressDialog progress("Opening file...", "Abort", 0, num_records, this);

	QDateTime date = QDateTime::currentDateTime();
	str = date.toString(Qt::DefaultLocaleShortDate);	

	QFileDialog::Options options;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
										"/home/jana/defect_list",
										tr("NVRAM log file (*.nvlog);;Defect list file (*.erlog);; All file (*.*)"));

	
	if(fileName=="") return;

	cntBads = 0;
	cntSlowings = 0;
	cntNotReady = 0;

	nvramList.clear();
	defectList.clear();
	pc3000List.clear();
	//nvramLog->clearContents();
	defectLog->clearContents();
	//nvramLog->setRowCount(0);
	defectLog->setRowCount(0);
	
	printString="";

	if(fileName.contains(".nvlog", Qt::CaseInsensitive))
	{
		openFile<NVRAM_LOG_ITEM>(fileName,&nvramList,buf,&len);
		if(len)
		{
			str=QString(buf).left(len);
			printString=QString("> Report was created: ")+str+"\n";
			MessageToLog(QString("> Report was created: ")+str);
		}

		num_records = nvramList.count();
		printString+=QString("> Number of records: %1 \n").arg(nvramList.count());
		MessageToLog(QString("> Number of records: %1 ").arg(nvramList.count()));
		//num_records = 133;
		nvramLog->show();
		defectLog->hide();
	
		progress.setWindowModality(Qt::ApplicationModal);
		for(int i=0; i<num_records;i++)
		{
			updateNvramLog(&nvramList[i],i);
			progress.setValue(i);
			if (progress.wasCanceled())
				break;
		}
		nvramLog->resizeRowsToContents(); 
		progress.setValue(num_records);
	}
	else
	{
		if(fileName.contains(".erlog", Qt::CaseInsensitive))
		{
			//char& buf = *((char*)&disk2Object.identify);
			char* buf=0;
			openFile<DEFECT_RECORD>(fileName,&defectList,buf,&len);
			if(len)
				memcpy((char*)&disk2Object.identify,buf,len);
			for(int i=0; i<defectList.count();i++)
			{
				defectLog->show();
				nvramLog->hide();
				updateDefectLog(&defectList[i],i);
			}
			ShowDiskInfo(disk2Object);
			ShowResults();
		}
		else
		{
			
			/*if(fileName.contains(".lba", Qt::CaseInsensitive))
			{
				openFile<PC3000_DEFECT_RECORD>(fileName,&pc3000List);
				for(int i=0; i<pc3000List.count();i++)
				{
					updatePc3000Log(&pc3000List[i],i);
				}
			}
			else
			{
				QMessageBox::warning(this, tr("Warning"),
                                tr("Wrong file format!\n"
								   "\n"
								   "\n"
                                   "You can view only NVRAM log files (.nvlog) or \n"
								   "DiskMaster defect list files (.erlog)"),
                                QMessageBox::Cancel);
			}*/
		}
	}

}


void DiskMasterTool::exportPc3000List(const QString& filename, const QList<DEFECT_RECORD> & list/* DEFECT list */)
{
	QList<PC3000_DEFECT_RECORD> pc3000list;
	
	if(!list.count())
	{
		MessageToLog("> defect list is empty");
		return;
	}
	if(!cntBads) 
	{
		MessageToLog("> no defects in list");
		return;
	}

	int record_num=1;
	int first_defect;
	long total_cnt_defects=0;
	
	for(int i=0;i<list.count();i++)
	{
		
		if(list[i].id == ID_ERROR_LBA)
		{
			pc3000list.append(* (new PC3000_DEFECT_RECORD));
			pc3000list.last().blank = 0xffff;
			pc3000list.last().start_lba = *((quint32*)&list[i].lba);
			pc3000list.last().end_lba = pc3000list.last().start_lba;
			pc3000list.last().cnt_defects=1;
			pc3000list.last().record_num=1;
			first_defect=i+1;
			total_cnt_defects++;
			break;
		}
	}

	for(int i=first_defect;i<list.count();i++)
	{
		if(list[i].id == ID_ERROR_LBA)
		{
			quint64 lba=0; 
			for(quint8 j=0;j<6;j++)
				*((quint8*)&lba+j)=list[i].lba[j];
			total_cnt_defects++;
			if((pc3000list.last().start_lba+1) != lba)
			{
				record_num++;

				pc3000list.append(*(new PC3000_DEFECT_RECORD));
				pc3000list.last().blank = 0xffff;
				pc3000list.last().start_lba=*((quint32*)&list[i].lba);
				pc3000list.last().end_lba = pc3000list.last().start_lba;
				pc3000list.last().cnt_defects=1;
				pc3000list.last().record_num=record_num;
			}
			else
			{
				pc3000list.last().end_lba++;
				pc3000list.last().cnt_defects++;
			}
		}
	}

	QFile data(filename);
	QDataStream out(&data);
	char count_rec = pc3000list.count();
	
	if (data.open(QFile::WriteOnly)) 
	{
		out.writeRawData((const char*)&pc3000_list_head,0x61);
		out.writeRawData((const char*)&total_cnt_defects,4);
		
		for(int i=0; i<count_rec;i++)
			out.writeRawData ((const char*)&pc3000list[i],sizeof(PC3000_DEFECT_RECORD));
		MessageToLog(QString("> save: ")+filename);
		data.close();
	}
	else
		MessageToLog("> error open file!");

}

//////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////
void DiskMasterTool::saveDataFile(bool checked)
{
	QFileDialog::Options options;
    QString selectedFilter;
	
	QString fileName;

	char count_rec=0;
	char size_rec=0;
	
	QDateTime date = QDateTime::currentDateTime();

	if(!defectList.isEmpty())
	{
		QString str = strModel+" - "+strSerial+" - "+date.toString(Qt::DefaultLocaleShortDate);	
		str.replace(QRegExp("[:]"), "-");
		str.replace(QRegExp("[/]"), ".");
		fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
											str,
											tr("Defect list file (*.erlog);;PC3000 defect list (*.lba)"));
		if(fileName=="") return;
		if(fileName.contains(".erlog", Qt::CaseInsensitive))
		{
			saveFile<DEFECT_RECORD>(fileName,defectList,(char*)&disk2Object.identify,sizeof(CUSTOM_IDENTIFY));
		}
		else
		{
			if(fileName.contains(".lba", Qt::CaseInsensitive))
			{
				exportPc3000List(fileName,defectList);
			}
		}

	}
	else
	{
		if(!nvramList.isEmpty())
		{
			QString str = "nvram_log_"+date.toString(Qt::DefaultLocaleShortDate);	
			str.replace(QRegExp("[:]"), "-");
			str.replace(QRegExp("[/]"), ".");
			fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
												str,
												tr("NVRAM log file (*.nvlog)"));
			if(fileName=="") return;
			str = date.toString(Qt::DefaultLocaleShortDate);
			int i;
			char* buf = new char[str.size()];
			QChar* data = str.data();
			for(i=0;i<str.size();i++)
			{
				buf[i]=data->toAscii();
				data++;
			}
			saveFile<NVRAM_LOG_ITEM>(fileName,nvramList,buf,i);
		}
	}
	
	
}



     
/*
//////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////
void DiskMasterTool::printLog()
{
	
	previewProc(printer);
	printer->setOutputFormat(QPrinter::NativeFormat);

    QPrintDialog *dialog = new QPrintDialog(printer, this);
    dialog->setWindowTitle(tr("Print Document"));
    //if (editor->textCursor().hasSelection())
    //    dialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (dialog->exec() != QDialog::Accepted)
		return;

}

//////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////
int DiskMasterTool::printPreview(void)
{
	
     printer->setOutputFormat(QPrinter::PdfFormat);
    // printer->setOutputFileName("nonwritable.txt");
   

	QPrintPreviewDialog* preview = new QPrintPreviewDialog(printer,this,Qt::Window);
	
	connect(preview,SIGNAL(paintRequested(QPrinter*)),this,SLOT(previewProc(QPrinter*)));
	
	preview->setViewMode(QPrintPreviewWidget::SinglePageView);
	preview->setZoomMode(QPrintPreviewWidget::FitToWidth);
	preview->setCurrentPage(1);
	preview->showMaximized();
	preview->exec();
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////
void DiskMasterTool::previewProc(QPrinter* printer)
{
	int row_height = 30;
	int row_pos = 0;
	int column_pos = 0;


	printer->setOrientation(QPrinter::Landscape); 
    QPainter painter;
	QRect rect;
    if (! painter.begin(printer)) { // failed to open file
        qWarning("failed to open file, is it writable?");
        return;
    }
    painter.drawText(10, 10, "Test");
    if (! printer->newPage()) {
        qWarning("failed in flushing page to disk, disk full?");
        return;
    }
	//painter.rotate(90);
	painter.scale(0.87,0.87);
	//painter.drawRect(10, 10, "Test 2");
	rect = printer->pageRect();
	row_pos = rect.y();
	column_pos = rect.x();
	painter.drawText(column_pos, row_pos, "Test 2");
	row_pos+=row_height;
	//painter.drawText(QRect(column_pos,row_pos,30,300), Qt::AlignTop , "Test 2");
	//row_pos+=row_height;
//    painter.drawRect (rect);
	//for(i=0;i<nvramList.count();i++)
	printRow(&painter,&nvramLogStrings,rect.x(),&row_pos,row_height);

	QStringList nvram_str;
	printRowNVRAMLog(&nvram_str);
	printRow(&painter,&nvram_str,rect.x(),&row_pos,row_height);

//	prepareHeaderToPrint
	
	
    painter.end();
}
*/

void DiskMasterTool::printRow(QPainter* painter, QStringList* str, int baseX,int* row_pos,int row_height)
{
	QVector<QRect> nvramPrintRects;
	int width=0;
	for(int i=0;i<nvramLogStrings.count();i++)
	{
		QRect* rect1 = new QRect;
		nvramPrintRects << *rect1;
		
		nvramPrintRects[i].setX(baseX+width);
		nvramPrintRects[i].setWidth(nvramLog->columnWidth(i));
		nvramPrintRects[i].setHeight(row_height);
		painter->drawText(baseX+width+10,*row_pos-row_height/2, str->at(i));
		width+=nvramLog->columnWidth(i);
		nvramPrintRects[i].setY(*row_pos);
	}
	painter->drawRects(nvramPrintRects);
	*row_pos= *row_pos + row_height;
}



void DiskMasterTool::fadeInWidget(HoveredButton** button_array, int num_buttons)
{
	for(int i=0;i<num_buttons;i++)
	{
		if (faderWidget[i])
			faderWidget[i]->close();

		button_array[i]->show();
		faderWidget[i] = new FaderWidget(button_array[i]);
		faderWidget[i]->start();
	}
}


//
//void DiskMasterTool::AddItemToDeviceTree(void)
//{	
//	QString str = "Device1";
//	QIcon* ico = &okIco;
//	QTreeWidgetItem* item = new QTreeWidgetItem(deviceTree);
//	item->setText(0,str);
//	item->setIcon(0,*ico);
//	//deviceTree->addItem(item);
//
//	//item->setData(Qt::UserRole,qVariantFromValue(&ListNVRAMItems[NumberRecordsNVRAM]));
//}

/*
nvramListSizes[""]=25;
nvramListSizes["Current Process"]=100;
nvramListSizes["Destination"]=120;
nvramListSizes["Source"]=120;
nvramListSizes["Done(Size)"]=120;
nvramListSizes["Bads"]=100;
nvramListSizes["NRDY1(2)"]=100;
nvramListSizes["UNCR/Slows"]=100;
nvramListSizes["Time average"]=100;
nvramListSizes["Time max"]=80;
nvramListSizes["Time Elaps(Time Colaps)"]=100;
*/



void DiskMasterTool::addNvramLogRow(char* buf,unsigned short len)
{	
	QString str;
	QIcon* ico;
	unsigned char item_len=0;
	bool selection=false;
	//quint16* ptr = (quint16*)buf;
	unsigned int count_rec=*((quint16*)buf);
	//count_rec<<=8;
	//count_rec&=buf[1];
	//*((unsigned char*)&count_rec+1)=buf[1];
	buf+=2;
	for(int i=0;i<count_rec;i++)
	{
		item_len=*buf;
		NVRAM_LOG_ITEM* nvramItem = new NVRAM_LOG_ITEM;
		memset(nvramItem,0x00,sizeof(NVRAM_LOG_ITEM));
		nvramList.append(*nvramItem);
		

		SaveRecordToList(buf+1,item_len);
		//SetModeString(&str,ListNVRAMItems[NumberRecordsNVRAM].CurrentProcess,ListNVRAMItems[NumberRecordsNVRAM].CurrentSubProcess);
	
		updateNvramLog(&nvramList[i],i);
		buf+=item_len;
		len-=item_len;
	} 
	nvramLog->resizeRowsToContents(); 

	saveButton->setEnabled(true);
	MessageToLog("> Read NVRAM ok!");

	QDateTime date = QDateTime::currentDateTime();
	str = date.toString(Qt::DefaultLocaleShortDate);	
	printString+=QString("> Report was created: ")+str+"\n";
	MessageToLog(QString("> Report was created: ")+str);
	printString+=QString("> Number of records: %1 ").arg(nvramList.count());
	MessageToLog(QString("> Number of records: %1 ").arg(nvramList.count()));
}

void DiskMasterTool::SaveRecordToList(char* nvramItemBuf,unsigned char lengthBuf)
{
	unsigned char code,i=0;

	NVRAM_LOG_ITEM* lastNvramItem = &nvramList.last();
	
	do
	{
		code=nvramItemBuf[i];
		i++;
		if(i==lengthBuf) break;
		switch(code)
		{
		
		case ID_COUNTER_BADS:
			memcpy(&lastNvramItem->counterBads,&nvramItemBuf[i],6);
			i+=6;
			break;


		case ID_COUNTER_SOFTS:
			memcpy(&lastNvramItem->counterSofts,&nvramItemBuf[i],6);
			i+=6;
			break;
		
		case ID_COUNTER_NRDY1:
			memcpy(&lastNvramItem->counterNrdy1,&nvramItemBuf[i],6);
			i+=6;
			break;
		
		case ID_COUNTER_NRDY2:
			memcpy(&lastNvramItem->counterNrdy2,&nvramItemBuf[i],6);
			i+=6;
			break;

		case ID_CNT_BLOCKS:	// ???? удалить параметр
			i+=2;
			break;
		/*case ID_COUNTER_SLOWS:
			memcpy(&lastNvramItem.CounterSlows,&nvramItemBuf[i],6);
			i+=6;
			break;*/

		case ID_CURR_LBA:
			memcpy(&lastNvramItem->DoningLBA,&nvramItemBuf[i],6);
			i+=6;
			break;

		case ID_MAX_LBA:
			memcpy(&lastNvramItem->MaxLBA,&nvramItemBuf[i],6);
			i+=6;
			break;

		case ID_CURR_PROCESS:
			lastNvramItem->CurrentProcess=nvramItemBuf[i];
			i+=1;
			break;
			
		case ID_CURR_SUB_PROCESS:
			lastNvramItem->CurrentSubProcess=nvramItemBuf[i];
			i+=1;
			break;

		case ID_DESTINATION_MODEL:
			memcpy(&lastNvramItem->DestinationModel,&nvramItemBuf[i],16);
			i+=16;
			break;

		case ID_DESTINATION_SERIAL:
			memcpy(&lastNvramItem->DestinationSerial,&nvramItemBuf[i],20);
			i+=20;
			break;

		case ID_SOURCE_MODEL:
			memcpy(&lastNvramItem->SourceModel,&nvramItemBuf[i],16);
			i+=16;
			break;

		case ID_SOURCE_SERIAL:
			memcpy(&lastNvramItem->SourceSerial,&nvramItemBuf[i],20);
			i+=20;
			break;

		case ID_TIME_ELAPS:
			//lastNvramItem.timeElaps.
			memcpy(&lastNvramItem->timeElaps,&nvramItemBuf[i],12);
			i+=12;
			break;

		case ID_TIME_COLAPS:
			memcpy(&lastNvramItem->timeColaps,&nvramItemBuf[i],12);
			i+=12;
			break;
		
		case ID_TOTAL_TIME:
			memcpy(&lastNvramItem->totalTime,&nvramItemBuf[i],4);
			i+=4;
			break;
		
		case ID_TIME_AVERAGE:
			memcpy(&lastNvramItem->timeAverage,&nvramItemBuf[i],4);
			i+=4;
			break;
		
		case ID_TIME_MAX:
			memcpy(&lastNvramItem->timeMax,&nvramItemBuf[i],4);
			i+=4;
			break;

		case ID_END_PROCESS_CODE:
			memcpy(&lastNvramItem->EndProcessCode,&nvramItemBuf[i],2);
			i+=2;
			break;

		case ID_END_OF_RECORD:
			i=lengthBuf;		//go out
		}
		
	} while(i<lengthBuf);
}

/*

void DiskMasterTool::printRowNVRAMLog(QStringList* nvram_str)
{
	QString str;
	QStringList* pStringList;
	int time_ms;
	int time_ms_remind;
	NVRAM_LOG_ITEM nvram_item = nvramList.last();

	//0
	pStringList = SetModeString(&str,nvram_item.CurrentProcess,nvram_item.CurrentSubProcess);
	nvram_str->append(str);
	//1
	str=tr((const char*)nvram_item.DestinationModel)+"; s/n: "+tr((const char*)nvram_item.DestinationSerial);
	nvram_str->append(str);
	//2
	str="";
	if(CheckForZero(nvram_item.SourceModel,16))
		str=QString::fromAscii((const char*)nvram_item.SourceModel,16)+"; s/n: "+QString::fromAscii((const char*)nvram_item.SourceSerial,20);
	nvram_str->append(str);
	//3
	str="";
	str=QString("%1 (%2)").arg(nvram_item.DoningLBA).arg(nvram_item.MaxLBA);
	nvram_str->append(str);
	//4
	str="";
	if(nvram_item.counterBads)
		str=QString("%1").arg(nvram_item.counterBads);
	nvram_str->append(str);
	//5
	str="";
	if(nvram_item.counterSofts)
		str=QString("%1").arg(nvram_item.counterSofts);
	nvram_str->append(str);
	//6
	str="";
	if(nvram_item.counterNrdy1 || nvram_item.counterNrdy2)
		str=QString("%1").arg(nvram_item.counterNrdy1+nvram_item.counterNrdy2);
	nvram_str->append(str);
	//7
	str="";
	if(nvram_item.timeAverage)
	{
		time_ms = nvram_item.timeAverage/10;
		time_ms_remind =  nvram_item.timeAverage % 10;
		str=QString("%1").arg(time_ms)+","+QString("%1").arg(time_ms_remind)+" msec";	
	}
	nvram_str->append(str);
	//8
	str="";
	if(nvram_item.timeMax)
	{
		QString measure = " msec";
		time_ms = nvram_item.timeMax/10;
		if(time_ms>1000)
			measure = " sec";
		time_ms_remind =  nvram_item.timeMax % 10;
		str=QString("%1").arg(time_ms) + "," + QString("%1").arg(time_ms_remind) + measure;
	}
	nvram_str->append(str);
	//9
	str="";
	if(nvram_item.totalTime)
	{
		int hours = nvram_item.totalTime/3600;
		int hours_rem = nvram_item.totalTime - 3600*hours;
		int mins = hours_rem/60;
		int secs = hours_rem - mins*60;
		str=QString("%1 : %2 : %3 (%4 : %5 : %6)").
					arg(nvram_item.timeElaps[8],2,10,QLatin1Char('0')).
					arg(nvram_item.timeElaps[4],2,10,QLatin1Char('0')).
					arg(nvram_item.timeElaps[0],2,10,QLatin1Char('0')).
					arg(nvram_item.timeColaps[8],2,10,QLatin1Char('0')).
					arg(nvram_item.timeColaps[4],2,10,QLatin1Char('0')).
					arg(nvram_item.timeColaps[0],2,10,QLatin1Char('0'));
	}
	nvram_str->append(str);
}
*/


void MultiRowTableWidgetItem::paintEvent(QPaintEvent* event)
{
		
}

void MultiLineTableWidget::paintEvent(QPaintEvent* event)
{
	QTableWidget::paintEvent(event);
}

void DiskMasterTool::updateNvramLog(NVRAM_LOG_ITEM* nvram_item, int row)
{
	QString str;
	QIcon* ico = new QIcon;
	QStringList* pStringList;
	QTableWidgetItem* tableItem;
	
	int time_ms;
	int time_ms_remind;


	//nvramLog->setRowCount(row+1);
	nvramLog->setRowCount(nvramLog->rowCount()+1);
	row = nvramLog->rowCount()-1;
	///////////////////////////////
	//nvramLog->setRowCount(1000);
	pStringList = SetModeString(&str,nvram_item->CurrentProcess,nvram_item->CurrentSubProcess);
	
	/*nvramLog->setRowCount(pStringList->indexOf("Finish Code"));
	nvramLog->setVerticalHeaderLabels(*pStringList);*/
	
	
	ico = &okIco;
	if(nvram_item->counterSofts)
		ico=&warningIco;

	if(nvram_item->counterBads || nvram_item->EndProcessCode)
		ico=&errorIco;

		//item->setIcon(*ico);
	
	tableItem = new QTableWidgetItem;
	nvramLog->setItem(row, nvramLogStrings.indexOf(QString(" ")), tableItem);
	tableItem->setIcon(*ico);

	
	tableItem = new QTableWidgetItem;
	nvramLog->setItem(row, nvramLogStrings.indexOf(QString("Current Process")), tableItem);
	tableItem->setText(str);
	//...............................................................
	tableItem = new QTableWidgetItem;
	nvramLog->setItem(row, nvramLogStrings.indexOf(QString("Destination")), tableItem);
	if(CheckForZero(nvram_item->SourceModel,16))
	{
//		nvramLog->setRowCount(nvramLog->rowCount()+1);
//		tableItem = new MultiRowTableWidgetItem;
//		nvramLog->setItem(nvramLog->rowCount()-1, nvramLogStrings.indexOf(QString("Destination")), tableItem);
	
		DiskStringFromBuf(str,nvram_item->SourceModel,16);
		QString str1;
		DiskStringFromBuf(str1,nvram_item->SourceSerial,20);
		str="Src: "+str+"; s/n:"+str1+"\n";
		tableItem->setText(str);
	}
	else
		str="";
	QString str1;
	DiskStringFromBuf(str1,nvram_item->DestinationModel,16);
	QString str2;
	DiskStringFromBuf(str2,nvram_item->DestinationSerial,20);
	str+=(str1+"; s/n:"+str2);
	tableItem->setText(str);

	//...............................................................
	tableItem = new QTableWidgetItem;
	nvramLog->setItem(row, nvramLogStrings.indexOf(QString("Done(Size)")), tableItem);
	str=QString("%1 (%2)").arg(nvram_item->DoningLBA).arg(nvram_item->MaxLBA);
	tableItem->setText(str);
	//...............................................................
	if(nvram_item->counterBads)
	{
		tableItem = new QTableWidgetItem;
		nvramLog->setItem(row, nvramLogStrings.indexOf(QString("Bads")), tableItem);
		if(nvram_item->CurrentProcess==MODE_COPY)
			tableItem->setToolTip(QString("HDD1 bads: %1").arg(nvram_item->counterBads));
		else
			tableItem->setToolTip(QString("HDD2 bads: %1").arg(nvram_item->counterBads));

		str=QString("%1").arg(nvram_item->counterBads);
		tableItem->setText(str);
	}
	//...............................................................
	if(nvram_item->counterSofts)
	{
		tableItem = new QTableWidgetItem;
		nvramLog->setItem(row, nvramLogStrings.indexOf(QString("UNCR/Slows")), tableItem);
		str=QString("%1").arg(nvram_item->counterSofts);
		tableItem->setText(str);
	}
	//...............................................................
	if(nvram_item->counterNrdy1 | nvram_item->counterNrdy2)
	{
		tableItem = new QTableWidgetItem;
		tableItem->setToolTip(QString("NRDY1: %1").arg(nvram_item->counterNrdy1)+"\n"+QString("NRDY2: %1").arg(nvram_item->counterNrdy2));
		nvramLog->setItem(row, nvramLogStrings.indexOf(QString("NRDY1(2)")), tableItem);
		str=QString("%1").arg(nvram_item->counterNrdy1 + nvram_item->counterNrdy2);
		tableItem->setText(str);
	}
	//...............................................................
	if(nvram_item->timeAverage)
	{
		tableItem = new QTableWidgetItem;
		time_ms = nvram_item->timeAverage/10;
		time_ms_remind =  nvram_item->timeAverage % 10;
		str=QString("%1").arg(time_ms)+","+QString("%1").arg(time_ms_remind)+" msec";	
		nvramLog->setItem(row, nvramLogStrings.indexOf(QString("Time mid")), tableItem);
		tableItem->setText(str);
	}
	//...............................................................
	if(nvram_item->timeMax)
	{
		tableItem = new QTableWidgetItem;
		nvramLog->setItem(row, nvramLogStrings.indexOf(QString("Time max")), tableItem);
		QString grad(" msec");
		double time_ms = nvram_item->timeMax/10;
		if(time_ms>1000)
		{
			time_ms/=1000;
			grad.clear();
			grad = " sec";
		}
		str=QString("%1").arg(time_ms)+grad;
		tableItem->setText(str);
	}
	//...............................................................
	if(nvram_item->totalTime)
	{
		tableItem = new QTableWidgetItem;
		nvramLog->setItem(row, nvramLogStrings.indexOf(QString("Time Elaps(Time Colaps)")), tableItem);
		int hours = nvram_item->totalTime/3600;
		int hours_rem = nvram_item->totalTime - 3600*hours;
		int mins = hours_rem/60;
		int secs = hours_rem - mins*60;
		str=QString("%1 : %2 : %3 (%4 : %5 : %6)").
					arg(nvram_item->timeElaps[8],2,10,QLatin1Char('0')).
					arg(nvram_item->timeElaps[4],2,10,QLatin1Char('0')).
					arg(nvram_item->timeElaps[0],2,10,QLatin1Char('0')).
					arg(nvram_item->timeColaps[8],2,10,QLatin1Char('0')).
					arg(nvram_item->timeColaps[4],2,10,QLatin1Char('0')).
					arg(nvram_item->timeColaps[0],2,10,QLatin1Char('0'));
		tableItem->setText(str);
	}


	/*if(!nvram_item->EndProcessCode)
		ui.stateLabel->setPixmap(QPixmap(":/DiskMasterTool/ok.png"));
	else
		ui.stateLabel->setPixmap(QPixmap(":/DiskMasterTool/err.png"));*/
}


void DiskMasterTool::toggleDefectsFromTable(QString str)
{
	matchList=defectLog->findItems(str,Qt::MatchExactly);
}

void DiskMasterTool::setDefectLogColumnSizes(QList<int>* listSizes)
{
	defectLog->setColumnWidth (defectLogStrings.indexOf(QString(" ")),25);
	defectLog->setColumnWidth (defectLogStrings.indexOf(QString("LBA")),100);
	defectLog->setColumnWidth (defectLogStrings.indexOf(QString("Type")),100);
	defectLog->setColumnWidth (defectLogStrings.indexOf(QString("Code")),50);
	defectLog->setColumnWidth (defectLogStrings.indexOf(QString("Time Op")),100);
	
	for(int i=0;i<defectLogStrings.count();i++)
		listSizes->append(defectLog->columnWidth(i));

}

void DiskMasterTool::updatePc3000Log(PC3000_DEFECT_RECORD* buf,quint8 flag)
{

}
void DiskMasterTool::updateDefectLog(DEFECT_RECORD* buf,int row, quint8 flag)
{
	QTableWidgetItem* tableItem;
	QString str;
	QIcon ico;
	qlonglong lba=0;
	QList<QTableWidgetItem*> list_defects;
	
	saveButton->setEnabled(true);
	defectLog->setRowCount(defectList.count());
	defectLog->resizeRowsToContents();
	//memcpy(&ListNVRAMItems[NumberRecordsNVRAM].counterBads,&nvramItemBuf[i],6);
	switch(flag)
	{
	case ARRIVE_NEW_DEFECT:			
		// [0] - icon
		tableItem = new QTableWidgetItem;
		defectLog->setItem(row, 0, tableItem);
		switch(buf->id)
		{
		case ID_SLOW_LBA:
			ico.addPixmap(QPixmap("warning.png"));
			cntSlowings++;
			break;

		case ID_ERROR_LBA:
			ico.addPixmap(QPixmap("error.png"));
			cntBads++;
			break;

		case ID_NOT_READY_LBA:
			ico.addPixmap(QPixmap("error.png"));
			cntNotReady++;
			break;
		}
		tableItem->setIcon(ico);

		// [1] - LBA
		tableItem = new QTableWidgetItem;
		defectLog->setItem(row, 1, tableItem);
		lba=0;
		for(int i=0;i<6;i++)
			*((unsigned char*)&lba+i)=buf->lba[i];
		str=QString("%1").arg(lba);
		tableItem->setText(str);
		
		// [2] - Type
		tableItem = new QTableWidgetItem;
		defectLog->setItem(row, 2, tableItem);
		switch(buf->id)
		{
		case ID_SLOW_LBA:
			str = QString("slowing");
			break;

		case ID_ERROR_LBA:
			str = QString("bad");
			break;

		case ID_NOT_READY_LBA:
			str = QString("not ready");
			break;
		}
		tableItem->setText(str);

		// [4] - Time(for slowings)
		if(buf->id == ID_ERROR_LBA)
		{
			// [3] - Code
			tableItem = new QTableWidgetItem;
			defectLog->setItem(row, 3, tableItem);
			str=QString("0x%1").arg(buf->code,2,16,QLatin1Char('0'));
			tableItem->setText(str);
		}

		// [4] - Time(for slowings)
		if(buf->id == ID_SLOW_LBA)
		{
			
			tableItem = new QTableWidgetItem;
			defectLog->setItem(row, 4, tableItem);
			QString grad(" msec");
			double time_ms = buf->time/10;
			if(time_ms>1000)
			{
				time_ms/=1000;
				grad.clear();
				grad = " sec";
			}
			str=QString("%1").arg(time_ms)+grad;
			tableItem->setText(str);
		}
		break;

	case TOGGLE_ERRORS:
		toggleDefectsFromTable(QString("bad"));
		
		break;
	
	case TOGGLE_SLOWINGS:
		toggleDefectsFromTable(QString("slowing"));
		break;


	}

//	defectLog->resizeColumnsToContents();
}



void DiskMasterTool::parseBufList(char* buf, quint16 len)
{
	USB_HEADER cmd;
	QString str;
	QMessageBox::Icon icon;
	quint8 msg_code = buf[0];
	int ret;
	QPixmap* ico;
	QMessageBox* msgBox  = new QMessageBox(this);
	QMessageBox* msgBoxCustom = new QMessageBox(this);
	msgBoxCustom->setIcon(QMessageBox::Question);
	msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::No | QMessageBox::Cancel);
	msgBox->setDefaultButton(QMessageBox::Ok);
	msgBox->setIcon(QMessageBox::Question);
	memset(&cmd,0x00,sizeof(USB_HEADER));

	switch(msg_code)
	{
	case USB_MSG_OK:
		MessageToLog("> ...ok!");
		break;

	case USB_MSG_NVRAM_READ_LOG:
		switch(buf[1])
		{
		case SUB_NVRAM_LOG_EMPTY:
			MessageToLog("> NVRAM is empty!");
			break;

		case SUB_NVRAM_ERROR:	
			MessageToLog("> NVRAM error!");
			break;
		default:
			addNvramLogRow(buf+3,len);
			break;
		}
		break;

	case USB_MSG_START_REGISTRATION:
		//buf[2]&=0xF0;
		//buf[2]>>=4;
		memset(&cmd,0x00,sizeof(USB_HEADER));
		switch(buf[2]>>4)
		{
		case SUB_START_OK:
			MessageToLog("> ...ok!");
			cmd.code=0;
			break;

		case SUB_FINISH_IDENTIFY:		
			if(!isAlreadyIdentify)
			{
				MessageToLog("> identify ok!");
				memcpy((char*)&disk1Object.identify,buf+CUSTOM_INFO_SIZE,sizeof(CUSTOM_IDENTIFY));
				memcpy((char*)&disk2Object.identify,buf+3+CUSTOM_INFO_SIZE,sizeof(CUSTOM_IDENTIFY));

				//memcpy(&diskObject.IdentifyInfo,(IDENTIFY_IDE*)(buf+3),512);
				//diskObject.ParseIdentify();
				
				if(currentProcess == MODE_COPY)
				{
					ShowDiskInfo(disk1Object);
					ShowDiskInfo(disk2Object);
				}
				else
					ShowDiskInfo(disk2Object);

				isAlreadyIdentify=true;
							
			}	
			if(buf[1]&0x0F) break;	// if only registration started skip dialog
			//MessageToLog("> Start New Task...");
			/*ico = new QPixmap(16,16);
			ico->load(":/DiskMasterTool/Goodshield.png");
			msgBox->setIconPixmap(*ico);*/
			ret = OkNoStandardDialog(cmd,msgBox,"   Identify finished,continue process?              ");
			if((ret == USB_REQ_CANCEL) || (ret == USB_REQ_DISCARD))
			{
				isAlreadyIdentify = false;
				runButton->setEnabled(true);
				pauseButton->setEnabled(false);
				stopButton->setEnabled(false);
				cmd.code = USB_REQ_BACK;
				MessageToLog("> operation canceled");
			}
			else
			{
				cmd.code = USB_REQ_CONTINUE;
				//qDebug()<<"->start process";
				//isRunningProcess=true;
				//stopButton->setEnabled(true);
			}
			break;
		case SUB_ARE_YOU_SURE_UNLOCK:
			ret = OkNoStandardDialog(cmd,msgBox,"   Are you sure to unlock HDD?              ");
			if((ret == USB_REQ_CANCEL) || (ret == USB_REQ_DISCARD))
			{
				runButton->setEnabled(true);
				pauseButton->setEnabled(false);
				stopButton->setEnabled(false);
				//cmd.code = USB_REQ_BACK;
				MessageToLog("> operation canceled");
			}
			else
			{
				//cmd.code = USB_REQ_CONTINUE;
				//qDebug()<<"->start process";
				//isRunningProcess=true;
				//stopButton->setEnabled(true);
			}
			break;

		case SUB_WAIT_NEW_TASK:		
			//if(!isAlreadyIdentify)
			//{
			//	MessageToLog("> identify ok!");
			//	memcpy((char*)&disk1Object.identify,buf+CUSTOM_INFO_SIZE,sizeof(CUSTOM_IDENTIFY));
			//	memcpy((char*)&disk2Object.identify,buf+3+CUSTOM_INFO_SIZE,sizeof(CUSTOM_IDENTIFY));

			//	//memcpy(&diskObject.IdentifyInfo,(IDENTIFY_IDE*)(buf+3),512);
			//	//diskObject.ParseIdentify();
			//	
			//	if(currentProcess == MODE_COPY)
			//	{
			//		ShowDiskInfo(disk1Object);
			//		ShowDiskInfo(disk2Object);
			//	}
			//	else
			//		ShowDiskInfo(disk2Object);

			//	isAlreadyIdentify=true;
			//				
			//}	
			//if(buf[1]&0x0F) break;	// if only registration started skip dialog
			MessageToLog("> Start New Task...");
			/*ico = new QPixmap(16,16);
			ico->load(":/DiskMasterTool/Goodshield.png");
			msgBox->setIconPixmap(*ico);*/
			ret = OkNoStandardDialog(cmd,msgBox,"              Start New Task?              ");
			if((ret == USB_REQ_CANCEL) || (ret == USB_REQ_DISCARD))
			{
				isAlreadyIdentify = false;
				MessageToLog("> operation canceled");
			}
			else
			{
				qDebug()<<"->start process";
				isRunningProcess=true;
			}
			break;

		case SUB_WAIT_LAST_MODE:
			/*if(!isAlreadyIdentify)
			{
				MessageToLog("> identify ok!");
				memcpy((char*)&disk1Object.identify,buf+3,sizeof(CUSTOM_IDENTIFY));
				memcpy((char*)&disk2Object.identify,buf+3+CUSTOM_INFO_SIZE,sizeof(CUSTOM_IDENTIFY));

				if(currentProcess == MODE_COPY)
				{
					ShowDiskInfo(disk1Object);
					ShowDiskInfo(disk2Object);
				}
				else
					ShowDiskInfo(disk2Object);

				isAlreadyIdentify=true;
			}*/
			//ico = new QPixmap(16,16);
			//ico->load(":/DiskMasterTool/Goodshield.png");
			//ico->scaled(QSize(32,32),Qt::KeepAspectRatio);
			//msgBoxCustom->setIconPixmap(*ico);

			msgBoxCustom->setText("                 Last Mode?                ");
			//msgBoxCustom->setStandardButtons(QMessageBox::Ok);
			msgBoxCustom->addButton(tr("Ok"), QMessageBox::AcceptRole);
			msgBoxCustom->addButton(tr("Discard"), QMessageBox::RejectRole);
			msgBoxCustom->addButton(tr("Start New Task"), QMessageBox::DestructiveRole);

			ret = msgBoxCustom->exec();
			switch (ret) 
			{
			case QMessageBox::AcceptRole:
				cmd.code = USB_REQ_OK;
				//MessageToLog(">start operation canceled");
				break;
			case QMessageBox::RejectRole:
				isAlreadyIdentify = false;
				cmd.code = USB_REQ_DISCARD; 
				break;
			case QMessageBox::DestructiveRole:
				cmd.code = USB_REQ_CANCEL;
				break;
	
			default:
			   // should never be reached
			   break;
			};
			break;

		case SUB_WAIT_UNLOCK_HPA:
			if((buf[2]&0x0F)!=0x01) break;							 
			msgBoxCustom->setText("                    Unlock HPA?                      ");
			msgBoxCustom->setStandardButtons(QMessageBox::Ok);
			msgBoxCustom->addButton(tr("Without Unlock"), QMessageBox::RejectRole);
			
			ret = msgBoxCustom->exec();
			switch (ret) 
			{
			case QMessageBox::Ok:
				cmd.code = USB_REQ_OK;
				//MessageToLog(">start operation canceled");
				break;
			case 0:
				cmd.code = USB_REQ_CANCEL;
				MessageToLog("> start without unlock HPA");
				break;
			default:
			   // should never be reached
			   break;
			};
			break;

		case SUB_ALREADY_STARTED:
			qDebug() << "-> process already started, turn-on registration";
			if(buf[1]>>4 !=MODE_TEST_VERIFY) 
			{
				msgBoxCustom->setText("              There is another task is running!                       ");
				msgBoxCustom->setStandardButtons(QMessageBox::Cancel);
				msgBoxCustom->setIcon(QMessageBox::Warning);
				msgBoxCustom->exec();
				stopButton->setEnabled(true);
				break;
			}
			isRunningProcess=true;
			isAlreadyIdentify=true;
			cmd.code = USB_REQ_START_REGISTRATION;
			cmd.sub_code[0] = LO_ONLY_REGISTRATION;	
			break;
		case SUB_HDD2_LOWER_HDD1:
			break;
		}
		if(cmd.code)
			SendCommand(cmd);
		break;

	case USB_MSG_STOP_REGISTRATION:
		if(!isAlreadyIdentify) break;
		switch(buf[1])
		{
		case SUB_BREAK_PROCESS:
			isBreakProcess = true;
			if(isStopProcess)
			{
				cmd.code = USB_REQ_STOP_REGISTRATION;
				cmd.sub_code[0] = LO_STOP_PROCESS;
			}
			// в случае если была прервана операция идентификации
			if(!isRunningProcess)
			{
				qDebug() <<"->cancel identification";
				isBreakProcess=false;
			}
			//stopButton->setEnabled(false);
			/*
			if(!isRunningProcess)
			{
				//MessageToLog("> break process");
			}
			else
			{
				////resumeButton->show();
				runButton->show();
				pauseButton->hide();

			}
			*/
			break;

		case SUB_STOP_PROCESS:
			cmd.code = 0x00;
			isRunningProcess=false;
			isAlreadyIdentify=false;
			MessageToLog("> stop process!");
			break;

		case SUB_WAIT_SAVE_NVRAM_LOG:
			isAlreadyIdentify=false;
			stopButton->setEnabled(false);
			OkNoStandardDialog(cmd,msgBox,"         Save results to NVRAM?            ");
			break;

		};
		if(cmd.code)
			SendCommand(cmd);
		break;


	case USB_MSG_DEFECT:
		defectList.append(*((DEFECT_RECORD*)(buf+1)));
		updateDefectLog(&defectList.last(),defectList.count()-1);
		break;

	case USB_MSG_CURRENT_LBA:
		break;

	case USB_MSG_FINISHED:
		switch(buf[1])
		{
		ShowResults();
		case SUB_FINISH_OK:
			icon = QMessageBox::Information;
			str = " Process finished ok!  ";
			break;

		case SUB_FINISH_ERR:
			icon = QMessageBox::Critical;
			str = " Process finished with errors!  ";
			break;

		case SUB_FINISH_ERR_RELOCK_ERR:
			icon = QMessageBox::Critical;
			str = " Process finished with error! \n\n Error restore HPA! ";
			break;

		case SUB_FINISH_OK_RELOCK_ERR:
			icon = QMessageBox::Warning;
			str = " Process finished ok! \n\n Error restore HPA! ";
			break;
		};
		MessageToLog(">"+str);
		msgBox = new QMessageBox(icon,QString("Device Notification"),str,QMessageBox::Ok,this);
		ret = msgBox->exec();
		cmd.code = USB_REQ_BACK; 
		SendCommand(cmd);
		break;

	case USB_MSG_ERR:
		switch(buf[1])
		{
		case SUB_HDD1_NOT_READY:
			MessageToLog("> HDD1 not ready \n");
			break;
		case SUB_HDD2_NOT_READY:
			MessageToLog("> HDD2 not ready\n");
			break;
		}
		isRunningProcess=false;
		break;
	}
	updateControls(OnUsbRequest);
}




QStringList* DiskMasterTool::SetModeString(QString* str,unsigned char mode,unsigned char sub_mode=0)
{
	QStringList* pStringList;
	
	switch(mode)
	{
	case MODE_COPY:
		pStringList = &listStringsCopy;
		str->append("COPY");
		break;

	case MODE_ERASE:
		pStringList = &listStringsErase;
		switch(sub_mode)
		{
		case MODE_ERASE_0x00:
			str->append("ERASE 0x00");
			break;
		case MODE_ERASE_0xFF:
			str->append("ERASE 0xFF");
			break;
		case MODE_ERASE_RAND:
			str->append("ERASE RAND");
			break;
		}		
		break;

	case MODE_TEST_VERIFY:
		pStringList = &listStringsVerify;
		str->append("TEST VERIFY");
		break;

	case MODE_WRITE_COMPARE:				
		switch(sub_mode)
		{
		case MODE_TEST_READ:
			pStringList = &listStringsTestWriteVerify;
			str->append("TEST WRITE VERIFY");
			break;
		default:
			pStringList = &listStringsTestWrite;
			str->append("TEST WRITE");
			break;
		}
		break;

	case MODE_TEST_READ:
		pStringList = &listStringsTestRead;
		str->append("TEST READ");
		break;
	}

	return pStringList;
}






void DiskMasterTool::MessageToLog(QString str)
{
	processTextLog->append(str);
}


void DiskMasterTool::ShowDiskInfo(Disk& disk)
{
	QByteArray str;
	QString str1;
	
	strSerial.clear();
	strModel.clear();

	strSerial = QString((char*)disk.identify.Serial).left(20);
	strSerial=strSerial.trimmed();
	strModel = QString((char*)disk.identify.Model).left(16);
	strModel=strModel.trimmed();

//	MessageToLog("> -------------------------------------");
	printString+=QString("> Model: ")+strModel+"\n";
	MessageToLog(QString("\n> Model: ")+strModel);

	printString+=QString("> Serial: ")+strSerial+"\n";
	MessageToLog(QString("> Serial: ")+strSerial);

	double size_temp = *((quint64*)&disk.identify.Size[0]);
	size_temp*=512;
	size_temp/=1024;	//kB
	size_temp/=1024;	//MB
	size_temp/=1024;	//GB
	str1=QString("%1").arg(size_temp)+QString(" GB");
	printString+=QString("> Size: ")+QString(str1)+"\n";
	MessageToLog(QString("> Size: ")+QString(str1)+"\n");
//	MessageToLog("> -------------------------------------");

}



void DiskMasterTool::ShowResults(void)
{
	//MessageToLog("> -------------------------------------");
	if(cntSlowings)
	{
		printString+="> Slowings: "+QString("%1").arg(cntSlowings)+"\n";
		MessageToLog("> Slowings: "+QString("%1").arg(cntSlowings));
	}
	if(cntBads)
	{
		printString+="> Bads: "+QString("%1").arg(cntBads)+"\n";
		MessageToLog("> Bads: "+QString("%1").arg(cntBads));
	}
	if(cntNotReady)
	{
		printString+="> Not ready: "+QString("%1").arg(cntNotReady)+"\n";
		MessageToLog("> Not ready: "+QString("%1").arg(cntNotReady));
	}

	//MessageToLog("> -------------------------------------");
}



int DiskMasterTool::OkNoStandardDialog(USB_HEADER& cmd, QMessageBox* msgBox, QString str)
{
	int ret;

	msgBox->setText(str);
	msgBox->hide();
	ret = msgBox->exec();
	
	switch (ret) 
	{
	case QMessageBox::Ok:
		cmd.code = USB_REQ_OK;
		//MessageToLog(">start operation canceled");
		break;
	case QMessageBox::No:
		cmd.code = USB_REQ_CANCEL;
		break;
	case QMessageBox::Cancel:
		cmd.code = USB_REQ_DISCARD;
		break;
	default:
	   // should never be reached
	   break;
	};
	return cmd.code;
}


void DiskMasterTool::print(bool ok)
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::ScreenResolution);
    QPrintPreviewDialog dlg(&printer);
	
    PrintView view(fileString,printString);

	if(!nvramList.isEmpty())
	{
		printer.setOrientation(QPrinter::Landscape);
		view.table->setModel(nvramLog->model());
		view.listSizes = &nvramLogColumnSizes;
		view.rowCount = nvramLog->rowCount();
	}
	if(!defectList.isEmpty())
	{
		printer.setOrientation(QPrinter::Portrait);
		view.table->setModel(defectLog->model());
		view.listSizes = &defectLogColumnSizes;
		view.rowCount = defectLog->rowCount();
	}
	view.setTableColumnSizes();
	view.table->resizeRowsToContents(); 

	connect(&dlg, SIGNAL(paintRequested(QPrinter*)),&view, SLOT(print(QPrinter*)));

	dlg.showMaximized();
    dlg.exec();
#endif
}
//#include "DiskMasterTool.moc"