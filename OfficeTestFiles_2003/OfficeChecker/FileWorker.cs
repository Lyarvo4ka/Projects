using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;


namespace OfficeChecker
{
    enum OfficeType : byte
    {
        msWord = 1,
        msExcel = 2,
        msPowerPoint = 3,
        msRTF = 4,
    }
    enum OfficeVersion : byte
    {
        Office2003 = 1,
        Office2007 = 2,
        OfficeRTF = 3,
        OfficeAll = 100,
        NoOffice = 101,
    }
    //enum DocumentType : byte 
    //{
    //    msWord2003 = 1,
    //    msExel2003 = 2,
    //    msPowerPoint2003 = 3,
    //    msWord2007 = 4,
    //    msExel2007 = 5,
    //    msPowerPoint2007 = 6,
    //    msRTF = 7,
    //    UNKNOWN = 100,
    //}
    class SelectedOffice
    {
        public void SelectWord(bool _bSelect)
        {
            m_bWord = _bSelect;
        }
        public void SelectExcel(bool _bSelect)
        {
            m_bExcel = _bSelect;
        }
        public void SelectPowerPoint(bool _bSelect)
        {
            m_bPowerPoint = _bSelect;
        }
        public void SelectAll(bool _bSelect)
        {
            SelectWord(_bSelect);
            SelectExcel(_bSelect);
            SelectPowerPoint(_bSelect);
        }
        public bool isWord 
        {
            get { return m_bWord; }
        }
        public bool isExcel
        {
            get { return m_bExcel; }
        }
        public bool isPowerPoint
        {
            get { return m_bPowerPoint; }
        }
        private bool m_bWord;
        private bool m_bExcel;
        private bool m_bPowerPoint;
    }
    class SearchMaker
    {
        public SelectedOffice m_Office_2003;
        public SelectedOffice m_Office_2007;
        public void SelectRTF(bool _bSelect)
        {
            m_bRTF = _bSelect;
        }
        public OfficeVersion GetRTF()
        {
            if (m_bRTF)
                return OfficeVersion.OfficeRTF;
            return OfficeVersion.NoOffice;
        }


        public OfficeVersion GetWordVersion()
        {
            if (m_Office_2003.isWord && m_Office_2007.isWord)
                return OfficeVersion.OfficeAll;
            else
                if (m_Office_2003.isWord)
                    return OfficeVersion.Office2003;
                else
                    if (m_Office_2007.isWord)
                        return OfficeVersion.Office2007;

            return OfficeVersion.NoOffice;
        }
        public OfficeVersion GetExcelVersion()
        {
            if (m_Office_2003.isExcel && m_Office_2007.isExcel)
                return OfficeVersion.OfficeAll;
            else
                if (m_Office_2003.isExcel)
                    return OfficeVersion.Office2003;
                else
                    if (m_Office_2007.isExcel)
                        return OfficeVersion.Office2007;

            return OfficeVersion.NoOffice;
        }
        public OfficeVersion GetPowerPointVersion()
        {
            if (m_Office_2003.isPowerPoint && m_Office_2007.isPowerPoint)
                return OfficeVersion.OfficeAll;
            else
                if (m_Office_2003.isPowerPoint)
                    return OfficeVersion.Office2003;
                else
                    if (m_Office_2007.isPowerPoint)
                        return OfficeVersion.Office2007;

            return OfficeVersion.NoOffice;
        }           
        private bool m_bRTF;
    }

    struct SearchFilter
    {
        public static string Word2003 = "*.doc";
        public static string Word2007 = "*.docx";
        public static string Excel2003 = "*.xls";
        public static string Excel2007 = "*.xlsx";
        public static string PowerPoint2003 = "*.ppt";
        public static string PowerPoint2007 = "*.pptx";
        public static string RTF = "*.rtf";
    }

    class FileWorker
    {
        public string[] GetFiles()
        {
            return m_arFiles;
        }
        public bool RenameFile(string _sFileName, OpenStatus _OpenStatus)
        {
            try
            {
                switch (_OpenStatus)
                {
                    case OpenStatus.OpenGOOD:
                        System.IO.File.Move(_sFileName, _sFileName + ".good");
                        break;
                    case OpenStatus.OpenBAD:
                        System.IO.File.Move(_sFileName, _sFileName + ".bad_file");
                        break;
                    case OpenStatus.OpenPassword:
                        System.IO.File.Move(_sFileName, _sFileName + ".passwd");
                        break;
                }
                return true;
            }
            catch (System.IO.IOException ex)
            {
                System.Console.WriteLine("Error Rename file {0}", ex.Message);
                return false;
            }
        }

        private bool isOfficeSignature(string _FileName, byte[] _officeSign)
        {
            int iSignatureSize = _officeSign.Length;
            byte[] fileSignFile = new byte[iSignatureSize];
            try
            {
                FileStream fileStream = new FileStream(_FileName, FileMode.Open, FileAccess.Read, FileShare.Read);
                fileStream.Read(fileSignFile, 0, iSignatureSize);
                fileStream.Close();
                return fileSignFile.SequenceEqual(_officeSign);
            }
            catch (UnauthorizedAccessException ex)
            {
                System.Console.WriteLine("Error access denied to file.", ex.Message);
            }
            catch( System.IO.IOException io_ex)
            {

            }
            return false;
        }
        public OfficeVersion TestSignature(string _FileName)
        {
            byte[] strOffice2003 = { 0xD0, 0xCF, 0x11 };    // РП.
            if (isOfficeSignature(_FileName, strOffice2003))
                return OfficeVersion.Office2003;

            byte[] strOffice2007 = { 0x50, 0x4B };          // PK
            if (isOfficeSignature(_FileName, strOffice2007))
                return OfficeVersion.Office2007;

            byte[] strOfficeRTF = { 0x7B, 0x5C, 0x72, 0x74, 0x66, 0x31 };// {\rtf1
            if (isOfficeSignature(_FileName, strOfficeRTF))
                return OfficeVersion.OfficeRTF;

            return OfficeVersion.NoOffice;
        }
        public bool SearchFiles(string _DirPath, OfficeVersion _OfficeVersion, OfficeType _officeType)
        {
            if (!System.IO.Directory.Exists(_DirPath))
                return false;

            this.setSearchFilter(ref m_SearchFilter, _OfficeVersion, _officeType);
            m_arFiles = FindFiles(_DirPath, m_SearchFilter, _OfficeVersion);
            if (m_arFiles.Length > 0)
                return true;
            return false;
        }

        private string[] FindFiles(string _DirPath, string _SearchFilter, OfficeVersion _OfficeVersion)
        {
            List<string> files = new List<string>();

            var list_files = Delimon.Win32.IO.Directory.GetFiles(_DirPath, _SearchFilter, Delimon.Win32.IO.SearchOption.AllDirectories);
            files.AddRange(list_files);
            if (_OfficeVersion == OfficeVersion.Office2003)
            {
                List<string> retFiles = new List<string>();
                for (int iIndex = 0; iIndex < files.Count; ++iIndex)
                {
                    FileInfo infoFile = new FileInfo(files.ElementAt(iIndex));
                    if (infoFile.Extension.Length <= 4)
                        retFiles.Add(files.ElementAt(iIndex));
                }
                retFiles.Sort();
                m_arFiles = retFiles.ToArray();
                return m_arFiles;
            }
            return files.ToArray();
        }
        private void setSearchFilter(ref string _SearchFilter, OfficeVersion _OfficeVersion, OfficeType _officeType)
        {
            switch (_officeType)
            {
                case OfficeType.msWord:
                    if (_OfficeVersion == OfficeVersion.Office2007)
                        _SearchFilter = SearchFilter.Word2007;
                    else
                        _SearchFilter = SearchFilter.Word2003;
                    break;
                case OfficeType.msExcel:
                    if (_OfficeVersion == OfficeVersion.Office2007)
                        _SearchFilter = SearchFilter.Excel2007;
                    else
                        _SearchFilter = SearchFilter.Excel2003;
                    break;
                case OfficeType.msPowerPoint:
                    if (_OfficeVersion == OfficeVersion.Office2007)
                        _SearchFilter = SearchFilter.PowerPoint2007;
                    else
                        _SearchFilter = SearchFilter.PowerPoint2003;
                    break;
                case OfficeType.msRTF:
                    _SearchFilter = SearchFilter.RTF;
                    break;
                default:
                    System.Console.WriteLine("Error... Never calling.");
                    break;
            }
            
        }
        private string[] m_arFiles;
        private string m_SearchFilter;

        public bool OperateFiles(string _Directory, OpenStatus _OpenStatus, BADFILES _BadFiles)
        {
            string [] sFoundFiles;
            string sSearchText;
            string toFile;
            int iSizeExt;
            switch (_OpenStatus)
            {
                case OpenStatus.OpenGOOD:
                    sSearchText = "*.good";
                    try
                    {
                        sFoundFiles = Directory.GetFiles(_Directory, sSearchText, SearchOption.AllDirectories);
                        foreach (string sFile in sFoundFiles)
                        {
                            iSizeExt = sSearchText.Length;
                            --iSizeExt;
                            toFile = sFile.Substring(0, sFile.Length - iSizeExt);
                            // try catch ...
                            try
                            {
                                //System.Console.WriteLine("Rename File {0} -> {1}", Path.GetFileName(sFile), Path.GetFileName(toFile));
                                System.IO.File.Move(sFile, toFile);
                            }
                            catch (Exception ex)
                            {
                                System.Console.WriteLine("Can't rename file :");
                                //System.Console.WriteLine("{0},{1}", sFile,toFile);
                                //System.Console.WriteLine(ex.Message);
                            }
                        }
                        return true;
                    }
                    catch (System.IO.IOException ex)
                    {
                        Console.WriteLine("Error Find Files");
                        return false;
                    }
                    break;
                case OpenStatus.OpenBAD:
                    sSearchText = "*.bad_file";
                    if (_BadFiles == BADFILES.Rename)
                        return true;

                    try
                    {
                        sFoundFiles = Directory.GetFiles(_Directory, sSearchText, SearchOption.AllDirectories);
                        foreach (string sFile in sFoundFiles)
                        {
                            iSizeExt = sSearchText.Length;
                            --iSizeExt;
                            toFile = sFile.Substring(0, sFile.Length - iSizeExt);
                            // try catch ...
                            try
                            {
                                string toFileName = Path.GetFileName(toFile);
                                switch (_BadFiles)
                                {
                                    case BADFILES.Move:
                                        string CurrentDir = _Directory;
                                        string BadDir = CurrentDir + "\\BadFiles\\";
                                        if (!Directory.Exists(BadDir))
                                            Directory.CreateDirectory(BadDir);
                                        toFile = BadDir + toFileName;
                                        try
                                        {
                                            System.IO.File.Move(sFile, toFile);
                                        }
                                        catch (System.IO.IOException ex)
                                        {
                                            Console.WriteLine("Can't rename file");
                                        }
                                        break;
                                    case BADFILES.Remove:
                                        try
                                        {
                                            System.IO.File.Delete(sFile);
                                        }
                                        catch (System.IO.IOException ex)
                                        {
                                            Console.WriteLine("Can't rename file");
                                        }
                                        break;
                                }

                            }
                            catch (Exception ex)
                            {
                                System.Console.WriteLine("Can't rename file :");
                                System.Console.WriteLine("{0},{1}", sFile, toFile);
                                System.Console.WriteLine(ex.Message);
                            }
                        }
                        return true;


                    }
                    catch (System.IO.IOException ex)
                    {
                        Console.WriteLine("Error Find Files");
                    }


                    break;

            }
            return false;
        }
    }
    public enum BADFILES : byte
    { 
        Rename = 0,
        Remove = 1,
        Move = 2,
    }
}
