#ifndef USB_CHIP_H
#define USB_CHIP_H

#include <QtCore>
#include <QtGui>
#include <QQueue>
#include "windows.h"
#include "FTD2XX.h"
#include "FTChipID.h"
#include "EventEx.h"

#pragma pack(1)

#define VID_PID_NUMBER			0x04036001
#define BIT_OPEN_PORT			0x00000001L

//class ChipFT245R;
enum
{
	STATE_READ_NVRAM_LOG,
	STATE_TEST_VERIFY
};
enum
{
	ID_BAD_DEFECT,
	ID_SOFT_DEFECT
};



typedef struct _USB_HEADER
{
	union
	{
		struct
		{
			union
			{
				quint16 length;
				quint8 length_buf[2];
			};
			quint8 code;
			quint8 sub_code[2];
		};
		unsigned char buf[5];
	};
	
} USB_HEADER,*PUSB_HEADER;



class ChipFT245R;
//===============================================================================================================
// Поток вывода в TextEdit
//===============================================================================================================
#include <QTextEdit>
class OutputThread : public QThread
{
	Q_OBJECT

public:
	OutputThread(QObject * parent);
	~OutputThread();

	ChipFT245R* pChip;
	FT_DEVICE_LIST_INFO_NODE*	pChipInfo;
	ULONG*						pChipID;
	QTextEdit*					pTextEdit;

protected:
	virtual void run(void/*PVOID* pOwner, unsigned long long nData*/);
signals:
	void updateBufList(char*,quint16 len);

	//void showBuffer(QTextEdit* pTextEdit,QList<QByteArray*>::iterator first_buf);

};

//===============================================================================================================
// Поток вывода в TextEdit
//===============================================================================================================
class RecieveThread : public QThread
{
	Q_OBJECT

public:
	RecieveThread(QObject * parent);
	~RecieveThread();

	ChipFT245R* pChip;
	FT_DEVICE_LIST_INFO_NODE* pChipInfo;
	ULONG* pChipID;
	//USB_HEADER UsbHeader;
protected:
	virtual void run(void/*PVOID* pOwner, unsigned long long nData*/);

signals:
	void defectDetected(void);
	void updateTableLogs(char* RecieveBuf,unsigned short length);

};

//===============================================================================================================
// Поток вывода в TextEdit
//===============================================================================================================
class SendThread : public QThread
{
public:	
	FT_DEVICE_LIST_INFO_NODE*	pChipInfo;
	ULONG*						pChipID;
	
	virtual int run(FT_DEVICE_LIST_INFO_NODE*	pChipInfo);
};


//////////////////////////////////////////////////////////////////////////////
class QUpdateDeviceList : public QThread
{
	Q_OBJECT

public:
	QUpdateDeviceList();

	//QWidget*	owner;
	PVOID		pOwner;
	QString		m_strSignature;
	BOOL		m_bChipPresence;
	BOOL		m_bOnlyConnectEvent;
	BOOL		isOpenedDevice;
	

//	QList<ChipFT245R*>	listDevices;
//	DeviceListModel		deviceModel;

	void run();	

signals:
	void changeDevice(int nType,ChipFT245R* pChip,unsigned long nChipID, QString serial);
	void removeOpenedDevice(void);
public slots:
	void FirstStart(int nType, GUID guidDevice, QString strDeviceName);//(QString strSignature, BOOL bOnlyConnectEvent);
	void updateDeviceTree(int nType, GUID guidDevice, QString dbcc_name);

};

//===============================================================================================================
// ChipFT245R
//===============================================================================================================
class ChipFT245R : public QThread
{
	Q_OBJECT
//	friend class CWrapperFT245R;
//	friend class CUpdateListThread;
public:
	ChipFT245R(ULONG chipID);
	ChipFT245R(FT_DEVICE_LIST_INFO_NODE* pInfo, ULONG chipID);
	~ChipFT245R();

	PVOID*						pOwner;
	FT_DEVICE_LIST_INFO_NODE	ftInfo;
	ULONG						ftChipID;
	QWaitCondition				waitShutdown;
	QWaitCondition				waitEnqueueData;
	QMutex						mutexShutdown;
	QMutex						dataQueueNotEmpty;
	QAutoResetEvent				eventRead;
	QAutoResetEvent				eventShutdown;
	QQueue<QByteArray*>			dataQueue;

	//USB_HEADER UsbHeader;
	RecieveThread* recieveThread;
	SendThread	sendThr;
	OutputThread* outputThread;
	
	QVector<QByteArray*> bufVector;
	QMutex mutexReadUsb;
	QWaitCondition waitRecieveUsb;
	QStringList defectList;
	

	quint16 arriveCounter;
	int logLength;
	char* pData;
	unsigned char* RecieveBuf;
	bool isHeader;
	qint8 state;

	int open(bool only_one_device);
	void close();
	void run();
	void WriteHeader(USB_HEADER header);

public slots:
	void startRecieveUsb(PVOID* pChip, unsigned long long nData);

signals:	
//	void postRequest(PVOID*	pOwner, unsigned long long nData);
	void defectDetected(void);
	

private:
	bool	isClosed;
};

Q_DECLARE_METATYPE(ChipFT245R*)


#endif