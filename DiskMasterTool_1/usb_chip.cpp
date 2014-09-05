#include "usb_chip.h"
#include "common.h"


QList<QByteArray*> listOutputBuffers;
QList<QByteArray*> listRecieveBuffers;
QList<QByteArray*> listEmptyBuffers;
QList<QByteArray*> listSendBuffers;

QWaitCondition outpBufNotEmty;
QWaitCondition isRecieveBufEmty;
QWaitCondition isSendBufEmty;
QMutex outpMutex;



enum ChipEvent
{
	ChipError,
	ChipConnected,
	ChipDisconnected,
	ChipReadRequest,
	ChipChangeModemStatus
};

//===============================================================================================================
// ChipFT245R
//===============================================================================================================

ChipFT245R::ChipFT245R(ULONG chipID)
{
	ftChipID = chipID;
	recieveThread = new RecieveThread(this);
	outputThread = new OutputThread(this);
	
//	connect(this,SIGNAL(postRequest(PVOID* ,unsigned long long)),this,SLOT(startRecieveUsb(PVOID*,unsigned long long)));

}
ChipFT245R::ChipFT245R(FT_DEVICE_LIST_INFO_NODE* pInfo, ULONG chipID)
//	: pOwner(pOwner)
{
	memcpy(&ftInfo, pInfo, sizeof(FT_DEVICE_LIST_INFO_NODE));
	ftChipID = chipID;
	isClosed=TRUE;
	recieveThread = new RecieveThread(this);
	outputThread = new OutputThread(this);
	
//	connect(this,SIGNAL(postRequest(PVOID* ,unsigned long long)),this,SLOT(startRecieveUsb(PVOID*,unsigned long long)));
}

ChipFT245R::~ChipFT245R()
{
	close();
}

int ChipFT245R::open(bool only_one_device)
{
	if (ftInfo.ftHandle && isClosed)
	{
		if(only_one_device) return true;
		//if (FT_SUCCESS(FT_OpenEx(pDevInfo[nIndex].SerialNumber, FT_OPEN_BY_SERIAL_NUMBER, &pDevInfo[nIndex].ftHandle)))
		if (FT_SUCCESS(FT_OpenEx(ftInfo.SerialNumber, FT_OPEN_BY_SERIAL_NUMBER, &ftInfo.ftHandle)))
		{
			isClosed=FALSE;
			/*recieveThr.pChipInfo=sendThr.pChipInfo=outputThr.pChipInfo=&ftInfo;
			recieveThr.pChipID=sendThr.pChipID=outputThr.pChipID=&ftChipID;
			recieveThr.start();
			outputThr.start();*/
			eventRead.ResetEvent();
			eventShutdown.ResetEvent();
			start();
			//if(!recieveThread->isRunning())
			recieveThread->start();
			outputThread->start();
			//run();

		}
		else
			return FALSE;
	}
	else
		return FALSE;

	return TRUE;
}

void ChipFT245R::startRecieveUsb(PVOID* pChip, unsigned long long nData)
{
	if(!recieveThread->isRunning())
		recieveThread->start();
}

void ChipFT245R::close()
{
	if (ftInfo.ftHandle)
	{
		//mutexShutdown.unlock();
	//	WaitThreadShutdown();
		isClosed=TRUE;
		recieveThread->quit();
		outputThread->quit();
		eventShutdown.SetEvent();
		//memset(this->UsbHeader,0x00,4);
	//	quit();
		//wait(1000);
		FT_Close(ftInfo.ftHandle);
		//ftInfo.ftHandle = NULL;
	}
}


void ChipFT245R::WriteHeader(USB_HEADER header)
{
	unsigned int ret_bytes=0;
	unsigned int cnt_bytes=0;
	ret_bytes = sizeof(USB_HEADER);
	do
	{
		if(!FT_Write(ftInfo.ftHandle,&header,sizeof(USB_HEADER),reinterpret_cast<LPDWORD>(&ret_bytes)))	
		{
			cnt_bytes+=ret_bytes;
		}
	} while(cnt_bytes!=sizeof(USB_HEADER));
}


int SendThread::run(FT_DEVICE_LIST_INFO_NODE*	pChipInfo)
{
	
	return 0;
}


void ChipFT245R::run(void)
{
	QByteArray*	buf;
	
	HANDLE	hEvent[2] = {eventShutdown.GetEvent(),eventRead.GetEvent()};
	DWORD	nEventMask;
	DWORD	nBytesRx;
	DWORD	nBytesTx;
	DWORD	nModemStatus;
	DWORD	ret;

	if (FT_OK != FT_SetEventNotification(ftInfo.ftHandle,
		FT_EVENT_RXCHAR|/*FT_EVENT_TXCHAR|*/FT_EVENT_MODEM_STATUS,hEvent[1]))
	{
	//	if (waitShutdown.wait(&mutexShutdown)) return;
		return;
	}
	//eventRead.SetEvent();
	//mutexShutdown.lock();
	while (true)
	{
		if (::WaitForMultipleObjects(2, hEvent, FALSE, INFINITE) == WAIT_OBJECT_0) break;
		if (FT_OK != FT_GetStatus(ftInfo.ftHandle, &nBytesRx, &nBytesTx, &nEventMask)) continue;
		if ((nEventMask & FT_EVENT_RXCHAR) && nBytesRx)
		{
			mutexReadUsb.lock();
			arriveCounter = nBytesRx;
			waitRecieveUsb.wakeAll();
			mutexReadUsb.unlock();
			//bufVector.append(buf); 
		
			//emit postRequest((PVOID*)this,nBytesRx);
			//pOwner->iocp.PostStatus((ULONG_PTR)pChip, ChipReadRequest, reinterpret_cast<OVERLAPPED*>(nBytesRx));
			//m_pOwner->PostRequest(this, ChipReadRequest, nBytesRx);
		}
		if ((nEventMask & FT_EVENT_MODEM_STATUS) && (FT_OK == FT_GetModemStatus(ftInfo.ftHandle, &nModemStatus)))
		{
			//emit PostRequest(this, ChipChangeModemStatus, nModemStatus);
			//pOwner->iocp.PostStatus((ULONG_PTR)pChip, ChipChangeModemStatus, reinterpret_cast<OVERLAPPED*>(nModemStatus));
		}
		Sleep(1);
	}

	return;
}


RecieveThread::RecieveThread(QObject * parent = 0 )
    : QThread(parent)
{
	pChip = (ChipFT245R*)parent;
}


RecieveThread::~RecieveThread()
{

}


void RecieveThread::run()//*PVOID* pOwner, unsigned long long nData
{
	//ChipFT245R* pChip=(ChipFT245R*)pOwner;
	FT_HANDLE ftHandle=pChip->ftInfo.ftHandle;
	FT_STATUS ftStatus;
	QByteArray* buf;
	char* str;
	unsigned int ret=0;
	quint32 localCounter=0;
	//unsigned int sizeof(USB_HEADER)=0;

	while(true)
	{
		pChip->mutexReadUsb.lock();
		if(pChip->waitRecieveUsb.wait(&pChip->mutexReadUsb))
		{
			pChip->mutexReadUsb.unlock();
			
			localCounter = ret = 0;
			str = new char[pChip->arriveCounter];
			buf = new QByteArray;
			
			do
			{
				//qDebug() << "Header Size: " << ret_bytes;
				//qDebug() << "cnt_bytes: " << cnt_bytes;

				if(FT_SUCCESS(FT_Read(ftHandle,str+localCounter,pChip->arriveCounter,reinterpret_cast<LPDWORD>(&ret))))	
					localCounter+=ret;
			} while(localCounter!=pChip->arriveCounter);
			qDebug() << " --------- pChip->arriveCounter: " << pChip->arriveCounter;
			buf->append(str,pChip->arriveCounter);
			pChip->dataQueue.enqueue(buf);
			pChip->waitEnqueueData.wakeAll();
			//delete buf;
			

		}
		else
		{
			/*if(pChip->waitRecieveUsb.wait(&pChip->mutexShutdownRecieveUsb))
			{*/
		}
	}
}

OutputThread::OutputThread(QObject * parent = 0 )
    : QThread(parent)
{
	pChip = (ChipFT245R*)parent;
}


OutputThread::~OutputThread()
{

}

#define LENGTH_SIZE 2	// двухбайтоый счетчик данных



void OutputThread::run()//*PVOID* pOwner, unsigned long long nData
{
	FT_HANDLE ftHandle=pChip->ftInfo.ftHandle;
	QByteArray buf1;
	QByteArray* buf;
	QByteArray* temp_buf=0;
	bool isParticularBuffer=false;
	quint16 buf_size=0;
	quint16 offset=0;
	quint16 dataSize=0;
	char* data_ptr;
	while(true)
	{
		pChip->dataQueueNotEmpty.lock();
		if(pChip->waitEnqueueData.wait(&pChip->dataQueueNotEmpty))
		{
			pChip->dataQueueNotEmpty.unlock();
			do
			{
				buf=pChip->dataQueue.head();
			
				if(isParticularBuffer)
				{
					// если был остаток от прошлых данных
				
//					offset = dataSize-(buf_size-offset)+1;
//					temp_buf->append(buf->data(),offset);
					temp_buf->append(*buf);
					buf_size = temp_buf->size();
					data_ptr = temp_buf->data();
					//emit updateBufList(temp_buf->data()+2,dataSize); 
					//delete temp_buf;
				}
				else
				{
					offset=0;
					buf_size = buf->size();
					data_ptr = buf->data();	
					
					*((quint8*)&dataSize+1) = *(data_ptr+offset+1);
					*((quint8*)&dataSize+0) = *(data_ptr+offset+0);
				}

				do
				{				
				
					// проверяем поместился ли в данный буфер
					// LENGTH_SIZE-байтовый размер данных
					if((buf_size-offset)>LENGTH_SIZE)
					{
						qDebug() << " --------- dataSize: " << dataSize << "------";
						qDebug() << " --------- buf_size: " << buf_size << "------";
						qDebug() << " --------- offset: " << offset << "------";

						// проверяем помещаются ли данные целиком в данный буфер
						if((dataSize+offset)<=(buf_size-LENGTH_SIZE))
						{

							qDebug() << " --------- emit buffer: " << dataSize << "------";
							TraceBuf(data_ptr+offset+LENGTH_SIZE,dataSize);
							qDebug() << " -----------------------------------------------";

							emit updateBufList(data_ptr+offset+LENGTH_SIZE,dataSize); 
							offset+=(dataSize+LENGTH_SIZE);
							if(offset==buf_size)
							{
								isParticularBuffer=false;
								pChip->dataQueue.dequeue();
								break;
							}
						}
						else
						{
alloc_temp_buf:
							// если данные полностью не умещаются, то копируем кусок данных в новый буфер
							// и ждем прибытия новой посылки по USB
							//if(offset)
							{
								// промежуточный буфер для хранения остатка данных 
								char* temp = new char[buf_size-offset];
								memcpy(temp,data_ptr+offset,buf_size-offset);
								if(temp_buf)
									delete temp_buf;
								// если не первая посылка, то выделить новый буфер
								temp_buf = new QByteArray(temp,buf_size-offset);
								qDebug() << " --------- new buffer: " << buf_size-offset << "------";
								TraceBuf(temp,buf_size-offset);
								offset=0;//????
								isParticularBuffer=true;
								pChip->dataQueue.dequeue();
							}
							break;
						}
						
						// вычисляем новый размер, если в данном буфере находится несколько записей
						*((quint8*)&dataSize+1) = *(data_ptr+offset+1);
						*((quint8*)&dataSize+0) = *(data_ptr+offset+0);

					}
					else	// check LENGTH_SIZE
					{
						goto alloc_temp_buf;
					}
				} while(1);

			// выполнять по список буферов не пустой
			} while(!(pChip->dataQueue.isEmpty()));



		}
	}
}



//===============================================================================================================
// FtdiListUpdateThread
//===============================================================================================================

QUpdateDeviceList::QUpdateDeviceList()
{
	isOpenedDevice = false;
}


void QUpdateDeviceList::FirstStart(int nType, GUID guidDevice, QString strDeviceName)
{
	start();
}


void QUpdateDeviceList::updateDeviceTree(int nType, GUID guidDevice, QString dbcc_name)
{
	FT_HANDLE ftHandle;
	FT_DEVICE ftDevice;
	FT_STATUS ftStatus;
	DWORD deviceID;
	char SerialNumber[16];
	char Description[64];

	unsigned long ChipID=0;
//	QString serial = dbcc_name.mid(26, 7);  
	QByteArray serial = (dbcc_name.mid(26, 7)).toLocal8Bit();
	if(nType == (0x0F & DBT_DEVICEARRIVAL))
	{
		if(FT_SUCCESS(FT_OpenEx(serial.data(), FT_OPEN_BY_SERIAL_NUMBER, &ftHandle)))
		{
			if (FTID_GetChipIDFromHandle(ftHandle, &ChipID) == FTID_SUCCESS)
			{
				if(FT_SUCCESS(FT_GetDeviceInfo(ftHandle,&ftDevice,&deviceID,SerialNumber,Description,NULL)))
				{
					ChipFT245R* pChip = new ChipFT245R(ChipID);
					FT_Close(ftHandle);
				
					memcpy(pChip->ftInfo.SerialNumber,SerialNumber,16);
					memcpy(pChip->ftInfo.Description,Description,64);
					emit changeDevice(nType,pChip,ChipID,serial);
					qDebug() << " >>>>>>> Add new chip to tree:" << pChip->ftChipID << pChip->ftInfo.ID;
				}
			}
			else
			{
				emit changeDevice(nType,0,0,serial);
				FT_Close(ftHandle);
			}							
		}
		else
		{
				emit changeDevice(nType,0,0,serial);
				FT_Close(ftHandle);
		}
	}
	else
	{
		if(nType == (0x0F & DBT_DEVICEREMOVECOMPLETE))
		{
			emit changeDevice(nType,0,ChipID,serial);
		}
	}
}


void QUpdateDeviceList::run()
{
	FT_DEVICE_LIST_INFO_NODE*	pDevInfo;
	ChipFT245R*					pChip;
	QStringList					lstCurrentDevices;
	QString						strSerial;
	unsigned long				nChipID;
	DWORD						nNumDevices;
	DWORD						nNumProccessed;
	
	lstCurrentDevices.clear();
	if(!isOpenedDevice)
	{
		emit removeOpenedDevice();
	}
		
		if (FT_SUCCESS(FT_CreateDeviceInfoList(&nNumDevices)) && nNumDevices)
		{

				pDevInfo = new FT_DEVICE_LIST_INFO_NODE[nNumDevices * sizeof(FT_DEVICE_LIST_INFO_NODE)];
				nNumProccessed = 0;
				if (FT_SUCCESS(FT_GetDeviceInfoList(pDevInfo, &nNumDevices)))
				{
					for (DWORD nIndex = 0; nIndex < nNumDevices; nIndex++)
					{
						// устройство присутствует, но не отдает VID/PID(занято или еще энумерируется)
						if (pDevInfo[nIndex].ID != VID_PID_NUMBER) 
						{
							qDebug() << " >>>>>>> Add UNKNOWN chip to tree:" + pDevInfo[nIndex].ID;
							emit changeDevice((0x00FF & DBT_DEVICEARRIVAL),(ChipFT245R*)NULL,NULL,0);
							continue;
						}
						nNumProccessed++;
						strSerial = QString(pDevInfo[nIndex].SerialNumber);
						//if (!strSerial.contains(m_strSignature)) continue;
						lstCurrentDevices.append(strSerial);
						if (!(pDevInfo[nIndex].Flags & BIT_OPEN_PORT))
						{
							/*foreach(pChip,deviceModel.m_list)
							{
								if(pChip->ftInfo.SerialNumber==strSerial)
										continue;

							}*/
							//if (listDevices[.find(pChip)!=listDevices.end() || listDevices.empty())
							{
								if (FT_SUCCESS(FT_OpenEx(pDevInfo[nIndex].SerialNumber, FT_OPEN_BY_SERIAL_NUMBER, &pDevInfo[nIndex].ftHandle)))
								{
									
									if (FTID_GetChipIDFromHandle(pDevInfo[nIndex].ftHandle, &nChipID) == FTID_SUCCESS)
									{
										m_bChipPresence=false;
										pChip = new ChipFT245R(&pDevInfo[nIndex], nChipID);
										FT_Close(pDevInfo[nIndex].ftHandle);
										emit changeDevice((0x00FF & DBT_DEVICEARRIVAL),pChip,nChipID,0);
										qDebug() << " >>>>>>> Add new chip to tree:" << pChip->ftChipID << pChip->ftInfo.ID;
									}
									else
									{
										FT_Close(pDevInfo[nIndex].ftHandle);
									}
									
								}
							}
						}
					}
				}
				delete pDevInfo;

			//if(owner->numDevices < nNumDevices)	// if arrived device
			//{
			//}
		}


	if(!nNumDevices)
	{
		isOpenedDevice = false;
		emit removeOpenedDevice();
	}
	msleep(1);
	
	//} while (!chipNotIdentify.wait(&mutexShutDown,1000) && nNumDevices && (nNumProccessed != nNumDevices));
	
	//mutexShutDown.unlock();
	/*
	// close disconnected devices
	for (POSITION pos = connectedChips.GetStartPosition(); pos != NULL; )
	{
		connectedChips.GetNextAssoc(pos, strSerial, (void*&)pChip);
		if (lstCurrentDevices.Find(strSerial) == NULL) CloseChip(pChip);
	}
	*/
}