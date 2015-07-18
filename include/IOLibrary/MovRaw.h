#ifndef MOVRAW_H
#define MOVRAW_H

#include "AbstractRaw.h"
#include "constants.h"

#include <conio.h>
#include <stddef.h>  
#include <memory>

#include "iolibrary_global.h"




#pragma pack( 1 )
struct QTAtom
{
	DWORD qt_size;
	DWORD qt_type;
};
#pragma pack( )



class QTRaw
	: public AbstractRaw
{


};












#pragma pack( 1 )
struct QtHeader
{
	BYTE header[Signatures::qt_header_size];
	BYTE qt__CAEP[8];	// skip this
	//BYTE wide[4];
	DWORD data_size;
	BYTE mdat[Signatures::mdat_size];
};
#pragma pack( )

#pragma pack( 1 )
struct moov_data
{
	DWORD moov_size;
	BYTE moov_text[4];
};
#pragma pack( )





struct InfoPartData
{
	LONGLONG offset;
	DWORD size;

	LONGLONG getLastPos() const
	{
		return (LONGLONG ) ( offset + size );
	}
};





inline bool isQtHeader( QtHeader * pHeader , BYTE * pSignature )
{
	//if ( SIZEOF_ARRAY( pSignature ) != Signatures::qt_header_size )
	//	return false;

	return ( memcmp( pHeader->header , pSignature , Signatures::qt_header_size ) == 0 )	? true : false;

}

inline bool isMoovText( moov_data * pMoov_data)
{
	auto size = Signatures::moov.size();
	auto data = Signatures::moov.data();
	//return ( memcmp( pMoov_data->moov_text , data , size == 0 ) ) ? true : false;
	for ( DWORD i = 0 ; i < size ; ++i )
	{
		if ( pMoov_data->moov_text[i] != data[i] ) 
			return false;
	}

	return true;
}



class MovRaw
	: public AbstractRaw
{
private:
	std::string folder_;
public:
	MovRaw(const std::string & file_name , const std::string & output_folder )
		: AbstractRaw( file_name )
		, folder_ ( output_folder )
	{
	}
	MovRaw(const DWORD drive_number , const std::string & output_folder )
		: AbstractRaw( drive_number )
		, folder_ ( output_folder )
	{
	}

	virtual bool cmp_header(const BYTE * data ) 
	{
		QtHeader * pQtHeader = ( QtHeader * ) data;
		return isQtHeader( pQtHeader , ( BYTE *) Signatures::qt_header );

	}
	bool find_header( const BYTE * data , const int data_size , int & header_offset )
	{
			for ( int iSector = 0 ; iSector < data_size ; iSector += SECTOR_SIZE )
			{
				if ( cmp_header( &data[iSector] ) )
				{
					header_offset = iSector;
					return true;
				}

			}
			return false;
	}

	DWORD getDataSize( const BYTE * data )
	{
		QtHeader * pQtHeader = ( QtHeader * ) data;
		DWORD size = pQtHeader->data_size;
		to_big_endian(size);
		return size;
	}	

	void show_found_header( LONGLONG offset_bytes )
	{
		printf( "Found header : %lld (sectors)\r\n", (LONGLONG) (offset_bytes / SECTOR_SIZE) );
	}

	void execute() override
	{
		if ( ! this->isReady() )
		{
			printf( "Error device isn't ready. \r\nProgram will be closed." ) ;
			_getch();
			return;
		}

		auto hSource = this->getHandle();

		BYTE read_buffer[BLOCK_SIZE];
		const int moov_data_size = sizeof( moov_data ) ;
		BYTE moov_buffer[1024];

		DWORD bytesRead = 0;

		bool bReadResult = false;


		LONGLONG pos = 0x149190000;
		DWORD mdat_offset = 24;
		LONGLONG moov_pos = 0;

		DWORD counter = 0;

		bool bHeader = false;

		HANDLE hTarget = INVALID_HANDLE_VALUE;
		int block_offset = 0;
		LONGLONG lSector = 0;

		while ( true )
		{
			IO::set_position( *hSource , pos );
			bReadResult = IO::read_block( *hSource , read_buffer , BLOCK_SIZE , bytesRead );
			if ( ( !bReadResult ) && ( bytesRead != 0 ) )
				break;


			if ( find_header( read_buffer , bytesRead , block_offset ) )
			{
				InfoPartData HeaderDataPart;
				HeaderDataPart.offset = pos + (LONGLONG)block_offset;
				HeaderDataPart.size = getDataSize( &read_buffer[block_offset]);
				show_found_header( HeaderDataPart.offset );
			//}

			//if ( bHeader )
			//{

				moov_pos = HeaderDataPart.offset;
				moov_pos += HeaderDataPart.size;
				moov_pos += mdat_offset;
				lSector = moov_pos;
				lSector /= SECTOR_SIZE;
				lSector *= SECTOR_SIZE;
				DWORD moov_offset = (DWORD) (moov_pos - lSector);

				IO::set_position( *hSource , lSector );
				DWORD bytes_read = 0;
				bReadResult =  IO::read_block( *hSource , moov_buffer , 1024 , bytes_read );
				if ( ( !bReadResult ) && ( bytes_read != 0 ) )
					break;

				moov_data * pMoov_data = ( moov_data *) &moov_buffer[moov_offset];
				if ( isMoovText( pMoov_data ) )
				{
					to_big_endian( pMoov_data->moov_size);
					DWORD file_size = mdat_offset + HeaderDataPart.size /*+ moov_data_size*/ + pMoov_data->moov_size;
					std::string file_path = IO::file_path_number( folder_ , counter++ , ".mov");
					if ( IO::create_file( hTarget , file_path ) )
						if ( IO::write_block_to_file ( *hSource , HeaderDataPart.offset , file_size , hTarget ) )
						{
							printf( "Write to file %s OK.\r\n" ,  file_path.c_str() );
							CloseHandle( hTarget );

							file_size /= SECTOR_SIZE ;
							file_size *= SECTOR_SIZE;
							pos  = (LONGLONG) (HeaderDataPart.offset + file_size);
							continue;
						}
						else
							printf( "Error to write file  %s.\r\n" , file_path.c_str() );
				}
				else
					printf( "Not found moov_text.\r\n" );

			}

			pos += bytesRead;
		}
	}
	std::string folder() const 
	{
		return folder_;
	}
};


class IOLIBRARY_EXPORT CanonMovRaw
	: public MovRaw
{
private:
	DWORD cluster_size_;
	LONGLONG offset_;
public:
	CanonMovRaw(const std::string & file_name , const std::string & output_folder );
	CanonMovRaw(const DWORD number , const std::string & output_folder );

	void show_error( const std::string & error_text);

	bool cmp_mdat( const BYTE * data );
	bool find_mdat( const BYTE * data , const int data_size , int & offset );
	DWORD getMdatSize( const BYTE * data )
	{
		DWORD * pSize = ( DWORD *) data;
		DWORD mdat_size = *pSize;
		to_big_endian( mdat_size );
		return mdat_size;
	}
	void setClusterSize(const DWORD cluster_size);
	void setOffset(const LONGLONG offset);
	void execute() override;

	bool check_parameters();

};


#endif