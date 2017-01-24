#include <QtCore/QCoreApplication>

#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QDebug>
#include <QList>


auto json_str = R"(
{
    "signatures": {
        "zbk": {
            "header": 
            [
              {
                "hexdata": "0F000B67636667507267506C7573",
                "offset": 2
              }
            ],
            "footer": {
                "hexdata": "504B0506",
                "tailsize": 18
            },
            "maxfilesize":  104857600,
            "extension": ".zbk"
        },
        "cdw": {
            "header": 
            [
                {
                    "hexdata": "4B46",
                    "offset": 0
                },
                {
                    "hexdata": "0100000000000000",
                    "offset": 16
                }
            ],
            "extension": ".cdw"
        },
        "zs2":{
          "header":
          [
            {
                "hexdata":"308203D602010330",
                "offset": 0
            }
          ],
          "maxfilesize":  986,
          "extension": ".ZS2"
        },
        "QT":{
          "header":
          [
            {
                "textdata":"ftyp",
                "offset": 4
            },
            {
                "textdata":"moov",
                "offset": 4
            },
            {
                "textdata":"mdat",
                "offset": 4
            }            
            
          ],
          "extension": ".mov"
        }
        
    }
}	)";


#include <iostream>


int main(int argc, char *argv[])
{

	QCoreApplication a(argc, argv);
	QJsonDocument json_doc = QJsonDocument::fromJson(json_str);
	qDebug() << "Hello" << endl;

	auto root = json_doc.object();
	auto signatures_root = root.value("signatures").toObject();

	auto signatureKeys = signatures_root.keys();

	QList<JsonFileStruct> listHeaders;

	for (auto signature_name : signatureKeys)
	{
		JsonFileStruct jsonFileStruct;
		jsonFileStruct.name = signature_name;
		auto object_value = signatures_root.value(signature_name);
		if (object_value.isObject())
		{
			qInfo() << "name = " << signature_name << endl;
			// find only header
			QJsonValue header_value = object_value.toObject().value(header_txt);
			if (header_value.isArray())
			{
				auto array_headers = header_value.toArray();
				ReadHadersOffset(array_headers, jsonFileStruct.headers);
			}

			auto footer_value = object_value.toObject().value(footer_txt);
			if (footer_value.isObject())
			{
				ReadFooter(footer_value.toObject(), jsonFileStruct.footer);
			}

			auto maxsize_value = object_value.toObject().value(maxfilesize_txt);
			if (!maxsize_value.isUndefined())
				jsonFileStruct.maxfilesize = maxsize_value.toVariant().toLongLong();

			auto extension_value = object_value.toObject().value(extension_txt);
			if (extension_value.isString())
				jsonFileStruct.extension = extension_value.toString();

			listHeaders.append(jsonFileStruct);
				
		}
		qInfo() << endl;
	}


	return a.exec();
}
