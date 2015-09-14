
// DiskVerifierDlg.h : header file
//

#pragma once


#include "afxwin.h"

#include "Drives.h"
#include "afxcmn.h"

#include "TaskVerify.h"
//
// IDENTIFY data (from ATAPI driver source)
//

#pragma pack(1)

typedef struct _IDENTIFY_DATA {
 //   USHORT GeneralConfiguration;            // 00 00
 //   USHORT Obsolete1; 
	//USHORT NumberOfCylinders;               // 02  1
 //   USHORT Obsolete2;                       // 04  2
	//USHORT Retired1[2]; 
 //   USHORT Obsolete3;                       // 04  2
	//USHORT ReservedForAssignment[2];
	//USHORT Retired2; 
    USHORT SerialNumber[10];                // 14  10-19
    USHORT BufferType;                      // 28  20
    USHORT BufferSectorSize;                // 2A  21
    USHORT NumberOfEccBytes;                // 2C  22
    USHORT FirmwareRevision[4];             // 2E  23-26
    USHORT ModelNumber[20];                 // 36  27-46
    UCHAR  MaximumBlockTransfer;            // 5E  47
    UCHAR  VendorUnique2;                   // 5F
    USHORT DoubleWordIo;                    // 60  48
    USHORT Capabilities;                    // 62  49
    USHORT Reserved2;                       // 64  50
    UCHAR  VendorUnique3;                   // 66  51
    UCHAR  PioCycleTimingMode;              // 67
    UCHAR  VendorUnique4;                   // 68  52
    UCHAR  DmaCycleTimingMode;              // 69
    USHORT TranslationFieldsValid:1;        // 6A  53
    USHORT Reserved3:15;
    USHORT NumberOfCurrentCylinders;        // 6C  54
    USHORT NumberOfCurrentHeads;            // 6E  55
    USHORT CurrentSectorsPerTrack;          // 70  56
    ULONG  CurrentSectorCapacity;           // 72  57-58
    USHORT CurrentMultiSectorSetting;       //     59
    ULONG  UserAddressableSectors;          //     60-61
    USHORT SingleWordDMASupport : 8;        //     62
    USHORT SingleWordDMAActive : 8;
    USHORT MultiWordDMASupport : 8;         //     63
    USHORT MultiWordDMAActive : 8;
    USHORT AdvancedPIOModes : 8;            //     64
    USHORT Reserved4 : 8;
    USHORT MinimumMWXferCycleTime;          //     65
    USHORT RecommendedMWXferCycleTime;      //     66
    USHORT MinimumPIOCycleTime;             //     67
    USHORT MinimumPIOCycleTimeIORDY;        //     68
    USHORT Reserved5[2];                    //     69-70
    USHORT ReleaseTimeOverlapped;           //     71
    USHORT ReleaseTimeServiceCommand;       //     72
    USHORT MajorRevision;                   //     73
    USHORT MinorRevision;                   //     74
    USHORT Reserved6[50];                   //     75-126
    USHORT SpecialFunctionsEnabled;         //     127
  //  USHORT Reserved7[128];                  //     128-255
} IDENTIFY_DATA, *PIDENTIFY_DATA;

#pragma pack()





// Thread Functions

DWORD WINAPI ThreadVerifyDisk(vector<READDATA*> &);
DWORD WINAPI ThreadRandomVerifyDisk(LPVOID lParam);

// CDiskVerifierDlg dialog
class CDiskVerifierDlg : public CDialogEx
{
// Construction
public:
	CDiskVerifierDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_DISKVERIFIER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

private:
	vector<CDiskDrive> m_vecDrives;
	vector<CDiskDrive> m_vecSelDrives;
	bool AddSelectedDrive(int iPos);
	bool bEasyOrRandomTest;
	CString setDiskReport(CDiskDrive &);
	CString getTimeReport();
	void WirteDiskInfoReport(CStdioFile *pFileWrite, const CDiskDrive & _diskDrive );

	CTaskVerify *m_pTaskVerify;

	vector<READDATA*> m_vecReadDATA;

	inline bool CheckBytes(BYTE *pByteCheck, const BYTE &_size);

	afx_msg LRESULT OnFindNotEqual(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFinishCheck(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEditReport(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetNullProgress(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEditTEXT(WPARAM wParam, LPARAM lParam);

	VERIFY_RANGE verifyRange;
	HANDLE hVerifyThread;
	TESTNUMBERS m_testNumbers;
	LONGLONG m_llReadSize;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCancel();
//	bool isPhysicalEqulToLogical(BYTE * pPasport);
//	void setWordFrom2Bytes(BYTE * pPasport, WORD * pWord, BYTE _pos = 0);
	CString strFileReport;

public:
	CDrives m_Drives;

	CButton m_ButtFullCheck;
	CButton m_ButtRandomlCheck;
	CButton m_ButtEasylCheck;
	CButton m_ButtToFirstMismatch;
	CButton m_ButtCheck;
	CButton m_ButtClear;


	CString m_StrDevices;
	CString m_TextCylinders;
	CString m_TextBytesPerSector;
	CString  m_TextSerialNumber;

	CListCtrl m_ListDrives;
	CListBox m_ListDevices;
	CListBox m_ListSelected;

	CProgressCtrl m_ProgressCheck;
	CEdit m_EditReport;
	CEdit m_EditCheckSize;
	CEdit m_EditStart;
	CEdit m_pEditSelections;

	afx_msg void OnBnClickedStopButton();
	afx_msg void OnBnClickedCheckButton();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnNMDblclkListDrives(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListDrives(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListDrives(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedOk();

	DECLARE_MESSAGE_MAP()
} ;

