using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;

namespace OfficeChecker
{
    public enum ProgramState : byte
    {
        STOP = 1,
        START = 2,
    }
    public partial class uiOfficeChecker : Form
    {
        public uiOfficeChecker()
        {
            InitializeComponent();
            //Assembly.LoadFile()

            m_SearchMarker = new SearchMaker();
            m_SearchMarker.m_Office_2003 = new SelectedOffice();
            m_SearchMarker.m_Office_2003.SelectAll(true);
            m_SearchMarker.m_Office_2007 = new SelectedOffice();
            m_SearchMarker.m_Office_2007.SelectAll(true);
            m_SearchMarker.SelectRTF(true);
            uiProgressBar.Value = 0;
            m_OfficeList = new List<AbstractOffice>();
            OfficeFactory FactoryOffice;
            FactoryOffice = new WordFacroty();
            AbstractOffice _abstractOffice;

            _abstractOffice = FactoryOffice.CreateOffice();
            ProgressObserver progressWord = new ProgressObserver(_abstractOffice);
            progressWord.EventUpdate += new ProgressObserver.UpdateProgress(UpdateProgress);
            RemainingObserver remainingWord = new RemainingObserver(_abstractOffice);
            remainingWord.EventRemaining += new RemainingObserver.UpdateRemaining(UpdateWordRemaining);
            PrintFileNameObserver showWordFile = new PrintFileNameObserver(_abstractOffice);
            showWordFile.EventShowCurrentName += new PrintFileNameObserver.ShowCurrentName(PrintWordFileName);
            m_OfficeList.Add(_abstractOffice);
            FactoryOffice = new ExcelFactory();

            _abstractOffice = FactoryOffice.CreateOffice();
            ProgressObserver progressExcel = new ProgressObserver(_abstractOffice);
            progressExcel.EventUpdate += new ProgressObserver.UpdateProgress(UpdateProgress);
            RemainingObserver remainingExcel = new RemainingObserver(_abstractOffice);
            remainingExcel.EventRemaining += new RemainingObserver.UpdateRemaining(UpdateExcelRemaining);
            PrintFileNameObserver showExcelFile = new PrintFileNameObserver(_abstractOffice);
            showExcelFile.EventShowCurrentName += new PrintFileNameObserver.ShowCurrentName(PrintExcelFileName);
            m_OfficeList.Add(_abstractOffice);
            m_ProgramState = ProgramState.STOP;
            //WordCounter CountWord = WordCounter.getInstance();
            FileCounter WordCounter = FileCounter.GetInstance(OfficeType.msWord);
            FileCounter ExcelCounter = FileCounter.GetInstance(OfficeType.msExcel);
            m_BadFiles = BADFILES.Rename;


        }

        public delegate void ProgressHandler(int _incProgress);
        public delegate void AddTextReport(string _strReport);
        public delegate void MaxProgressHandler(int _iMaxProgress);
        public delegate void RemainingFiles(int _Remaining);
        public delegate void PrintFileName(string fileName );
       // public event ProgressHandler UpdateProgressEvent;

        private bool FindWord(AbstractOffice _abstractOffice)
        {
            return (_abstractOffice.GetOfficeType() == OfficeType.msWord);
        }
        private bool FindExcel(AbstractOffice _abstractOffice)
        {
            return (_abstractOffice.GetOfficeType() == OfficeType.msExcel);
        }
        private bool FindPowerPoint(AbstractOffice _abstractOffice)
        {
            return (_abstractOffice.GetOfficeType() == OfficeType.msPowerPoint);
        }

        public void UpdateProgress(int _progress)
        {
            if (this.uiProgressBar.InvokeRequired)
                this.uiProgressBar.Invoke(new ProgressHandler(UpdateProgress), _progress);
            else
            {
                this.uiProgressBar.Value = _progress;
                if (ProgressCounter.Progress.isFinish())
                {
                    this.m_ProgramState = ProgramState.STOP;
                    this.UpdateSTARTButton();
                    this.RenameFiles();
                    MessageBox.Show("The program has finished test office files.");
                }
            }
        }
        private void RenameFiles()
        {
            FileWorker fileWorker = new FileWorker();
            fileWorker.OperateFiles(this.m_strDirPath, OpenStatus.OpenGOOD ,this.m_BadFiles);
            fileWorker.OperateFiles(this.m_strDirPath, OpenStatus.OpenBAD, this.m_BadFiles);
        }
        public void UpdateText(string _Text)
        {
            //if (this.uiReportTXT.InvokeRequired)
            //    this.uiReportTXT.Invoke(new AddTextReport(UpdateText), _Text);
            //else
            //    this.uiReportTXT.AppendText(_Text);
        }
        public void UpdateMaxProgress(int _iMaxProgress)
        {
            if (this.uiProgressBar.InvokeRequired)
                this.uiProgressBar.Invoke(new MaxProgressHandler(UpdateMaxProgress), _iMaxProgress);
            else
                this.uiProgressBar.Maximum = _iMaxProgress;
        }
        public void UpdateWordRemaining(int _iWordRemainig)
        {
            if (uiRemainWord.InvokeRequired)
                this.uiRemainWord.Invoke(new RemainingFiles(UpdateWordRemaining), _iWordRemainig);
            else
                this.uiRemainWord.Text = _iWordRemainig.ToString();
        }
        public void UpdateExcelRemaining(int _iRemainig)
        {
            if (uiRemainExcel.InvokeRequired)
                this.uiRemainExcel.Invoke(new RemainingFiles(UpdateExcelRemaining), _iRemainig);
            else
                this.uiRemainExcel.Text = _iRemainig.ToString();
        }
        public void PrintWordFileName(string fileName)
        {
            if (fileNameWord.InvokeRequired)
                this.fileNameWord.Invoke(new PrintFileName(PrintWordFileName), fileName);
            else
                this.fileNameWord.Text = fileName;
        }
        public void PrintExcelFileName(string fileName)
        {
            if (fileNameExcel.InvokeRequired)
                this.fileNameExcel.Invoke(new PrintFileName(PrintExcelFileName), fileName);
            else
                this.fileNameExcel.Text = fileName;
        }

        //        public void 

        private string m_strDirPath;
        private SearchMaker m_SearchMarker;
        private int m_iTimeOut;
        private ProgramState m_ProgramState;
        private BADFILES m_BadFiles;

        private void uiOpen_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dirBrowse = new FolderBrowserDialog();
            dirBrowse.RootFolder = Environment.SpecialFolder.MyComputer;
            DialogResult dirResult = dirBrowse.ShowDialog();
            if (dirResult == DialogResult.OK)
            {
                m_strDirPath = dirBrowse.SelectedPath;
                //this.EditDirPath.Text = strDirPath;
                this.uiFolderPath.Text = m_strDirPath;
            }
        }

        private void uiFolderPath_TextChanged(object sender, EventArgs e)
        {
            m_strDirPath = this.uiFolderPath.Text;
        }

        private void UpDateCheck(OfficeVersion _officeVersion, bool _bStatus)
        {
            switch (_officeVersion)
            {
                case OfficeVersion.Office2003:
                    m_SearchMarker.m_Office_2003.SelectAll(_bStatus);
                    this.uiWord2003check.Checked = _bStatus;
                    this.uiExcel2003Check.Checked = _bStatus;
                    this.uiPowerPoint2003Check.Checked = _bStatus;
                    break;
                case OfficeVersion.Office2007:
                    m_SearchMarker.m_Office_2007.SelectAll(_bStatus);
                    this.uiWord2007check.Checked = _bStatus;
                    this.uiExcel2007Check.Checked = _bStatus;
                    this.uiPowerPoint2007Check.Checked = _bStatus;
                    break;
                default:
                    Console.WriteLine("Error it's bag. Never calling");
                    break;
            }
        }

        private List<AbstractOffice> m_OfficeList;

        private void uiSTART_Click(object sender, EventArgs e)
        {
            if (!System.IO.Directory.Exists(m_strDirPath))
            {
                string message = "Directory is not Exist!!!";
                string caption = "Error Directory not Find";
                MessageBox.Show(message, caption, MessageBoxButtons.OK);
                return;
            }
            m_iTimeOut = Convert.ToInt32(this.uiTextTimeOut.Text);
            if (!this.uiEnableTimeOut.Checked)
                m_iTimeOut = 0;
            //-------------------------------------------------------------------------//

            m_ProgramState = ProgramState.START;
            this.UpdateSTARTButton();
            //// Starting Checking Documents...
            OfficeVersion officeVersion;
            List<OfficeVersion> listOfficeVersion = new List<OfficeVersion>();

            ProgressCounter _Progress = ProgressCounter.Progress;
            _Progress.ToDefault();
            FileCounter.GetInstance(OfficeType.msWord).ToDefault();
            FileCounter.GetInstance(OfficeType.msExcel).ToDefault();
            // Starting Testing Microsoft Word
            officeVersion = m_SearchMarker.GetWordVersion();
            if (officeVersion != OfficeVersion.NoOffice)
                listOfficeVersion.Add(officeVersion);
            officeVersion = m_SearchMarker.GetRTF();
            if (officeVersion != OfficeVersion.NoOffice)
                listOfficeVersion.Add(officeVersion);

            bool bPasswdChecked = passwdCheck.Checked;


            if (listOfficeVersion.Count > 0)
            {
                AbstractOffice microsofWord = m_OfficeList.Find(FindWord);
                int iFileCount = microsofWord.FindFiles(m_strDirPath, listOfficeVersion);
                if (iFileCount > 0)
                {
                    _Progress.AddMaxProgress(iFileCount);
                    this.UpdateMaxProgress(_Progress.MaxProgress);
                    FileCounter WordCounter = FileCounter.GetInstance(OfficeType.msWord);
                    WordCounter.Total = iFileCount;
                    //                    m_updateData.AddWord(iFileCount);
                    //microsofWord.
                    microsofWord.Run(m_iTimeOut);
                }
                else
                {
                    string caption = "Word Document";
                    string message = "Program didn't find any word documents.";
                    MessageBox.Show(message, caption, MessageBoxButtons.OK);
                }
            }

            //System

            // Starting Testing Microsoft Excel
            listOfficeVersion.Clear();
            officeVersion = m_SearchMarker.GetExcelVersion();
            if (officeVersion != OfficeVersion.NoOffice)
                listOfficeVersion.Add(officeVersion);

            if (listOfficeVersion.Count > 0)
            {
                AbstractOffice microsofExcel = m_OfficeList.Find(FindExcel);
                if (microsofExcel != null)
                {

                    int iFileCount = microsofExcel.FindFiles(m_strDirPath, listOfficeVersion);
                    if (iFileCount > 0)
                    {
                        _Progress.AddMaxProgress(iFileCount);
                        this.UpdateMaxProgress(_Progress.MaxProgress);
                        FileCounter ExcelCounter = FileCounter.GetInstance(OfficeType.msExcel);
                        ExcelCounter.Total = iFileCount;
                        microsofExcel.Run(m_iTimeOut);
                    }
                    else
                    {
                        string caption = "Excel Document";
                        string message = "Program didn't find any excel documents.";
                        MessageBox.Show(message, caption, MessageBoxButtons.OK);
                    }

                }
            }

            if (ProgressCounter.Progress.isFinish())
            {
                m_ProgramState = ProgramState.STOP;
                UpdateSTARTButton();
            }
        }
        private void uiSTOP_Click(object sender, EventArgs e)
        {
            AbstractOffice microsofWord = m_OfficeList.Find(FindWord);
            if (microsofWord != null)
                microsofWord.Stop();
            AbstractOffice microsoftExcel = m_OfficeList.Find(FindExcel);
            if (microsoftExcel != null)
                microsoftExcel.Stop();
            m_ProgramState = ProgramState.STOP;
            this.UpdateSTARTButton();
        }
        private void UpdateSTARTButton()
        {
            if (m_ProgramState == ProgramState.STOP)
            {
                uiSTART.Enabled = true;
                this.uiFolderPath.Enabled = true;
            }
            else
            {
                uiSTART.Enabled = false;
                this.uiFolderPath.Enabled = false;
            }

        }

        private void uiCheckAll2003_CheckedChanged(object sender, EventArgs e)
        {
            UpDateCheck(OfficeVersion.Office2003, this.uiCheckAll2003.Checked);
        }

        private void uiCheckAll2007_CheckedChanged(object sender, EventArgs e)
        {
            UpDateCheck(OfficeVersion.Office2007, this.uiCheckAll2007.Checked);
        }

        private void uiWord2003check_CheckedChanged(object sender, EventArgs e)
        {
            m_SearchMarker.m_Office_2003.SelectWord(uiWord2003check.Checked);
        }

        private void uiWord2007check_CheckedChanged(object sender, EventArgs e)
        {
            m_SearchMarker.m_Office_2007.SelectWord(uiWord2007check.Checked);
        }

        private void uiExel2003Check_CheckedChanged(object sender, EventArgs e)
        {
            m_SearchMarker.m_Office_2003.SelectExcel(uiExcel2003Check.Checked);
        }

        private void uiExel2007Check_CheckedChanged(object sender, EventArgs e)
        {
            m_SearchMarker.m_Office_2007.SelectExcel(uiExcel2007Check.Checked);
        }

        private void uiPowerPoint2003Check_CheckedChanged(object sender, EventArgs e)
        {
            m_SearchMarker.m_Office_2003.SelectPowerPoint(uiPowerPoint2003Check.Checked);
        }

        private void uiPowerPoint2007Check_CheckedChanged(object sender, EventArgs e)
        {
            m_SearchMarker.m_Office_2007.SelectPowerPoint(uiPowerPoint2007Check.Checked);
        }

        private void uiRTFcheck_CheckedChanged(object sender, EventArgs e)
        {
            m_SearchMarker.SelectRTF(uiRTFcheck.Checked);
        }

        private void uiTextTimeOut_KeyPress(object sender, KeyPressEventArgs e)
        {
            if ((e.KeyChar < 48 || e.KeyChar > 57) && e.KeyChar != 8)
            {
                //MessageBox.Show("Only Digit!");
                e.Handled = true;
            }
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            m_BadFiles = BADFILES.Rename;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            m_BadFiles = BADFILES.Remove;
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            m_BadFiles = BADFILES.Move;
        }

        private void uiEnableTimeOut_CheckedChanged(object sender, EventArgs e)
        {
            this.uiTextTimeOut.Enabled = this.uiEnableTimeOut.Checked;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }
    }
}
