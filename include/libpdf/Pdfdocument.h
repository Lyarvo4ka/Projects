#ifndef PDFDOCUMENT_H
#define PDFDOCUMENT_H

#include <string>

#include "libpdf.h"
#include "acrobat.h"
#include "iac.h"

#include <afxdisp.h>

BOOL LIBPDF_API isAcrobatInstalled( COleException &e );

const CString sAutor = "Autor";
const CString sCreationDate = "CreationDate";
const CString sCreator = "Creator";
const CString sProducer = "Producer";
const CString sTitle = "Title";
const CString sSubject = "Subject";
const CString sKeywords = "Keywords";
const CString sModDate = "ModDate";


struct LIBPDF_API DocInfo
{
	CString Author;
	CString CreationDate;
	CString Creator;
	CString Producer;
	CString Title;
	CString Subject;
	CString Keywords;
	CString ModDate;
};

struct LIBPDF_API DateString
{
	CString YEAR;
	CString MONTH;
	CString DAY;
	CString HOUR;
	CString MINUTES;
	CString SECONDS;
};

void LIBPDF_API PdfStringToTime( const CString & pdf_string , DateString & date_string );
bool LIBPDF_API ParseDateString( const CString & date_string , DateString & parsed_date );

class LIBPDF_API PdfDocument
{
public:
	PdfDocument( );
	~PdfDocument( ); 
	BOOL CreateDocument( COleException & e );
	void DestroyDocument();
	BOOL Open( const std::string & pdf_file );
	void Close();
	//CString getInfo( const CString & info_keyword );
	DocInfo getInfo( );

private:
	CAcroPDDoc *  m_pAcroPdDoc;
};



#endif 