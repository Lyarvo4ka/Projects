// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#include "IOLibrary\DVR_raw.h"
//#include "IOLibrary\MXF_raw.h"
#include "IOLibrary\MovRaw.h"
//#include "IOLibrary\djvu_raw.h"
//#include "IOLibrary\RemoveInserts.h"
#include <conio.h>


#include <iostream>

#include <string>

void show_help()
{
	std::cout << "To run this programm use : -d|f (path) target folder" << std::endl;
	std::cout << "\t d - to physical drives." << std::endl;
	std::cout << "\t f - to file." << std::endl;

	std::cout << std::endl << std::endl << "Press any key." << std::endl;
	_getch();
}

void show_error_invalid_params()
{
	std::cout <<"You entered invalid params." << std::endl;
	show_help();
}

//#include "IOLibrary\Translator.h"
//#include "IOLibrary\XorAnalyzer.h"

//int main(int argc, char *argv[])
//{
//	if ( argc == 3 )
//	{
//		std::string source_file( argv[1] );
//		//std::string bitmap_file( argv[2] );
//		std::string target_file( argv[2] );
//
//
//		//RemoveBytesByBitMap( source_file , target_file );
//		//RemoveInserts removeInserts( source_file , bitmap_file );
//		//removeInserts.execute( target_file );
//		//XorAnalyzer xorAnalyzer;
//		//xorAnalyzer.Analize( source_file , target_file , 9011200 );
//	}
//	else
//	{
//		printf( "Error. Not correct arguments" );
//	}
//
//	printf("\r\nFinished\r\nPress any key.");
//	_getch();
//	return 0;
//}

//#include "IOLibrary/Entropy.h"

int main(int argc, char *argv[])
{
	////////////	QtMovRaw	////////////
	MovRaw canon_mov( "e:\\freespace.bin" , "D:\\PaboTa\\36262\\raw\\" );
	canon_mov.execute();

	//std::cout <<  std::endl << "arguments count "<< argc << std::endl;

	//calcEntropy("e:\\GOPR0591.LRV", 131072);

	//removeLRV("e:\\36141\\36141.bin", "e:\\36141\\36141.bin_NO_LRV");

	//removeLRV("e:\\36141\\1.mp4", "e:\\36141\\1.mp4_no_lrv");



	//if ( argc == 2 )
	//{
	//	if ( argv[1] == "?" )
	//		show_help();

	//	return 0;
	//}
	//else
	//	if ( argc == 3 )
	//	{
			//std::string source_file( argv[1] );
			//std::string target_file( argv[2] );

			//MovRename movReaname;
			//movReaname.rename_files( "E:\\res\\" );

			//RemoveBytesByBitMap(source_file , target_file );
		//}
		//else
		//{
		//	show_error_invalid_params();
		//	return -1;
		//}

}

/*
int main(int argc, char *argv[])
{

	//Translator::iPhone1 iPhone;
	//iPhone.open( "d:\\Public\\35179_iPhone\\Result.dump" );
	//iPhone.execute( "d:\\Public\\35179_iPhone\\Result.bin" );

	////////////	QtMovRaw	////////////

	std::cout <<  std::endl << "arguments count "<< argc << std::endl;

	if ( argc == 2 )
	{
		if ( argv[1] == "?" )
			show_help();

		return 0;
	}
	else
	if ( argc == 4 )
	{
		std::string sParam( argv[1] );
		if ( sParam.size() == 2 )
			if ( sParam[0] == '-' )
			{
				MovRaw * pMovRaw = nullptr;

				std::string target_folder( argv[3] );
				if ( sParam[1] == 'f' )
				{
					std::string soruce_file( argv[2] );
					pMovRaw = new MovRaw( soruce_file , target_folder );
				}
				else
				if ( sParam[1] = 'd' )
				{
					DWORD drive_number = strtol( argv[2] , NULL , 10 );
					pMovRaw = new MovRaw( drive_number , target_folder );
				}

				if ( pMovRaw )
				{
					pMovRaw->execute();
					delete pMovRaw;
					pMovRaw = nullptr;
					std::cout << "Finished." << "Press any key."<<std::endl;
					_getch();
				}
				else
				{
					show_error_invalid_params();
					return -1;
				}

			}

	}
	else
	{
		show_error_invalid_params();
		return -1;
	}


	//DWORD drive_number = strtol( argv[1] , NULL , 10 );

	//CanonMovRaw mov_raw( "e:\\35192.img"  , "D:\\Public\\35192\\" );
	//mov_raw.execute();

	//DjvuRaw djvu_raw( drive_number , folder );
	//MovRaw mov_raw( file , folder );
	//mov_raw.execute();

	//const int map_size = 5;
	//BYTE map_data[map_size];
	//ZeroMemory( map_data , map_size );
	//
	//const int page_size = map_size*BITS_IN_BYTE;
	//BYTE page_data[page_size];

	//map_data[1] = 0x03;
	//mapToPage( map_data , map_size , page_data , page_size );

	//map_data[3] = 0xC0;
	//mapToPage( map_data , map_size , page_data , page_size );



	//BYTE source_data[page_size];
	//memset( source_data, 11 , page_size );
	//source_data[14] = 0xAA;
	//source_data[15] = 0xAA;
	//source_data[24] = 0xAA;
	//source_data[25] = 0xAA;

	//BYTE target_data[page_size];
	//memset( target_data, 0xBB , page_size );


	//copyPageWithMap( source_data , page_data, target_data , page_size );

	//std::string source_file( argv[1] );
	//std::string bit_map( argv[2] );
	//std::string target_file( argv[3] );

	//RemoveInserts remIns( source_file , bit_map );
	//remIns.execute( target_file );
	//int k = 1;
	//k = 2;

	printf("Finished\r\nPress any key.");
	_getch();
	return 0;
}

*/