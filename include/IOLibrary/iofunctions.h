#ifndef IOFUNCTIONS_H
#define IOFUNCTIONS_H

#include "iolibrary_global.h"

#include <windows.h>
#include <string>
#include <list>
#include <vector>

typedef std::list< std::string > stringlist;
typedef std::vector< unsigned short > tablelist;


namespace IO
{
	bool IOLIBRARY_EXPORT open_read( HANDLE & handle , const std::string & path );
	bool IOLIBRARY_EXPORT open_write( HANDLE & handle , const std::string & path );
	bool IOLIBRARY_EXPORT create_file( HANDLE & handle , const std::string & path );
	LONGLONG IOLIBRARY_EXPORT getFileSize(HANDLE & handle);


	void IOLIBRARY_EXPORT set_position( HANDLE & handle , LONGLONG position );
	bool IOLIBRARY_EXPORT read_block( HANDLE & handle , BYTE * buffer , DWORD size , DWORD & bytesRead );
	bool IOLIBRARY_EXPORT write_block( HANDLE & handle , BYTE * buffer , DWORD size , DWORD & bytesWritten );

	bool IOLIBRARY_EXPORT read_all(HANDLE & handle, BYTE * buffer, LONGLONG size);
	bool IOLIBRARY_EXPORT write_all(HANDLE & handle, BYTE * buffer, LONGLONG size);

	bool IOLIBRARY_EXPORT write_block_to_file( HANDLE & source , 
											   LONGLONG source_offset , 
											   DWORD block_size, 
											   HANDLE & target ,
											   LONGLONG target_offset = 0 );

	bool IOLIBRARY_EXPORT copy_to_file( HANDLE & source , 
										LONGLONG source_offset , 
										LONGLONG block_size, 
										HANDLE & target ,
										LONGLONG target_offset = 0 );

	DWORD IOLIBRARY_EXPORT BytesToCopy(LONGLONG current, LONGLONG max_size, DWORD block_size);

	std::string IOLIBRARY_EXPORT file_path_number( const std::string & folder , DWORD number , const std::string & extension );

	bool IOLIBRARY_EXPORT isLastBackspace( const std::string str );
	void IOLIBRARY_EXPORT addBackspace( std::string & str );
	std::string IOLIBRARY_EXPORT addFolderName( const std::string & folder , std::string new_folder);
	std::string IOLIBRARY_EXPORT make_file_path( const std::string & folder , const std::string & file );

	bool IOLIBRARY_EXPORT isPresentInList( const std::list< std::string > & strlist , const std::string & text );

	// from 1 to "00001"
	std::string IOLIBRARY_EXPORT numberToString( const int number );

	LONGLONG IOLIBRARY_EXPORT toSectors( const LONGLONG data_val );

	void IOLIBRARY_EXPORT read_table( const std::string & table_file ,  tablelist & table_list );
	void IOLIBRARY_EXPORT gatherByTable( const std::string & source_file , const std::string & target_file , const tablelist * table_list );

	void IOLIBRARY_EXPORT joinWithBad( const std::string & withBad , const std::string & withoutBad , const std::string & target_file );
	bool IOLIBRARY_EXPORT cmpSectorWithByte( const BYTE * data , BYTE byte_value);
	bool IOLIBRARY_EXPORT isSectorOnly00( const BYTE * data );
	bool IOLIBRARY_EXPORT isDataSector( const BYTE * data );
	void IOLIBRARY_EXPORT SaveOnlyData( const std::string & source_file , const std::string & target_file );
	void IOLIBRARY_EXPORT XorFiles( const std::string &file1 , const std::string & file2 , const std::string & target_file);

};

void IOLIBRARY_EXPORT to_big_endian( DWORD & val );
void IOLIBRARY_EXPORT to_little_endian( DWORD & val );
const DWORD IOLIBRARY_EXPORT nameToValue( const char * name  );


#endif // IO_FUNCTIONS_H