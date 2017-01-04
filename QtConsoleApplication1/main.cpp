#include <QtCore/QCoreApplication>

#include <QJsonObject>
#include <QJsonDocument>
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
                    "data": "",
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

int main(int argc, char *argv[])
{

	QCoreApplication a(argc, argv);
	QJsonDocument json_doc = QJsonDocument::fromJson(json_str);
	qDebug() << "Hello" << endl;

	auto root = json_doc.object();
	auto signatures_root = root.value("signatures").toObject();
	auto signatures = signatures_root.toVariantMap();



	for (QVariantMap::const_iterator iter = signatures.begin(); iter != signatures.end(); ++iter) 
	{
		QString key_name = iter.key();
		qInfo() << "name = " << key_name << endl;
		auto val = iter.value();
		if ( val.isValid())
		{
			auto headers = val.toJsonObject();
			QJsonValue header_value = headers.value(header_txt);
			if (header_value.isArray())
			{
				QJsonArray array_headers = header_value.toArray();
				
				for ( int i = 0 ; i < array_headers.size(); ++i)
				{
					auto headerData = array_headers[i].toObject().toVariantMap();
					qInfo() << headerData.key();
					//for ( auto data_iter = headerData.)
				}
			}
		}
		//headers.
	}
	//auto objects = root.keys();
	return a.exec();
}
