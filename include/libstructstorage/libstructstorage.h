#ifndef LIBSTRUCTSTORAGE_H
#define LIBSTRUCTSTORAGE_H

#include <Windows.h>
#include <string>
#include "libstructstorage_global.h"

std::string LIBSTRUCTSTORAGE_API getTimeFromFileTime(const FILETIME & file_time);
std::string LIBSTRUCTSTORAGE_API getDateFromFileTime(const FILETIME & file_time);
std::string LIBSTRUCTSTORAGE_API getDateTimeFromFileTime(const FILETIME & file_time);


#include "Objbase.h"
#include "Objidl.h"

namespace idNames
{
	const std::string Title = "Title";
	const std::string Subject = "Subject";
	const std::string Author = "Author";
	const std::string Keywords = "Keywords";
	const std::string Comments = "Comments";
	const std::string Template = "Template";
	const std::string LastSavedBy = "Last Saved By";
	const std::string RevisionNumber = "Revision Number";
	const std::string TotalEditingTime = "Total Editing Time";
	const std::string LastPrinted = "Last Printed";
	const std::string CreateTime = "Create Time/Date";
	const std::string LastSavedTime = "Last saved Time/Date";
	const std::string NumberOfPages = "Number of Pages";
	const std::string NumberOfWords = "Number of Words";
	const std::string NumberOfCharacters = "Number of Characters";
	const std::string Thumbnail = "Thumbnail";
	const std::string NameOfCreatingApplication = "Name of Creating Application";
	const std::string Security = "Security";

	const std::string Unknown = "Unknown";
};

inline std::string SummaryInformationName(PROPID prop_id)
{
	switch (prop_id)
	{
	case PIDSI_TITLE:
		return idNames::Title;
	case PIDSI_SUBJECT:
		return idNames::Subject;
	case PIDSI_AUTHOR:
		return idNames::Author;
	case PIDSI_KEYWORDS:
		return idNames::Keywords;
	case PIDSI_COMMENTS:
		return idNames::Comments;
	case PIDSI_TEMPLATE:
		return idNames::Template;
	case PIDSI_LASTAUTHOR:
		return idNames::LastSavedBy;
	case PIDSI_REVNUMBER:
		return idNames::RevisionNumber;
	case PIDSI_EDITTIME:
		return idNames::TotalEditingTime;
	case PIDSI_LASTPRINTED:
		return idNames::LastPrinted;
	case PIDSI_CREATE_DTM:
		return idNames::CreateTime;
	case PIDSI_LASTSAVE_DTM:
		return idNames::LastSavedTime;
	case PIDSI_PAGECOUNT:
		return idNames::NumberOfPages;
	case PIDSI_WORDCOUNT:
		return idNames::NumberOfWords;
	case PIDSI_CHARCOUNT:
		return idNames::NumberOfCharacters;
	case PIDSI_THUMBNAIL:
		return idNames::Thumbnail;
	case PIDSI_APPNAME:
		return idNames::NameOfCreatingApplication;
	case PIDSI_DOC_SECURITY:
		return idNames::Security;
	default:
		return idNames::Unknown;

	};

}


class LIBSTRUCTSTORAGE_API SummaryInformation
{
public:
	SummaryInformation();
	void setTitile(const std::string & title);
	std::string title() const;
	void setSubject(const std::string & subject);
	std::string subject() const;
	void setAuthor(const std::string & author);
	std::string author() const;
	void setKeywords(const std::string & keywords);
	std::string keywords() const;
	void setComments(const std::string & comments);
	std::string comments() const;
	void setTemplate(const std::string & strTemplate);
	std::string getTemplate() const;
	void setLastSavedBy(const std::string & LastSavedBy);
	std::string LastSavedBy() const;
	void setRevisionNumber(const std::string & RevisionNumber);
	std::string RevisionNumber() const;
	void setTotalEditingTime(const FILETIME & file_time);
	FILETIME totalEditTime() const;
	void setLastPrintedTime(const FILETIME & file_time);
	FILETIME lastPrintedTime() const;
	void setCreateTime(const FILETIME & file_time);
	FILETIME createTime() const;
	void setLastSavedTime(const FILETIME & file_time);
	FILETIME lastSavedTime() const;
private:
	std::string Title_;
	std::string Subject_;
	std::string Author_;
	std::string Keywords_;
	std::string Comments_;
	std::string Template_;
	std::string LastSavedBy_;
	std::string RevisionNumber_;
	FILETIME TotalEditTime_;
	FILETIME LastPrinted_;
	FILETIME CreateTime_;
	FILETIME LastSavedTime_;

};


class LIBSTRUCTSTORAGE_API SSReader
{
private:
	IPropertySetStorage * toPropertySetStorage(IStorage * pStorage);
	IStorage * open_storage(const std::wstring & file);

public:
	SSReader();

	// Open the document as an OLE compound document.


	// read properties of a property storage
	bool read_properties(const std::string & file_path, SummaryInformation & summary_information);

	void setSummaryInformation(const PROPSPEC * pPropSpec, const PROPVARIANT * pPropVar, int nCount, SummaryInformation & summary_info);

};



#endif
