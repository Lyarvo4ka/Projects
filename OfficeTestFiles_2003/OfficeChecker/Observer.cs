using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace OfficeChecker
{
    class ProgressCounter
    {
        Object m_LockMax = new Object();
        Object m_LockCount = new Object();
        public bool isFinish()
        {
            if (MaxProgress == this.Count)
                return true;
            return false;
        }
        protected ProgressCounter()
        {
            ToDefault();
        }
        static readonly ProgressCounter m_instance = new ProgressCounter();
        public static ProgressCounter Progress
        {
            get { return m_instance;}
        }
        public void AddProgress()
        {
            Interlocked.Increment(ref m_CountProgress);
            //lock (m_LockCount)
            //{
            //    ++m_CountProgress;
            //}
        }
        public int Count
        {
            get {
                int iCount = 0;
                lock (m_LockCount)
                {
                    iCount = m_CountProgress;
                }
                return iCount;
            }
        }
        private int m_CountProgress;
        public void AddMaxProgress(int _iMax)
        {
            lock (m_LockMax)
            {
                m_MaxProgress += _iMax;
            }
        }
        public void ToDefault()
        {
            m_MaxProgress = 0;
            m_CountProgress = 0;
        }
        public int MaxProgress
        {
            get { return m_MaxProgress; }
        }
        private int m_MaxProgress;
    }

    class Singleton
    {
        protected Singleton()
        {

        }
        public static Singleton getInstance()
        {
            if (_instance == null)
                return new Singleton();
            return _instance;
        }
        private static Singleton _instance;
    }

    class FileCounter 
    {
        protected FileCounter()
        {}
        public int Total
        {
            get { return m_iTotalFiles; }
            set { m_iTotalFiles = value; }
        }
        public int RemainingFiles
        {
            get { return m_iRemainingFiles; }
        }
        public int CheckedFiles
        {
            get { return m_iCheckedFiles; }
        }
        public void ToDefault()
        {
            m_iCheckedFiles = 0;
            m_iTotalFiles = 0;
            m_iRemainingFiles = 0;
        }
        public void Increment()
        {
            ++m_iCheckedFiles;
            m_iRemainingFiles = m_iTotalFiles - m_iCheckedFiles;
        }

        private int m_iTotalFiles;
        private int m_iRemainingFiles;
        private int m_iCheckedFiles;
        public static FileCounter GetInstance(OfficeType _OfficeType)
        {
            switch (_OfficeType)
            {
                case OfficeType.msWord:
                    if (_instanceWord == null)
                        _instanceWord = new FileCounter();
                    return _instanceWord;
                case OfficeType.msExcel:
                    if (_instanceExcel == null)
                        _instanceExcel = new FileCounter();
                    return _instanceExcel;
                default:
                    return null;
            }
        }
        private static FileCounter _instanceWord;
        private static FileCounter _instanceExcel;
    }

    //class WordCounter : FileCounter
    //{
    //    protected WordCounter(){}
    //}
    //class ExcelConter : FileCounter
    //{
    //    protected ExcelConter(){}
    //}
    abstract class Subject
    {
        protected Subject()
        {
            m_ObserverList = new List<Observer>();
        }
        public virtual void Attach(Observer _Observer)
        {
            m_ObserverList.Add(_Observer);
        }
        public virtual void Deatch(Observer _Observer)
        {
            m_ObserverList.Remove(_Observer);
        }
        public virtual void Notify(string file)
        {

        }
        public virtual void Notify()
        {
            if (m_ObserverList != null)
            foreach (Observer observer in m_ObserverList)
            {
                observer.Update(this);
            }
        }
        private List<Observer> m_ObserverList;
    }
    //class 
    abstract class Observer
    {
        protected Observer()
        {

        }
        public abstract void Update(Subject _subject);
    }

    class PrintFileNameObserver : Observer
    {
        private AbstractOffice m_Subject;

        public delegate void ShowCurrentName(string fileName);
        public event ShowCurrentName EventShowCurrentName;

        public PrintFileNameObserver(AbstractOffice _abstractOffice)
        {
            m_Subject = _abstractOffice;
            m_Subject.Attach(this);
        }

        public override void Update(Subject _subject)
        {
            if (m_Subject == _subject)
            {

                EventShowCurrentName(m_Subject.GetFileName());
            }

        }
    }
    class ProgressObserver : Observer
    {
        public delegate void UpdateProgress(int _iProgressPosition);
        public event UpdateProgress EventUpdate;
        public ProgressObserver(AbstractOffice _abstractOffice)
        {
            m_Subject = _abstractOffice;
            m_Subject.Attach(this);

        }

        public override void Update(Subject _subject)
        {
            if (m_Subject == _subject)
            {
                ProgressCounter _Progress = ProgressCounter.Progress;
                _Progress.AddProgress();
                EventUpdate(_Progress.Count);
            }
        }



        private AbstractOffice m_Subject;
    }
    class RemainingObserver : Observer
    {
        public RemainingObserver(AbstractOffice _abstractOffice)
        {
            m_Subject = _abstractOffice;
            m_Subject.Attach(this);
        }
        public delegate void UpdateRemaining(int _iRemainingFiles);
        public event UpdateRemaining EventRemaining;
        public override void Update(Subject _subject)
        {
            if (m_Subject == _subject)
            {

                OfficeType TypeOffice = m_Subject.GetOfficeType();
                switch (TypeOffice)
                {
                    case OfficeType.msWord:
                        FileCounter WordCounter = FileCounter.GetInstance(OfficeType.msWord);
                        WordCounter.Increment();
                        EventRemaining(WordCounter.RemainingFiles);

                        break;
                    case OfficeType.msExcel:
                        FileCounter ExcelCounter = FileCounter.GetInstance(OfficeType.msExcel);
                        ExcelCounter.Increment();
                        EventRemaining(ExcelCounter.RemainingFiles);
                        break;
                }


            }
        }
        private AbstractOffice m_Subject;
    }
    //class OpenObserver : Observer
    //{
    //    public OpenObserver(AbstractOffice _abstractOffice)
    //    {

    //    }
    //    private AbstractOffice m_Subject;
    //}
/*
    class UpdateObserver
    {
        public UpdateObserver()
        {
            iCountTested = 0;
        }

        private Object m_locker = new Object();
        private Object m_lockUpdate = new Object();
        private Object m_lockFiles = new Object();
        private int m_iMaxFiles;

        private int iCountTested;
        public void AddWord(int _iWord)
        {
            lock (m_locker)
            {
                m_iMaxFiles += _iWord;
                UpdateMaxProgress();
            }
        }
        public void AddExel(int _iExel)
        {
            lock (m_locker)
            {
                m_iMaxFiles += _iExel;
                UpdateMaxProgress();
            }
        }
        public void AddPowerPoint(int _iPowerPoint)
        {
            lock (m_locker)
            {
                m_iMaxFiles += _iPowerPoint;
                UpdateMaxProgress();
            }
        }
        public void Update(AbstractOffice _office)
        {
            //if (_office is MicrosoftWord)

            lock (m_lockUpdate)
            {
                string FileName = _office.GetFileName();
                OpenStatus openStatus = _office.GetOpenStatus();
                Console.WriteLine("{0} - {1}", FileName, openStatus.ToString());
                ++iCountTested;
                if (m_uiInterface != null)
                {
                    string strText = FileName + " - " + openStatus.ToString() + "\r\n";
                    m_uiInterface.UpdateProgress(iCountTested);
                    m_uiInterface.UpdateText(strText);
                }
            }
        }
        public void setFrom(uiOfficeChecker _uiInterface)
        {
            m_uiInterface = _uiInterface;
        }
        private void UpdateMaxProgress()
        {
            if (m_uiInterface != null)
            {
                if (m_iMaxFiles > 0)
                    m_uiInterface.UpdateMaxProgress(m_iMaxFiles);
            }
        }
        private uiOfficeChecker m_uiInterface;
    }
*/
}

