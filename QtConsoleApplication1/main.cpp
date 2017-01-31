#include <QtCore/QCoreApplication>

#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QDebug>
#include <QList>





#include <iostream>

#include "../JsonReader/JsonReader.h"
int main(int argc, char *argv[])
{

	QCoreApplication a(argc, argv);
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
	IO::SignatureFinder signatureFinder(nullptr , headerBase);

	for (auto theFileStruct : listFileStruct)
		headerBase->addFileFormat(toFileStruct(theFileStruct));

	return a.exec();
}
