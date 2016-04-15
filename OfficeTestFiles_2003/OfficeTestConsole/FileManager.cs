using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace OfficeTestConsole
{
//    abstract class OpenedStatus
//    {
//        private enFileStatus m_FileStatus;
//        public enFileStatus Status
//        { 
//            get { return m_FileStatus; }
//            set { m_FileStatus = value; }
//        }

//        private string m_StatusName;
//        private string Name
//        {
//            get { return m_StatusName; }
//            set { m_StatusName = value; }
//        }
////        public abstract
//    }

    class FileManager
    {
        private string m_CurrentDir;
        public string DirectoryBAD
        {
            get { return m_CurrentDir; }
            set { m_CurrentDir = value; }
        }

        public void MoveFiles(string _directory, enFileStatus _fileStatus)
        { 
            string [] sFiles;
            string sSearchText;
            string toFile;
            int iSizeText;
         
            switch (_fileStatus)
            {
                case enFileStatus.enGoodFile:
                    sSearchText = "*.good";
                    sFiles = Directory.GetFiles(_directory, sSearchText, SearchOption.AllDirectories);
                    foreach ( string sFile in sFiles)
                    {
                        iSizeText = sSearchText.Length;
                        --iSizeText;
                        toFile = sFile.Substring(0,sFile.Length - iSizeText);
                        // try catch ...
                        try
                        {
                            System.Console.WriteLine("Rename File {0} -> {1}", Path.GetFileName(sFile), Path.GetFileName(toFile));
                            System.IO.File.Move(sFile, toFile);
                        }
                        catch (Exception ex)
                        {
                            System.Console.WriteLine("Can't rename file :");
                            System.Console.WriteLine("{0},{1}", sFile,toFile);
                            System.Console.WriteLine(ex.Message);
                        }
                    }
                    break;
                case enFileStatus.enBadFile:
                    sSearchText = "*.bad_file";
                    sFiles = Directory.GetFiles(_directory, sSearchText, SearchOption.AllDirectories);
                    string CurrentDir = _directory;
                    string BadFiles = CurrentDir + "\\BadFiles\\";
                    if (! Directory.Exists(BadFiles) )
                        Directory.CreateDirectory(BadFiles);
                    foreach (string sFile in sFiles)
                    {
                        iSizeText = sSearchText.Length;
                        --iSizeText;
                        toFile = sFile.Substring(0, sFile.Length - iSizeText);
                        // try catch ...
                        try
                        {
                            string toFileName = Path.GetFileName(toFile);

                            toFile = BadFiles + toFileName;
                            System.Console.WriteLine("Move File {0} -> {1}", toFileName, toFile);
                            System.IO.File.Move(sFile, toFile);
                        }
                        catch (Exception ex)
                        {
                            System.Console.WriteLine("Can't rename file :");
                            System.Console.WriteLine("{0},{1}", sFile, toFile);
                            System.Console.WriteLine(ex.Message);
                        }
                    }
                    break;
            }
        }
    }

}
