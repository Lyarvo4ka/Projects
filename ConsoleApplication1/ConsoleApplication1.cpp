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

#include "boost/filesystem.hpp"
#include "../ZipLib/ZipFile.h"
#include "../libTinyXML2/tinyxml2.h"

const std::string core_xml_str = "core.xml";

const std::string open_tag = "<dcterms:modified";
const std::string close_tag = "</dcterms:modified>";


int main(int argc, char *argv[])
{
	auto zip_file = ZipFile::Open("d:\\test_folder\\Анкета посетителя фабрики.docx");
	for (auto i = 0; i < zip_file->GetEntriesCount(); ++i)
	{
		auto zip_entry = zip_file->GetEntry(i);
		if (zip_entry->GetName().compare(core_xml_str) == 0)
		{
			printf("Found core.xml\r\n");
			
			auto decompressStream = zip_entry->GetDecompressionStream();

			std::ofstream output_file;
			output_file.open(core_xml_str);
			output_file << decompressStream->rdbuf();
			output_file.close();

			tinyxml2::XMLDocument xml_doc;
			auto result = xml_doc.LoadFile(core_xml_str.c_str());
			auto xml_last_node1 = xml_doc.LastChild();
			auto xml_last_node2 = xml_last_node1->LastChild();
			auto xml_first_node = xml_last_node2->FirstChild();
			auto val_text = xml_first_node->ToText();
			//2014-12-29T08:07:00Z
			auto text = val_text->Value();

		}

	}
	//if (argc == 7)
	//{
		
		//std::string source_file = argv[1];
		//std::string target_file = argv[2];
		//DWORD src_size = strtol(argv[3], NULL, 10);
		//DWORD dst_size = strtol(argv[4], NULL, 10);
		//DWORD page_count = strtol(argv[5], NULL, 10);
		//DWORD block_size = strtol(argv[6], NULL, 10);
		//insertInEachPage(source_file, target_file, src_size, dst_size, page_count, block_size);
	//}
	//else
	//	std::cout << "You entered invalid params." << std::endl;


	printf("finished");
	_getch();


}
