#ifndef FILEFINDER_H
#define FILEFINDER_H

#include "iofunctions.h"

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

//class AbstractFolder

#include "iofs.h"




inline bool isDirectoryAttribute(const WIN32_FIND_DATA & attributes)
{
	return attributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
}

using path_list = std::list<IO::path_string>;

inline bool isPresentInList(const IO::path_string & text_value, const path_list & listToFind)
{
	auto str = text_value;
	boost::algorithm::to_lower(str);
	auto findIter = std::find(listToFind.begin(), listToFind.end(), str);
	return (findIter != listToFind.end()) ? true : false;
}

static const wchar_t back_slash = L'\\';
const IO::path_string UNC_prefix = L"\\\\?\\";
const IO::path_string OneDot = L".";
const IO::path_string TwoDot = L"..";
const IO::path_string mask_all = L"*.*";




inline bool isOneDotOrTwoDots(const IO::path_string & name_string)
{
	if (name_string.compare(OneDot) == 0)
		return true;
	if (name_string.compare(TwoDot) == 0 )
		return true;
	return false;
}

class FileFinder
{
private:
	IO::DirectoryNode::Ptr rootFolder_;


public:
	FileFinder()
	{

	}
	void FindFiles(const std::string , stringlist ext_list)
	{}
	void FindFiles(const IO::path_string & folder, const path_list & list_extensions)
	{
		rootFolder_ = IO::DirectoryNode::CreateDirectoryNode(folder);
		Find(rootFolder_, list_extensions);
	}
	stringlist getFileNames() const {
		stringlist list;
		return list;
	}
private:

	void Find(IO::DirectoryNode::Ptr folder_node, const path_list & list_extensions)
	{
		IO::path_string current_folder = folder_node->getFullPath();
		IO::path_string mask_folder(current_folder + mask_all);
		HANDLE hFindFile = INVALID_HANDLE_VALUE;
		WIN32_FIND_DATA findData = { 0 };

		hFindFile = FindFirstFile(mask_folder.c_str(), &findData);
		if (hFindFile != INVALID_HANDLE_VALUE)
		{
			do
			{
				IO::path_string current_file(findData.cFileName);

				if (isOneDotOrTwoDots(current_file))
					continue;

				if (isDirectoryAttribute(findData))
				{
					IO::path_string new_folder = findData.cFileName;
					folder_node->AddDirectory(new_folder);
					//Find(new_folder, list_extensions);
				}

				// Than it's must be file
				if (!isDirectoryAttribute(findData))
				{
					IO::path_string file_name = findData.cFileName;
					boost::filesystem::path tmp_path(file_name);
					IO::path_string file_ext = tmp_path.extension().wstring();
					if (isPresentInList(file_ext, list_extensions))
					{
						folder_node->AddFile(file_name);
					}
				}

				//SearchFiles(
			} while (FindNextFile(hFindFile, &findData));

			FindClose(hFindFile);

		}


	}


	// recursive function
	//void FindFileRecursive(const IO::path_string & folder, const path_list & list_extensions)
	//{
	//	if (folder.empty())
	//		return;

	//	IO::path_string current_folder = AddBackSlash(folder);
	//	IO::path_string mask_folder(current_folder + mask_all);

	//	HANDLE hFindFile = INVALID_HANDLE_VALUE;
	//	WIN32_FIND_DATA findData = { 0 };

	//	hFindFile = FindFirstFile(mask_folder.c_str(), &findData);
	//	if (hFindFile != INVALID_HANDLE_VALUE)
	//	{
	//		do
	//		{
	//			IO::path_string current_file(findData.cFileName);

	//			if ( isOneDotOrTwoDots(current_file) )
	//				continue;

	//			if (isDirectoryAttribute(findData))
	//			{
	//				std::string sub_folder(IO::addFolderName(folder, findData.cFileName));
	//				IO::addBackspace(sub_folder);
	//				//FindFiles(sub_folder, ext);
	//			}

	//			// Than it's must be file
	//			if (!isDirectoryAttribute(findData) )
	//			{
	//				std::string file_name(findData.cFileName);

	//				auto file_ext = boost::filesystem::extension(file_name);
	//				if (IO::isPresentInList(ext, file_ext))
	//				{
	//					auto full_path = IO::make_file_path(folder, file_name);
	//					file_list_.push_back(full_path);
	//				}
	//			}

	//			//SearchFiles(
	//		} while (FindNextFileA(hFindFile, &findData));

	//		FindClose(hFindFile);

	//	}

	//}



};


inline stringlist readAllFiles(const std::string & folder)
{
	FileFinder finder;
	stringlist freelist;
	//finder.FindFiles(folder, freelist);
	//return finder.getFileNames();
	return freelist;
}

#endif