#ifndef DiskMasterTool_H
#define DiskMasterTool_H

#include <QDialog>
#include "ui_DiskMasterTool.h"
#include <QString>
#include <QIcon>
#include <windows.h>
#include "QNotificatorPnP.h"
#include "usb_chip.h"
#include "faderwidget.h"
#include "verifywidget.h"
#include "common.h"
#include "disk.h"
#include "printview.h"

#include <QTableWidgetItem>
#include <QTreeWidget>

#pragma pack(1)

typedef struct _NVRAM_LOG_ITEM
{
	unsigned char CurrentProcess;		//1
	unsigned char CurrentSubProcess;	//1
	unsigned char EndProcessCode;		//1
	quint8 SourceModel[16];				//16
	quint8 SourceSerial[20];			//20
	quint8 DestinationModel[16];		//16
	quint8 DestinationSerial[20];		//20
	unsigned long long DoningLBA;		//8
	unsigned long long MaxLBA;			//8
	quint64 counterBads;				//8
	quint64 counterSofts;				//8
	quint64 counterNrdy1;				//8
	quint64 counterNrdy2;				//8
	//QTime timeElaps;
	//QTime timeColaps;
	//QTime totalTime;

	unsigned char timeElaps[12];		//12
	unsigned char timeColaps[12];		//12
	unsigned long totalTime;			//4
	unsigned long timeAverage;			//4
	unsigned long timeMax;				//4

} NVRAM_LOG_ITEM,*PNVRAM_LOG_ITEM;


#define newButton mainButtons[0]
#define openButton mainButtons[1]
#define saveButton mainButtons[2]
#define printButton mainButtons[3]
#define refreshButton mainButtons[4]
#define downloadButton mainButtons[5]
#define clearButton mainButtons[6]



//#define resumeButton registrationButtons[0]
#define runButton registrationButtons[0]
#define pauseButton registrationButtons[1]
#define stopButton registrationButtons[2]
//#define errorButton registrationButtons[3]
//#define warningButton registrationButtons[4]




enum
{
	ID_DESTINATION_SERIAL,
    ID_DESTINATION_MODEL,      
    ID_CURR_PROCESS,    
    ID_CURR_SUB_PROCESS,   
    ID_CURR_LBA,  
	ID_MAX_LBA,
    ID_CNT_BLOCKS,      
    ID_TIME_ELAPS,      
    ID_TIME_COLAPS,     
    ID_TOTAL_TIME,

    ID_COUNTER_BADS, 
    ID_COUNTER_SOFTS,
	ID_COUNTER_NRDY1, 
    ID_COUNTER_NRDY2,
    ID_TIME_AVERAGE, 
    ID_TIME_MAX,   

    ID_SOURCE_SERIAL,
    ID_SOURCE_MODEL, 

    ID_SIGNATURE1=0x20, 
    ID_SIGNATURE2, 
    ID_SIGNATURE3, 
    ID_SIGNATURE4, 
    ID_SIGNATURE5, 
    ID_SIGNATURE6, 
    ID_SIGNATURE7, 
    ID_SIGNATURE8, 
    ID_SIGNATURE9, 
    ID_SIGNATURE10,
    ID_SIGNATURE11,
    ID_SIGNATURE12,
    ID_SIGNATURE13,
    ID_SIGNATURE14,
    ID_SIGNATURE15,
    ID_SIGNATURE16,

    ID_ORDER_CODE,
	ID_END_PROCESS_CODE,
	ID_END_OF_RECORD
};

enum ControlStates
{
	OnAllDevicesRemove,
	OnUsbRequest
};

#define ID_COUNTER_SLOWS	ID_COUNTER_SOFTS

#define PREPARE_HEADER(_length,_code,_sub_code) \
			pFtdiChip->UsbHeader.length = _length; \
			pFtdiChip->UsbHeader.code = _code; \
			pFtdiChip->UsbHeader.sub_code = _sub_code; \


enum ProcessSubCodes
{
	MODE_ERASE_0x00=0x01,
	MODE_ERASE_0xFF,
	MODE_ERASE_RAND
};

enum EndProcessCodes
{
	HDD1_NOT_READY,
	HDD2_NOT_READY
};


/*

#define	END_OK		0x00
#define	END_ERROR	0xFF




*/

enum IndexOfTable
{
	ITEM_CURR_PROCESS=0,
	ITEM_DST_SERIAL_MODEL,
	ITEM_SRC_SERIAL_MODEL,
	ITEM_DONE_LBA,
	ITEM_TIME_ELAPS_COLAPS,	
	ITEM_COUNTER_BADS,
	ITEM_COUNTER_SOFTS,
	ITEM_COUNTER_NRDY,
	ITEM_TIME_AVERAGE,
	ITEM_TIME_MAX,
	ITEM_TOTAL_TIME
};


typedef struct _DEFECT_RECORD
{
	union
	{
		struct
		{
			quint8 id;
			quint8 code;
			quint8 lba[6];
			quint32 time;
		};
		quint8 buf[12];
	};
} DEFECT_RECORD, *PDEFECT_RECORD;


typedef struct _PC3000_DEFECT_RECORD
{
	quint16 blank;
	quint32 start_lba;
	quint32 end_lba;
	quint32 record_num;
	quint32 cnt_defects;
	
} PC3000_DEFECT_RECORD, *PPC3000_DEFECT_RECORD;


enum
{
	ARRIVE_NEW_DEFECT,
	TOGGLE_ERRORS,
	TOGGLE_SLOWINGS
};

	// usb request
    #define	USB_REQ_NVRAM_READ_LOG           0x01
    #define USB_REQ_NVRAM_READ_STRING        0x02
    #define USB_REQ_NVRAM_WRITE_LOG_ITEM     0x03
    #define USB_REQ_NVRAM_WRITE_STRING       0x04
    #define USB_REQ_NVRAM_CLEAR_LOG          0x05
	//////////////////////////////////////////////
    #define USB_REQ_START_REGISTRATION       0x06
		// [sub_code - hi]
		// curr mode: COPY/ERASE/VERIFY
		// [sub_code - lo]
		#define	LO_REGISTRATION_W_PROCESS  	 0x00
		#define	LO_ONLY_REGISTRATION 		 0x01
		
		#define	LO_NEW_TASK_UNLOCK	 	0x02
		#define	LO_NEW_TASK_NO_UNLOCK 	0x03
		#define	LO_LAST_MODE			0x04
		#define	LO_NOT_LAST_MODE		0x05
		#define	LO_RESUME_PROCESS		0x06
	/////////////////////////////////////////////
	#define    USB_REQ_STOP_REGISTRATION     0x07
		// [sub_code - hi]
		#define	HI_REGISTRATION_W_PROCESS	 0x00
		#define	HI_REGISTRATION 		0x01
		// [sub_code - lo]
		#define LO_BREAK_PROCESS      	0x00
		#define LO_STOP_PROCESS			0x01
		#define LO_SAVE_NVRAM     		0x02
		#define LO_NOT_SAVE_NVRAM 		0x03
	 ///////////////////////////////////////
    #define USB_REQ_TRACE_ENABLE        0x08
		// [sub_code]
		#define ONLY_ENABLE			   	0x00
		#define ENABLE_AND_SAVE    		0x01
		#define ONLY_DISABLE	 		0x02
		#define DISABLE_AND_SAVE 		0x03

	#define	USB_REQ_OK	            	0x09
	#define USB_REQ_CANCEL				0x0A
	#define USB_REQ_DISCARD				0x0B
	#define USB_REQ_CONTINUE			0x0C
	#define USB_REQ_BACK	            0x0D

    #define USB_REQ_SET_ORDER_CODE      0x10
    #define USB_REQ_SET_CODE_SIGNATURE  0x11
    #define USB_REQ_ACCEPT              0x12
    #define USB_REQ_DECLINE             0x13
    
        // sub code request
        #define WRITE_NVRAM_LOG_ITEM    0x41


	// usb messages
	#define USB_MSG_OK         			0x80	

    #define USB_MSG_NVRAM_READ_LOG		0x81
		#define SUB_NVRAM_LOG_EMPTY		0x01
		#define SUB_NVRAM_ERROR			0x02

    #define USB_MSG_NVRAM_READ_STRING   0x82
    #define USB_MSG_NVRAM_WRITE_STRING	0x84
	//;	#define	USB_MSG_CLEAR_NVRAM_LOG		 0x85

    #define USB_MSG_START_REGISTRATION	0x86
		// [sub message]
		#define SUB_WAIT_NEW_TASK		0x01
		#define SUB_WAIT_LAST_MODE		0x02
		#define SUB_WAIT_UNLOCK_HPA		0x03	
		#define	SUB_START_OK			0x04
		#define SUB_ALREADY_STARTED		0x05
		#define	SUB_HDD2_LOWER_HDD1		0x06
		#define	SUB_FINISH_IDENTIFY		0x07
		#define SUB_ARE_YOU_SURE_UNLOCK 0x08
		// отсылать которкое сообщения или с сектором IDENTIFY
		#define 	WITH_IDENTIFY		1
		#define 	WITHOUT_IDENTIFY	0

	#define    USB_MSG_STOP_REGISTRATION	0x87
		#define	SUB_BREAK_PROCESS			0x01
		//SUB_WAIT_UNLOCK_HPA		= 0x02			!!!!!!
		#define	SUB_WAIT_SAVE_NVRAM_LOG		0x03
		#define	SUB_STOP_PROCESS  			0x04


	#define    USB_MSG_FINISHED	  			0x88
		#define	SUB_FINISH_OK				0x00
    	#define	SUB_FINISH_ERR				0x01
		#define	SUB_FINISH_ERR_RELOCK_ERR	0x02
		#define	SUB_FINISH_OK_RELOCK_ERR	0x03

//	#define    USB_MSG_TRACE_ENABLE			0x87
    #define    USB_MSG_SET_ORDER_CODE		0x8B
    #define    USB_MSG_SET_CODE_SIGNATURE	0x8C

	#define	USB_MSG_DEFECT					0x8D
		#define    ID_SLOW_LBA        0x01
    	#define    ID_ERROR_LBA       0x02
    	#define    ID_NOT_READY_LBA   0x03

	#define    USB_MSG_CURRENT_LBA			0x8E

	#define    USB_MSG_NVRAM_FAIL			0xF0
    #define    USB_MSG_NVRAM_LOG_DISABLED	0xF2
	#define    USB_MSG_NVRAM_OVERFLOW		0xF3
	#define    USB_MSG_ERR        			0xFE
		#define	SUB_HDD1_NOT_READY			0x01
		#define	SUB_HDD2_NOT_READY			0x02
	#define    USB_MSG_UNKNOWN_REQUEST 		0xFF


	// numbers of menu items		
	#define	MODE_IDENTIFY 		0x01
	#define	MODE_INFO			0x02
	#define	MODE_COPY			0x03
	#define	MODE_ERASE			0x04
	#define	MODE_TEST_VERIFY	0x05
	#define	MODE_TEST_READ		0x06
    
    #define	MODE_WRITE_COMPARE	0x07
    //    #define    STEP_WRITE  0x01
    //    #define	STEP_READ   0x02
    #define	MODE_HPA_DETECT		0x08
    #define	MODE_SETTINGS		0x09

   	#define	MODE_USB_ERASE0		0x0D
	#define	MODE_USB_ERASE1		0x0E
    #define	MODE_USB_ERASE_RAND 0x0F



#define SET_HI_THETRADE(byte,value) byte=value; byte<<=4;
#define GET_HI_THETRADE(byte) byte>>=4;


class MultiRowTableWidgetItem : public QTableWidgetItem
{
	void paintEvent(QPaintEvent* event);
};

class MultiLineTableWidget : public QTableWidget
{
	void paintEvent(QPaintEvent* event);
};

class MyTreeWidget : public QTreeWidget
{
public:
	MyTreeWidget( QWidget * parent = 0 )
		: QTreeWidget(parent)
	{

	}

	QTreeWidgetItem * MyTreeWidget::itmFromIndex ( const QModelIndex & index )
	{
		QTreeWidgetItem * item;
		item = itemFromIndex(index);
		return item;
	}
};

#include <QMainWindow>
#include <QSplitter>
#include <QTextBrowser>
#include <QGroupBox>
#include <QListWidgetItem>

//////////////////////////////////////////////////////////////////////////////
class DiskMasterTool : public QMainWindow
{
	Q_OBJECT
	
	typedef void (DiskMasterTool::*ptrMainButtonProc)(bool); // ;

public:
	DiskMasterTool(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~DiskMasterTool();

	int numDevices;				// количество присоединенных USB-устройств
	bool isOnlyRegistration;
	bool isRunningProcess;
	bool isBreakProcess;
	bool isStopProcess;
	bool isAlreadyIdentify;

	quint8 currentProcess;

	quint64 cntSlowings;
	quint64 cntBads;
	quint64 cntNotReady;
	QList<NVRAM_LOG_ITEM> nvramList;
	QList<DEFECT_RECORD> defectList;
	QList<PC3000_DEFECT_RECORD> pc3000List;

	QToolBar* mainToolBar;	
	QToolBar* nvramToolBar;	
	QToolBar* registrationToolBar;	
	QString strSerial;
	QString strModel;

	ChipFT245R*	pFtdiChip;
	
	QIcon errorIco;
	QIcon warningIco;
	QIcon okIco;
	QString printString;
	QString fileString;
	QFont fontDeviceTree;
	QList<int> nvramLogColumnSizes;
	QList<int> defectLogColumnSizes;

	QList<ResizebleToolButton*> mainButtons;
	QList<ResizebleToolButton*> registrationButtons;
	QList<QPointer<FaderWidget>> faderWidget;
	
	QModelIndexList indexes;

	QAction* downloadButtonAct;
	QAction* actPrint;
	QAction* actPreview;
	QMenu* printPopupMenu;
	
	//QPrinter* printer;

	QAction* actionErase0;
	QAction* actionErase1;
	QAction* actionEraseRand;
	QAction* actionVerify;
	QAction* actionTestRead;
	QAction* actionTestWriteCompare;
	QAction* actionCopy;
	QAction* actionTraceEnable;
	QAction* actionTraceDisable;
	QAction* actionOnlyRegistration;
	
	QMenu* startRegistrationPopup;	

	QVBoxLayout* mainLayout;
	QSplitter* headerSplitter;
	MyTreeWidget* deviceTree;
	QTextBrowser* processTextLog;
	MultiLineTableWidget* nvramLog;
	QTableWidget* defectLog;
	//QListWidget* listNvramLogs;

	QHBoxLayout* mainButtonLayout;
	QGroupBox* registrationButtonBox;
	QHBoxLayout* registrationButtonLayout;
	QGroupBox* mainButtonBox;
	
	QList<ptrMainButtonProc> mainButtonProc;
	QSplitter* mainSplitter;
	QList<QTableWidgetItem*> matchList;
	QGridLayout* topLeftLayout;
	QGroupBox* mainLeftGroup;
	QGridLayout* menuButtonLayout;

	Disk disk1Object;
	Disk disk2Object;
	//
	template <class T> void openFile(const QString& filename,QList<T>* list,char*& buf,char* buf_len=0/* NVRAM or DEFECT list */);
	template <class T> void saveFile(const QString& filename, const QList<T>& list,char* buf=0,char buf_len=0 );
	void printRowNVRAMLog(QStringList* nvram_str);
	void printRow(QPainter* painter, QStringList* str,int baseX, int* row_pos,int row_height);
	void exportPc3000List(const QString& filename, const QList<DEFECT_RECORD> & list/* DEFECT list */);
	void SaveRecordToList(char* nvramItemBuf,unsigned char lengthBuf);
	QStringList* SetModeString(QString* str,unsigned char mode,unsigned char sub_mode);
	int OkNoStandardDialog(USB_HEADER& cmd, QMessageBox* msgBox, QString str);
	void ShowDiskInfo(Disk& disk);
	void setNvramLogToolTips(void);

	void updateNvramLog(NVRAM_LOG_ITEM* nvram_item, int row);
	void updatePc3000Log(PC3000_DEFECT_RECORD* buf, quint8 flag=ARRIVE_NEW_DEFECT);
	void updateDefectLog(DEFECT_RECORD* buf, int row, quint8 flag=ARRIVE_NEW_DEFECT);
	
	void setDefectLogColumnSizes(QList<int>* listSizes);
	void setNvramLogColumnSizes(QList<int>* listSizes);

	void createMainButtons(void);
	void createRegistrationButtons(void);
	void MessageToLog(QString str);
	void ShowResults(void);
	void toggleDefectsFromTable(QString str);
	void runProcess(USB_HEADER cmdPkt);				
	
	void SendCommand(USB_HEADER header);

private:
		void updateControls(int state);

signals:
	void completeDownload(QListWidgetItem* current_item);

public slots:
	void sortColumn( int row, int column );
	void updateTree(int nType, ChipFT245R* pChip,unsigned long nChipID, QString serial);
	void openDev(QTreeWidgetItem* item, int column);
	void parseBufList(char* buf, quint16 len);
	//////////////////////////////////////////////////
	void newDocument(bool checked);
	void openDataFile(bool checked);
	void saveDataFile(bool checked);
	void refreshDeviceList(bool checked);			// [0] main button
	void downloadLog(bool checked);					// [2] 
	//void printLog();								// [4]
	void clearLog(bool checked);					// [1]
	//void startRegistration(bool checked);			// [5]
	//////////////////////////////////////////////////
	void resumeProcess(bool checked);				// [0]
	//[1]
	void breakProcess(bool checked);				// [2]
	void stopProcess(bool checked);					// [3]
	void toggleWarning(bool checked);				// [4]
	void toggleError(bool checked);					// [5]
	//////////////////////////////////////////////////
	void updatePauseButton(void);
	void switchTask(bool checked);
	void toggleOnlyRegFlag(bool changed);				
	void addNvramLogRow(char* buf,unsigned short len);	
	void print(bool checked);
	void updateRemoveOpenedDevice(void);
	//int  printPreview(void);
	//void previewProc(QPrinter* printer);

private:
	Ui::DiskMasterDialog ui;
	QNotificatorPnP PnpNotificator;
	QUpdateDeviceList DeviceListThread;

	void AddItemToDeviceTree(void);
	void fadeInWidget(HoveredButton** button_array,int num_buttons);
};


Q_DECLARE_METATYPE(NVRAM_LOG_ITEM*)
//Q_DECLARE_METATYPE(GUID)

#endif // DiskMasterTool_H
