using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Outlook = Microsoft.Office.Interop.Outlook;
using System.IO;

namespace Import_VCF_to_Outlook
{
    class Program
    {
        static void Main(string[] args)
        {
            Program outLook = new Program();
            string path = "E:\\ss-Backup-0001\\contact\\";
            outLook.ImportContacts(path);
        }

        static byte[] GetBytes(string str)
        {
            byte[] bytes = new byte[str.Length * sizeof(char)];
            System.Buffer.BlockCopy(str.ToArray(), 0, bytes, 0, bytes.Length);
            return bytes;
        }

    public void ImportContacts(string path)
    {
    Outlook.ContactItem contact;
    Outlook.ContactItem moveContact;
    Outlook.Application app = new Outlook.Application();
    if (Directory.Exists(path))
    {
        string[] files = Directory.GetFiles(path, "*.vcf");
        foreach (string file in files)
        {
            contact = (Outlook.ContactItem)app.Session.OpenSharedItem(file)
                as Outlook.ContactItem;
            Outlook.Folder targetFolder = (Outlook.Folder) app.Session.GetDefaultFolder(Outlook.OlDefaultFolders.olFolderContacts) ;
            if ( targetFolder != null )
            {
                Encoding utf8 = Encoding.UTF8;
                Encoding ascii = Encoding.ASCII;
                
                string str = contact.FullName;

                //Encoding encode = Encoding.GetEncoding(str);
                byte[] utf8_str = Encoding.Default.GetBytes(str);

                byte[] converted_bytes = Encoding.Convert(Encoding.UTF8, Encoding.Default, utf8_str);

                string src_data = Encoding.Default.GetString(converted_bytes);
                contact.FullName = src_data;
                contact.Save();
            }
            else
            {
                moveContact = contact.Move(targetFolder)
                    as Outlook.ContactItem;
                moveContact.Save();
            }
        }
    }
    }

    }
}
