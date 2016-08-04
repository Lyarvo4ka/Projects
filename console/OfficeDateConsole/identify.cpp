#include "identify.h"

const std::string core_xml_str = "core.xml";
#include "../ZipLib/ZipFile.h"
#include "../libTinyXML2/tinyxml2.h"

#include "IOLibrary/Finder.h"
#include "libstructstorage/libstructstorage.h"

OfficeTester::OfficeTester() :ext_list_({ L".doc",L".xls",L".ppt" })
{

}

void OfficeTester::checkFiles(IO::path_string & folder)
{
	IO::Finder finder;
	finder.FindFiles(folder, ext_list_);
	auto root_folder = finder.getFiles();

	listFiles(root_folder);
}

void OfficeTester::listFiles(IO::DirectoryNode::Ptr dir_node)
{
	if (auto file = dir_node->getFirstFile())
	{
		auto folder_path = dir_node->getFullPath();
		do
		{
			// TODO:::::
			auto file_name = file->getName();

			if (IO::isOffice2003(IO::getExtension(file_name)))
				test_file(folder_path, file_name);
			file = dir_node->getNextFile();
		} while (file != nullptr);
	}
	if (auto folder = dir_node->getFirstFolder())
	{
		do
		{
			listFiles(folder);
			folder = dir_node->getNextFolder();
		} while (folder != nullptr);
	}
}

void OfficeTester::test_file(const IO::path_string & folder, const IO::path_string & file)
{
	// Test file signature
	SSReader ssreader;
	auto file_path = IO::addBackSlash(folder) + file;
	auto pStorage = ssreader.open_storage(file_path);
	if (pStorage)
	{
		wprintf_s(L"%s - ", file_path.c_str());
		if (ssreader.read_storage(pStorage))
		{
			wprintf_s(L"OK\n");
		}
		else
			wprintf_s(L"FALSE\n");

	}



}

/*


void identify_files(const std::string & source_dir, const std::string & target_dir)
{
	std::string bad_dir = "bad";
	stringlist ext_list;
	ext_list.push_back(".doc");
	ext_list.push_back(".docx");
	ext_list.push_back(".xls");
	ext_list.push_back(".xlsx");
	ext_list.push_back(".ppt");
	ext_list.push_back(".pptx");
	//	ext_list.push_back(".pdf");

	FileFinder finder;
	finder.FindFiles(source_dir, ext_list);
	auto file_list = finder.getFileNames();

	DWORD counter = 0;

	auto fileIter = file_list.begin();

	while (fileIter != file_list.end())
	{
		std::string source_name(*fileIter);

		printf("%s -", source_name.c_str());

		boost::filesystem::path file_path(source_name);
		std::string ext = file_path.extension().generic_string();

		bool bResult = false;
		std::string target_name;

		if (isOffice2007(ext))
			bResult = identify_office2007(source_name, target_name, counter);
		else
			bResult = identify_office2003(source_name, target_name, counter);
		++counter;

		std::string target_file_path;
		std::string ext_folder = ext.substr(1);
		std::string new_folder = (bResult) ? ext_folder : bad_dir;
		std::string target_folder = IO::add_folder(target_dir, new_folder);
		target_file_path = IO::make_file_path(target_folder, target_name);

		if ( bResult ) 
			printf(" OK\r\n");
		else
			printf(" FAILED\r\n");


		try
		{
			boost::filesystem::rename(source_name, target_file_path);
		}
		catch (const boost::filesystem::filesystem_error& e)
		{
			std::cout << "Error: " << e.what() << std::endl;
		}
 
		++fileIter;
	}
}
 
bool identify_office2003(const std::string & file_name, std::string & new_filename, int counter)
{
	SSReader ssreader;
	SummaryInformation sammary_info;

	std::string ext = IO::get_extension(file_name);

	new_filename = IO::numberToString(counter++) + ext;

	if (ssreader.read_properties(file_name, sammary_info))
	{
		std::string dataName = getDateTimeFromFileTime(sammary_info.lastSavedTime().getFiletime());
		if (!dataName.empty())
			new_filename = dataName + IO::numberToString(counter) + ext;
		else
			new_filename = IO::numberToString(counter) + ext;

		return true;
	}

	return false;
}


bool identify_office2007(const std::string & file_name, std::string & new_filename, int counter)
{

	std::string ext = IO::get_extension(file_name);
	new_filename = IO::numberToString(counter) + ext;

	auto zip_file = ZipFile::Open(file_name.c_str());
	for (auto i = 0; i < zip_file->GetEntriesCount(); ++i)
	{
		auto zip_entry = zip_file->GetEntry(i);
		if (zip_entry->GetName().compare(core_xml_str) == 0)
		{

			auto decompressStream = zip_entry->GetDecompressionStream();

			std::ofstream output_file;
			output_file.open(core_xml_str);
			output_file << decompressStream->rdbuf();
			output_file.close();

			tinyxml2::XMLDocument xml_doc;
			auto xml_result = xml_doc.LoadFile(core_xml_str.c_str());
			if ( xml_result == tinyxml2::XML_SUCCESS)
				if (auto xml_coreProperties = xml_doc.RootElement())//("cp:coreProperties")
					if (auto xml_dcterm_modified = xml_coreProperties->FirstChildElement("dcterms:modified"))
						if (auto xml_date_element = xml_dcterm_modified->FirstChild())
							if (auto val_text = xml_date_element->ToText() )
							{
								//2014-12-29T08:07:00Z
								auto xml_text_date = val_text->Value();

								std::string original_date = xml_text_date;
								auto tmp_str = parse_string_date(original_date);

								if (!tmp_str.empty())
									new_filename = tmp_str + "-" + IO::numberToString(counter) + ext;
								else
									new_filename = IO::numberToString(counter) + ext;

								
								return true;
							}

		}
	}


	return false;
}



*/