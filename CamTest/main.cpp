#include "camtest.h"
#include <QtWidgets/QApplication>
#include <QCamera>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


		//CoInitialize ( NULL );
		//CAcroPDDoc * pAcroPdDoc = new CAcroPDDoc();

		//CString pdfPath = "c:\\simple.pdf";

		//if (!AfxOleInit())	{
		//	AfxMessageBox("OLE initialization failed in BasicIacVc sample.");
		//	return FALSE;
		//}

		//// === Create an Acrobat IAC PDDoc object  
		//COleException e;
		//BOOL bCreate = pAcroPdDoc->CreateDispatch("AcroExch.PDDoc", &e);
		//if(!bCreate) {
		//	AfxMessageBox("Creating Acrobat IAC object failed in BasicIacVc sample.");
		//	return FALSE;
		//}
	
		//// === Open a pdf file.  

		//if(!pAcroPdDoc->Open(pdfPath)) {
		//	CString message = "Opening the PDF file \"";
		//	message += pdfPath;
		//	message += "\" failed in the BasicIacVc sample.";
		//	AfxMessageBox(message);
		//	return FALSE;
		//}

		//// === Get the number of pages, and compose a massage.  
		//char str[256];
		//sprintf_s(str,"PDF document %s is loaded in Acrobat through IAC program.\n",pdfPath);
		//long n = pAcroPdDoc->GetNumPages();

		//CString date = pAcroPdDoc->GetInfo("ModDate");

		//VARIANT_BOOL saved_ok = pAcroPdDoc->Save( PDSaveFull , "c:\\detected.pdf" );
		//if ( !saved_ok )
		//{
		//	sprintf_s(str, "Document is corrupted." );
		//
		//}

		//if(n!=-1) 
		//	sprintf_s(str, "%sThe PDF file has %d pages.", str, n);
		//else
		//	sprintf_s(str, "Error in getting page number.");
	
		//// message
		//AfxEnableControlContainer();
		//AfxMessageBox(str);

		//// === Code to finish program.
		//pAcroPdDoc->Close();
		//delete pAcroPdDoc;
		//pAcroPdDoc = NULL;
		//CoUninitialize();
	//CamTest w;
	//w.show();

	//QCamera *camera;

	//foreach(const QByteArray &dev_name, QCamera::availableDevices()) {
	//	QString desc = QCamera::deviceDescription(dev_name);
	//	camera = new QCamera(dev_name);
	//	if (camera) {
	//		int x = 0;
	//	}
	//}



	return a.exec();
}
