#ifndef R3D_RAW_H
#define R3D_RAW_H

#include "IOLibrary/AbstractRaw.h"
#include <string>


enum Raw_State { not_found , found_header };

class r3d_raw
	: public AbstractRaw
{
public:
	r3d_raw (const DWORD drive_number , const std::string & output_folder )
		: AbstractRaw( drive_number )
		, folder_ ( output_folder )
	{

	}
	~r3d_raw() 
	{

	}
	void execute( ) override
	{
		if ( !this->isReady() )
		{
			printf("Device isn't ready.");
			return;
		}
		auto hSource = this->getHandle();

		DWORD bytesRead = 0;
		int counter = 0;
		

		BYTE buffer[BLOCK_SIZE];

		std::string write_file( IO::file_path_number( folder_ , counter++ , ".r3d" ) );

		Raw_State raw_state = not_found; 

		while ( true )
		{
			bytesRead = 0;
			IO::set_position( *hSource , offset );
			if ( !IO::read_block( *hSource , buffer , BLOCK_SIZE , bytesRead ) )
				break;
			if ( bytesRead == 0 )
				break;

			for ( int iPos = 0 ; iPos < BLOCK_SIZE ; iPos += SECTOR_SIZE )
			{
				if ( memcmp( &buffer[iPos] , r3d_header , r3d_header_size ) == 0  )
				{
					if ( raw_state == not_found )
					{
						
					}
					else
					{
						// create new file;
					}
					


				}
			}



	}
private:

	std::string folder_;
};


#endif