#pragma once

#include "constants.h"
#include "IODevice.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

namespace IO
{
	inline path_string addBackSlash(const path_string & path_str)
	{
		path_string new_string(path_str);
		if (*path_str.rbegin() != back_slash)
			new_string.push_back(back_slash);

		return new_string;
	}

	inline bool createFoldersFromPath(const path_string & path)
	{

		return false;
	}
	inline bool isDirectoryAttribute(const WIN32_FIND_DATA & attributes)
	{
		return (attributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}

	inline bool isOneDotOrTwoDots(const path_string & name_string)
	{
		if (name_string.compare(OneDot) == 0)
			return true;
		if (name_string.compare(TwoDot) == 0)
			return true;
		return false;
	}


	inline bool isPresentInList(const path_string & text_value, const path_list & listToFind)
	{
		auto str = text_value;
		boost::algorithm::to_lower(str);
		auto findIter = std::find(listToFind.begin(), listToFind.end(), str);
		return (findIter != listToFind.end()) ? true : false;
	}

	inline path_string getExtension(const path_string & file_name)
	{
		boost::filesystem::path file_path(file_name);	// can crash ????
		return file_path.extension().generic_wstring();
	}

	inline bool isOffice2003(const path_string & file_extension)
	{
		return isPresentInList(file_extension, listExtensions2003);
	}

	inline bool isOffice2007(const path_string & file_extension)
	{
		return isPresentInList(file_extension, listExtensions2007);
	}

	inline void JoinWithService(const path_string & data_file, 
								const path_string & service_file,
								const path_string & target_file,
								const uint32_t data_size,
								const uint32_t service_size)
	{
		const uint32_t target_page = data_size + service_size;
		
		File f_data(data_file);
		if (!f_data.Open(OpenMode::OpenRead))
		{
			wprintf_s(L"Error open file. %s\n", f_data.getFileName().c_str());
			return;
		}

		File f_sevice(service_file);
		if (!f_sevice.Open(OpenMode::OpenRead))
		{
			wprintf_s(L"Error open file. %s\n", f_sevice.getFileName().c_str());
			return;
		}

		File f_target(target_file);
		if (!f_target.Open(OpenMode::Create))
		{
			wprintf_s(L"Error open file. %s\n", f_target.getFileName().c_str());
			return;
		}

		
		Buffer data_buffer(data_size);
		Buffer service_buffer(service_size);
		Buffer target_buffer(target_page);

		bool bResult = false;

		LONGLONG max_size = f_data.Size();

		LONGLONG cur = 0;
		while (cur < max_size)
		{
			if ( f_data.ReadData(data_buffer.data, data_buffer.data_size) == 0 )
			{
				wprintf_s(L"Error read data file.\n");
				break;
			}

			
			if (f_sevice.ReadData(service_buffer.data, service_buffer.data_size) == 0)
			{
				wprintf_s(L"Error read service file.\n");
				break;
			}

			memcpy(target_buffer.data, data_buffer.data, data_buffer.data_size);
			memcpy(target_buffer.data + data_buffer.data_size, service_buffer.data, service_buffer.data_size);

			if (f_target.WriteData(target_buffer.data, target_buffer.data_size) == 0)
			{
				wprintf_s(L"Error write  file.\n");
				break;
			}


			cur += data_size;

		}


	}

	inline path_string toNumberString(const uint32_t number)
	{
		const int numValues = 11;
		wchar_t buff[numValues];
		ZeroMemory(buff, sizeof(wchar_t) * numValues);

		swprintf_s(buff, numValues, L"%.10u", number);
		path_string number_str(buff);
		return number_str;
	}

	inline path_string toNumberExtension(const uint32_t number, const path_string & extension)
	{
		return toNumberString(number) + extension;
	}
	inline path_string toFullPath(const path_string & folder, const uint32_t number, const path_string & extension)
	{
		return addBackSlash(folder) + toNumberString(number) + extension;
	}


};