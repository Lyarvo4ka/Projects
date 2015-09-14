#include "StdAfx.h"
#include "TaskVerify.h"




CTaskVerify::CTaskVerify(void)
:m_bStop(false),
m_bFind(false),
lNotRandom(0),
lNotFull(0)
{

}


CTaskVerify::~CTaskVerify(void)
{
}


void CTaskVerify::CreateThreads()
{
	hThread = CreateThread(NULL,
						   0,
						   (LPTHREAD_START_ROUTINE )ThreadMainFunc,
						   this,
						   0,NULL);
	//WaitForSingleObject(hThread,INFINITE);
	//CloseHandle(hThread);

}

#define HDD_COUNT 2

DWORD WINAPI CTaskVerify::ThreadMainFunc(LPVOID lParam)
{
	PTASKVERIFY pData = (PTASKVERIFY)lParam;
	// set DATA

	for (size_t i = 0; i < HDD_COUNT; ++i)
	{
		READDATA * pReadDATA = new CReadDATA(pData->m_vecDiskDrives.at(i).getDiskDrive());
		pReadDATA->setRange(pData->m_VerifyRange);
		pReadDATA->setSelectionCount(pData->iCountSelection);


	//	// Critical section for Input DATA from HDD and write to Queue
	//	// and is not need to read Queue in Verify Thread
		pReadDATA->pAllowAccess = new CRITICAL_SECTION();
		InitializeCriticalSection(pReadDATA->pAllowAccess);

	//	// This Semaphors synchonize Threads HDDRead and Verify
		pReadDATA->hWhaitCheck = new HANDLE();
		*pReadDATA->hWhaitCheck = CreateSemaphore(NULL,0,1,NULL);
		pReadDATA->hWaitReaded = new HANDLE();
		*pReadDATA->hWaitReaded = CreateSemaphore(NULL,0,1,NULL);
		// This Semaphore is Send Command to Finish Thread
		pReadDATA->hFinishThread = new HANDLE();
		*pReadDATA->hFinishThread = CreateSemaphore(NULL,0,1,NULL);
		

		pData->m_vecReadHDDs.push_back(pReadDATA);
	}
	CStdioFile fileReportTxt;
	if (!fileReportTxt.Open(pData->strFileReport,CFile::modeWrite))
			AfxMessageBox(_T("Unable to open file"),MB_OK);

	pData->WirteTimeReport(&fileReportTxt,0);
	fileReportTxt.Close();
	if (pData->testNumbers.bRandomTest)
	{
		::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)NEW_STRING);
		::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_SETNULL_PROGRESS,0,0);
		pData->startRandomTest();
	}
	if (pData->testNumbers.bEasyTest && !pData->m_bStop )
	{
		if (pData->m_bFind && pData->testNumbers.isFirstMismatch)
		{}
		else
		{
		::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)NEW_STRING);
		::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_SETNULL_PROGRESS,0,0);
		for (size_t i = 0; i < HDD_COUNT; ++i)
		{
			ReleaseSemaphore(*pData->m_vecReadHDDs.at(i)->hWhaitCheck,0,NULL);
			ReleaseSemaphore(*pData->m_vecReadHDDs.at(i)->hWaitReaded,0,NULL);

		}

		pData->startFullTest(EASY_TEST);
		}
		
	}
	if (pData->testNumbers.bFullTest && !pData->m_bStop)
	{
		if (pData->m_bFind && pData->testNumbers.isFirstMismatch)
		{}
		else
		{
		::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)NEW_STRING);
		::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_SETNULL_PROGRESS,0,0);
		for (size_t i = 0; i < HDD_COUNT; ++i)
		{
			ReleaseSemaphore(*pData->m_vecReadHDDs.at(i)->hWhaitCheck,0,NULL);
			ReleaseSemaphore(*pData->m_vecReadHDDs.at(i)->hWaitReaded,0,NULL);

		}

		pData->startFullTest(FULLTEST);
		}
	
	}
	//pData->


	
	::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_FINISH,pData->lNotRandom,pData->lNotFull);
	return 0;
}

void CTaskVerify::setTestNumbers(TESTNUMBERS & _rTestNumbers)
{
	testNumbers = _rTestNumbers;
}

void CTaskVerify::setDisk(vector<CDiskDrive> &_vec)
{
	m_vecDiskDrives = _vec;
}




void CTaskVerify::startRandomTest()
{
	// Set RANDOM POSINITON

	::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)START_RANDOM);

	LONGLONG *lPOS = new LONGLONG[iCountSelection*HDD_ZONE];
	
	LONGLONG lHddZones = m_VerifyRange.lTo/HDD_ZONE;
	UINT iMax = (int)(lHddZones/RAND_MAX) ;
	LONGLONG longVal = 0, longTemp = 0;
// RANDOM
	UINT iCounter = 0;

	srand(time(0));
	if (iMax == 0)
	{
		for (UINT i = 0; i < iCountSelection*HDD_ZONE; ++i)
		{
			lPOS[i] = rand()%RAND_MAX + 1;
		}

	}
	else
	for (UINT j = 0; j < HDD_ZONE; ++j)
	{
	for (UINT i = 0; i < iCountSelection; ++i)
	{
		if (i % 2 == 0)
		{
			longTemp = rand()%(iMax / (rand()%5 +1 ) + 1);
			//if (j % 2 == 0)
			//	longVal = longTemp*(rand()%(iMax / (rand()%5 + 1)));
			//else
				longVal = longTemp*(rand()%iMax);
			longVal += j * lHddZones;
		}
		else
		{
			longTemp = rand()%iMax ;
			longVal = longTemp*(rand()%RAND_MAX);
			longVal += j * lHddZones;
		}

		if (longVal == 0)
		{
			--i;
			continue;
		}
		lPOS[iCounter] = longVal;
		++iCounter;
	}
	
	}

	CStdioFile fileReportTxt;
	if (!fileReportTxt.Open(strFileReport,CFile::modeWrite))
		if (!fileReportTxt.Open(strFileReport,CFile::modeWrite|CFile::modeCreate))
			AfxMessageBox(_T("Unable to open file"),MB_OK);
	fileReportTxt.SeekToEnd();

	CString strReport;

	strReport = _T("Starting Random check: \r\n");
	fileReportTxt.WriteString(strReport);

	for (size_t i = 0; i < HDD_COUNT; ++i)
	{
		m_vecReadHDDs.at(i)->setRandomPositions(lPOS);
		m_vecReadHDDs.at(i)->setSelectionCount(iCountSelection);
		m_vecReadHDDs.at(i)->CreateRandomThread();
	}

	bool bFind = false;
	m_bStop = false;

	BYTE *pByte1, *pByte2;

	LONGLONG lposLBA = 0;


	iCounter = 0;
	for (UINT iTest = 0 ; iTest < iCountSelection; ++iTest)
	{
	for (int iCount = 0; iCount < HDD_ZONE; ++iCount)
	{
		bFind = false;
		for (size_t i = 0; i < HDD_COUNT; ++i)
			WaitForSingleObject(*m_vecReadHDDs.at(i)->hWhaitCheck,INFINITE);


		for (size_t i = 0; i < HDD_COUNT; ++i)
		EnterCriticalSection(m_vecReadHDDs.at(i)->pAllowAccess);
//-----------------------------------------------------------------------------------------

		if ( m_vecReadHDDs.at(0)->isEmpty() && m_vecReadHDDs.at(1)->isEmpty() )
		{
			lposLBA = lPOS[iCounter];
			for (size_t j = 0; j < 255; ++j)
			{
				pByte1 = m_vecReadHDDs.at(0)->getBlock();
				pByte2 = m_vecReadHDDs.at(1)->getBlock();


				for (WORD wCount = 0; wCount < 512; ++wCount)
				{

					// !!!!!!!!!!!!!! FUNC CHECK
					if (pByte1[wCount] != pByte2[wCount])
					{
						strReport.Format(_T("HDD NOT EQUAL LBA # %I64d"),lposLBA);
						strReport += _T("\r\n");

						++lposLBA;

						fileReportTxt.WriteString(strReport);
						bFind = true;
						break;
					}
				}

				m_vecReadHDDs.at(0)->removeBlock();
				m_vecReadHDDs.at(1)->removeBlock();
				//if (bFind)
				//{
				//	m_vecReadHDDs.at(0)->ClearQueue();
				//	m_vecReadHDDs.at(1)->ClearQueue();
				//	break;
				//}
				// check
			}

		}

//-----------------------------------------------------------------------------------------
		for (size_t i = 0; i < HDD_COUNT; ++i)
			LeaveCriticalSection(m_vecReadHDDs.at(i)->pAllowAccess);	

		for (size_t i = 0; i < m_vecReadHDDs.size(); ++i)
			ReleaseSemaphore(*m_vecReadHDDs.at(i)->hWaitReaded,1,NULL);
		if (bFind)
		{
			++lNotRandom;
			if (!m_bFind)
			{
				::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_REPORT,0,0);
				m_bFind = true;
				
			}
		
			if (testNumbers.isFirstMismatch)
			{
				for (size_t i = 0; i < m_vecReadHDDs.size(); ++i)
					m_vecReadHDDs.at(i)->bFlagFINISH = true;				

				m_vecReadHDDs.at(0)->ClearQueue();
				m_vecReadHDDs.at(1)->ClearQueue();

				break;
			}
		}

		if (m_bStop)
		{
				for (size_t i = 0; i < m_vecReadHDDs.size(); ++i)
					m_vecReadHDDs.at(i)->bFlagFINISH = true;				

				m_vecReadHDDs.at(0)->ClearQueue();
				m_vecReadHDDs.at(1)->ClearQueue();

				break;
		
		}
		++iCounter;
	}
	::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_UPDATE_PROGRESS,0,0);
		if (m_bStop || (bFind && testNumbers.isFirstMismatch))
			break;




	}

	strReport = _T("Finish Random check: \r\n");
	fileReportTxt.WriteString(strReport);

	fileReportTxt.Close();
	// CLEAR All VERABLS;
	::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)FINISH_RANDOM);

	for (size_t i = 0; i < HDD_COUNT; ++i)
		WaitForSingleObject(*m_vecReadHDDs.at(i)->hFinishThread,INFINITE);

	delete lPOS;
	//for (size_t i = 0; i < HDD_COUNT; ++i)
	//{
	//		DeleteCriticalSection(m_vecReadHDDs.at(i)->pAllowAccess);	
	//		CloseHandle(*m_vecReadHDDs.at(i)->hWhaitCheck);
	//		CloseHandle(*m_vecReadHDDs.at(i)->hWaitReaded);
	//}



}

void CTaskVerify::startFullTest(TEST_TYPE byTestType)
{
	BYTE *pBYTE1,*pBYTE2;

	::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)NEW_STRING);

	CStdioFile fileReportTxt;
	if (!fileReportTxt.Open(strFileReport,CFile::modeWrite))
		if (!fileReportTxt.Open(strFileReport,CFile::modeWrite|CFile::modeCreate))
			AfxMessageBox(_T("Unable to open file"),MB_OK);
	fileReportTxt.SeekToEnd();

	CString strReport;


	switch (byTestType)
	{
	case FULLTEST:
		::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)START_FULL);
		strReport = _T("Starting FULL check: \r\n");
		break;
	case EASY_TEST:
		::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)START_STEP_FOLLOW);
		strReport = _T("Starting FOLLOW STEP check: \r\n");
		break;
	};

	fileReportTxt.WriteString(strReport);

	WORD wNotEqualCount = 0;

	int iCount = 0;


	// Creating Threads "HDD Read"
	for (size_t i = 0; i < HDD_COUNT; ++i)
	{
		m_vecReadHDDs.at(i)->setTestType(byTestType);
		m_vecReadHDDs.at(i)->CreateFullThread();
	}

	LONGLONG lNumLBA = 0;
	//LONGLONG lMaxCounter = m_VerifyRange.lTo;

	//lMaxCounter /= 512;


	LONGLONG lProgress = m_VerifyRange.lTo / iCountSelection;

	LONGLONG dwCheck = m_VerifyRange.lTo / iCountSelection;

	LONGLONG lStep = m_VerifyRange.lTo / iCountSelection - m_VerifyRange.lFrom;
	if ( lStep % 255 != 0)
		lStep = lStep - lStep%255;
	LONGLONG lMoveTo = lStep;
	size_t iQueueSize = 0;

	bool bFind = false;
	m_bStop = false;
	m_bFind = false;
	//queue<BYTE*> *pQueueRead1 = new queue<BYTE*>();
	//queue<BYTE*> *pQueueRead2 = new queue<BYTE*>();

	// !!!!!!!!!!!!!!!!!!!!!!!!!
	while (lNumLBA < m_VerifyRange.lTo)
	{
		for (size_t i = 0; i < HDD_COUNT; ++i)
			WaitForSingleObject(*m_vecReadHDDs.at(i)->hWhaitCheck,INFINITE);
		
		
		for (size_t i = 0; i < HDD_COUNT; ++i)
			EnterCriticalSection(m_vecReadHDDs.at(i)->pAllowAccess);

		if (m_vecReadHDDs.at(0)->isEmpty() && m_vecReadHDDs.at(1)->isEmpty())
		{
				iQueueSize = *m_vecReadHDDs.at(0)->getSize();
				if (iQueueSize > *m_vecReadHDDs.at(1)->getSize())
					iQueueSize = *m_vecReadHDDs.at(1)->getSize();


				//pQueueRead1 = &_vecReadDATA.at(0)->g
				for (size_t i = 0; i < iQueueSize; ++i)
				{
				pBYTE1 = m_vecReadHDDs.at(0)->getBlock();
				pBYTE2 = m_vecReadHDDs.at(1)->getBlock();

				++lNumLBA; 
				for (size_t i = 0; i < 512; ++i)
				{
					if (pBYTE1[i] != pBYTE2[i])
					{

						strReport.Format(_T("HDD NOT EQUAL LBA # %I64d\r\n"),lNumLBA);
						fileReportTxt.WriteString(strReport);
						bFind = true;
						break;
					}


				}
				if ( lProgress <= lNumLBA )
				{
					lProgress += dwCheck; // ZDVIG
					::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_UPDATE_PROGRESS,0,0);
				}
				m_vecReadHDDs.at(0)->removeBlock();
				m_vecReadHDDs.at(1)->removeBlock();
				}

			}
			LeaveCriticalSection(m_vecReadHDDs.at(0)->pAllowAccess);
			LeaveCriticalSection(m_vecReadHDDs.at(1)->pAllowAccess);

			for (size_t i = 0; i < m_vecReadHDDs.size(); ++i)
				ReleaseSemaphore(*m_vecReadHDDs.at(i)->hWaitReaded,1,NULL);

			
		if (bFind)
		{
			++lNotFull;
			if (!m_bFind)
			{
				::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_REPORT,0,0);
				m_bFind = true;
				
			}

			if (testNumbers.isFirstMismatch)
			{
				for (size_t i = 0; i < m_vecReadHDDs.size(); ++i)
					m_vecReadHDDs.at(i)->bFlagFINISH = true;				

				m_vecReadHDDs.at(0)->ClearQueue();
				m_vecReadHDDs.at(1)->ClearQueue();

				break;
			}
		}
		if (m_bStop)
		{
				for (size_t i = 0; i < m_vecReadHDDs.size(); ++i)
					m_vecReadHDDs.at(i)->bFlagFINISH = true;				

				m_vecReadHDDs.at(0)->ClearQueue();
				m_vecReadHDDs.at(1)->ClearQueue();

				break;
		
		}
		

		if (EASY_TEST == byTestType)
				lNumLBA += lStep;
	}


	switch (byTestType)
	{
	case FULLTEST:
		::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)FINISH_FULL);
		strReport = _T("Finish FULL check: \r\n");
		break;
	case EASY_TEST:
		::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)FINISH_STEP_FOLLOW);
		strReport = _T("Finish FOLLOW STEP check: \r\n");
		break;
	};
	fileReportTxt.WriteString(strReport);

	fileReportTxt.Close();	

	// Whait For Finish Threads
	for (size_t i = 0 ; i < 2; ++i)
	{
		WaitForSingleObject(*m_vecReadHDDs.at(i)->hFinishThread,INFINITE);
		m_vecReadHDDs.at(i)->CloseThreads();
	}

//	::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_EDIT_TEXT_CHANGE,0,(LPARAM)FINISH_FULL);
	//if (!bSTOP)
	//	::PostMessageW(::AfxGetApp()->m_pMainWnd->GetSafeHwnd(),WM_FINISH,0,0);
	
}


void CTaskVerify::setRange(VERIFY_RANGE & _rRange)
{
	if (_rRange.lTo % 255 != 0)
		if (_rRange.lTo > 255)
		_rRange.lTo = _rRange.lTo - 255;
	m_VerifyRange = _rRange;
}

void CTaskVerify::setCountSelection(UINT _iCount)
{
	iCountSelection = _iCount;
}

void CTaskVerify::setStopSignal()
{
	m_bStop = true;
}

void CTaskVerify::WirteTimeReport(CStdioFile *pFileWrite, BYTE byStartFinish)
{
	CTime cTime =  CTime::GetCurrentTime();
	CString strStartFinish = _T("");
	if ( byStartFinish == 0)
		 strStartFinish= _T("Start ");
	else
		strStartFinish = _T("Finish ");

	CString strReport = _T("");

	strReport.Format(_T("%schecking disks ( %i.%02i.%02i %02i:%02i:%02i  ) \r\n"),
					strStartFinish,
					cTime.GetYear(),
					cTime.GetMonth(),
					cTime.GetDay(),
					cTime.GetHour(),
					cTime.GetMinute(),
					cTime.GetSecond()
					);

	pFileWrite->WriteString(strReport);

}

void CTaskVerify::setFileReportPath(CString str)
{
	strFileReport = str;
}
