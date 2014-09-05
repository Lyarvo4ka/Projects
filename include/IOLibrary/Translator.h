#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "iolibrary_global.h"

#include "iofunctions.h"



namespace Translator
{


class iPhone1
{
private:
	HANDLE hRead_;
private:
	struct MarkerData
	{
		DWORD marker1;
		WORD marker2;
		ULONGLONG offset;
	};
public:
	iPhone1( )
		: hRead_ ( INVALID_HANDLE_VALUE )
	{
	}
	~iPhone1( )
	{
		CloseHandle(hRead_);
	}

	bool open( const std::string & file )
	{
		return IO::open_read( hRead_ , file );
	}
	void close( )
	{
		CloseHandle( hRead_ );
	}

	void execute( const std::string & target_file )
	{
		const int PageSize = 4224;
		const int DataSize = 4096;
		const int Offset1 = 0;
		const int Offset2 = 4;
		const int MaxPages = 0x200000;


		HANDLE hWrite  = INVALID_HANDLE_VALUE;
		if ( ! IO::create_file( hWrite , target_file ) )
		{
			printf("Error to create file.\r\n");
			return;
		}

		std::vector< MarkerData* > table;
		table.resize( MaxPages );


		DWORD bytesRead = 0;
		BYTE buffer[PageSize];

		ULONGLONG offset = 0;

		DWORD Marker1 = 0;

		while ( true )
		{
			IO::set_position( hRead_ , offset );
			if ( !IO::read_block( hRead_ , buffer , PageSize , bytesRead ) )
				break;
			if ( bytesRead == 0 )
				break;

			DWORD * pMarker1 = (DWORD *) &buffer[ DataSize ];
			Marker1 = * pMarker1;
			WORD * pMarker2 = (WORD *) &buffer[ DataSize + Offset2 ];

			/*to_big_endian( Marker1 );*/

			if (Marker1 < MaxPages )
			{
				if ( table[ Marker1 ] == nullptr )
				{
					MarkerData * pMarkerData = new MarkerData;
					pMarkerData->marker1 = Marker1;
					pMarkerData->marker2 = * pMarker2;
					pMarkerData->offset = offset;
					table[ Marker1 ] = pMarkerData;

				}
				else
				{
					if ( table[ Marker1 ]->marker1 <= * pMarker1 )
					{
						auto pMarkerData = table[ Marker1 ];
						pMarkerData->marker1 = Marker1;
						pMarkerData->marker2 = * pMarker2;
						pMarkerData->offset = offset;
					}
				}
			}
		
			offset += PageSize;
		}

		offset = 0;

		ULONGLONG target_offset = 0;
		DWORD bytesWritten = 0;

		for ( std::size_t iTable = 0; iTable < table.size() ; ++iTable )
		{
			if ( auto pMarkerData = table[iTable] )
			{
				IO::set_position( hRead_ , pMarkerData->offset );
				if ( !IO::read_block( hRead_ , buffer , DataSize , bytesRead ) )
					break;
				if ( bytesRead == 0 )
					break;

				target_offset = (LONGLONG)pMarkerData->marker1 * (LONGLONG)DataSize;
				IO::set_position( hWrite , target_offset );
				if ( ! IO::write_block(hWrite , buffer , DataSize , bytesWritten ) )
					break;
				if ( bytesWritten == 0 )
					break;

			}

		}



		for ( size_t i = 0 ; i < table.size() ; ++i )
			if( table[i] != nullptr )
			{
				delete table[i];
				table[i] = nullptr;
			}


		CloseHandle( hWrite );
		




	}



};

}


#endif