// StructuredStorageReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include <string>
#include <stdlib.h>

#include "IOLibrary\FileFinder.h"
#include "boost/filesystem.hpp"
#include "libstructstorage/libstructstorage.h"

#include <conio.h>
   void main(int argc, char **argv) {
	   setlocale(LC_ALL, "Ukranian");

	   std::string source_dir = "F:\\raw\\";
	   std::string target_dir = "F:\\doc\\";
	   std::string bad_dir =	"F:\\bad\\";
	   stringlist ext_list;
	   ext_list.push_back(".doc");
	   ext_list.push_back(".xls");
	   ext_list.push_back(".ppt");

	   FileFinder finder;
	   finder.FindFiles(source_dir , ext_list);
	   auto file_list = finder.getFileNames();

	   DWORD counter = 0;
	
	   auto fileIter = file_list.begin();

	   while ( fileIter != file_list.end() )
	   {
		   std::string source_name( *fileIter );
		   SSReader ssreader;
		   SummaryInformation sammary_info ;

		   boost::filesystem::path file_path( source_name );

		   std::string ext = file_path.extension().generic_string();
		   std::string file_name = file_path.filename().generic_string();
		   std::string path = file_path. root_path().generic_string();


		   if ( ssreader.read_properties ( source_name , sammary_info ) )
		   {
			   std::string dataName = getDateTimeFromFileTime( sammary_info.lastSavedTime() );

			   std::string target_name ( IO::make_file_path( target_dir , dataName ) + IO::numberToString( counter++ ) + ext);
			   printf("target name: %s\r\n", target_name.c_str() );
			   boost::filesystem::copy_file( source_name , target_name );
			   
			   int k = 1;
			   k = 2;
		   }
		   else
		   {
			   std::string bad_file_name = IO::make_file_path( bad_dir , file_name );
			   boost::filesystem::copy_file( source_name , bad_file_name );
		   }
					

		   ++fileIter;
	   }


	  
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