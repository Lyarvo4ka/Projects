#pragma once

#include "Imports.h"


#define ImportLang   __declspec( dllimport )
#define ExportLang   __declspec( dllexport )


#ifndef LANG_EXPORTS
#define LangExport ImportLang
#else
#define LangExport ExportLang
#endif

#include <string>
using std::string;


namespace  Declaration
{
	static const int EngishLanguage = 0;
	static const int RussianLanguage = 1;


	class LangExport LanguageDll
	{
	protected:
		LanguageDll(int DefaultLanguage = 1);
		~LanguageDll();
	public:
		static LanguageDll * GetInstance();
		void Remove();
		void SetLanguage(const int _LenguageNumber = 1); 
		bool isRussian() const;
	private:
		static LanguageDll * m_Instance;
		int LenguageNumber_;
	};

	const string sWrittingFileEng = "Writing file ";
	const string sWrittingFileRus = "Запись в файл ";


	string LangExport ErrorBPSNull();
	string LangExport ErrorOutOffRange();
	string LangExport ErrorMaxTransferSizeNULL();
	string LangExport ErrorOpenDevice();
	string LangExport ErrorMoreThenDeviceSize();
	string LangExport ErrorNoSelectedDevice();
	string LangExport ErrorStartSectorMore();
	string LangExport ErrorEnCaseMoreZZZ();
	string LangExport ErrorOpenFile();
	string LangExport ErrorOpenFileShow(const string & _FilePath);
	string LangExport VerifyPath();
	string LangExport WritingFile();
	string LangExport WrittingToFile(const string & _FilePath);
	string LangExport ErrorReadSectors();
	string LangExport ErrorReadSector();
}
