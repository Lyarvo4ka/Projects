#include <QtCore/QCoreApplication>

#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include <QDebug>


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

const QString header_txt = "header";
const QString footer_txt = "footer";
const QString maxfilesize_txt = "maxfilesize";

//void 

int main(int argc, char *argv[])
{

	QCoreApplication a(argc, argv);
	QJsonDocument json_doc = QJsonDocument::fromJson(json_str);
	qDebug() << "Hello" << endl;

	auto root = json_doc.object();
	auto signatures_root = root.value("signatures").toObject();

	auto signatureKeys = signatures_root.keys();

	for (auto signature_name : signatureKeys)
	{

		auto object_value = signatures_root.value(signature_name);
		if (object_value.isObject())
		{
			qInfo() << "name = " << signature_name << endl;
			// find only header
			QJsonValue header_value = object_value.toObject().value(header_txt);
			if (header_value.isArray())
			{
				auto array_headers = header_value.toArray();

				for (int i = 0; i < array_headers.size(); ++i)
				{
					auto theHeader = array_headers.at(i);
					if (theHeader.isObject())
					{
						for (auto name_value : theHeader.toObject().keys())
						{
							auto the_value = theHeader.toObject().value(name_value);
							if (the_value.isString())
							{
								qInfo()  << name_value << " : " << the_value.toString();
							}
							else
								qInfo() << name_value << " : " << the_value.toInt();
							//the_value.toDo
						}

					}
				}
			}
		}
		qInfo() << endl;
	}


	return a.exec();
}
