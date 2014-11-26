// StructuredStorageReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#include "Objbase.h"
#include "Objidl.h"

#include <string>

#include <stdlib.h>

#define STORAGE_OPEN_MODE_FLAGS        (STGM_TRANSACTED |\
                                        STGM_READWRITE |\
                                        STGM_SHARE_EXCLUSIVE)

    struct CatalogHeader
    {
        WORD      cbSize;
        WORD      wVersion;
        DWORD     dwEntryCount;
    };


	DWORD GetAccessMode( DWORD dwMode, BOOL fStream )
{
    dwMode &= 0x3;

    DWORD dwFlags = dwMode;

    // the root only needs Deny_Write, streams need exclusive....
    if ( dwMode == STGM_READ && !fStream )
    {
        dwFlags |= STGM_SHARE_DENY_WRITE;
    }
    else
    {
        dwFlags |= STGM_SHARE_EXCLUSIVE;
    }

    return dwFlags;
}

#define CATALOG_STREAM      L"Catalog"

/*
  // Dumps simple PROPVARIANT values.
   void DumpPropVariant(PROPVARIANT *pPropVar) {
      // Don't iterate arrays, just inform as an array.
      if(pPropVar->vt & VT_ARRAY) {
         printf("(Array)\n");
         return;
      }

      // Don't handle byref for simplicity, just inform byref.
      if(pPropVar->vt & VT_BYREF) {
         printf("(ByRef)\n");
         return;
       }

      // Switch types.
      switch(pPropVar->vt) {
      case VT_EMPTY:
         printf("(VT_EMPTY)\n");
         break;
      case VT_NULL:
         printf("(VT_NULL)\n");
         break;
      case VT_BLOB:
         printf("(VT_BLOB)\n");
         break;
      case VT_BOOL:
         printf("%s (VT_BOOL)\n",
         pPropVar->boolVal ? "TRUE/YES" : "FALSE/NO");
         break;
      case VT_I2: // 2-byte signed int.
         printf("%d (VT_I2)\n", (int)pPropVar->iVal);
         break;
      case VT_I4: // 4-byte signed int.
         printf("%d (VT_I4)\n", (int)pPropVar->lVal);
         break;
      case VT_R4: // 4-byte real.
         printf("%.2lf (VT_R4)\n", (double)pPropVar->fltVal);
         break;
      case VT_R8: // 8-byte real.
         printf("%.2lf (VT_R8)\n", (double)pPropVar->dblVal);
         break;
         case VT_BSTR: // OLE Automation string.
         {
            // Translate into ASCII.
            char dbcs[1024];
            char *pbstr = (char *)pPropVar->bstrVal;
            size_t i = 0;
			wcstombs_s( &i , dbcs, pPropVar->bstrVal, *((DWORD *)(pbstr-4)));
            dbcs[i] = 0;
            printf("%s (VT_BSTR)\n", dbcs);
         }
         break;
      case VT_LPSTR: // Null-terminated string.
         {
         printf("%s (VT_LPSTR)\n", pPropVar->pszVal);
         }
         break;
      case VT_FILETIME:
         {
            char *dayPre[] =
                         {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

            FILETIME lft;
            FileTimeToLocalFileTime(&pPropVar->filetime, &lft);                SYSTEMTIME lst;
            FileTimeToSystemTime(&lft, &lst);

            printf("%02d:%02d.%02d %s, %s %02d/%02d/%d (VT_FILETIME)\n",
               1+(lst.wHour-1)%12, lst.wMinute, lst.wSecond,
               (lst.wHour>=12) ? "pm" : "am",
               dayPre[lst.wDayOfWeek%7],
               lst.wMonth, lst.wDay, lst.wYear);
         }
         break;
      case VT_CF: // Clipboard format.
         printf("(Clipboard format)\n");

         break;
      default: // Unhandled type, consult wtypes.h's VARENUM structure.
         printf("(Unhandled type: 0x%08lx)\n", pPropVar->vt);
         break;
      }
   }

   // Dump's built-in properties of a property storage.
   void DumpBuiltInProps(IPropertySetStorage *pPropSetStg) {
      printf("\n==================================================\n");
      printf("BuiltInProperties Properties...\n");
      printf("==================================================\n");

      IPropertyStorage *pPropStg = NULL;
      HRESULT hr;

      // Open summary information, getting an IpropertyStorage.
      hr = pPropSetStg->Open(FMTID_SummaryInformation,
      STGM_READ | STGM_SHARE_EXCLUSIVE, &pPropStg);
      //hr = pPropSetStg->Open(FMTID_UserDefinedProperties,
         //STGM_READ | STGM_SHARE_EXCLUSIVE, &pPropStg);
      if(FAILED(hr)) {
         printf("No Summary-Information.\n");
         return;
      }
      // Array of PIDSI's you are interested in.
      struct pidsiStruct {
         char *name;
         long pidsi;
      } 
	  pidsiArr[] = {
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
         printf("IPropertyStg::ReadMultiple() failed w/error %08lx\n",
                hr);
      }
      else {
         // Dump properties.
         for( int i=0; i<nPidsi; i++) {
            printf("%16s: ", pidsiArr[i].name);
            DumpPropVariant(pPropVar + i);
         }
      }

      // De-allocate memory.
      delete [] pPropVar;
      delete [] pPropSpec;

      // Release obtained interface.
      pPropStg->Release();

   }

   // Dump's custom properties of a property storage.
   void DumpCustomProps(IPropertySetStorage *pPropSetStg) {
      printf("\n==================================================\n");
      printf("Custom Properties...\n");
      printf("==================================================\n");

      IPropertyStorage *pPropStg = NULL;
      HRESULT hr;
      IEnumSTATPROPSTG *pEnumProp;

      // Open User-Defined-Properties, getting an IpropertyStorage.
      hr = pPropSetStg->Open(FMTID_UserDefinedProperties,
         STGM_READ | STGM_SHARE_EXCLUSIVE, &pPropStg);
      if(FAILED(hr)) {
         printf("No User Defined Properties.\n");
         return;
      }

      // Get property enumerator.
      hr = pPropStg->Enum(&pEnumProp);
      if(FAILED(hr)) {
      pPropStg->Release();
         printf("Couldn't enumerate custom properties.\n");
         return;
      }

      // Enumerate properties.
      STATPROPSTG sps;
      ULONG fetched;
      PROPSPEC propSpec[1];
      PROPVARIANT propVar[1];
      while(pEnumProp->Next(1, &sps, &fetched) == S_OK) {
         // Build a PROPSPEC for this property.
         ZeroMemory(&propSpec[0], sizeof(PROPSPEC));
         propSpec[0].ulKind = PRSPEC_PROPID;
         propSpec[0].propid = sps.propid;

         // Read this property.

         hr = pPropStg->ReadMultiple(1, &propSpec[0], &propVar[0]);
         if(!FAILED(hr)) {
            // Translate Prop name into ASCII.
           // char dbcs[1024];
            char *pbstr = (char *)sps.lpwstrName;
            int i = 0;
			//stombs_s(&i, dbcs, sps.lpwstrName, *((DWORD *)(pbstr-4)));
           //bcs[i] = 0;

            // Dump this property.
            wprintf(L"%16s: ", sps.lpwstrName );
            DumpPropVariant(&propVar[0]);
         }
      }

      // Release obtained interface.
      pEnumProp->Release();
      pPropStg->Release();

   }

   // Dump's custom and built-in properties of a compound document.
   void DumpProps(char *filename) {
      // Translate filename to Unicode.
      WCHAR wcFilename[1024];
      setlocale( LC_ALL, "" );
      size_t i =0;
	  mbstowcs_s(&i, wcFilename, filename, strlen(filename));
      setlocale( LC_ALL, "C" );
      wcFilename[i] = 0;

      IStorage *pStorage = NULL;
      IPropertySetStorage *pPropSetStg = NULL;
      HRESULT hr;

      // Open the document as an OLE compound document.
      hr = ::StgOpenStorage(wcFilename, NULL,
      STGM_READ | STGM_SHARE_EXCLUSIVE, NULL, 0, &pStorage);

      if(FAILED(hr)) {
         if(hr == STG_E_FILENOTFOUND)
            printf("File not found.");
         else if(hr == STG_E_FILEALREADYEXISTS)
            printf("Not a compound file.");
         else
            printf("StgOpenStorage() failed w/error %08lx", hr);
         return;
      }

      // Obtain the IPropertySetStorage interface.
      hr = pStorage->QueryInterface(
              IID_IPropertySetStorage, (void **)&pPropSetStg);
      if(FAILED(hr)) {
         printf("QI for IPropertySetStorage failed w/error %08lx", hr);
         pStorage->Release();
         return;
      }

      // Dump properties.
      DumpBuiltInProps(pPropSetStg);
      DumpCustomProps(pPropSetStg);

      // Release obtained interfaces.
      pPropSetStg->Release();
      pStorage->Release();
   }

   // Program entry-point.

   */

#include "StructuredStorageReader.h"

#include "IOLibrary\FileFinder.h"

#include "boost/filesystem.hpp"

#include "libstructstorage/libstructstorage.h"

#include <conio.h>
   void main(int argc, char **argv) {
	   setlocale(LC_ALL, "Ukranian");
      // Validate arguments.
      //if(argc != 2) {
      //   printf("- OLE Document Property Viewer\n");
      //   printf("- Usage: %s filename", argv[0]);
      //   return;
      //}

      // Pass filename to the subroutine.
	  //std::wstring file_name = L"d:\\Temp\\00057.doc";
	  //SSReader ssreader;
	  //SummaryInformation summary_info;
	  //if ( ssreader.read_properties( file_name ,  summary_info ) )
	  //{
		 // printf( "Last saved time: %s", getDateTimeFromFileTime( summary_info.lastSavedTime() ).c_str() );

	  //}

	   //std::string sSource = "d:\\Public\\35044\\02_01.dump";
	   //std::string sTarget = "d:\\Public\\35044\\02_01.dump.target";
	   //std::string sTable = "d:\\Public\\35044\\table_2.bin";


	   //tablelist table;
	   //IO::read_table( sTable  , table );
	   //IO::gatherByTable( sSource , sTarget , &table );


	   //printf("\r\n\r\n");

	   std::string source_dir = "G:\\raw\\";
	   std::string target_dir = "G:\\NoName\\doc\\";
	   std::string bad_dir =	"G:\\NoName\\bad\\";
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