#ifndef FINDER_H
#define FINDER_H

#include "iofs.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <locale>
#include <codecvt>
#include <boost/algorithm/string.hpp>


namespace IO
{
	inline int NotNullPosFromEnd(const Buffer & buffer)
	{
		int pos = buffer.data_size - 1;
		while (pos >= 0)
		{
			if (buffer.data[pos] != 0)
				return (buffer.data_size - pos);
			--pos;
		}
		return 0;
	}

	inline void removeNullsFromEndFile(const path_string & file_path , uint32_t sizeToTest = 4096)
	{
		File file(file_path);
		if (!file.Open(OpenMode::OpenWrite))
		{
			wprintf_s(L"Error open file.\n");
			return;
		}

		auto file_size = file.Size();
		Buffer buffer(sizeToTest);
		if (file_size > sizeToTest)
		{
			uint64_t lastBlock = file_size - sizeToTest;
			file.setPosition(lastBlock);
			auto bytesRead = file.ReadData(buffer.data, buffer.data_size);
			if (bytesRead == sizeToTest)
			{
				int not_null = NotNullPosFromEnd(buffer);
				if (not_null > 0)
				{
					uint64_t new_size = file_size - not_null + 1;
					file.setSize(new_size);
					wprintf_s(L"FIle size has been changed %s.\n", file_path.c_str());
				}
			}
		}

	}

	struct pck_t
	{
		char header[3];
		char reserved[29];
		char digits[15];
		char text[33];
	}; 

	class Finder
	{
	private:
		DirectoryNode::Ptr rootFolder_;
		path_list list_ext_;
		path_list files_;

	public:
		void add_extension(path_string ext)
		{
			list_ext_.push_back(ext);
		}
		Finder()
		{

		}
		void FindFiles(const path_string & folder)
		{
			this->rootFolder_ = DirectoryNode::CreateDirectoryNode(folder);
			Find(rootFolder_);
		}
		void FindFiles(const path_string & folder, const path_list & list_extensions)
		{
			this->list_ext_ = list_extensions;
			FindFiles(folder);
		}
		DirectoryNode::Ptr getRoot()
		{
			return rootFolder_;
		}
		path_list getFiles() const
		{
			return files_;
		}
		void printFiles(DirectoryNode::Ptr current_folder)
		{

			if (auto file = current_folder->getFirstFile())
			{
				auto folder_path = current_folder->getFullPath();
				do
				{
					//changeSizeIfFindMarker(file->getFullPath());
					wprintf_s(L"%s\n", file->getFullPath().c_str());
					auto full_path = file->getFullPath();
					removeNullsFromEndFile(full_path);

					files_.push_back(full_path);



					//path_string source_name(full_path.begin(), full_path.end());
					//auto new_name = getNameFromPCKFileAndChangeSize(source_name);
					//const std::string target_folder("d:\\PaboTa\\40746\\result\\");

					//try
					//{
					//	boost::filesystem::rename(full_path, target_folder + new_name + ".PCK");
					//}
					//catch (const boost::filesystem::filesystem_error& e)
					//{
					//	std::cout << "Error: " << e.what() << std::endl;
					//}


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
		std::string getNameFromPCKFileAndChangeSize(const path_string & file_path)
		{
			static int counter = 0;
			++counter;
			File file(file_path);
			if (!file.Open(OpenMode::OpenWrite))
			{
				wprintf_s(L"Error open file.\n");
				return std::to_string(counter);
			}
			std::string new_name = std::to_string(counter);

			auto file_size = file.Size();
			if (file_size > 0)
			{
				uint32_t bytes_read = 0;
				const int pck_size = sizeof(pck_t);

				Buffer buffer((uint32_t)file_size);
				bytes_read = file.ReadData(buffer.data, buffer.data_size);
				if (bytes_read != file_size)
					return std::to_string(counter);

				pck_t * pck_header = (pck_t *)buffer.data;

				std::string digit_name(pck_header->digits);
				std::string text_name(pck_header->text);

				new_name = digit_name + "_"/* + text_name + "_"*/ + std::to_string(counter);
				boost::algorithm::erase_all(new_name, "_"); // '\"'
				//new_name.erase(std::remove_if(new_name.begin(), new_name.end(), '\\'), new_name.end());
				//std::remove_if(new_name.begin(), new_name.end(), );

				int pos = (int)(file_size - 1);
				while (pos != 0)
				{
					if ( buffer.data[pos] != 0)
						break;
					--pos;
				}

				file.setSize(pos+1);
			}

			return new_name;
		}
	private:

		void Find(DirectoryNode::Ptr folder_node)
		{
			path_string current_folder = folder_node->getFullPath();
			path_string mask_folder(addBackSlash(current_folder) + mask_all);
			WIN32_FIND_DATA findData = { 0 };

			HANDLE hFindFile = FindFirstFile(mask_folder.c_str(), &findData);
			if (hFindFile != INVALID_HANDLE_VALUE)
			{
				do
				{
					path_string current_file(findData.cFileName);

					if (isOneDotOrTwoDots(current_file))
						continue;

					if (isDirectoryAttribute(findData))
					{
						path_string new_folder = findData.cFileName;

						auto new_folder_node = DirectoryNode::CreateDirectoryNode(new_folder);

						folder_node->AddDirectory(new_folder_node);
						Find(new_folder_node);
					}

					// Than it's must be file
					if (!isDirectoryAttribute(findData))
					{
						path_string file_name = findData.cFileName;
						boost::filesystem::path tmp_path(file_name);
						path_string file_ext = tmp_path.extension().wstring();

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