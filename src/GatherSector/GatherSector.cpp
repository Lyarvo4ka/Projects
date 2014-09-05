// GatherSector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "Files.h"
#include <conio.h>

int _tmain(int argc, _TCHAR* argv[])
{
	CFiles *pFiles = new CFiles(PAGE_FULL);
	DumpWriter *pDumpWriter = new DumpWriter(DATA_SIZE);
	string FileName = "";
	FileName = "d:\\Public\\35179_iPhone\\Result.dump";
	pFiles->Open(FileName);
	pDumpWriter->Run(pFiles);
	pFiles->Close();
	//string FileName = "e:\\Work\\iMobilko\\iPhone_0.dat";
	//pFiles->Open(FileName);
	//pDumpWriter->Run(pFiles);
	//pFiles->Close();

	//FileName = "e:\\Work\\iMobilko\\iPhone_1.dat";
	//pFiles->Open(FileName);
	//pDumpWriter->Run(pFiles);
	//pFiles->Close();

	//FileName = "e:\\Work\\iMobilko\\iPhone_2.dat";
	//pFiles->Open(FileName);
	//pDumpWriter->Run(pFiles);
	//pFiles->Close();

	//FileName = "e:\\Work\\iMobilko\\iPhone_3.dat";
	//pFiles->Open(FileName);
	//pDumpWriter->Run(pFiles);
	//pFiles->Close();

	//pDumpWriter->WriteNotFound();

	delete pDumpWriter;
	delete pFiles;
	printf("The End");
	_getch();
	return 0;
}

