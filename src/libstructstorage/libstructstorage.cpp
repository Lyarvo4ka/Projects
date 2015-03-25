// libstructstorage.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "libstructstorage.h"


std::string getTimeFromFileTime(const FILETIME & file_time)
{
	SYSTEMTIME st = { 0 };
	std::string time_nane = "";
	if (::FileTimeToSystemTime(&file_time, &st))
	{
		char time_buffer[255];
		::GetTimeFormatA(LOCALE_USER_DEFAULT, 0, &st, "HH-mm-ss", time_buffer, 255);
		time_nane = time_buffer;
	}
	return time_nane;
}

std::string getDateFromFileTime(const FILETIME & file_time)
{
	SYSTEMTIME st = { 0 };
	std::string date_nane;
	if (FileTimeToSystemTime(&file_time, &st))
	{
		char date_buffer[255];
		GetDateFormatA(LOCALE_USER_DEFAULT, 0, &st, "yyyy-MM-dd", date_buffer, 255);
		date_nane = date_buffer;
	}
	return date_nane;
}

std::string LIBSTRUCTSTORAGE_API getDateTimeFromFileTime(const FILETIME & file_time)
{
	return getDateFromFileTime(file_time) + "-" + getTimeFromFileTime(file_time);
}

SummaryInformation::SummaryInformation() : Title_("")
, Subject_("")
, Author_("")
, Keywords_("")
, Comments_("")
, Template_("")
, LastSavedBy_("")
, RevisionNumber_("")
//, TotalEditTime_()
{

}

void SummaryInformation::setTitile(const std::string & title)
{
	Title_ = title;
}

std::string SummaryInformation::title() const
{
	return Title_;
}

void SummaryInformation::setSubject(const std::string & subject)
{
	Subject_ = subject;
}

std::string SummaryInformation::subject() const
{
	return Subject_;
}

void SummaryInformation::setAuthor(const std::string & author)
{
	Author_ = author;
}

std::string SummaryInformation::author() const
{
	return Author_;
}

void SummaryInformation::setKeywords(const std::string & keywords)
{
	Keywords_ = keywords;
}

std::string SummaryInformation::keywords() const
{
	return Keywords_;
}

void SummaryInformation::setComments(const std::string & comments)
{
	Comments_ = comments;
}

std::string SummaryInformation::comments() const
{
	return Comments_;
}

void SummaryInformation::setTemplate(const std::string & strTemplate)
{
	Template_ = strTemplate;
}

std::string SummaryInformation::getTemplate() const
{
	return Template_;
}

void SummaryInformation::setLastSavedBy(const std::string & LastSavedBy)
{
	LastSavedBy_ = LastSavedBy;
}

std::string SummaryInformation::LastSavedBy() const
{
	return LastSavedBy_;
}

void SummaryInformation::setRevisionNumber(const std::string & RevisionNumber)
{
	RevisionNumber_ = RevisionNumber;
}

std::string SummaryInformation::RevisionNumber() const
{
	return RevisionNumber_;
}

void SummaryInformation::setTotalEditingTime(const FILETIME & file_time)
{
	TotalEditTime_ = file_time;
}

FILETIME SummaryInformation::totalEditTime() const
{
	return TotalEditTime_;
}

void SummaryInformation::setLastPrintedTime(const FILETIME & file_time)
{
	LastPrinted_ = file_time;
}

FILETIME SummaryInformation::lastPrintedTime() const
{
	return LastPrinted_;
}

void SummaryInformation::setCreateTime(const FILETIME & file_time)
{
	CreateTime_ = file_time;
}

FILETIME SummaryInformation::createTime() const
{
	return CreateTime_;
}

void SummaryInformation::setLastSavedTime(const FILETIME & file_time)
{
	LastSavedTime_ = file_time;
}

FILETIME SummaryInformation::lastSavedTime() const
{
	return LastSavedTime_;
}

IPropertySetStorage * SSReader::toPropertySetStorage(IStorage * pStorage)
{
	IPropertySetStorage * pPropSetStg = NULL;
	HRESULT hr = S_OK;
	if (FAILED(hr = pStorage->QueryInterface(IID_IPropertySetStorage, (void **)&pPropSetStg))) {
		printf("QI for IPropertySetStorage failed w/error %08lx", hr);
		pStorage->Release();
	}
	return pPropSetStg;
}

IStorage * SSReader::open_storage(const std::wstring & file)
{
	HRESULT hr = S_OK;
	IStorage *pStorage = NULL;
	hr = ::StgOpenStorage(file.c_str(), NULL,
		STGM_READ | STGM_SHARE_EXCLUSIVE, NULL, 0, &pStorage);

	if (FAILED(hr)) {
		if (hr == STG_E_FILENOTFOUND)
			printf("File not found.");
		else if (hr == STG_E_FILEALREADYEXISTS)
			printf("Not a compound file.");
		else
			printf("StgOpenStorage() failed w/error %08lx", hr);
		return NULL;
	}
	return pStorage;
}

SSReader::SSReader()
{

}

bool SSReader::read_properties(const std::string & file_path, SummaryInformation & summary_information)
{
	WCHAR buff[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, file_path.c_str(), -1, buff, MAX_PATH);
	std::wstring file_name(buff);

	IStorage * pStorage = this->open_storage(file_name);
	if (!pStorage)
		return false;

	IPropertySetStorage * pPropSetStg = this->toPropertySetStorage(pStorage);
	IPropertyStorage *pPropStg = NULL;
	HRESULT hr = S_OK;

	hr = pPropSetStg->Open(FMTID_SummaryInformation, STGM_READ | STGM_SHARE_EXCLUSIVE, &pPropStg);
	if (FAILED(hr)) {
		printf("No Summary-Information.\n");
		return false;
	}

	struct pidsiStruct {
		char *name;
		long pidsi;
	}	  pidsiArr[] = {
		{ "Title", PIDSI_TITLE }, // VT_LPSTR
		{ "Subject", PIDSI_SUBJECT }, // ...
		{ "Author", PIDSI_AUTHOR },
		{ "Keywords", PIDSI_KEYWORDS },
		{ "Comments", PIDSI_COMMENTS },
		{ "Template", PIDSI_TEMPLATE },
		{ "LastAuthor", PIDSI_LASTAUTHOR },
		{ "Revision Number", PIDSI_REVNUMBER },
		{ "Edit Time", PIDSI_EDITTIME }, // VT_FILENAME (UTC)
		{ "Last printed", PIDSI_LASTPRINTED }, // ...
		{ "Created", PIDSI_CREATE_DTM },
		{ "Last Saved", PIDSI_LASTSAVE_DTM },
		{ "Page Count", PIDSI_PAGECOUNT }, // VT_I4
		{ "Word Count", PIDSI_WORDCOUNT }, // ...
		{ "Char Count", PIDSI_CHARCOUNT },

		{ "Thumpnail", PIDSI_THUMBNAIL }, // VT_CF
		{ "AppName", PIDSI_APPNAME }, // VT_LPSTR
		{ "Doc Security", PIDSI_DOC_SECURITY }, // VT_I4
		{ 0, 0 }
	};

	// Count elements in pidsiArr.
	int nPidsi = 0;
	for (nPidsi = 0; pidsiArr[nPidsi].name; nPidsi++);

	// Initialize PROPSPEC for the properties you want.
	PROPSPEC *pPropSpec = new PROPSPEC[nPidsi];
	PROPVARIANT *pPropVar = new PROPVARIANT[nPidsi];

	for (int i = 0; i < nPidsi; i++) {
		ZeroMemory(&pPropSpec[i], sizeof(PROPSPEC));
		pPropSpec[i].ulKind = PRSPEC_PROPID;
		pPropSpec[i].propid = pidsiArr[i].pidsi;
	}

	// Read properties.
	hr = pPropStg->ReadMultiple(nPidsi, pPropSpec, pPropVar);

	if (FAILED(hr)) {
		printf("IPropertyStg::ReadMultiple() failed w/error %08lx\n", hr);
	}
	else {
		setSummaryInformation(pPropSpec, pPropVar, nPidsi, summary_information);
	}

	delete[] pPropSpec;
	delete[] pPropVar;

	pPropSetStg->Release();
	pStorage->Release();

	return (SUCCEEDED(hr)) ? true : false;
}

void SSReader::setSummaryInformation(const PROPSPEC * pPropSpec, const PROPVARIANT * pPropVar, int nCount, SummaryInformation & summary_info)
{
	for (int i = 0; i < nCount; ++i)
	{
		switch (pPropSpec[i].propid)
		{
		case PIDSI_TITLE:
			if (pPropVar[i].pszVal != NULL)
				summary_info.setTitile(pPropVar[i].pszVal);
			break;
		case PIDSI_SUBJECT:
			if (pPropVar[i].pszVal != NULL)
				summary_info.setSubject(pPropVar[i].pszVal);
		case PIDSI_AUTHOR:
			if (pPropVar[i].pszVal != NULL)
				summary_info.setAuthor(pPropVar[i].pszVal);
			break;
		case PIDSI_KEYWORDS:
			if (pPropVar[i].pszVal != NULL)
				summary_info.setKeywords(pPropVar[i].pszVal);
		case PIDSI_COMMENTS:
			if (pPropVar[i].pszVal != NULL)
				summary_info.setComments(pPropVar[i].pszVal);
			break;
		case PIDSI_TEMPLATE:
			if (pPropVar[i].pszVal != NULL)
				summary_info.setTemplate(pPropVar[i].pszVal);
		case PIDSI_LASTAUTHOR:
			if (pPropVar[i].pszVal != NULL)
				summary_info.setLastSavedBy(pPropVar[i].pszVal);
		case PIDSI_REVNUMBER:
			if (pPropVar[i].pszVal != NULL)
				summary_info.setRevisionNumber(pPropVar[i].pszVal);
		case PIDSI_EDITTIME:
			summary_info.setTotalEditingTime(pPropVar[i].filetime);
			break;
		case PIDSI_LASTPRINTED:
			summary_info.setLastPrintedTime(pPropVar[i].filetime);
		case PIDSI_CREATE_DTM:
			summary_info.setCreateTime(pPropVar[i].filetime);
		case PIDSI_LASTSAVE_DTM:
			summary_info.setLastSavedTime(pPropVar[i].filetime);
			break;
			//default:
			/*
			????????
			*/

		};
	}
}
