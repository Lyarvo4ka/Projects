#ifndef STRUCTUREDSTORAGEREADER_H
#define STRUCTUREDSTORAGEREADER_H

#include <string>
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

inline std::string SummaryInformationName( PROPID prop_id)
{
	switch ( prop_id )
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
	case PIDSI_WORDCOUNT :
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


class SummaryInformation
{
public:
	SummaryInformation()
		: Title_("")
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
	void setTitile( const std::string & title)
	{
		Title_ = title;
	}
	std::string title() const
	{
		return Title_;
	}
	void setSubject(const std::string & subject)
	{
		Subject_ = subject;
	}
	std::string subject() const
	{
		return Subject_;
	}
	void setAuthor(const std::string & author)
	{
		Author_ = author;
	}
	std::string author() const
	{
		return Author_;
	}
	void setKeywords(const std::string & keywords)
	{
		Keywords_ = keywords;
	}
	std::string keywords() const
	{
		return Keywords_;
	}
	void setComments(const std::string & comments)
	{
		Comments_ = comments;
	}
	std::string comments() const
	{
		return Comments_;
	}
	void setTemplate(const std::string & strTemplate)
	{
		Template_ = strTemplate;
	}
	std::string getTemplate() const
	{
		return Template_;
	}
	void setLastSavedBy(const std::string & LastSavedBy)
	{
		LastSavedBy_ = LastSavedBy;
	}
	std::string LastSavedBy() const
	{
		return LastSavedBy_;
	}	
	void setRevisionNumber(const std::string & RevisionNumber)
	{
		RevisionNumber_ = RevisionNumber;
	}
	std::string RevisionNumber() const
	{
		return RevisionNumber_;
	}
	void setTotalEditingTime( const FILETIME & file_time)
	{
		TotalEditTime_ = file_time;
	}
	FILETIME totalEditTime() const
	{
		return TotalEditTime_;
	}
	void setLastPrintedTime( const FILETIME & file_time)
	{
		LastPrinted_ = file_time;
	}
	FILETIME lastPrintedTime() const
	{
		return LastPrinted_;
	}
	void setCreateTime( const FILETIME & file_time)
	{
		CreateTime_ = file_time;
	}
	FILETIME createTime() const
	{
		return CreateTime_;
	}
	void setLastSavedTime( const FILETIME & file_time)
	{
		LastSavedTime_ = file_time;
	}
	FILETIME lastSavedTime() const
	{
		return LastSavedTime_;
	}
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

class SSReader
{
private:
	IPropertySetStorage * toPropertySetStorage( IStorage * pStorage )
	{
		IPropertySetStorage * pPropSetStg = NULL;
		HRESULT hr = S_OK;
      if(FAILED( hr = pStorage->QueryInterface( IID_IPropertySetStorage, (void **)&pPropSetStg) ) ) {
         printf("QI for IPropertySetStorage failed w/error %08lx", hr);
         pStorage->Release();
		}
	  return pPropSetStg;
	}
	IStorage * open_storage( const std::wstring & file )
	{

		HRESULT hr = S_OK;
		IStorage *pStorage = NULL;
		hr = ::StgOpenStorage(file.c_str(), NULL,
								 STGM_READ | STGM_SHARE_EXCLUSIVE, NULL, 0, &pStorage);

		if(FAILED(hr)) {
			 if(hr == STG_E_FILENOTFOUND)
				printf("File not found.");
			 else if(hr == STG_E_FILEALREADYEXISTS)
				printf("Not a compound file.");
			 else
				printf("StgOpenStorage() failed w/error %08lx", hr);
			 return NULL;
		}
		return pStorage;
	}

public:
	SSReader( )
	{

	}

	// Open the document as an OLE compound document.


	// read properties of a property storage
	bool read_properties(  const std::string & file_path, SummaryInformation & summary_information)
	{
		WCHAR buff[MAX_PATH];
		MultiByteToWideChar( CP_ACP , 0 , file_path.c_str() , -1 , buff , MAX_PATH );
		std::wstring file_name( buff );

		IStorage * pStorage = this->open_storage( file_name );
		if ( !pStorage )
			return false;

		IPropertySetStorage * pPropSetStg = this->toPropertySetStorage( pStorage );
		IPropertyStorage *pPropStg = NULL;
		HRESULT hr = S_OK;

		hr = pPropSetStg->Open(FMTID_SummaryInformation, STGM_READ | STGM_SHARE_EXCLUSIVE, &pPropStg);
		 if(FAILED(hr)) {
			 printf("No Summary-Information.\n");
         return false;
		}

      struct pidsiStruct {
         char *name;
         long pidsi;
      }	  pidsiArr[] = {
         {"Title",            PIDSI_TITLE}, // VT_LPSTR
         {"Subject",          PIDSI_SUBJECT}, // ...
         {"Author",           PIDSI_AUTHOR},
         {"Keywords",         PIDSI_KEYWORDS},
         {"Comments",         PIDSI_COMMENTS},
         {"Template",         PIDSI_TEMPLATE},
         {"LastAuthor",       PIDSI_LASTAUTHOR},
         {"Revision Number",  PIDSI_REVNUMBER},
         {"Edit Time",        PIDSI_EDITTIME}, // VT_FILENAME (UTC)
         {"Last printed",     PIDSI_LASTPRINTED}, // ...
         {"Created",          PIDSI_CREATE_DTM},
         {"Last Saved",       PIDSI_LASTSAVE_DTM},
         {"Page Count",       PIDSI_PAGECOUNT}, // VT_I4
         {"Word Count",       PIDSI_WORDCOUNT}, // ...
         {"Char Count",       PIDSI_CHARCOUNT},

         {"Thumpnail",        PIDSI_THUMBNAIL}, // VT_CF
         {"AppName",          PIDSI_APPNAME}, // VT_LPSTR
         {"Doc Security",     PIDSI_DOC_SECURITY}, // VT_I4
         {0, 0}
      };		

      // Count elements in pidsiArr.
      int nPidsi = 0;
      for(nPidsi=0; pidsiArr[nPidsi].name; nPidsi++);

		// Initialize PROPSPEC for the properties you want.
		PROPSPEC *pPropSpec = new PROPSPEC [nPidsi];
		PROPVARIANT *pPropVar = new PROPVARIANT [nPidsi];

		for(int i=0; i<nPidsi; i++) {
			 ZeroMemory(&pPropSpec[i], sizeof(PROPSPEC));
			pPropSpec[i].ulKind = PRSPEC_PROPID;
			pPropSpec[i].propid = pidsiArr[i].pidsi;
		}		 

     // Read properties.
      hr = pPropStg->ReadMultiple(nPidsi, pPropSpec, pPropVar);

      if(FAILED(hr)) {
         printf("IPropertyStg::ReadMultiple() failed w/error %08lx\n",hr);
      }
      else {
		  setSummaryInformation( pPropSpec , pPropVar , nPidsi , summary_information );
	  }

	  delete [] pPropSpec;
	  delete [] pPropVar;

	  pPropSetStg->Release();
	  pStorage->Release();

	  return ( SUCCEEDED( hr ) ) ? true : false;
	}

	void setSummaryInformation( const PROPSPEC * pPropSpec , const PROPVARIANT * pPropVar , int nCount , SummaryInformation & summary_info )
	{
	  for ( int i = 0; i < nCount ; ++i )
	  {
		  switch( pPropSpec[i].propid )
		  {
		  case PIDSI_TITLE:
			  if ( pPropVar[i].pszVal != NULL )
			  summary_info.setTitile( pPropVar[i].pszVal );
			  break;
		  case PIDSI_SUBJECT:
			  if ( pPropVar[i].pszVal != NULL )
			  summary_info.setSubject( pPropVar[i].pszVal );
		  case PIDSI_AUTHOR:
			  if ( pPropVar[i].pszVal != NULL )
			  summary_info.setAuthor( pPropVar[i].pszVal );
			  break;
		  case PIDSI_KEYWORDS:
			  if ( pPropVar[i].pszVal != NULL )
			  summary_info.setKeywords( pPropVar[i].pszVal );
		  case PIDSI_COMMENTS:
			  if ( pPropVar[i].pszVal != NULL )
			  summary_info.setComments( pPropVar[i].pszVal );
			  break;
		  case PIDSI_TEMPLATE:
			  if ( pPropVar[i].pszVal != NULL )
			  summary_info.setTemplate( pPropVar[i].pszVal );
		  case PIDSI_LASTAUTHOR:
			  if ( pPropVar[i].pszVal != NULL )
			  summary_info.setLastSavedBy( pPropVar[i].pszVal );
		  case PIDSI_REVNUMBER:
			  if ( pPropVar[i].pszVal != NULL )
			  summary_info.setRevisionNumber( pPropVar[i].pszVal );
		  case PIDSI_EDITTIME:
			  summary_info.setTotalEditingTime( pPropVar[i].filetime );
			  break;
		  case PIDSI_LASTPRINTED:
			  summary_info.setLastPrintedTime( pPropVar[i].filetime );
		  case PIDSI_CREATE_DTM:
			  summary_info.setCreateTime( pPropVar[i].filetime );
		  case PIDSI_LASTSAVE_DTM:
			  summary_info.setLastSavedTime( pPropVar[i].filetime );
			  break;
		  //default:
			  /*
			  ????????
			  */

		  };
	  }
	}

};

#endif