using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using Microsoft.Office.Interop.Word;




//[OfficeTestFiles]
namespace OfficeTestFiles
{
    abstract class AbstractOffice
    {
        public AbstractOffice()
        {
            //this.m_strDirPath = new string(' ',1) ;
        }
        
        public abstract void CreateApplication();
        public abstract void CloseApplication();
        public abstract void OpenDocuments(AbstractOffice _officeFile);

        public string[] GetFilesPath()
        {
            string[] searchExt = SearchFilter.Split('|');
            List<string> files = new List<string>();

            foreach (string extPattern in searchExt)
            {
                files.AddRange(Directory.GetFiles(DirectoryPath, extPattern, SearchOption.AllDirectories));
            }
            files.Sort();
            return files.ToArray();
        
        }
        private bool isOfficeSignature(string _FileName, byte[] _officeSign)
        {
            int iSignatureSize = _officeSign.Length;
            byte[] fileSignFile = new byte[iSignatureSize];

            FileStream fileStream = new FileStream(_FileName, FileMode.Open, FileAccess.Read, FileShare.Read);
            fileStream.Read(fileSignFile, 0, iSignatureSize);
            fileStream.Close();
            return fileSignFile.SequenceEqual(_officeSign);
        }
        protected MsOfficeType TestSignature(string _FileName)
        {
            byte[] strOffice2003 = { 0xD0, 0xCF, 0x11 };    // РП.
            if (isOfficeSignature(_FileName, strOffice2003))
                return MsOfficeType.MsOffice2003;

            byte[] strOffice2007 = { 0x50, 0x4B };          // PK
            if (isOfficeSignature(_FileName, strOffice2007))
                return MsOfficeType.MsOffice2007;

            byte[] strOfficeRTF = { 0x7B, 0x5C, 0x72, 0x74, 0x66, 0x31 };// {\rtf1
            if (isOfficeSignature(_FileName, strOfficeRTF))
                return MsOfficeType.MsRTF;

            return MsOfficeType.UNKNOWN;
        }

        protected void RenameFile(string _FileName, enFileStatus bStatusFile)
        { 
            switch (bStatusFile)
            {
                case enFileStatus.enGoodFile:
                    System.IO.File.Move(_FileName, _FileName + ".good");
                    break;
                case enFileStatus.enBadFile:
                    System.IO.File.Move(_FileName, _FileName + ".bad_file");
                    break;
                case enFileStatus.enPasswordFile:
                    System.IO.File.Move(_FileName, _FileName + ".pass_file");
                    break;
            }
        }

        protected void PrintOpenStatus(enFileStatus bStatusFile)
        {
            switch (bStatusFile)
            { 
                case enFileStatus.enGoodFile:
                    System.Console.WriteLine("- Open OK!");
                    break;
                case enFileStatus.enBadFile:
                    System.Console.WriteLine("- Open BAD!");
                    break;
                case enFileStatus.enPasswordFile:
                    System.Console.WriteLine("- Open PASSWORD!");
                    break;
                default:
                    System.Console.WriteLine("- Other Error (BUG)!");
                    break;
                }       
        }
        public string DirectoryPath
        {
            get { return m_strDirPath; }
            set { m_strDirPath = value; }
        }
        private string m_strSearchFilter;

        public string SearchFilter
        {
            get { return m_strSearchFilter; }
            set { m_strSearchFilter = value; }
        }

        // Fields WORD
        protected Microsoft.Office.Interop.Word.Application m_AppWord;
        protected Microsoft.Office.Interop.Word.Document m_DocWord;
        //
        // Fields EXCEL
        protected Microsoft.Office.Interop.Excel.Application m_AppExcel;
        protected Microsoft.Office.Interop.Excel.Workbook m_WorkWookExcel; 

        // Fields POWER POINT
        protected Microsoft.Office.Interop.PowerPoint.Application m_AppPowerPoint;
        private string m_strDirPath;

    }

    class MicrosoftWord : AbstractOffice
    {
        public MicrosoftWord()
        {


        }
        public override void OpenDocuments(AbstractOffice _officeFile)
        {
            System.Console.WriteLine("Method Testing [WORD] started...");
            string[] strFilesPath = GetFilesPath();
            enFileStatus resultOpen;
            MsOfficeType msWordType;
            foreach (string strCurrentFile in strFilesPath)
            {
                string strExtension = Path.GetExtension(strCurrentFile);
                resultOpen = enFileStatus.enBadFile;
                msWordType = MsOfficeType.UNKNOWN;
                msWordType = TestSignature(strCurrentFile);
                switch (msWordType)
                {
                    case MsOfficeType.MsOffice2003:
                    case MsOfficeType.MsOffice2007:
                        resultOpen = OpenWord(strCurrentFile, WdOpenFormat.wdOpenFormatAuto);
                        CloseWord();
                        break;
                    case MsOfficeType.MsRTF:
                        resultOpen = OpenWord(strCurrentFile, WdOpenFormat.wdOpenFormatRTF);
                        CloseWord();
                        break;
                }
                System.Console.Write("File {0} ", strCurrentFile);
                PrintOpenStatus(resultOpen);
                RenameFile(strCurrentFile, resultOpen);

            }

            System.Console.WriteLine("Method Testing [WORD] Finished...");

        }

        private enFileStatus OpenWord(string _FileName, object _OpenFormat)
        {
            object fileName = _FileName;
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
                                                      Format: _OpenFormat
                    //WritePasswordDocument: "",
                    //PasswordDocument: ""
                                                  );

                return enFileStatus.enGoodFile;
            }
            catch (System.Runtime.InteropServices.COMException ex)
            {
                switch (ex.ErrorCode)
                {
                    case -2146822880:
                    /* P A S S W O R D*/
                        return enFileStatus.enPasswordFile;
                }
                return enFileStatus.enBadFile;
            };
           
        }

        private void CloseWord()
        {
            if (m_DocWord != null)
            {
                m_DocWord.Close(SaveChanges: WdSaveOptions.wdDoNotSaveChanges);
                m_DocWord = null;
            }
            else
                if (m_AppWord.Documents.Count > 0)
                {
                    m_AppWord.Documents.Add(Visible: true);
                    m_AppWord.Documents.Close(SaveChanges: WdSaveOptions.wdDoNotSaveChanges);
                    m_AppWord.Documents.Add(Visible: false);
                }

  

        }


        public override void CreateApplication()
        {
            m_AppWord = new Microsoft.Office.Interop.Word.Application();
        }
        public override void CloseApplication()
        {
            m_AppWord.Quit(SaveChanges: WdSaveOptions.wdDoNotSaveChanges);
            Thread.Sleep(1000);
        }
    }

    class MicrosoftExcel : AbstractOffice
    {
        private static string strErrorPassword = "The password you supplied is not correct. Verify that the CAPS LOCK key is off and be sure to use the correct capitalization.";

        public override void  OpenDocuments(AbstractOffice _officeFile)
        {
           // System.Diagnostics.Process [] pProcessec = System.Diagnostics.Process.GetProcessesByName("winword");
            System.Console.WriteLine("Method Testing [EXCEL] started...");
            string[] strFilesPath = GetFilesPath();
            MsOfficeType msExcelType;
            enFileStatus ExcelStatus;
            foreach (string strCurrentFile in strFilesPath)
            {
                ExcelStatus = enFileStatus.enBadFile;
                msExcelType = TestSignature(strCurrentFile);
                switch (msExcelType)
                {
                    case MsOfficeType.MsOffice2003:
                    case MsOfficeType.MsOffice2007:
                        ExcelStatus = OpenExcel(strCurrentFile);
                        CloseExcel();
                        break;
                }
                System.Console.Write("File {0} ", strCurrentFile);
                PrintOpenStatus(ExcelStatus);
                RenameFile(strCurrentFile, ExcelStatus);

            }
         
            //m_AppExcel.
            System.Console.WriteLine("Method Testing [EXCEL] Finished...");
        }
        private enFileStatus OpenExcel(string _FileName)
        {
            m_WorkWookExcel = null;
            try
            {
                m_WorkWookExcel = m_AppExcel.Workbooks.Open(_FileName,
                                                          UpdateLinks: 2,
                                                          ReadOnly: true,
                                                          Password:"XYU");
                return enFileStatus.enGoodFile;
            }
            catch (System.Runtime.InteropServices.COMException ex)
            {
                if (ex.Message.Equals(strErrorPassword))
                    return enFileStatus.enPasswordFile;

                return enFileStatus.enBadFile;
            };
           
        }

        private void CloseExcel()
        {
            if (m_WorkWookExcel != null)
                m_WorkWookExcel.Close(SaveChanges: false);
        }

        public override void CreateApplication()
        {
            m_AppExcel = new Microsoft.Office.Interop.Excel.Application();
        }
        public override void CloseApplication()
        {
            m_AppExcel.Quit();
            Thread.Sleep(1000);
        }
    }

    class PowerPoint : AbstractOffice
    {
        public override void OpenDocuments(AbstractOffice _officeFile)
        {
            System.Console.WriteLine("Method Testing [POWER POINT] started...");
            string[] strFilesPath = GetFilesPath();
            MsOfficeType msPowerPointType;
            enFileStatus PowerPointStatus;
            foreach (string strCurrentFile in strFilesPath)
            {
                PowerPointStatus = enFileStatus.enBadFile;
                msPowerPointType = TestSignature(strCurrentFile);
                switch (msPowerPointType)
                { 
                    case MsOfficeType.MsOffice2003:
                    case MsOfficeType.MsOffice2007:
                        PowerPointStatus = OpenPowerPoint(strCurrentFile, msPowerPointType);
                        break;
                }
                System.Console.Write("File {0} ", strCurrentFile);
                PrintOpenStatus(PowerPointStatus);
                RenameFile(strCurrentFile, PowerPointStatus);
            }
            System.Console.WriteLine("Method Testing [POWER POINT] Finished...");
        }

        private enFileStatus OpenPowerPoint(string _FileName,MsOfficeType _PowerPointType)
        {
            try
            {

                    if (_PowerPointType == MsOfficeType.MsOffice2003)
                    {
                        m_PresentationPowerPoint = m_AppPowerPoint.Presentations.Open(_FileName,
                                                    ReadOnly: Microsoft.Office.Core.MsoTriState.msoTrue,
                                                    //Untitled: Microsoft.Office.Core.MsoTriState.msoFalse,
                                                    WithWindow: Microsoft.Office.Core.MsoTriState.msoFalse);
                        ClosePowerPoint();
                        return enFileStatus.enGoodFile;
                    }
                    if (_PowerPointType == MsOfficeType.MsOffice2007)
                    {
                        m_PresentationPowerPoint = m_AppPowerPoint.Presentations.Open2007(_FileName, 
                                                    ReadOnly: Microsoft.Office.Core.MsoTriState.msoTrue,
                                                    WithWindow: Microsoft.Office.Core.MsoTriState.msoFalse,
                                                    OpenAndRepair: Microsoft.Office.Core.MsoTriState.msoTrue);
                        ClosePowerPoint();
                        return enFileStatus.enGoodFile;
                    }
                    return enFileStatus.enBadFile;
            }
            catch (System.Runtime.InteropServices.COMException ex)
            {
                string strError = ex.Message;
                return enFileStatus.enBadFile;
            }
        }

        private void ClosePowerPoint()
        {
            if (m_PresentationPowerPoint != null)
                m_PresentationPowerPoint.Close();
        }

        public override void CreateApplication()
        {
            m_AppPowerPoint = new Microsoft.Office.Interop.PowerPoint.Application();
        }

        public override void CloseApplication()
        {
            m_AppPowerPoint.Quit();
        }
        protected Microsoft.Office.Interop.PowerPoint.Presentation m_PresentationPowerPoint;

    }

    abstract class OfficeFactory
    {
        public abstract AbstractOffice CreateOffice(MsOfficeType _officeType = 0);
    }

    class WordFactory : OfficeFactory
    {
        public override AbstractOffice CreateOffice(MsOfficeType _officeType = 0)
        {
             return new MicrosoftWord();
        }
    }

    class ExcelFactory : OfficeFactory
    {
        public override AbstractOffice CreateOffice(MsOfficeType _officeType = 0)
        {
            return new MicrosoftExcel();
        }
    }

    class PowerPointFactory : OfficeFactory 
    {
        public override AbstractOffice CreateOffice(MsOfficeType _officeType = 0)
        {
            return new PowerPoint();
        }
    }

    public enum MsOfficeType : byte
    {
        MsOfficeWord = 1,
        MsOfficeExcel = 2,
        MsPowerPoint = 3,
        MsRTF = 4,
        MsOffice2003 = 10,
        MsOffice2007 = 11,
        UNKNOWN = 100,
    };

    public enum enFileStatus : byte
    {
       enGoodFile = 1,
       enBadFile = 2,
       enPasswordFile = 3,
    };
}
