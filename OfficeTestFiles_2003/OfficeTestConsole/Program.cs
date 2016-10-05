using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace OfficeTestConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            //string pathDirecory = Application.StartupPath;
            //pathDirecory += @"\bad_files"
            Console.Write("Directory: ");
            string strDirPath = Console.ReadLine();
            FileStream fsStream = new FileStream("Report.txt", FileMode.Create);
            fsStream.Close();

            if (!Directory.Exists(strDirPath))
            {
                string strErrorTxt = "Invalid directory path (";
                strErrorTxt += strDirPath;
                strErrorTxt += ")\n";
                //               MessageBox.Show(strErrorTxt, "Error select directory");
                return;
            }
           // AbstractOffice OfficeWord = null;
            OfficeFactory officeFactory = null;
            //officeFactory = new WordFactory();
            //OfficeWord = officeFactory.CreateOffice();

            //string strExt = "*.doc|*.rtf";

            //OfficeWord.DirectoryPath = strDirPath;
            //OfficeWord.SearchFilter = strExt;

            //OfficeWord.CreateApplication();
            //OfficeWord.OpenDocuments(OfficeWord);

            //OfficeWord.CloseApplication();

            //AbstractOffice OfficeExel = null;
            //officeFactory = new ExcelFactory();
            //OfficeExel = officeFactory.CreateOffice();
            //OfficeExel.CreateApplication();
            //OfficeExel.DirectoryPath = strDirPath;
            //OfficeExel.SearchFilter = "*.xls";
            //OfficeExel.OpenDocuments(OfficeExel);
            //OfficeExel.CloseApplication();



            AbstractOffice PowerPoint = null;
            officeFactory = new PowerPointFactory();
            PowerPoint = officeFactory.CreateOffice();
            PowerPoint.DirectoryPath = strDirPath;
            PowerPoint.SearchFilter = "*.pptx";
            PowerPoint.CreateApplication();
            PowerPoint.OpenDocuments(PowerPoint);
            PowerPoint.CloseApplication();

            //FileManager fileManager = new FileManager();
            //fileManager.MoveFiles(strDirPath, enFileStatus.enGoodFile);
            //bool bResult = false;
            //while (true)
            //{
            //    Console.WriteLine();
            //    Console.WriteLine();
            //    Console.WriteLine("Move *.bad_file to Directory (\"BadFiles\")");
            //    Console.WriteLine("Type \"y\"-[YES], \"n\"-[NO]");
            //    ConsoleKeyInfo iKeyInfo = Console.ReadKey();
            //    if (iKeyInfo.Key == ConsoleKey.Y )
            //    {
            //        bResult = true;
            //        break;
            //    }
            //    else
            //        if (iKeyInfo.Key == ConsoleKey.N)
            //        {
            //            bResult = false;
            //            break;
            //        }


            //}
            //if (bResult == true)
            //    fileManager.MoveFiles(strDirPath, enFileStatus.enBadFile);
            Console.WriteLine("\nFinish Testing ...");
            Console.WriteLine("Press any key to QUIT");
            Console.ReadKey();
        }
    }
}
