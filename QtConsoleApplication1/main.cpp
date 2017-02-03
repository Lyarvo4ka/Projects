#include <QtCore/QCoreApplication>

#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QDebug>
#include <QList>



#include <boost/lexical_cast.hpp>

#include <iostream>

#include "../JsonReader/JsonReader.h"

#include "IOLibrary/AbstractRaw.h"
#include "IOLibrary/Factories.h"
#include "IOLibrary/RawMTS.h"
#include "IOLibrary/RawMPEG.h"
#include "IOLibrary/QuickTime.h"

const int param_count = 4;
const int option = 1;
const int source = 2;
const int target = 3;

const std::string d_str = "-d";
const std::string f_str = "-f";

void initFactoryMananger(IO::RawFactoryManager & factory_manager)
{
	factory_manager.Register("mts", std::make_unique<IO::RawMTSFactory>());
	factory_manager.Register("mpeg", std::make_unique<IO::RawMPEGFactory>());
	factory_manager.Register("quicktime", std::make_unique<IO::QuickTimeRawFactory>());


}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	IO::IODevicePtr src_device = nullptr;

	if (argc == param_count)
	{
		std::string option_str(argv[option]);
		if (option_str.compare(d_str) == 0)
		{
			auto drive_number = boost::lexical_cast<uint32_t>(argv[source]);

			auto drive_list = IO::ReadPhysicalDrives();
			auto physical_drive = drive_list.find_by_number(drive_number);
			if (physical_drive)
			{
				qInfo() << "You selected";
				qInfo() << "Number : " << drive_number;
				qInfo() << "Name :" << physical_drive->getDriveName().c_str();
				qInfo() << "Serial number : " << physical_drive->getSerialNumber().c_str();
				qInfo() << "Size : " << physical_drive->getSize() << "(bytes)";
			}
			src_device = std::make_shared<IO::DiskDevice>(physical_drive);
		}
		else if (option_str.compare(f_str) == 0)
		{
			std::string src_path = argv[source];
			src_device = IO::makeFilePtr(IO::path_string(src_path.begin(), src_path.end()));
		}

		if (!src_device->Open(IO::OpenMode::OpenRead))
		{
			qInfo() << "Error open source device.";
			return -1;
		}

		std::string targer_path = argv[target];
		IO::path_string target_folder(targer_path.begin(), targer_path.end());

		if (!src_device)
			return -1;

		//////////////////////////////////////////////////////////////////////////
		QList<JsonFileStruct> listFileStruct;


		QFile file("video.json");
		if (!file.open(QIODevice::ReadOnly))
		{
			qInfo() << "Error to open file.";
			return -1;
		}

		auto json_str = file.readAll();
		ReadJsonFIle(json_str, listFileStruct);

		IO::HeaderBase::Ptr headerBase = std::make_shared<IO::HeaderBase>();
		for (auto theFileStruct : listFileStruct)
			headerBase->addFileFormat(toFileStruct(theFileStruct));

		IO::RawFactoryManager factory_manager;
		initFactoryMananger(factory_manager);

		IO::SignatureFinder signatureFinder(src_device, headerBase);

		uint64_t start_offset = 0;
		uint64_t header_offset = 0;
		uint32_t counter = 0;
		while (start_offset < src_device->Size())
		{
			auto file_struct = signatureFinder.findHeader(start_offset, header_offset);
			if (!file_struct)
			{
				qInfo() << "No more found headers.";
				break;
			}
			qInfo() << "Found signature for " << file_struct->getName().c_str() << "file."; 
			qInfo() << "Offset : " << header_offset << "(bytes)";

			start_offset = header_offset;
 			auto raw_factory = factory_manager.Lookup(file_struct->getName());
			if (raw_factory)
			{
				auto raw_algorithm = raw_factory->createRawAlgorithm(src_device);
				if (raw_algorithm->Specify(header_offset))
				{
					auto target_file = IO::toFullPath(target_folder, counter++, file_struct->getExtension());
					auto dst_file = IO::makeFilePtr(target_file);
					if (dst_file->Open(IO::OpenMode::Create))
					{
						auto target_size = raw_algorithm->SaveRawFile(*dst_file, header_offset);
						if ( target_size > 0)
						{
							//target_size /= src_device;

						}
					}
							

				}
			}

			start_offset += default_sector_size;

		}


	}
	else
		qInfo() << "Wrong params";
	return a.exec();
}
