// StructuredStorageReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <string>
#include <stdlib.h>
#include <iostream>

#include "IOLibrary\FileFinder.h"
#include "boost/filesystem.hpp"
#include "libstructstorage/libstructstorage.h"

#include <conio.h>
   void main(int argc, char **argv) {
	   setlocale(LC_ALL, "Ukranian");

	   std::string source_dir = "f:\\raw\\";
	   std::string target_dir = "f:\\NoName\\";
		
	   identify_files(source_dir, target_dir);

	  
	  printf("\r\nPress any key.");
	  _getch();
      //DumpProps(file_name);
   }



//int _tmain(int argc, _TCHAR* argv[])
//{
//	setlocale(LC_ALL, "Russian");
//
//	
//	return 0;
//}


/*
void func()
{
	WCHAR * file = L"d:\\Temp\\00057.doc";
	DWORD inBytes = 0;

	IPropertySetStorage* pProperSetStorage = NULL;
	IPropertyStorage * pPropertyStorage = NULL;

	HRESULT hr = S_OK;

	if ( SUCCEEDED( hr = StgOpenStorageEx( file , STORAGE_OPEN_MODE_FLAGS , STGFMT_ANY , 0 , NULL , 0 , IID_IPropertySetStorage , (void **) (& pProperSetStorage ) ) ) )
	{
		if ( SUCCEEDED( hr = pProperSetStorage->Open( FMTID_SummaryInformation , GetAccessMode( STGM_READ, TRUE ) , & pPropertyStorage ) ) )
		{
			IEnumSTATPROPSTG  * pEnum = NULL;
			if ( SUCCEEDED( hr = pPropertyStorage->Enum( &pEnum ) ) )
			{
				int nStruct = 1;
				STATPROPSTG pStatPropSTG = {0};
				DWORD nCelt = 1;
				PROPSPEC prop_spec;
				prop_spec.ulKind = PRSPEC_PROPID;
				PROPVARIANT  pPropVariant[1] = {0};

				if ( SUCCEEDED ( hr = pEnum->Next( nStruct , &pStatPropSTG , &nCelt ) ) )
				do
				{
					prop_spec.ulKind = PRSPEC_PROPID;
					prop_spec.propid = pStatPropSTG.propid;
					

					if ( SUCCEEDED (hr = pPropertyStorage->ReadMultiple( 1 , & prop_spec , pPropVariant) ) )
					{
						if ( pPropVariant[0].vt == VT_LPSTR )
						{
							std::string autor_str( pPropVariant[0].pszVal );
							printf( "%s : %s \r\n" , SummaryInformationName(prop_spec.propid ).c_str(), autor_str.c_str() );
						}
						else if ( pPropVariant[0].vt == VT_FILETIME )
						{
							SYSTEMTIME st = {0};
							if ( FileTimeToSystemTime( &pPropVariant[0].filetime , &st ) )
							{
								char date_buffer[255];
								char time_buffer[255];
								GetDateFormatA( LOCALE_USER_DEFAULT  , 0 , &st , "yyyy-MM-dd" , date_buffer , 255);
								GetTimeFormatA( LOCALE_USER_DEFAULT , 0 , &st , "HH-mm-ss" , time_buffer , 255);
								printf("%s : ( date : %s ) (time : %s ) \r\n" , SummaryInformationName( prop_spec.propid ).c_str(), date_buffer , time_buffer );

							}

						}
					}
					if ( FAILED ( hr = pEnum->Next( nStruct , &pStatPropSTG , &nCelt ) ) )
						break;
				} while ( nCelt != 0 );
			}
		}

		
		

		int k = 1;
		k = 2;

	}

}
*/