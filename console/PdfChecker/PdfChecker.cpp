// PdfChecker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PdfChecker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



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

//
#include "libpdf\Pdfdocument.h"
////#include "..\ZipLib\ZipFile.h"



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	//ZipFile zip_file;
	//auto zipPtr = ZipFile::Open("d:\\test_folder\\Анкета посетителя фабрики.zip");
	//zipPtr->GetEntriesCount() > 




	



	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{

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
			AfxMessageBox(L"OLE initialization failed in BasicIacVc sample.");
			return FALSE;
		}

		COleException e;
		if ( ! isAcrobatInstalled( e ) )
		{
			printf( "Error to start acrobat app." );
			return -1;
		}
		if (argc == 2)
		{
			std::wstring source_folder(argv[1]);
			verify_pdf_files(source_folder);
		//	std::wstring target_folder(argv[2]);

			//identify_files(source_folder, target_folder);
		}
		else
			printf("Error. You entered invalid params.\r\n");

		CoUninitialize();


		}
	}
	else
	{
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

std::wstring get_wstring_from_sz(const char* psz)
{
	int res;
	wchar_t buf[0x400];
	wchar_t *pbuf = buf;
	boost::shared_ptr<wchar_t[]> shared_pbuf;

	res = MultiByteToWideChar(CP_ACP, 0, psz, -1, buf, sizeof(buf) / sizeof(wchar_t));

	if (0 == res && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		res = MultiByteToWideChar(CP_ACP, 0, psz, -1, NULL, 0);

		shared_pbuf = boost::shared_ptr<wchar_t[]>(new wchar_t[res]);

		pbuf = shared_pbuf.get();

		res = MultiByteToWideChar(CP_ACP, 0, psz, -1, pbuf, res);
	}
	else if (0 == res)
	{
		pbuf = L"error";
	}

	return std::wstring(pbuf);
}

inline std::string get_string_from_wcs(const wchar_t* pcs)
{
	int res;
	char buf[0x400];
	char* pbuf = buf;
	boost::shared_ptr<char[]> shared_pbuf;

	res = WideCharToMultiByte(CP_ACP, 0, pcs, -1, buf, sizeof(buf), NULL, NULL);

	if (0 == res && GetLastError() == ERROR_INSUFFICIENT_BUFFER)
	{
		res = WideCharToMultiByte(CP_ACP, 0, pcs, -1, NULL, 0, NULL, NULL);

		shared_pbuf = boost::shared_ptr<char[]>(new char[res]);

		pbuf = shared_pbuf.get();

		res = WideCharToMultiByte(CP_ACP, 0, pcs, -1, pbuf, res, NULL, NULL);
	}
	else if (0 == res)
	{
		pbuf = "error";
	}

	return std::string(pbuf);
}

bool open_pdf_file(const std::string & file_name)
{
	COleException e;
	PdfDocument pdfDoc;
	if (pdfDoc.CreateDocument(e))
	{
		if (pdfDoc.Open(file_name))
			return true;
	}

	return false;
}

void verify_pdf_files(const IO::path_string & folder)
{
	using namespace IO;
	path_string add_bad_name = L".bad_file";
	path_string add_good_name = L".good";

	Finder finder;
	finder.add_extension(L".pdf");
	finder.FindFiles(folder);
	finder.printAll();

	auto listFiles = finder.getFiles();

	for (auto the_file : listFiles)
	{
		auto test_file = get_string_from_wcs(the_file.c_str());
		auto add_name = (open_pdf_file(test_file)) ? add_good_name : add_bad_name;

		try
		{
			boost::filesystem::rename(the_file, the_file + add_name);
		}
		catch (const boost::filesystem::filesystem_error& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

}

void identify_files(const std::string & source_dir, const std::string & target_dir)
{
	//std::string bad_dir = "bad";
	//stringlist ext_list;
	//ext_list.push_back(".pdf");

	//IO::Finder finder;
	//finder.FindFiles(source_dir, ext_list);
	//auto file_list = finder.getFileNames();

	//DWORD counter = 0;

	//auto fileIter = file_list.begin();

	//while (fileIter != file_list.end())
	//{
	//	std::string source_name(*fileIter);


	//	boost::filesystem::path file_path(source_name);
	//	std::string ext = file_path.extension().generic_string();

	//	bool bResult = false;
	//	std::string target_name;

	//	if (ext.compare(".pdf") == 0)
	//		bResult = identify_pdf(source_name, target_name, counter);
	//	//else
	//	//	if (isOffice2007(ext))
	//	//		bResult = identify_office2007(source_name, target_name, counter);
	//	//	else
	//	//		bResult = identify_office2003(source_name, target_name, counter);
	//	++counter;

	//	std::string target_file_path;
	//	std::string ext_folder = ext.substr(1);
	//	std::string new_folder = (bResult) ? ext_folder : bad_dir;
	//	std::string target_folder = IO::add_folder(target_dir, new_folder);
	//	target_file_path = IO::make_file_path(target_folder, target_name);

	//	try
	//	{
	//		boost::filesystem::rename(source_name, target_file_path);
	//	}
	//	catch (const boost::filesystem::filesystem_error& e)
	//	{
	//		std::cout << "Error: " << e.what() << std::endl;
	//	}

	//	++fileIter;
	//}
}



bool identify_pdf(const std::string & file_name, std::string & new_filename, int counter)
{
/*	COleException e;
	PdfDocument pdfDoc;
	std::string ext = IO::get_extension(file_name);
	new_filename = IO::numberToString(counter) + ext;
	if (pdfDoc.CreateDocument(e))
	{
		if (pdfDoc.Open(file_name))
		{ 
			auto docInfo = pdfDoc.getInfo();
			DateString data_string;
			CStringA targe_name = IO::numberToString(counter).c_str();

			CString dataToParse = (!docInfo.ModDate.IsEmpty()) ? docInfo.ModDate : docInfo.CreationDate;
			if (!dataToParse.IsEmpty())
				if (ParseDateString(dataToParse, data_string))
				{
					targe_name = data_string.YEAR + "-" +
						data_string.MONTH + "-" +
						data_string.DAY + "-" +
						data_string.HOUR + "-" +
						data_string.MINUTES + "-" +
						data_string.SECONDS + "-" +
						IO::numberToString(counter).c_str();
				}
			new_filename = targe_name.GetString() + ext;

			pdfDoc.DestroyDocument();
			return true;
		}

	}
	else
		printf("Error to create pdf document application\r\n");
		*/
	return false;
}
