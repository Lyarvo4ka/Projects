#ifndef ABSTRACT_RAW_H
#define ABSTRACT_RAW_H

#include <windows.h>
#include <string>

#include "iofunctions.h"



class AbstractRaw
{
public:
	AbstractRaw( const std::string & file_name  )
		: hSource_( INVALID_HANDLE_VALUE )
		, bReady_( false )
	{
		bReady_ = IO::open_read( hSource_ , file_name );
	}
	AbstractRaw( const DWORD drive_number  )
		: hSource_( INVALID_HANDLE_VALUE )
		, bReady_( false )
	{
		std::string drive_path( drivePathFromNumber( drive_number ) );
		bReady_ = IO::open_read( hSource_ , drive_path );
	}
	virtual ~AbstractRaw()
	{
		close();
	}
	bool isReady() const
	{
		return bReady_;
	}
	void close()
	{
		if ( hSource_ != INVALID_HANDLE_VALUE )
		{
			CloseHandle( hSource_ );
			hSource_ = INVALID_HANDLE_VALUE;
			bReady_ = false;
		}
	}
	HANDLE * getHandle() 
	{
		return &hSource_;
	}
	virtual void execute() = 0;
private:
	HANDLE hSource_;
	bool bReady_;
};

#endif
