#pragma once

#include "constants.h"
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

};