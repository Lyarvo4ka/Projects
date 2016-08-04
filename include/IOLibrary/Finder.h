#ifndef FINDER_H
#define FINDER_H

#include "iofs.h"


namespace IO
{
	class Finder
	{
	private:
		IO::DirectoryNode::Ptr rootFolder_;
		path_list list_ext_;

	public:
		Finder()
		{

		}
		void FindFiles(const path_string & folder)
		{
			this->rootFolder_ = IO::DirectoryNode::CreateDirectoryNode(folder);
			Find(rootFolder_);
		}
		void FindFiles(const path_string & folder, const path_list & list_extensions)
		{
			this->list_ext_ = list_extensions;
			FindFiles(folder);
		}
		DirectoryNode::Ptr getFiles()
		{
			return rootFolder_;
		}
		void printFiles(DirectoryNode::Ptr current_folder)
		{

			if (auto file = current_folder->getFirstFile())
			{
				auto folder_path = current_folder->getFullPath();
				do
				{
					
					wprintf_s(L"%s\n", file->getFullPath().c_str());

					file = current_folder->getNextFile();
				} while (file != nullptr);
			}
			if (auto folder = current_folder->getFirstFolder())
			{
				do
				{
					printFiles(folder);
					folder = current_folder->getNextFolder();
				} while (folder != nullptr);
			}

		}
		void printAll()
		{
			if (!rootFolder_)
				return;

			wprintf_s(L"Root: %s\n", rootFolder_->getFullPath().c_str());
			printFiles(rootFolder_);

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