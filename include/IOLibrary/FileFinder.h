#ifndef FILEFINDER_H
#define FILEFINDER_H

#include "iofs.h"
#include "utility.h"

namespace IO
{
	class FileFinder
	{
	private:
		IO::DirectoryNode::Ptr rootFolder_;
		path_list list_ext_;

	public:
		FileFinder()
		{

		}
		void FindFiles(const std::string, stringlist ext_list)
		{
			// convert std::string to IO::path_string 
		}
		void FindFiles(const path_string & folder)
		{
			
		}
		void FindFiles(const path_string & folder, const path_list & list_extensions)
		{
			this->rootFolder_ = IO::DirectoryNode::CreateDirectoryNode(folder);
			this->list_ext_ = list_extensions;
			Find(rootFolder_);
		}
		stringlist getFileNames() const {
			stringlist list;
			return list;
		}
	private:

		void Find(IO::DirectoryNode::Ptr folder_node)
		{
			path_string current_folder = folder_node->getFullPath();
			path_string mask_folder(IO::addBackSlash(current_folder) + mask_all);
			HANDLE hFindFile = INVALID_HANDLE_VALUE;
			WIN32_FIND_DATA findData = { 0 };

			hFindFile = FindFirstFile(mask_folder.c_str(), &findData);
			if (hFindFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					path_string current_file(findData.cFileName);

					if (isOneDotOrTwoDots(current_file))
						continue;

					if (isDirectoryAttribute(findData))
					{
						IO::path_string new_folder = findData.cFileName;

						auto new_folder_node = IO::DirectoryNode::CreateDirectoryNode(new_folder);

						folder_node->AddDirectory(new_folder_node);
						Find(new_folder_node);
					}

					// Than it's must be file
					if (!isDirectoryAttribute(findData))
					{
						IO::path_string file_name = findData.cFileName;
						boost::filesystem::path tmp_path(file_name);
						IO::path_string file_ext = tmp_path.extension().wstring();

						if ( list_ext_.empty())
							folder_node->AddFile(file_name);
						else
						if (isPresentInList(file_ext, this->list_ext_))
							folder_node->AddFile(file_name);
					}

					//SearchFiles(
				} while (FindNextFile(hFindFile, &findData));

				FindClose(hFindFile);

			}


		}



	};

};

#endif