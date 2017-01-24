#pragma once

//#include "jsonreader_global.h"
//
//class JSONREADER_EXPORT JsonReader
//{
//public:
//    JsonReader();
//};


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
				if (text_value.isUndefined())
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
