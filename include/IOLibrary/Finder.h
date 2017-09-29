#ifndef FINDER_H
#define FINDER_H

#include "iofs.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <locale>
#include <codecvt>
#include <boost/algorithm/string.hpp>
#include <algorithm>

#include "IODevice.h"
#include "QuickTime.h"
#include "dbf.h"
#include "tinyxml2.h"

namespace IO
{
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
					wprintf_s(L"%s\n", file->getFullPath().c_str());
					auto full_path = file->getFullPath();

					files_.push_back(full_path);
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
		bool isQtSignature(const uint8_t * qt_header , const uint32_t size)
		{
			if (memcmp(qt_header, IO::s_ftyp, size) == 0)
				return true;
			else if (memcmp(qt_header, IO::s_moov, size) == 0)
				return true;
			else if (memcmp(qt_header, IO::s_mdat, size) == 0)
				return true;

			return false;
		}
		void testSignatureMP4(const IO::path_string & filePath)
		{
			auto test_file = IO::makeFilePtr(filePath);
			//const uint8_t const_header[] = { 0x66 , 0x74 , 0x79 , 0x70/*0x47 , 0x40 , 0x00 , 0x10 , 0x00 , 0x00 , 0xB , 0x011*/ };
			const uint32_t offset = 4;
			const uint32_t header_size = 4;
			uint8_t buff[header_size];
			ZeroMemory(buff, header_size);
			if (test_file->Open(IO::OpenMode::OpenRead))
			{
				if (test_file->Size() >= header_size)
				{
					test_file->setPosition(offset);
					test_file->ReadData(buff, header_size);
					test_file->Close();

					if (isQtSignature(buff,header_size) == false)
					{
						boost::filesystem::rename(filePath, filePath + L".bad_file");
					}
				}

			}


		}
		void Rename_wave(const IO::path_string & filePath)
		{
			auto test_file = IO::makeFilePtr(filePath);
			const uint32_t date_offset = 0x154;
			const uint32_t date_size = 18;
			const uint32_t check_size = 0x16A;
			char buff[date_size + 1];
			ZeroMemory(buff, date_size + 1);

			if (test_file->Open(IO::OpenMode::OpenRead))
			{
				if (check_size > test_file->Size())
					return;

				test_file->setPosition(date_offset);
				test_file->ReadData((ByteArray)buff, date_size);


				if (buff[0] == '2' && buff[1] == '0')
				{

					std::string date_string(buff);
					std::replace(date_string.begin(), date_string.end(), ' ', '-');
					std::replace(date_string.begin(), date_string.end(), '.', '-');
					std::replace(date_string.begin(), date_string.end(), ':', '-');
					date_string.insert(10, 1, '-');

					IO::path_string new_date_str(date_string.begin(), date_string.end());

					boost::filesystem::path src_path(filePath);
					auto folder_path = src_path.parent_path().generic_wstring();
					auto only_name_path = src_path.stem().generic_wstring();
					auto ext = src_path.extension().generic_wstring();
					auto new_name = folder_path + L"//" + new_date_str + L"-" + only_name_path + ext;
					test_file->Close();
					try
					{
						boost::filesystem::rename(filePath, new_name);
					}
					catch (const boost::filesystem::filesystem_error& e)
					{
						std::cout << "Error: " << e.what() << std::endl;
					}

				}


			}
		}

		void TestEndJpg(const IO::path_string & filePath)
		{
			auto test_file = IO::makeFilePtr(filePath);
			const uint32_t constSize = 2;
			uint8_t buff[constSize];
			ZeroMemory(buff, constSize);

			//const uint8_t const_r3d_header[] = { 0x52 , 0x45 , 0x44 , 0x32 };
			const uint8_t const_end_jpg[] = {0xFF, 0xD9};
			//const uint8_t const_end_pdf[] = { 0x25 , 0x25 , 0x45 , 0x4F , 0x46 , 0x0A };

			if (test_file->Open(IO::OpenMode::OpenRead))
			{
				if (test_file->Size() >= constSize)
				{
					test_file->setPosition(test_file->Size() - constSize);
					test_file->ReadData(buff, constSize);
					test_file->Close();

					if (memcmp(buff, const_end_jpg, constSize) != 0)
					{

						boost::filesystem::rename(filePath, filePath + L".bad_file");
					}
				}

			}
		}
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
						{
							auto full_name = addBackSlash(current_folder) + file_name;

							//TestEndJpg(full_name);
							//zbk_rename(full_name);
							//removeNullsFromEndFile(full_name, 2048);
							//addDateToFile(full_name);
							//testSignatureMP4(full_name);
							//Rename_wave(full_name);
							files_.push_back(full_name);

							folder_node->AddFile(file_name);
						}
					}

					//SearchFiles(
				} while (FindNextFile(hFindFile, &findData));

				FindClose(hFindFile);

			}


		}



	};

};

#endif