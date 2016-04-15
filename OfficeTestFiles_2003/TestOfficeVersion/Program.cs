using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Reflection;

namespace TestOfficeVersion
{
    class TestVersion
    {
        private Microsoft.Office.Interop.Word.Document m_DocWord;
        private Microsoft.Office.Interop.Excel.Application m_AppExcel;

        public void Execute()
        {
            //Assembly.Load("Microsoft.Office.Interop.Word.dll");
            //Assembly.Load("Microsoft.Office.Interop.Excel.dll");
            //Assembly WordAssembly = Assembly.LoadFile("Microsoft.Office.Interop.Word.dll");
            //Assembly ExcelAssembly = Assembly.LoadFile("Microsoft.Office.Interop.Excel.dll");
            Microsoft.Office.Interop.Word.Application m_AppWord = new Microsoft.Office.Interop.Word.Application();
            Microsoft.Office.Interop.Word.Document m_DocWord = new Microsoft.Office.Interop.Word.Document();
            m_DocWord = m_AppWord.Documents.Add();
            string strVersion = m_AppWord.Version;
            Console.WriteLine("AppDomain Name : {0}", System.AppDomain.CurrentDomain.FriendlyName);
            System.Console.WriteLine("Word version is : {0}", strVersion);
            AppDomain myDomain = AppDomain.CurrentDomain;
            Assembly[] LoadedAssemblies = myDomain.GetAssemblies();
            foreach (Assembly CurrentAssembly in LoadedAssemblies)
            {
                //Console.WriteLine("Loaded {0}", CurrentAssembly.FullName);
                Console.WriteLine("Loaded {0}", CurrentAssembly.Location);
                Console.WriteLine("");
            }

            Console.WriteLine("Get Referenced Assemblies");
            Assembly a = Assembly.GetExecutingAssembly();
            foreach (AssemblyName an in a.GetReferencedAssemblies())
            {
                Console.WriteLine(an.FullName);
            }
            //LoadedAssemblies = myDomain.
            Console.WriteLine("");
            Console.WriteLine("Press any key...");
            System.Console.ReadKey();
            m_AppWord.Quit();

            Console.Write("Directory: ");
            string strDirPath = Console.ReadLine();
            string[] strFilePath = Directory.GetFiles(strDirPath, "*.xls", SearchOption.AllDirectories);

            Microsoft.Office.Interop.Excel.Workbook m_BookExcel;

            System.IO.StreamWriter fileReport = new System.IO.StreamWriter("Report.txt");

            Microsoft.Office.Interop.Excel.Application m_AppExcel = new Microsoft.Office.Interop.Excel.Application();

            foreach (string strFile in strFilePath)
            {
                object fileName = strFile;
                try
                {
                    m_BookExcel = m_AppExcel.Workbooks.Open(strFile,
                                                            UpdateLinks: 2,
                                                            ReadOnly: true,
                                                            Password: "XYU");
                    string strReport = strFile;
                    strReport += " - Open OK";
                    fileReport.WriteLine(strReport);
                    System.Console.WriteLine(strReport);
                }
                catch (System.Runtime.InteropServices.COMException ex)
                {
                    string strReport = strFile;
                    strReport += " - (";
                    strReport += ex.ErrorCode.ToString();
                    strReport += ") - ";
                    strReport += ex.Message;
                    fileReport.WriteLine(strReport);
                    Console.WriteLine(strReport);
                }

            }
            m_AppExcel.Quit();
            KillExelProcess();
            fileReport.Close();
            Console.WriteLine("Press any key...");
            System.Console.ReadKey();
        }
        private void KillExelProcess()
        {
            System.Diagnostics.Process[] NoClosedProcess;
            NoClosedProcess = System.Diagnostics.Process.GetProcessesByName("excel");
            foreach (System.Diagnostics.Process exelProcess in NoClosedProcess)
            {
                exelProcess.Kill();
            }

        }
     
    }
    class Program
    {
        static void Main(string[] args)
        {
            TestVersion testVer = new TestVersion();
            testVer.Execute();
        }
    }
}
