using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Microsoft.Office.Interop.Word;
using Microsoft.Office.Interop.Excel;


namespace OfficeChecker
{
    public enum OpenStatus : byte
    {
        OpenGOOD = 1,
        OpenBAD = 2,
        OpenPassword = 3,
    }

    public struct ProcessName
    {
        public static string WordProcessName = "winword";
        public static string ExelProcessName = "excel";
    }

    abstract class AbstractOffice : Subject
    {
        // Constructor
        public AbstractOffice()
        {
            m_OpenStatus = OpenStatus.OpenBAD;
            m_OfficeVersion = OfficeVersion.NoOffice;
            m_TestingFiles = null;
        }
        protected OpenStatus m_OpenStatus;
        protected OfficeVersion m_OfficeVersion;
        protected string[] m_TestingFiles;

        public abstract int Run(int _iTimeOut);
        public abstract void Stop();
        public abstract OpenStatus TestDocumnet(string _TestFiles, OfficeVersion _OfficeVersion);
        public abstract int FindFiles(string _Directory, List<OfficeVersion> _ListOfficeVersion);
        public abstract bool CreateApplication();
        public abstract bool CloseApplication();
        public abstract void Close();
        public abstract void Clear(); 
        public abstract OfficeType GetOfficeType();


        public abstract OpenStatus GetOpenStatus();
        public abstract string GetFileName();
    }

    class MicrosoftWord : AbstractOffice 
    {
        private Microsoft.Office.Interop.Word.Application m_AppWord;
        private Microsoft.Office.Interop.Word.Document m_DocWord;

        private string m_FilePath;
        private int m_iTimeOut;

        private Thread m_thread;
        private Thread m_MainThread;
        private FileWorker m_fileWorker;
        public int TimeOut
        {
            set { m_iTimeOut = value; }
            get { return m_iTimeOut; }
        }

        public MicrosoftWord()
        {
            m_fileWorker = new FileWorker();
            m_OpenStatus = OpenStatus.OpenBAD;
            m_OfficeVersion = OfficeVersion.NoOffice;
            m_iTimeOut = 0;
        }
        public override int Run(int _iTimeOut)
        {
            m_iTimeOut = _iTimeOut;
            if (m_TestingFiles.Length == 0)
                return -1;

            m_MainThread = new Thread(new ThreadStart(this.ThreadTesting));
            m_MainThread.Start();

            return 0;
        }
        public override void Stop()
        {
            if (m_MainThread != null)
            {
                m_MainThread.Abort();
                this.CloseApplication();
            }
        }
        public override OpenStatus TestDocumnet(string _testFiles, OfficeVersion _OfficeVersion)
        {
            m_FilePath = _testFiles;
            m_OpenStatus = OpenStatus.OpenBAD;
            m_OfficeVersion = _OfficeVersion;

            // Opening in thread to test Document;
            if (!this.isCreated())
                CreateApplication();

            m_thread = new Thread(new ThreadStart(this.ThreadOpenWORD));
            m_thread.Start();
            if (m_iTimeOut > 0)
                m_thread.Join(m_iTimeOut * 1000);
            else
                m_thread.Join();

            return m_OpenStatus;
        }
        public override int FindFiles(string _Directory, List<OfficeVersion> _ListOfficeVersion)
        {
            FileFilder finder = new FileFilder;
            //finder.addExtension()

            List<string> listFiles = new List<string>();
            foreach (OfficeVersion officeVersion in _ListOfficeVersion)
            {
                if (officeVersion == OfficeVersion.OfficeRTF)
                    m_fileWorker.SearchFiles(_Directory, OfficeVersion.OfficeRTF, OfficeType.msRTF);
                else
                    m_fileWorker.SearchFiles(_Directory, officeVersion, this.GetOfficeType());

                listFiles.AddRange(m_fileWorker.GetFiles());
            }
            m_TestingFiles = listFiles.ToArray();
            return m_TestingFiles.Length;

        }
        public override bool CreateApplication()
        {
            if (!this.isCreated())
            {
                m_AppWord = new Microsoft.Office.Interop.Word.Application();
                return true;
            }
            return false;
        }
        public override bool CloseApplication()
        {
            try
            {
                //string str = m_AppWord.Name;
                m_AppWord.Quit();
                System.Runtime.InteropServices.Marshal.ReleaseComObject(m_AppWord);
                KillWordProcess();
                return true;
            }
            catch (System.Exception ex)
            {
                m_AppWord = null;
            }
            KillWordProcess();

            return false;
        }
        public override void Close() 
        {
            if (m_DocWord != null)
            {
                try
                {
                    m_DocWord.Close(SaveChanges: WdSaveOptions.wdDoNotSaveChanges);
                    m_DocWord = null;
                }
                catch (System.Exception ex)
                {
                    CloseApplication();
                    System.Console.WriteLine("Error Close Document");
                }
            }
            else
                if (m_AppWord.Documents.Count > 0)
                {
                    m_AppWord.Documents.Add(Visible: true);
                    try
                    {
                        m_AppWord.Documents.Close(SaveChanges: WdSaveOptions.wdDoNotSaveChanges);
                    }
                    catch (System.Exception ex)
                    {
                        CloseApplication();
                        System.Console.WriteLine("Error Close Document");
                        return;
                    }
                    m_AppWord.Documents.Add(Visible: false);
                }
        }
        public override void Clear()
        {
            m_TestingFiles = null;
            m_FilePath = null;
            m_iTimeOut = 0;
            m_OpenStatus = OpenStatus.OpenBAD;
            m_OfficeVersion = OfficeVersion.NoOffice;
        }
        public override OfficeType GetOfficeType()
        {
            return OfficeType.msWord;
        }
        public override OpenStatus GetOpenStatus()
        {
            return m_OpenStatus;
        }
        public override string GetFileName()
        {
            return m_FilePath;
        }

        private void ThreadTesting()
        {
            m_OfficeVersion = OfficeVersion.NoOffice;

            foreach (string TestingFile in m_TestingFiles)
            {
                m_OpenStatus = OpenStatus.OpenBAD;
                //Console.WriteLine("{0}", TestingFile);
                m_OfficeVersion = m_fileWorker.TestSignature(TestingFile);
                if (m_OfficeVersion != OfficeVersion.NoOffice)
                {
                    if (!this.isCreated())
                        this.CreateApplication();
                    m_OpenStatus = TestDocumnet(TestingFile, m_OfficeVersion);
                    // Send Event to "Change"
                    // 1 - Update progress...
                    // 2 - File Name, Opened Status, OfficeType...
                }
                if (this.isCreated())
                    this.Close();

                if (!m_fileWorker.RenameFile(TestingFile, m_OpenStatus))
                {
                    this.CloseApplication();
                    m_fileWorker.RenameFile(TestingFile, m_OpenStatus);
                }
                this.Notify();
            }
            this.CloseApplication();
            Console.WriteLine("\n\n\n\n F I N I S H  --  W O R D");
        }
        private void ThreadOpenWORD()
        {
            object fileName = m_FilePath;
            WdOpenFormat OpenFormat = WdOpenFormat.wdOpenFormatAuto;
            if (m_OfficeVersion == OfficeVersion.OfficeRTF)
                OpenFormat = WdOpenFormat.wdOpenFormatRTF;
            try
            {
                m_DocWord = m_AppWord.Documents.Open(FileName: ref fileName,
                                                      ReadOnly: true,
                                                      Visible: false,
                                                      OpenAndRepair: true,
                                                      ConfirmConversions: false,
                                                      Encoding: false,
                                                      Revert: false,
                                                      NoEncodingDialog: true,
                                                      Format: OpenFormat,
                                                      PasswordDocument: "XUY"
                    //WritePasswordDocument: "",
                    //PasswordDocument: ""
                                                  );

                m_OpenStatus = OpenStatus.OpenGOOD;
            }
            catch (System.Runtime.InteropServices.COMException ex)
            {


                switch (ex.ErrorCode)
                {
                    ////Error Message = Ошибка на сервере. (Exception from HRESULT: 0x80010105 (RPC_E_SERVERFAULT))
                    //case -2147417851:
                    //    CloseApplication();
                    //    CreateApplication();
                    //    break;
                    case -2146822880:
                    case -2146824090:
                        /* P A S S W O R D*/
                        m_OpenStatus = OpenStatus.OpenPassword;
                        return;
                }
                m_OpenStatus = OpenStatus.OpenBAD;
            };

            // End Thread...
        }
        private void KillWordProcess()
        {
            System.Diagnostics.Process[] NoClosedProcess;
            NoClosedProcess = System.Diagnostics.Process.GetProcessesByName(ProcessName.WordProcessName);
            foreach (System.Diagnostics.Process docProcess in NoClosedProcess)
            {
                docProcess.Kill();
            }
        }
        private bool isCreated()
        {
            if (m_AppWord == null)
                return false;
            try
            {
                int k = 1;
                string str = m_AppWord.Name;
                return true;
            }
            catch (System.Exception ex)
            {
                m_AppWord = null;
            }

            return false;
        }
    }

    class MicrosoftExcel : AbstractOffice
    {
        private Microsoft.Office.Interop.Excel.Application m_AppExcel;
        private Microsoft.Office.Interop.Excel.Workbook m_BookExcel;

        private FileWorker m_fileWorker;
        private Thread m_thread;
        private Thread m_MainThread;
        private int m_iTimeOut;
        private string m_FilePath;
        private static string strErrorPassword = "CAPS LOCK";

        public MicrosoftExcel()
        {
            m_fileWorker = new FileWorker();
            m_iTimeOut = 0;
        }

        public override int Run(int _iTimeOut)
        {
            m_iTimeOut = _iTimeOut;
            if (m_TestingFiles.Length == 0)
                return -1;

            m_MainThread = new Thread(new ThreadStart(this.ThreadTesting));
            m_MainThread.Start();

            return 0;
        }
        public override void Clear()
        {
        
        }
        public override void Stop()
        {
            if (m_MainThread != null)
            {
                m_MainThread.Abort();
                this.CloseApplication();
            }
        }
        public override OpenStatus TestDocumnet(string _testFiles, OfficeVersion _OfficeVersion)
        {
            m_FilePath = _testFiles;
            m_OpenStatus = OpenStatus.OpenBAD;
            m_OfficeVersion = _OfficeVersion;

            //// Opening in thread to test Document;
            if (!this.isCreated())
                CreateApplication();

            m_thread = new Thread(new ThreadStart(this.ThreadOpenExcel));
            m_thread.Start();
            if (m_iTimeOut > 0)
                m_thread.Join(m_iTimeOut * 1000);
            else
                m_thread.Join();

            return m_OpenStatus;
        }
        public override int FindFiles(string _Directory, List<OfficeVersion> _ListOfficeVersion)
        {
            List<string> listFiles = new List<string>();
            foreach (OfficeVersion officeVersion in _ListOfficeVersion)
            {
                m_fileWorker.SearchFiles(_Directory, officeVersion, OfficeType.msExcel);
                listFiles.AddRange(m_fileWorker.GetFiles());
            }
            m_TestingFiles = listFiles.ToArray();
            return m_TestingFiles.Length;
       }
        public override bool CreateApplication()
        {
            if (!this.isCreated())
            {
                m_AppExcel = new Microsoft.Office.Interop.Excel.Application();
                return true;
            }
            return false;
        }
        public override bool CloseApplication()
        {
            try
            {
                string strName = m_AppExcel.Name;
                m_AppExcel.Quit();
                System.Runtime.InteropServices.Marshal.ReleaseComObject(m_AppExcel);
                KillExelProcess();
                return true;
            }
            catch (System.Exception ex)
            {
                m_AppExcel = null;
            }
            KillExelProcess();
            return false;
        }
        public override void Close()
        {
            if (m_BookExcel != null)
            {
                try
                {
                    //m_BookExcel.
                    m_BookExcel.Close(SaveChanges: WdSaveOptions.wdDoNotSaveChanges);
                    m_BookExcel = null;
                }
                catch (System.Exception ex)
                {
                    CloseApplication();
                    System.Console.WriteLine("Error Close Document");
                }
            }
            else
                CloseApplication();
        }
        public override OfficeType GetOfficeType()
        {
            return OfficeType.msExcel;
        }
        public override OpenStatus GetOpenStatus()
        {
            return m_OpenStatus;
        }
        /*!!!*/
        public override string GetFileName()
        {
            return m_FilePath;
        }
        /*!!!*/

        private void ThreadTesting()
        {
            foreach (string TestingFile in m_TestingFiles)
            {
                m_OpenStatus = OpenStatus.OpenBAD;
                //Console.WriteLine("{0}", TestingFile);
                m_OfficeVersion = m_fileWorker.TestSignature(TestingFile);
                if (m_OfficeVersion != OfficeVersion.NoOffice)
                {
                    if (!this.isCreated())
                        this.CreateApplication();
                    System.Console.WriteLine(TestingFile);
                    m_OpenStatus = TestDocumnet(TestingFile, m_OfficeVersion);
                    // Send Event to "Change"
                    // 1 - Update progress...
                    // 2 - File Name, Opened Status, OfficeType...
                }
                if (this.isCreated())
                    this.Close();

                if (!m_fileWorker.RenameFile(TestingFile, m_OpenStatus))
                {
                    this.CloseApplication();
                    m_fileWorker.RenameFile(TestingFile, m_OpenStatus);
                }
                this.Notify();
            }
            this.CloseApplication();
            Console.WriteLine("\n\n\n\n F I N I S H EXCEL");
        }
        private void ThreadOpenExcel()
        {
            try
            {
                m_BookExcel = m_AppExcel.Workbooks.Open(m_FilePath,
                                                        UpdateLinks: 2,
                                                        ReadOnly: true,
                                                        Password:"liberta68");
                m_OpenStatus = OpenStatus.OpenGOOD;
            }
            catch (System.Runtime.InteropServices.COMException ex)
            {
                string sError = ex.Message;
                if (sError.IndexOf(strErrorPassword) != -1) 
                //if (ex.Message.Equals(strErrorPassword))
                {
                    m_OpenStatus = OpenStatus.OpenPassword;
                    return;
                }

                m_OpenStatus = OpenStatus.OpenBAD;
            };
        }
        private void KillExelProcess()
        {
            System.Diagnostics.Process[] NoClosedProcess;
            NoClosedProcess = System.Diagnostics.Process.GetProcessesByName(ProcessName.ExelProcessName);
            foreach (System.Diagnostics.Process exelProcess in NoClosedProcess)
            {
                exelProcess.Kill();
            }

        }
        private bool isCreated()
        {
            if (m_AppExcel == null)
                return false;
            try
            {
                string str = m_AppExcel.Name;
                return true;
            }
            catch (System.Exception ex)
            {
                m_AppExcel = null;
            }

            return false;
        }
    }


    abstract class OfficeFactory
    {
        public abstract AbstractOffice CreateOffice();
    }

    class WordFacroty : OfficeFactory
    {
        public override AbstractOffice CreateOffice()
        {
            return new MicrosoftWord();
        }
    }
    class ExcelFactory : OfficeFactory
    {
        public override AbstractOffice CreateOffice()
        {
            return new MicrosoftExcel();
        }
    }
}
