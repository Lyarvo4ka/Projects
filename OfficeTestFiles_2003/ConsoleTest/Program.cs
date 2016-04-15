using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace ConsoleTest
{
    class Test1
    {
        public delegate void UpdateDelegate(int i);
        public event UpdateDelegate EventUpdate;
        public void Update()
        {
            for (int i = 0; i < 100; ++i)
                EventUpdate(i);
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Test1 t1 = new Test1();
            t1.EventUpdate += new Test1.UpdateDelegate(Update);
            // m_thread = new Thread(new ThreadStart(this.ThreadOpenExcel));
            Thread thread1 = new Thread(new ThreadStart(t1.Update));
            Thread thread2 = new Thread(new ThreadStart(t1.Update));
            thread1.Start();
            thread2.Start();
            thread1.Join();
            thread2.Join();
            Console.ReadKey();
        }
        public static void Update(int _iVal)
        {
            Console.WriteLine(_iVal.ToString());
        }
    }
}
