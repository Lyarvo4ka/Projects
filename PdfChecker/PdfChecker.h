#pragma once

#include "resource.h"



#include "IOLibrary/iofunctions.h"
#include "IOLibrary/FileFinder.h"
#include <iostream>




void identify_files(const std::string & source_dir, const std::string & target_dir);

void identify_files(const std::string & source_dir, const std::string & target_dir)
{
	std::string bad_dir = "bad";
	stringlist ext_list;
	ext_list.push_back(".doc");
	ext_list.push_back(".xls");
	ext_list.push_back(".ppt");

	FileFinder finder;
	finder.FindFiles(source_dir, ext_list);
	auto file_list = finder.getFileNames();

	DWORD counter = 0;

	auto fileIter = file_list.begin();

	while (fileIter != file_list.end())
	{
		std::string source_name(*fileIter);
		SSReader ssreader;
		SummaryInformation sammary_info;

		boost::filesystem::path file_path(source_name);

		std::string ext = file_path.extension().generic_string();
		std::string file_name = file_path.filename().generic_string();
		std::string path = file_path.root_path().generic_string();

		bool bResult = false;
		std::string target_name;

		if (bResult = ssreader.read_properties(source_name, sammary_info))
		{
			std::string dataName = getDateTimeFromFileTime(sammary_info.lastSavedTime().getFiletime());
			if (!dataName.empty())
				target_name = dataName + IO::numberToString(counter++) + ext;
			else
				target_name = IO::numberToString(counter++) + ext;
			//printf("target name: %s\r\n", target_name.c_str());

		}
		else
		{
			target_name = IO::numberToString(counter++) + ext;
		}

		std::string target_file_path;
		std::string ext_folder = ext.substr(1);
		std::string new_folder = (bResult) ? ext_folder : bad_dir;
		std::string target_folder = add_folder(target_dir, new_folder);
		target_file_path = IO::make_file_path(target_folder, target_name);

		try
		{

			boost::filesystem::copy_file(source_name, target_file_path);
		}
		catch (const boost::filesystem::filesystem_error& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}

		++fileIter;
	}
}

