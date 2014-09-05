#include "StdAfx.h"
#include "Declaration.h"
#include "Error.h"

Declaration::LanguageDll * Declaration::LanguageDll::m_Instance = NULL;

Declaration::LanguageDll * Declaration::LanguageDll::GetInstance()
{
	if (m_Instance == NULL)
		m_Instance = new LanguageDll;
	return m_Instance;
}
Declaration::LanguageDll::LanguageDll(const int DefaultLanguage)
	: LenguageNumber_(DefaultLanguage)
{
	setlocale(LC_ALL, "Russian");
}
Declaration::LanguageDll::~LanguageDll()
{

}
bool Declaration::LanguageDll::isRussian() const
{
	return (LenguageNumber_ == RussianLanguage) ? true : false;
}
void Declaration::LanguageDll::Remove()
{
	delete m_Instance;
	m_Instance = NULL;
}
void Declaration::LanguageDll::SetLanguage(const int _LenguageNumber)
{
	LenguageNumber_ = _LenguageNumber;
}
string Declaration::ErrorBPSNull()
{
	bool bResult = LanguageDll::GetInstance()->isRussian();
	return (bResult) ? Errors::sBytesPerSectorNullRus : Errors::sBytesPerSectorNullEng;
}

string Declaration::ErrorOutOffRange()
{
	return ( LanguageDll::GetInstance()->isRussian() ) ? Errors::sOutOffRangeRus : Errors::sOutOffRangeEng;
}
string Declaration::ErrorMaxTransferSizeNULL()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Errors::sMaxTransferSizeNullRus : Errors::sMaxTransferSizeNullEng;
}
string Declaration::ErrorOpenDevice()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Errors::sErrorOpenDeviceRus : Errors::sErrorOpenDeviceEng;
}

string Declaration::ErrorMoreThenDeviceSize()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Errors::sMoreThenDeviceSizeRus : Errors::sMoreThenDeviceSizeEng;
}

string Declaration::ErrorNoSelectedDevice()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Errors::sNoSelectedDeviceRus : Errors::sNoSelectedDeviceEng;
}
string Declaration::ErrorStartSectorMore()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Errors::sNoSelectedDeviceRus : Errors::sNoSelectedDeviceEng;
}
string Declaration::ErrorEnCaseMoreZZZ()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Errors::sEnCaseMoreZZZRus : Errors::sEnCaseMoreZZZEng;
}

string Declaration::ErrorOpenFile()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Errors::sErrorOpenFileRus : Errors::sErrorOpenFileEng;

}
string Declaration::ErrorOpenFileShow(const string & _FilePath)
{
	return ErrorOpenFile() + "\r\n\"" + _FilePath + "\".\r\n" + VerifyPath();
}
string Declaration::VerifyPath()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Errors::sVerifyCorrectPathRus : Errors::sVerifyCorrectPathEng;
}

string Declaration::WritingFile()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Declaration::sWrittingFileRus : Declaration::sWrittingFileEng;
}
string Declaration::WrittingToFile(const string & _FilePath)
{
	return WritingFile() + "\"" + _FilePath + "\"...\r\n";
}
string Declaration::ErrorReadSectors()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Errors::sErrorReadSectorsRus : Errors::sErrorReadSectorsEng;
}
string Declaration::ErrorReadSector()
{
	return (LanguageDll::GetInstance()->isRussian()) ? Errors::sErrorReadSectorRus : Errors::sErrorReadSectorEng;
}
