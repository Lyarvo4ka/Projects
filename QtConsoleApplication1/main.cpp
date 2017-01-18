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
const QString offset_txt = "offset";
const QString footer_txt = "footer";
const QString textdata_txt = "textdata";
const QString hexdata_txt = "hexdata";

const QString maxfilesize_txt = "maxfilesize";

//void 

struct HeaderOffset
{
	QString header;
	int offset;
};

using ArrayOfHeader = QVector<HeaderOffset>;

void ReadHadersOffset(const QJsonArray & json_array, ArrayOfHeader &header_array)
{
	for (int i = 0; i < json_array.size(); ++i)
	{
		auto theHeader = json_array.at(i);
		HeaderOffset headerOffset;
		if (theHeader.isObject())
		{
			auto text_value = theHeader.toObject().value(textdata_txt);
			if (text_value.isUndefined())
			{
				text_value = theHeader.toObject().value(hexdata_txt);
				if ( text_value.isUndefined() )
					return;
			}
			headerOffset.header = text_value.toString();

			auto offset_value = theHeader.toObject().value(offset_txt);
			if (!offset_value.isUndefined())
				headerOffset.offset = offset_value.toInt();

			header_array.append(headerOffset);
		}
	}

}

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
				ArrayOfHeader arrayOfHeaders;
				ReadHadersOffset(array_headers, arrayOfHeaders);
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
								qInfo() << name_value << " : " << the_value.toString();
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
