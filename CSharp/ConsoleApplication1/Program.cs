using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;




namespace ConsoleApplication1
{


class Program
    {
        static void Main(string[] args)
        {
            string ext = ".docx";
            string path = @"d:\LongPathFolder\";
            FileFilder finder = new FileFilder();
            finder.addExtension(ext);
            finder.FindFileRecurcive(path);
           
        }

    }
}
