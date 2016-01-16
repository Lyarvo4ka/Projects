#ifndef FILEFINDER_H
#define FILEFINDER_H

#include "iofunctions.h"

#include <boost/filesystem.hpp>


//class AbstractFolder

#include "iofs.h"




inline bool isDirectoryAttribute(const WIN32_FIND_DATAA & attributes)
{
	return attributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
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
		FindFileRecursive(folder, ext);
	}



	stringlist getFileNames() const
	{
		return file_list_;
	}
private:
	// recursive function
	void FindFileRecursive(const std::string & folder, const stringlist & ext)
	{
		if (folder.empty())
			return;


		std::string mask_folder(folder + "*.*");

		HANDLE hFindFile = INVALID_HANDLE_VALUE;
		WIN32_FIND_DATAA findData = { 0 };

		hFindFile = FindFirstFileA(mask_folder.c_str(), &findData);
		if (hFindFile != INVALID_HANDLE_VALUE)
		{
			do
			{
				if (!strncmp(findData.cFileName, ".", 1) || !strncmp(findData.cFileName, "..", 2))
					continue;

				if (isDirectoryAttribute(findData))
				{
					std::string sub_folder(IO::addFolderName(folder, findData.cFileName));
					IO::addBackspace(sub_folder);
					FindFiles(sub_folder, ext);
				}

				// Than it's must be file
				if (!isDirectoryAttribute(findData) )
				{
					std::string file_name(findData.cFileName);

					auto file_ext = boost::filesystem::extension(file_name);
				//	if (IO::isPresentInList(ext, file_ext))
					{
						file_list_.push_back(IO::make_file_path(folder, file_name));
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