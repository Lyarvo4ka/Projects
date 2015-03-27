// PdfChecker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PdfChecker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "IOLibrary\FileFinder.h"
#include <boost/filesystem.hpp>


CWinApp theApp;

using namespace std;

//bool pdfDateToNormal( const CString & pdfDateStr  , FILETIME * file_time )
//{
//	if ( pdfDateStr.IsEmpty() ) 
//		return false;
//
//
//}


#include "libpdf\Pdfdocument.h"
/*
BOOL CheckPdfFile( const std::string & fileName , const std::string & target_folder )
{
		CAcroPDDoc * pAcroPdDoc = new CAcroPDDoc();



		// === Create an Acrobat IAC PDDoc object  
		COleException e;
		BOOL bCreate = pAcroPdDoc->CreateDispatch("AcroExch.PDDoc", &e);
		if(!bCreate) {
			AfxMessageBox("Creating Acrobat IAC object failed in BasicIacVc sample.");
			return FALSE;
		}
	
		// === Open a pdf file.  

		if( !pAcroPdDoc->Open(fileName.c_str() ) ) {
			printf("File %s Error to open.\r\n" , fileName.c_str() );
			return FALSE;
		}

		CString date = pAcroPdDoc->GetInfo("ModDate");
		printf("File %s has %s\r\n", fileName.c_str() , date ); 

		std::string good_file(fileName + ".good" );

		VARIANT_BOOL saved_ok = pAcroPdDoc->Save( PDSaveFull , good_file.c_str() );
		if ( !saved_ok )
		{
			printf("%s Document is corrupted.\r\n" , fileName.c_str() );
		
		}
		printf("%s Document opened OK.\r\n" , fileName.c_str() );

		// === Code to finish program.
		pAcroPdDoc->Close();
		delete pAcroPdDoc;
		pAcroPdDoc = NULL;

		return TRUE;
}
*/

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		if ( argc != 2 )
		{
			printf("Wrong arguments count");
			return -3;
		}
		std::string folder( "D:\\PaboTa\\37372\\pdf\\" );

		//std::string folder("D:\\ןנטלונû פאיכמג\\pdf\\");

		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
		

		CoInitialize( NULL );

		if (!AfxOleInit())	{
			AfxMessageBox("OLE initialization failed in BasicIacVc sample.");
			return FALSE;
		}

		COleException e;
		if ( ! isAcrobatInstalled( e ) )
		{
			printf( "Error to start acrobat app." );
			return -1;
		}

		//ParseDateString( "D:20020314220331" );


		FileFinder finder;
		stringlist filter;
		filter.push_back(".pdf");
		std::string target_folder = "";
		finder.FindFiles(folder, filter);
		auto files ( finder.getFileNames() );
	
		int counter = 0;
		for ( auto iter = files.begin() ; iter != files.end() ; ++iter )
		{
			std::string target_file = *iter;
			PdfDocument pdfDoc;
			if ( pdfDoc.CreateDocument( e ) )
			{
				
				if ( pdfDoc.Open( *iter ) )
				{
				//	auto docInfo = pdfDoc.getInfo();
				//	DateString data_string;
				//	CString targe_name = IO::numberToString(counter).c_str();

				//	CString dataToParse = ( !docInfo.ModDate.IsEmpty() ) ? docInfo.ModDate : docInfo.CreationDate;
				//	if ( ! dataToParse.IsEmpty() )
				//	if ( ParseDateString( dataToParse , data_string ) )
				//	{
				//		targe_name = data_string.YEAR + "-" +
				//					 data_string.MONTH + "-" +
				//					 data_string.DAY + "-" +
				//					 data_string.HOUR + "-" +
				//					 data_string.MINUTES + "-" +
				//					 data_string.SECONDS + "-" +
				//					 IO::numberToString(counter).c_str();

				//	}

					//target_file = target_folder + targe_name.GetString() + ".pdf"; 
					target_file += ".good";
					boost::filesystem::copy_file( *iter ,  target_file );
					printf("File %s was opened OK\n", iter->c_str() );
					++counter;
				}
				
				else
				{
					printf("File %s wasn't opened\n", iter->c_str() );
					target_file += ".bad_file"; 
					boost::filesystem::copy_file(  *iter , target_file );

				}
				pdfDoc.Close();
			}

		}
		

		CoInitialize ( NULL );
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
