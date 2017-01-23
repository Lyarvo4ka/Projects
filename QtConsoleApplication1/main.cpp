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

const QString header_txt = "header";
const QString offset_txt = "offset";
const QString footer_txt = "footer";
const QString tailsize_txt = "tailsize";
const QString textdata_txt = "textdata";
const QString hexdata_txt = "hexdata";

const QString maxfilesize_txt = "maxfilesize";
const QString extension_txt = "extension";

//void 

struct HeaderOffset
{
	QString header;
	int offset = 0;
	bool bHex = false;
};

struct Footer
{
	QString footer;
	int tailsize = 0;
	bool bHex = false;
};

using ArrayOfHeader = QVector<HeaderOffset>;

struct JsonFileStruct
{
	QString name;
	ArrayOfHeader headers;
	Footer footer;
	qlonglong maxfilesize = 0;
	QString extension;
};

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
				headerOffset.bHex = true;
			}
			headerOffset.header = text_value.toString();

			auto offset_value = theHeader.toObject().value(offset_txt);
			if (!offset_value.isUndefined())
				headerOffset.offset = offset_value.toInt();

			header_array.append(headerOffset);
		}
	}

}

void ReadFooter(const QJsonObject footer_object, Footer & footer)
{
	auto text_value = footer_object.value(hexdata_txt);
	if (!text_value.isUndefined())
	{
		footer.bHex = true;
		footer.footer = text_value.toString();
	}
	else
	{
		text_value = footer_object.value(textdata_txt);
		if (text_value.isUndefined())
			return;
		footer.footer = text_value.toString();
	}
	
	auto tail_size = footer_object.value(tailsize_txt);
	if (!tail_size.isUndefined())
		footer.tailsize = tail_size.toInt();
}

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

			auto maxsize_value = signatures_root.value(maxfilesize_txt);
			if (!maxsize_value.isUndefined())
				jsonFileStruct.maxfilesize = maxsize_value.toVariant().toLongLong();

			auto extension_value = signatures_root.value(extension_txt);
			if (extension_value.isString())
				jsonFileStruct.extension = extension_value.toString();

			listHeaders.append(jsonFileStruct);
				
		}
		qInfo() << endl;
	}


	return a.exec();
}
