using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.IO;
using System.Threading;


using Microsoft.Office.Interop.Word;



namespace OfficeTestFiles
{
    public partial class OfficeTester : Form
    {

        public delegate void ProgressHandler(int incProgress);
        public delegate void ProgressVisible(bool _bShow);
        public delegate void EditTextHandler(string _iStrText);
        public delegate void SetMaxProgress(int _iProgress);
        public delegate void setCountWordUpdate(int _iFilesRemained);
        public delegate void setCountExelUpdate(int _iFilesRemained);
        
        public OfficeTester()
        {
            InitializeComponent();
        }

        static string strDirPath;

        public static string[] GetFiles(string _path, string _searchPattern, SearchOption _seachOptional)
        {
            string[] searchExt = _searchPattern.Split('|');
            List<string> files = new List<string>();

            foreach (string extPattern in searchExt )
            {
                files.AddRange( Directory.GetFiles(_path,extPattern,_seachOptional) );
            }
            files.Sort();
            return files.ToArray();

        }

        public event ProgressHandler Progress;
        public event EditTextHandler AddText;

        public void ThreadFunc()
        {
            if (strDirPath != "")
            {

                // Find Microsoft Word Files
                if (checkWord.Checked)
                {
                    // |*.docx
                    string filter = "*.doc|*.rtf";
                    ProgressShows(true);

                   // string[] strDocFiles = Directory.GetFiles(strDirPath, filter, SearchOption.AllDirectories);
                    string[] strDocFiles = GetFiles(strDirPath, filter, SearchOption.AllDirectories);

                    int iFindFiles = strDocFiles.GetLength(0);
                    if (iFindFiles > 0)
                    {
                        this.SetProgressMaxValue(iFindFiles);
                        this.SetRemainedWordFiles(iFindFiles);
                        // Microsoft.Office.Interop.Excel.Application exel = new Microsoft.Office.Interop.Excel.Application();

                        Microsoft.Office.Interop.Word.Application word = new Microsoft.Office.Interop.Word.Application();
                        Microsoft.Office.Interop.Word.Document doc = null;

                        int iProgressPos = 1;
                        foreach (string strCurrentFile in strDocFiles)
                        {
                            try
                            {
                                doc = null;
                                object fileName = strCurrentFile;
                                object missing = System.Reflection.Missing.Value;
                                object falseValue = false;
                                object trueValue = true;
                                object EmptyString = "";
                                //word.Application.Visible = true;

                                Console.Write("File Name : ");
                                Console.WriteLine(strCurrentFile);
                                word.Visible = false;

                                this.EditText("File : ");
                                this.EditText(strCurrentFile);
                                doc = word.Documents.Open(ref fileName,
                                                          ReadOnly: true,
                                                          Visible: false,
                                                          OpenAndRepair: true,
                                                          ConfirmConversions: false,
                                                          Encoding: false,
                                                          Revert: false,
                                                          NoEncodingDialog: true,
                                                          Format: WdOpenFormat.wdOpenFormatAuto
                                    //WritePasswordDocument: "",
                                    //PasswordDocument: ""
                                                      );

                                //  string docName = doc.Application.Name;
                                // doc.Activate();
                                doc.Close(SaveChanges: WdSaveOptions.wdDoNotSaveChanges);
                                this.EditText(" -- Open OK\n");
                                try
                                {
                                    System.IO.File.Move(strCurrentFile, strCurrentFile + ".good");
                                }
                                catch (Exception ex)
                                {
                                    word.Application.Quit();
                                    Thread.Sleep(1000);
                                    System.IO.File.Move(strCurrentFile, strCurrentFile + ".good");
                                    word = new Microsoft.Office.Interop.Word.Application();
                                }
                                doc = null;


                            }
                            catch (System.Runtime.InteropServices.COMException ex)
                            {

                                // "Word was unable to read this document.  It may be corrupt.\nTry one or more of the following:\n* Open and Repair the file.\n* Open the file with the Text Recovery converter.\r (D:\\TEST\\BAD\\1\\00236.doc)"
                                //   Console.WriteLine("Error #\r\n", ex);
                                switch (ex.ErrorCode)
                                {
                                    case -2146822307:

                                        this.EditText(" -- Open GOOD \n");

                                        if (word.Documents.Count > 0)
                                        {
                                            word.Documents.Add(Visible: true);
                                            word.Documents.Close(SaveChanges: false);
                                            word.Documents.Add(Visible: false);
                                            System.IO.File.Move(strCurrentFile, strCurrentFile + ".good");
                                        }
                                        else
                                            System.IO.File.Move(strCurrentFile, strCurrentFile + ".good");
                                        break;

                                    case -2146822273:

                                        this.EditText(" -- Open with need Repair (");

                                        // this.TextReport.AppendText(ex.Message);
                                        this.EditText(")\n");
                                        // doc = word.ActiveDocument;
                                        word.Documents.Close();
                                        System.IO.File.Move(strCurrentFile, strCurrentFile + ".repair_file");
                                        break;
                                    case -2146822186:
                                    /*
                                      {"Word encountered an error processing the XML file Bad\n
                                        No error detail available"}
                                     */
                                    case -2146823137:
                                    case -2146822890:
                                    case -2146823191:
                                    case -2146824090:
                                    case -2146822494:
                                        
                                    /*      1 - OPEN WITH Error */
                                    case -2146823176:
                                    /* {"There is not enough memory or disk space to complete the operation."}*/
                                    case -2146823167:
                                        /*"Word experienced an error trying to open the file.\n
                                         * Try these suggestions.\n* 
                                         * Check the file permissions for the document or drive.\n* 
                                         * Make sure there is sufficient free memory and disk space.\n* 
                                         * Open the file with the Text Recovery converter.\r)"*/

                                        this.EditText(" -- OPEN BAD");
                                        //this.TextReport.AppendText(ex.Message);
                                        this.EditText("\n");

                                        if (word.Documents.Count > 0)
                                        {
                                            word.Documents.Add(Visible: true);
                                            word.Documents.Close(SaveChanges: false);
                                            word.Documents.Add(Visible: false);
                                            System.IO.File.Move(strCurrentFile, strCurrentFile + ".bad_file");

                                        }
                                        else
                                            System.IO.File.Move(strCurrentFile, strCurrentFile + ".bad_file");


                                        break;
                                    case -2146822880:
                                        /* P A S S W O R D*/
                                        System.IO.File.Move(strCurrentFile, strCurrentFile + ".pass_file");
                                        this.EditText(" -- PASSWORD\n");
                                        if (word.Documents.Count > 0)
                                        {
                                            word.Documents.Add(Visible: true);
                                            word.Documents.Close();
                                            word.Documents.Add(Visible: false);
                                        }

                                        word.Application.Quit();
                                        word = new Microsoft.Office.Interop.Word.Application();
                                        break;

                                    case -2146823156:
                                        // word.Application.Quit(SaveChanges : false);
                                        if (word.Documents.Count > 0)
                                        {
                                            word.Documents.Add(Visible: true);
                                            word.Documents.Close();

                                            this.EditText(" -- OPEN BAD");
                                            System.IO.File.Move(strCurrentFile, strCurrentFile + ".bad_file");
                                            word.Documents.Add(Visible: false);
                                            //word = new Microsoft.Office.Interop.Word.Application();
                                        }
                                        break;


                                    default:
                                        if (word.Documents.Count > 0)
                                        {
                                            word.Documents.Add(Visible: true);
                                            word.Documents.Close();

                                            this.EditText(" -- OPEN BAD");
                                            System.IO.File.Move(strCurrentFile, strCurrentFile + ".bad_file");
                                            word.Documents.Add(Visible: false);
                                            //word = new Microsoft.Office.Interop.Word.Application();
                                        }
                                            Console.WriteLine("Error unknown exception");
                                            break;
                                        
                                }



                                // doc.Close();
                            }
                            finally
                            {
                                // this we never
                            }
                            this.ProcessorProgress(iProgressPos);
                            this.SetRemainedWordFiles(iFindFiles - iProgressPos);
                            ++iProgressPos;

                        }

                        word.Quit();
                        // set Progress Bar to end

                    }
                    else
                    {
                        this.EditText("\nMicrosoft Word (*.doc, *.docx) Files not Found \n");
                        this.SetProgressMaxValue(100);
                        this.ProcessorProgress(100);
                        this.SetRemainedWordFiles(iFindFiles);
                    }
                    Console.WriteLine("\n\n The Program Finished testing Microsoft Word Files (*.doc). \n\n");
                    this.EditText("\n\n The Program Finished testing Microsoft Word Files (*.doc). \n\n");

                } // end Word

                if (checkExel.Checked)
                {
                    string filter = "*.xls";
                    string[] strExelFiles = GetFiles(strDirPath, filter, SearchOption.AllDirectories);

                    int iFindFiles = strExelFiles.GetLength(0);
                    if (iFindFiles > 0)
                    {
                        int iProgressPos = 1;
                        this.SetRemainedExelFiles(iFindFiles);
                        this.SetProgressMaxValue(iFindFiles);
                        Microsoft.Office.Interop.Excel.Application exelApp = new Microsoft.Office.Interop.Excel.Application();
                        Microsoft.Office.Interop.Excel.Workbook exelBook = null;
                        foreach (string strCurrentFile in strExelFiles)
                        {
                            object fileName = strCurrentFile;
                            object missing = System.Reflection.Missing.Value;

                            Console.Write("File Name : ");
                            Console.WriteLine(strCurrentFile);
                            //exelBook.Visible = false;

                            this.EditText("File : ");
                            this.EditText(strCurrentFile);
                            exelBook = null;
                            try
                            {
                                exelBook = exelApp.Workbooks.Open(strCurrentFile,
                                                                  UpdateLinks: 2,
                                                                  ReadOnly: true);
                                exelBook.Close(SaveChanges: false);
                                this.EditText(" -- Open OK\n");
                                System.IO.File.Move(strCurrentFile, strCurrentFile + ".good");
                            }
                            catch (System.Runtime.InteropServices.COMException ex)
                            {
                                switch (ex.ErrorCode)
                                {
                                    case -2146827284:
                                        // exelBook.Close(SaveChanges: false);
                                        this.EditText(" -- Open OK\n");
                                        System.IO.File.Move(strCurrentFile, strCurrentFile + ".bad_file");

                                        break;
                                }

                            };

                            exelApp.Quit();
                            this.ProcessorProgress(iProgressPos);
                            SetRemainedExelFiles(iFindFiles - iProgressPos);
                            ++iProgressPos;
                        }

                    }
                    else
                    {
                        this.EditText("\nMicrosoft Exel (*.xls) Files not Found \n");
                    }

                    Console.WriteLine("\n\n The Program Finished testing Microsoft Exel Files (*.xls). \n\n");
                    this.EditText("\n\n The Program Finished testing Microsoft Exel Files (*.xls). \n\n");

                } // end Exel

                if (checkPowerPoint.Checked)
                { 
                    //string[] strPowerPointFiles = Directory.GetFiles(strDirPath, "*.ppt", SearchOption.AllDirectories);
                    //int iFindFiles = strPowerPointFiles.GetLength(0);
                    //if (iFindFiles > 0)
                    //{
                    //    Microsoft.Office.Interop.PowerPoint.Application pptApp = new Microsoft.Office.Interop.PowerPoint.Application();

                    //}
                   
                }// end PowerPoint
            }
            ProgressShows(false);
            const string message = "Finish Testing Office files!!!";
            const string caption = "Window Information";
            this.EditText("\n     !!!  F  I  N  I  S  H  !!! ");
            var result = MessageBox.Show(message, caption);
            
  
        }

        void ProcessorProgress(int _progress)
        {
            if (progressBar1.InvokeRequired)
                progressBar1.Invoke(new ProgressHandler(ProcessorProgress), _progress) ;
            else
                progressBar1.Value = _progress;
        }

        void ProgressShows(bool _bShow)
        {
            if (progressBar1.InvokeRequired)
                progressBar1.Invoke(new ProgressVisible(ProgressShows), _bShow);
            else
            {
                progressBar1.Visible = _bShow;
            }
        }
        void EditText(string _strText)
        {
            if (TextReport.InvokeRequired)
                TextReport.Invoke(new EditTextHandler(EditText),_strText);
            else
                TextReport.AppendText(_strText);
        }

        void SetProgressMaxValue(int _MaxVal)
        { 
            if (progressBar1.InvokeRequired)
                progressBar1.Invoke(new SetMaxProgress(SetProgressMaxValue), _MaxVal);
            else
                progressBar1.Maximum = _MaxVal;
        }

        void SetRemainedWordFiles(int _iFilesRemained)
        {
            if (EditCountWord.InvokeRequired)
                EditCountWord.Invoke(new setCountWordUpdate(SetRemainedWordFiles), _iFilesRemained);
            else
                EditCountWord.Text = _iFilesRemained.ToString();
        }

        void SetRemainedExelFiles(int _iFilesRemained)
        {
            if (EditCountExel.InvokeRequired)
                EditCountExel.Invoke(new setCountExelUpdate(SetRemainedExelFiles), _iFilesRemained);
            else
                EditCountExel.Text = _iFilesRemained.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            strDirPath = this.EditDirPath.Text;
            if (!Directory.Exists(strDirPath))
            {
                string strErrorTxt = "Invalid directory path (";
                strErrorTxt += strDirPath;
                strErrorTxt += ")\n";
                MessageBox.Show(strErrorTxt, "Error select directory");
                return;
            }
            AbstractOffice OfficeWord = null;
            OfficeFactory officeFactory = null;
            officeFactory = new WordFactory();
            OfficeWord = officeFactory.CreateOffice();

            string strExt = "*.doc|*.rtf";

            OfficeWord.DirectoryPath = strDirPath;
            OfficeWord.SearchFilter = strExt;

            OfficeWord.CreateApplication();
            OfficeWord.OpenDocuments(OfficeWord);

            OfficeWord.CloseApplication();

            AbstractOffice OfficeExel = null;
            officeFactory = new ExcelFactory();
            OfficeExel = officeFactory.CreateOffice();
            OfficeExel.CreateApplication();
            OfficeExel.DirectoryPath = strDirPath;
            OfficeExel.SearchFilter = "*.xls";
            OfficeExel.OpenDocuments(OfficeExel);
            OfficeExel.CloseApplication();

            AbstractOffice PowerPoint = null;
            officeFactory = new PowerPointFactory();
            PowerPoint = officeFactory.CreateOffice();
            PowerPoint.DirectoryPath = strDirPath;
            PowerPoint.SearchFilter = "*.ppt";
            PowerPoint.CreateApplication();
            PowerPoint.OpenDocuments(PowerPoint);
            PowerPoint.CloseApplication();


            //Thread ThreadTestDoc = new Thread(ThreadFunc);
            //ThreadTestDoc.Start();

       }


        private void OpenDirDialog_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dirBrowse = new FolderBrowserDialog();
            dirBrowse.RootFolder = Environment.SpecialFolder.MyComputer;
            DialogResult dirResult = dirBrowse.ShowDialog();
            if (dirResult == DialogResult.OK)
            {
                strDirPath = dirBrowse.SelectedPath;
                this.EditDirPath.Text = strDirPath;
            }
            
        }

 
    }
}
