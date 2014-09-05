// IOLibraryTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_TEST_MODULE IOFunctionsTestModule

#include <boost/test/unit_test.hpp>

#include "IOLibrary\iofunctions.h"
#include "IOLibrary\RemoveInserts.h"
#include "IOLibrary\constants.h"

#include "IOLibrary\Entropy.h"

BOOST_AUTO_TEST_CASE( TestIsLastBackspace )
{
	BOOST_CHECK_EQUAL( IO::isLastBackspace("c:\\asd\\" ) , true );
	BOOST_CHECK_EQUAL( IO::isLastBackspace("c:\\asd" ) , false );
}

BOOST_AUTO_TEST_CASE ( TestAddFolderName )
{
	BOOST_CHECK_EQUAL( IO::addFolderName("c:\\asd\\" , "new_folder" ) , "c:\\asd\\new_folder" );
	BOOST_CHECK_EQUAL( IO::addFolderName("c:\\asd" , "new_folder" ) , "c:\\asd\\new_folder" );
}

BOOST_AUTO_TEST_CASE( TestMakeFilePath )
{
	BOOST_CHECK_EQUAL( IO::make_file_path("c:\\1" , "1.txt")  , "c:\\1\\1.txt" );
	BOOST_CHECK_EQUAL( IO::make_file_path("c:\\1\\" , "1.txt")  , "c:\\1\\1.txt" );
}

BOOST_AUTO_TEST_CASE( TestIsPresentInList )
{
	stringlist strlist;
	strlist.push_back( ".doc");
	strlist.push_back( ".xls");
	strlist.push_back( ".ppt");

	BOOST_CHECK_EQUAL( IO::isPresentInList( strlist , ".doc" ) , true );
	BOOST_CHECK_EQUAL( IO::isPresentInList( strlist , ".xls" ) , true );
	BOOST_CHECK_EQUAL( IO::isPresentInList( strlist , ".xxx" ) , false );
}

BOOST_AUTO_TEST_CASE( TestNumberToString )
{
	BOOST_CHECK_EQUAL ( IO::numberToString( 1 ) , "00001" );
	BOOST_CHECK_EQUAL ( IO::numberToString( 11111 ) , "11111" );
	BOOST_CHECK_EQUAL ( IO::numberToString( -1 ) , "-00001" );

}

BOOST_AUTO_TEST_CASE( TestToSectors )
{
	BOOST_CHECK_EQUAL ( IO::toSectors( 1024 ) , 2 );
	BOOST_CHECK_EQUAL ( IO::toSectors( 512 ) , 1 );
	BOOST_CHECK_EQUAL ( IO::toSectors( 0 ) , 0 );

}

BOOST_AUTO_TEST_CASE( TestMapToPage )
{
	const int map_size = 5;
	BYTE map_data[map_size];
	
	const int page_size = map_size*BITS_IN_BYTE;
	BYTE page_data[page_size];

	map_data[1] = 3;
	mapToPage( map_data , map_size , page_data , page_size );
	BOOST_CHECK_EQUAL ( page_data[ 14 ] , SKIP_NARKER );
	BOOST_CHECK_EQUAL ( page_data[ 15 ] , SKIP_NARKER );


	map_data[3] = 0xC0;
	mapToPage( map_data , map_size , page_data , page_size );
	BOOST_CHECK_EQUAL ( page_data[ 24 ] , SKIP_NARKER );
	BOOST_CHECK_EQUAL ( page_data[ 25 ] , SKIP_NARKER );
}



BOOST_AUTO_TEST_CASE( TestNameToValue )
{
	const DWORD be_ftyp = 0x66747970;
	const DWORD le_ftyp = 0x70797466;

	const DWORD be_moov = 0x6d6f6f76;
	const DWORD le_moov = 0x766f6f6d;

	const DWORD be_mdat = 0x6d646174;
	const DWORD le_mdat = 0x7461646d;

	const DWORD be_free = 0x66726565;
	const DWORD le_free = 0x65657266;

	const DWORD be_skip = 0x736b6970;
	const DWORD le_skip = 0x70696b73;

	const DWORD be_wide = 0x77696465;
	const DWORD le_wide = 0x65646977;

	const DWORD be_pnot = 0x706e6f74;
	const DWORD le_pnot = 0x746f6e70;

	BOOST_CHECK_EQUAL( nameToValue( QTKeyword::ftyp_name)  , le_ftyp );
	BOOST_CHECK_EQUAL( nameToValue( QTKeyword::moov_name)  , le_moov );
	BOOST_CHECK_EQUAL( nameToValue( QTKeyword::mdat_name)  , le_mdat );
	BOOST_CHECK_EQUAL( nameToValue( QTKeyword::free_name)  , le_free );
	BOOST_CHECK_EQUAL( nameToValue( QTKeyword::skip_name)  , le_skip );
	BOOST_CHECK_EQUAL( nameToValue( QTKeyword::wide_name)  , le_wide );
	BOOST_CHECK_EQUAL( nameToValue( QTKeyword::pnot_name)  , le_pnot );
}

BOOST_AUTO_TEST_CASE( TestisDataSector )
{
	BYTE zero_data[512];
	ZeroMemory( zero_data , 512 );

	BOOST_CHECK_EQUAL( IO::isDataSector( zero_data ), true );

	zero_data[10] = 0xFF;
	BOOST_CHECK_EQUAL( IO::isDataSector( zero_data ), true );

	zero_data[10] = 0xFA;
	BOOST_CHECK_EQUAL( IO::isDataSector( zero_data ), false );
}

BOOST_AUTO_TEST_CASE(getEntropyTest)
{
	//IO::
}