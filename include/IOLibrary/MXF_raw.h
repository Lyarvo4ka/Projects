#include "AbstractRaw.h"
#include "constants.h"

//
//#pragma comment(lib, "wsock32.lib")

inline bool isHeader( BYTE * data ,  const BYTE * header , const int header_size )
{
	if ( header_size <= 0 )
		return false;

	return (memcmp( data, header, header_size ) == 0 ) ;
	
}

class MXFVideoRaw
	: public AbstractRaw
{
	static const int SectorSize = 512;
	static const int BlockCount = 256;
	static const int BlockSize = BlockCount * SectorSize;
	static const int TailSize = 512;
public:
	MXFVideoRaw( const std::string & source_file, const std::string & output_folder )
		: AbstractRaw( source_file )
		, folder_( output_folder )
	{

	}
	MXFVideoRaw( const DWORD drive_number , const std::string & output_folder )
		: AbstractRaw( drive_number )
		, folder_ ( output_folder )
	{

	}
	void execute( )
	{
		if ( !this->isReady() )
		{
			printf("Device isn't ready.");
			return;
		}
		auto hSource = this->getHandle();

		BYTE read_buffer[BlockSize];
		LONGLONG file_offset = 0;
		LONGLONG offset = 0;
		DWORD bytesRead = 0;
		int counter = 0;
		DWORD file_size = 0;

		bool bFound = 0;

		BYTE tail_sector[SECTOR_SIZE];

		while ( true )
		{
			bytesRead = 0;
			IO::set_position( *hSource , offset );
			if ( !IO::read_block( *hSource , read_buffer , BlockSize , bytesRead ) )
				break;
			if ( bytesRead == 0 )
				break;

			for ( DWORD iSector = 0 ; iSector < bytesRead ; iSector += SectorSize )
			{
				if ( isHeader( &read_buffer[iSector] , Signatures::mxf_header , Signatures::mxf_header_size ) )
				{
					file_offset = offset;
					file_offset += iSector;					
					printf( "Found mxf_header : %lld\r\n", (LONGLONG) (file_offset / SECTOR_SIZE) );


					DWORD * pFile_size = (DWORD*) &read_buffer[iSector + 48];
					file_size = ntohl(*pFile_size);

					if ( file_size % SECTOR_SIZE != 0 )
						printf( "File size divide by 512 isn't 0\r\n" );

					LONGLONG tail_offset = ( file_offset + file_size );

					IO::set_position( *hSource , tail_offset );
					DWORD sector_read = 0;
					if ( !IO::read_block( *hSource , tail_sector , TailSize , sector_read ) )
						break;
					if ( bytesRead == 0 )
						break;					

					if ( isHeader( tail_sector , Signatures::mxf_footer , Signatures::mxf_footer_size ) )
					{
						HANDLE hWrite = INVALID_HANDLE_VALUE;
						std::string write_file( IO::file_path_number( folder_ , counter++ , ".mxf" ) );

						if ( !IO::create_file(hWrite , write_file) )
						{
							printf("error to create new file...\r\n");
							exit(-1);
						}
						DWORD full_size = file_size + TailSize;
						if ( !IO::write_block_to_file( *hSource , file_offset , full_size , hWrite ) )
						{
							printf("error to write to file...\r\n");
							break;
						}
						else
							printf("Write file OK.\r\n");

							offset = file_offset ;
							offset += full_size ;
							CloseHandle(hWrite);

							bFound = true;
							break;
					}
				}

				

			}
			if ( !bFound )
				offset += bytesRead;
			else
				bFound = false;
		}


	}
private:
	std::string folder_;
};