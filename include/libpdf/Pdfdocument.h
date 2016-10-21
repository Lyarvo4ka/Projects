#ifndef PDFDOCUMENT_H
#define PDFDOCUMENT_H

#include <string>

#include "libpdf.h"
#include "acrobat.h"
#include "iac.h"

#include <afxdisp.h>

BOOL LIBPDF_API isAcrobatInstalled( COleException &e );

const CStringA sAutor = "Autor";
const CStringA sCreationDate = "CreationDate";
const CStringA sCreator = "Creator";
const CStringA sProducer = "Producer";
const CStringA sTitle = "Title";
const CStringA sSubject = "Subject";
const CStringA sKeywords = "Keywords";
const CStringA sModDate = "ModDate";


struct LIBPDF_API DocInfo
{
	CStringA Author;
	CStringA CreationDate;
	CStringA Creator;
	CStringA Producer;
	CStringA Title;
	CStringA Subject;
	CStringA Keywords;
	CStringA ModDate;
};

struct LIBPDF_API DateString
{
	CStringA YEAR;
	CStringA MONTH;
	CStringA DAY;
	CStringA HOUR;
	CStringA MINUTES;
	CStringA SECONDS;
};

void LIBPDF_API PdfStringToTime( const CStringA & pdf_string , DateString & date_string );
bool LIBPDF_API ParseDateString( const CStringA & date_string , DateString & parsed_date );

class LIBPDF_API PdfDocument
{
public:
	PdfDocument( );
	~PdfDocument( ); 
	BOOL CreateDocument( COleException & e );
	void DestroyDocument();
	BOOL Open( const std::string & pdf_file );
	void Close();
	//CStringA getInfo( const CStringA & info_keyword );
	DocInfo getInfo( );

private:
	CAcroPDDoc *  m_pAcroPdDoc;
};



#endif 