
#include "iofunctions.h"

#include <assert.h>
#include "constants.h"

#include <algorithm>

bool IO::open_read( HANDLE & handle , const std::string & path)
{
	handle = CreateFileA( path .c_str(),
						GENERIC_READ ,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						NULL,
						OPEN_EXISTING,
						0,
						NULL);
	DWORD dwError = GetLastError();
	return (handle != INVALID_HANDLE_VALUE) ? true : false;		
	
}

bool IO::open_write(HANDLE & handle, const std::string & path)
{
	handle = CreateFileA( path .c_str(),
						GENERIC_READ | GENERIC_WRITE ,
						FILE_SHARE_READ,
						NULL,
						OPEN_EXISTING,
						0,
						NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;	
}

bool IO::create_file( HANDLE & handle , const std::string & path )
{
	handle = CreateFileA( path .c_str(),
						GENERIC_WRITE ,
						FILE_SHARE_READ,
						NULL,
						CREATE_ALWAYS,
						0,
						NULL);
	return (handle != INVALID_HANDLE_VALUE) ? true : false;	
}

LONGLONG IO::getFileSize(HANDLE & handle)
{
	LARGE_INTEGER liSize;
	::GetFileSizeEx(handle, &liSize);
	return liSize.QuadPart;
}

void IO::set_position( HANDLE & handle , LONGLONG position )
{
	LARGE_INTEGER pos;
	pos.QuadPart = position;

	::SetFilePointerEx( handle , pos , NULL , FILE_BEGIN );
}

bool IO::read_block( HANDLE & handle , BYTE * buffer , DWORD size , DWORD & bytesRead )
{
	assert ( handle != INVALID_HANDLE_VALUE );
	assert( handle != nullptr );
	assert( size != 0 );

	bytesRead = 0;
	return (::ReadFile(handle , buffer , size , &bytesRead , NULL )  ) ? true : false;
}

bool IO::write_block( HANDLE & handle , BYTE * buffer , DWORD size , DWORD & bytesWritten )
{
	assert ( handle != INVALID_HANDLE_VALUE );
	assert(buffer != nullptr);
	assert( size != 0 );

	bytesWritten = 0;
	return (::WriteFile(handle , buffer , size , &bytesWritten , NULL ) ) ? true : false ;
}

bool IO::write_block_to_file( HANDLE & source , LONGLONG source_offset , DWORD block_size, HANDLE & target , LONGLONG write_offset )
{
	assert( source != INVALID_HANDLE_VALUE );
	assert( target != INVALID_HANDLE_VALUE );
	assert( block_size != 0 );

	BYTE read_buffer[ BLOCK_SIZE + SECTOR_SIZE ];
	//BYTE write_buffer[ BLOCK_SIZE ];

	DWORD bytes_read = 0;
	DWORD bytes_written = 0;


	DWORD bytes_to_copy = 0;
	DWORD cur_pos = 0;
	DWORD bytes_to_write = 0;

	bool bReadResult = false;
	bool bWriteResult = false;


	IO::set_position( source , source_offset );

	while( cur_pos < block_size )
	{
		if ( (cur_pos + BLOCK_SIZE) < block_size )
			bytes_to_copy = BLOCK_SIZE;
		else
		{
			bytes_to_copy = ( block_size - cur_pos );
		}

		bytes_to_write = bytes_to_copy;

		if ( bytes_to_copy % SECTOR_SIZE != 0 )
		{
			bytes_to_copy /= SECTOR_SIZE;
			++bytes_to_copy;
			bytes_to_copy *= SECTOR_SIZE;
		}


		bReadResult = IO::read_block(source , read_buffer , bytes_to_copy , bytes_read );
		if ( bytes_read == 0 && !bReadResult )
			return false;

		bWriteResult = IO::write_block( target , read_buffer , bytes_to_write , bytes_written );
		if ( bytes_written == 0 && !bWriteResult )
			return false;

		cur_pos += bytes_read;
	}
	return true;
}

bool IO::read_all(HANDLE & handle, BYTE * buffer, LONGLONG size)
{
	assert( handle != INVALID_HANDLE_VALUE);
	assert(buffer != nullptr);
	assert ( size != 0 );

	LONGLONG cur = 0;
	DWORD bytesRead = 0;
	DWORD bytesToRead = BLOCK_SIZE;


	while (cur < size)
	{
		bytesToRead = IO::BytesToCopy(cur , size , BLOCK_SIZE);
		if ( !IO::read_block(handle , &buffer[cur] , BLOCK_SIZE , bytesRead ) )
			return false;

		if ( bytesRead == 0 )
			return false;

		cur += bytesRead;
	}
	return false;
}

bool IO::copy_to_file( HANDLE & source , LONGLONG source_offset , LONGLONG block_size, HANDLE & target , LONGLONG target_offset )
{
	assert( source != INVALID_HANDLE_VALUE );
	assert( target != INVALID_HANDLE_VALUE );
	assert( block_size != 0 );

	BYTE read_buffer[ BLOCK_SIZE + SECTOR_SIZE ];
	//BYTE write_buffer[ BLOCK_SIZE ];

	DWORD bytes_read = 0;
	DWORD bytes_written = 0;


	DWORD bytes_to_copy = 0;
	LONGLONG cur_pos = 0;
	DWORD bytes_to_write = 0;

	bool bReadResult = false;
	bool bWriteResult = false;


	IO::set_position( source , source_offset );

	while( cur_pos < block_size )
	{
		if ( (cur_pos + BLOCK_SIZE) < block_size )
			bytes_to_copy = BLOCK_SIZE;
		else
		{
			bytes_to_copy = DWORD( block_size - cur_pos );
		}

		bytes_to_write = bytes_to_copy;

		/*	This need only for physical drive/*/
		//if ( bytes_to_copy % SECTOR_SIZE != 0 )
		//{
		//	bytes_to_copy /= SECTOR_SIZE;
		//	++bytes_to_copy;
		//	bytes_to_copy *= SECTOR_SIZE;
		//}


		bReadResult = IO::read_block(source , read_buffer , bytes_to_copy , bytes_read );
		if ( bytes_read == 0 && !bReadResult )
			return false;

		bWriteResult = IO::write_block( target , read_buffer , bytes_to_write , bytes_written );
		if ( bytes_written == 0 && !bWriteResult )
			return false;

		cur_pos += bytes_read;
	}
	return true;
}

DWORD IO::BytesToCopy(LONGLONG current , LONGLONG max_size , DWORD block_size)
{
	return ((current + block_size) < max_size) ? block_size : DWORD(max_size - current);
}

std::string IO::file_path_number( const std::string & folder , DWORD number , const std::string & extension )
{
	char buff[10];
	memset(buff,0,10);
	sprintf_s(buff,10,"%.9d", number );
	std::string file_name( folder );

	file_name.append( buff );
	file_name.append(extension);

	return file_name;
}

bool IO::isLastBackspace( const std::string str )
{
	if ( !str.empty() )
	{
		char back_space = *str.rbegin();
		if ( back_space == '\\' )
			return true;
	}
		
	return false;
}
void IO::addBackspace( std::string & str )
{
	if ( ! isLastBackspace( str ) )
		str.append("\\");
}
std::string IO::addFolderName( const std::string & folder , std::string new_folder)
{
	std::string result_name( folder );
	if ( !IO::isLastBackspace( result_name ) )
		result_name.append("\\");

	result_name.append( new_folder );
	return result_name;
}
std::string IO::make_file_path( const std::string & folder , const std::string & file )
{
	std::string new_file( folder );
	if ( ! IO::isLastBackspace( folder ) )
		new_file.append("\\");

	new_file.append( file );
	return new_file;
}

bool IO::isPresentInList( const stringlist & strlist , const std::string & text )
{
	auto findIter = std::find( strlist.begin() , strlist.end() , text );
	return (findIter != strlist.end() ) ? true : false;
}

std::string IO::numberToString( const int number )
{
	char buff[10];
	memset(buff,0,10);
	sprintf_s(buff,10,"%.5d", number );
	return std::string( buff );
}
LONGLONG IO::toSectors( const LONGLONG data_val)
{
	LONGLONG sectors = data_val;
	sectors /= SECTOR_SIZE;
	return sectors;
}

void IO::read_table( const std::string & table_file ,  tablelist & table_list )
{
	HANDLE hFile = INVALID_HANDLE_VALUE;
	if ( !IO::open_read( hFile , table_file ) )
		return;

	DWORD file_size = ::GetFileSize( hFile , NULL );
	if ( file_size > 0 )
	{
		BYTE * data = new BYTE[ file_size ];
		DWORD bytes_read = 0;

		if ( !IO::read_block( hFile , data , file_size , bytes_read ) )
			return;

		if ( bytes_read == 0 )
			return ;

		unsigned short table_value = 0;
		unsigned short * pAddr = ( unsigned short * ) data ;


		// set table from memory
		while ( pAddr < ( pAddr + file_size/sizeof( unsigned short ) ) )
		{
			table_value = *pAddr << 8 | *pAddr >>8;

			if ( table_value == 0 )
				break;

			table_list.push_back( table_value );


			++pAddr;
		}
		delete [] data;
	}

	CloseHandle( hFile );
}

void IO::gatherByTable( const std::string & source_file , const std::string & target_file , const tablelist * table_list )
{
	HANDLE hSource = INVALID_HANDLE_VALUE;
	HANDLE hTarget = INVALID_HANDLE_VALUE;

	if ( !IO::open_read( hSource , source_file ) )
		return;

	if ( !IO::create_file( hTarget , target_file ) )
		return;

	const int block_size = 2211840;
	const LONGLONG max_size = 9059696640;


	auto iter = table_list->begin();

	ULONGLONG source_offset = 0;
	ULONGLONG write_offset = 0;

	BYTE data[block_size];
	DWORD bytes_read = 0;
	DWORD bytes_write = 0;
	int iTargetPage = 0;

	auto tableValue = 0;

	while ( iter != table_list->end() )
	{
		tableValue = *iter;
		source_offset =   (ULONGLONG)tableValue * block_size ;
		write_offset =  (ULONGLONG)iTargetPage * block_size ;

		if ( source_offset < max_size )
		{
			IO::set_position( hSource , source_offset );
			if ( IO::read_block( hSource , data , block_size , bytes_read) )
				if ( bytes_read == 0 )
					break;

			IO::set_position( hTarget , write_offset );
			if ( IO::write_block( hTarget , data , block_size , bytes_write ) )
				if ( bytes_write == 0 )
					break;

		}

		++iTargetPage;
		++iter;
	}

	CloseHandle( hSource );
	CloseHandle( hTarget );



}

void IO::joinWithBad( const std::string & withBad , const std::string & withoutBad , const std::string & target_file)
{
	DWORD max_size = 0;
	HANDLE hWithBad = INVALID_HANDLE_VALUE;
	HANDLE hWithoutBad = INVALID_HANDLE_VALUE;
	if ( !IO::open_read( hWithBad , withBad ) )
		return ;
	if ( !IO::open_read( hWithoutBad , withoutBad ) )
		return ;

	DWORD size1 = ::GetFileSize( hWithBad , NULL );
	DWORD size2 = ::GetFileSize( hWithoutBad , NULL );

}

bool IO::cmpSectorWithByte( const BYTE * data , BYTE byte_value)
{
	for ( int i = 8; i < 512; ++i )
	{
		if ( data[i] != byte_value )
			return false;
	}
	return true;
}

bool IO::isDataSector( const BYTE * data )
{
	if ( !data )
		return false;

	if ( IO::cmpSectorWithByte( data , 0xFF ) )
		return false;
	
	if ( IO::cmpSectorWithByte( data , 0x00 ) )
		return false;

	return true;
}

void IO::SaveOnlyData( const std::string & source_file , const std::string & target_file )
{
	HANDLE hSource = INVALID_HANDLE_VALUE;
	HANDLE hTarget = INVALID_HANDLE_VALUE;

	if ( ! IO::open_read( hSource , source_file ) )
	{
		printf( "Error open %s to read", source_file.c_str() );
		return;
	}

	if ( ! IO::create_file( hTarget , target_file ) )
	{
		printf( "Error open %s to read", target_file.c_str() );
		return;
	}

	LARGE_INTEGER max_size = { 0 };
	if ( !::GetFileSizeEx(hSource , &max_size) )
	{
		printf("Error to get file size ");
		return;
	}
	if ( max_size.QuadPart == 0 )
	{
		printf("file size == 0");
		return;
		
	}


	const int BlockSize = 256*SECTOR_SIZE;
	BYTE read_data[ BlockSize ] ;
	BYTE write_data[ BlockSize ] ;
	DWORD bytesRead = 0;
	DWORD bytesWritten = 0;
	int write_offset = 0;
	LONGLONG source_offset = 0;
	LONGLONG target_offset = 0;

	while ( true )
	{
		if ( source_offset >= max_size.QuadPart )
			break;

		IO::set_position( hSource , source_offset );
		if ( !IO::read_block( hSource , read_data, BlockSize , bytesRead ) )
			break;
		if ( bytesRead == 0 )
			break;

		write_offset = 0;
		for ( int iSector = 0 ; iSector < bytesRead ; iSector += SECTOR_SIZE )
		{
			if ( IO::isDataSector( &read_data[iSector] ) )
			{
				memcpy( write_data + write_offset , read_data + iSector , SECTOR_SIZE );
				write_offset += SECTOR_SIZE;
			}
		}

		if ( write_offset > 0 )
		{
			if ( !IO::write_block( hTarget , write_data , write_offset , bytesWritten ) )
				break;

		}

		source_offset += bytesRead;
	}

	CloseHandle( hSource );
	CloseHandle( hTarget );

}

void IO::XorFiles(const std::string &file1, const std::string & file2, const std::string & target_file)
{
	//HANDLE hFile1 = INVALID_HANDLE_VALUE;
	//HANDLE hFile2 = INVALID_HANDLE_VALUE;
	//HANDLE hTarget = INVALID_HANDLE_VALUE;

	//if ( ! IO::open_read(hFile1 , file1) )
	//{
	//	printf("Error open file: %s\r\n" , file1.c_str() );
	//	return;
	//}
	//if (!IO::open_read(hFile2, file2))
	//{
	//	printf("Error open file: %s\r\n", file2.c_str());
	//	return;
	//}
	//if (!IO::create_file(hTarget, target_file))
	//{
	//	printf("Error open file: %s\r\n", target_file.c_str());
	//	return;
	//}

	//DWORD bytesRead = 0;
	//DWORD bytesWritten = 0;

	//BYTE buff1[BLOCK_SIZE];
	//BYTE buff2[BLOCK_SIZE];
	//BYTE buff_write[BLOCK_SIZE];


	//LONGLONG pos = 0;

	//while (true)
	//{
	//	// file 1
	//	IO::set_position(hFile1 , pos );
	//	if ( !IO::read_block(hFile1 , buff1 , BLOCK_SIZE , bytesRead ) )
	//		break;

	//	if ( bytesRead == 0 )
	//		break;

	//	// file 1
	//	IO::set_position(hFile2, pos);
	//	if (!IO::read_block(hFile2, buff2, BLOCK_SIZE, bytesRead))
	//		break;

	//	if (bytesRead == 0)
	//		break;


	//	for ( DWORD iByte = 0 ; iByte < bytesRead; ++iByte)
	//		buff_write[iByte] = buff1[iByte]^buff2[iByte];

	//	IO::set_position(hTarget, pos);
	//	if (!IO::read_block(hTarget, buff_write, BLOCK_SIZE, bytesRead))
	//		break;

	//	if (bytesRead == 0)
	//		break;


	//}


	//CloseHandle(hFile1);
	//CloseHandle(hFile2);
	//CloseHandle(hTarget);


}



void to_big_endian( DWORD & val )
{
	val = ntohl( val );
}
void to_little_endian( DWORD & val )
{
	val = htonl( val );
}
const DWORD nameToValue( const char * name  )
{
	return * ( DWORD * ) name;
}
