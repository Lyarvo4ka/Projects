using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.IO;
using System.Runtime.InteropServices;

namespace WorkWithFiles
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        static extern IntPtr CreateFile(
                        string filename,
                        [MarshalAs(UnmanagedType.U4)]FileAccess fileaccess,
                        [MarshalAs(UnmanagedType.U4)]FileShare fileshare,
                        int securityattributes,
                        [MarshalAs(UnmanagedType.U4)]FileMode creationdisposition,
                        int flags,
                        IntPtr template);

        private void button1_Click(object sender, EventArgs e)
        {
            //CreateFile
            CreateFile("c:\\One.txt",FileAccess.Write,FileShare.Write,0,FileMode.Create,0,IntPtr.Zero);

        }
    }
}
