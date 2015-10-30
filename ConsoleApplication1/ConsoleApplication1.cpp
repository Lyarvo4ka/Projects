// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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
//#include "IOLibrary\BlockNumber.h"


//#include "IOLibrary/SignatureTest.h"
#include "IOLibrary/SignatureTest.h"
//#include "IOLibrary/iofunctions.h"

#include "boost/filesystem.hpp"
//#include "IOLibrary/dbf.h"
//#include "IOLibrary/XorAnalyzer.h"
#include "IOLibrary/MovRaw.h"
#include "IOLibrary/RemoveInserts.h"
#include "IOLibrary/Entropy.h"
#include "IOLibrary/PanasonicRaw.h"

#include "IOLibrary/XorAnalyzer.h"
#include "IOLibrary/GoPro_raw.h"


int main(int argc, char *argv[])
{
	//CanonMovRaw mov_raw("d:\\PaboTa\\38208\\image.bin" , "e:\\38208\\");
	//mov_raw.setClusterSize(131072);
	//mov_raw.execute();

	//DWORD target_number = 4;
	//std::string target_file = drivePathFromNumber(target_number);
	////std::string target_file = "d:\\PaboTa\\38569\\target.bin";
	//
	//std::string xor_file = "d:\\PaboTa\\38569\\encrypted_1.bin";
	//DWORD drive_number = 3;
	//XorHardDrive(drive_number, target_file, xor_file);



	////9347072
	if (argc == 4)
	{


		int i = 1;
		i = 1;
		//std::string source_folder = argv[1];
		//std::string target_folder = argv[2];
		//DWORD block_size = strtol(argv[3], NULL, 10);
		//GoProgRaw gopro_raw(source_folder, target_folder);
		//gopro_raw.execute(block_size);




	}
	else
		std::cout << "You entered invalid params." << std::endl;


	//	XorAnalyzer xorFinder(dump_file);
	//	xorFinder.Analize(xor_file, block_size);
	//}
	//else
	//	show_error_invalid_params();

	printf("finished");
	_getch();
	//Translator::FlyTranslator flyTranslator("d:\\incoming\\fly\\fly_0.dat");
	//flyTranslator.setPageParams(2112, 2048, 64);
	//flyTranslator.setMarkers(2054, 2058);
	////flyTranslator.make_table();
	//flyTranslator.save_data();
		//Signture_Testing("h:\\37870\\");
		//if (argc == 2)
		//{
		//	
		//	
		//}
		//else
		//{
		//	show_error_invalid_params();
		//	return -1;
		//}



	//FileFinder finder;
	//stringlist dbf_ext;
	//dbf_ext.push_back(".dbf");
	//finder.FindFiles("d:\\PaboTa\\37294\\2012_new\\", dbf_ext);
	//stringlist files = finder.getFileNames();
	//auto iter = files.begin();


	//while (iter != files.end())
	//{
	//	auto dbf_file = *iter;
	//	HANDLE hDBF = INVALID_HANDLE_VALUE;
	//	if ( !IO::open_write(hDBF, dbf_file) )
	//		break;

	//	DWORD file_size = 0;

	//	DWORD bytesRead = 0;
	//	dbf_header dbf_data = {0};
	//	if (!IO::read_block(hDBF, (BYTE*)&dbf_data, dbf_header_size, bytesRead))
	//		break;
	//	if ( bytesRead == 0 )
	//		break;

	//	if (dbf_data.numRecords > 0)
	//	{
	//		file_size = dbf_data.numRecords*dbf_data.record_size;
	//		file_size += dbf_data.header_size;

	//		::SetFilePointer(hDBF, file_size, NULL, FILE_BEGIN);
	//		::SetEndOfFile(hDBF);

	//		BYTE end_line = 0x1A;
	//		DWORD bytesWritten = 0;
	//		if (!IO::write_block(hDBF, &end_line, 1, bytesWritten))
	//			break;
	//		if (bytesWritten == 0)
	//			break;
	//	}

	//	::CloseHandle(hDBF);

	//	++iter;

	//}

	//CanonMovRaw mov_raw("d:\\PaboTa\\37277\\image.bin" , "D:\\PaboTa\\37277\\mov\\");
	//mov_raw.execute();

	//IO::JoinWithService("d:\\Public\\37132\\raw.image", "d:\\Public\\37132\\sa.image" , "d:\\Public\\37132\\dump.dump");
	//RemoveBytesByBitMap("d:\\Public\\37132\\0001.dmp" , "d:\\Public\\37132\\target.dump");

	//std::string folder = "H:\\36820\\Partition 2\\!Problem\\";
	//Signture_Testing(folder);

	//save_free_space("i:\\36490\\Free_space.bin", "i:\\36490\\cluster.map", 32768);
	//IO::replaceBads("d:\\PaboTa\\1C\\bads.1CD" , "d:\\PaboTa\\1C\\1Cv8 091214.1CD"  , "D:\\PaboTa\\1C\\target.1CD" );
	//MTS_raw_new mts_raw("m:\\free_space.bin", "M:\\36984\\");
	//mts_raw.execute();

	//get_difference("d:\\PaboTa\\36490\\00468.MTS", atom_size);

	//BlockNumber block_number;
	//if (block_number.OpenDump("d:\\Public\\36564\\01_01.dump"))
	//if (block_number.CreateImage("d:\\Public\\36564\\Image.bin"))
	//{
	//	block_number.ReadBank(0, 1107296256);
	//	block_number.WriteBank(0);

	//	block_number.ReadBank(1107296256, 2214592512);
	//	block_number.WriteBank(1);

	//	block_number.ReadBank(2214592512, 3321888768);
	//	block_number.WriteBank(2);

	//	block_number.ReadBank(3321888768, 4429185024);
	//	block_number.WriteBank(3);

	//	block_number.ReadBank(4429185024, 5536481280);
	//	block_number.WriteBank(4);

	//	block_number.ReadBank(5536481280, 6643777536);
	//	block_number.WriteBank(5);

	//	block_number.ReadBank(6643777536, 7751073792);
	//	block_number.WriteBank(6);

	//	block_number.ReadBank(7751073792, 8858370048);
	//	block_number.WriteBank(7);
	//}



	//IO::calcEntropyForFile("e:\\entropy\\GOPR0595.LRV", 524288);
	//IO::calcEntropyForFile("e:\\entropy\\GOPR0595.MP4", 524288);
	//IO::calcEntropyForFile("e:\\entropy\\GOPR0596.LRV", 524288);
	//IO::calcEntropyForFile("e:\\entropy\\GOPR0596.MP4", 524288);
	//IO::removeLRV("e:\\36141\\36141.bin", "D:\\36141\\free_space.bin.NO_LRV", 524288);

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