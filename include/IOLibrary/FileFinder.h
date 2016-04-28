#ifndef FILEFINDER_H
#define FILEFINDER_H

#include "iofunctions.h"

#include <boost/filesystem.hpp>


//class AbstractFolder

#include "iofs.h"




inline bool isDirectoryAttribute(const WIN32_FIND_DATA & attributes)
{
	return attributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

using path_list = std::list<IO::path_string>;

const wchar_t back_slash = L'\\';
const IO::path_string UNC_prefix = L"\\\\?\\";
const IO::path_string OneDot = L".";
const IO::path_string TwoDot = L"..";
const IO::path_string mask_all = L"*.*";


IO::path_string AddBackSlash(const IO::path_string & path_str)
{
	IO::path_string new_string(path_str);
	if (*path_str.rbegin() != back_slash)
		new_string.push_back(back_slash);

	return new_string;
}

bool isOneDotOrTwoDots(const IO::path_string & name_string)
{
	if (name_string.compare(OneDot))
		return true;
	if (name_string.compare(TwoDot))
		return true;
	return false;
}

class FileFinder
{
private:
	stringlist file_list_;
	IO::DirectoryNode root_folder_;
	IO::Directory * current_;

public:
	FileFinder()
		: root_folder_(IO::DirectoryNode(new IO::Directory("root")))
		, current_(nullptr)
	{

	}

	void FindFiles(const std::string & folder, const stringlist & ext)
	{
		//FindFileRecursive(folder, ext);
	}
	void FindFiles(const IO::path_string & folder, const path_list & list_extensions)
	{
		IO::path_string new_folder = UNC_prefix + folder;
		FindFileRecursive(new_folder, list_extensions);
	}



	stringlist getFileNames() const
	{
		return file_list_;
	}
private:
	// recursive function
	void FindFileRecursive(const IO::path_string & folder, const path_list & list_extensions)
	{
		if (folder.empty())
			return;

		IO::path_string current_folder = AddBackSlash(folder);
		IO::path_string mask_folder(current_folder + mask_all);

		HANDLE hFindFile = INVALID_HANDLE_VALUE;
		WIN32_FIND_DATA findData = { 0 };

		hFindFile = FindFirstFile(mask_folder.c_str(), &findData);
		if (hFindFile != INVALID_HANDLE_VALUE)
		{
			do
			{
				IO::path_string current_file(findData.cFileName);

				if ( isOneDotOrTwoDots(current_file) )
					continue;

				if (isDirectoryAttribute(findData))
				{
					std::string sub_folder(IO::addFolderName(folder, findData.cFileName));
					IO::addBackspace(sub_folder);
					//FindFiles(sub_folder, ext);
				}

				// Than it's must be file
				if (!isDirectoryAttribute(findData) )
				{
					std::string file_name(findData.cFileName);

					auto file_ext = boost::filesystem::extension(file_name);
					if (IO::isPresentInList(ext, file_ext))
					{
						auto full_path = IO::make_file_path(folder, file_name);
						file_list_.push_back(full_path);
					}
				}

				//SearchFiles(
			} while (FindNextFileA(hFindFile, &findData));

			FindClose(hFindFile);

		}

	}



};


inline stringlist readAllFiles(const std::string & folder)
{
	FileFinder finder;
	stringlist freelist;
	finder.FindFiles(folder, freelist);
	return finder.getFileNames();
}

#endif