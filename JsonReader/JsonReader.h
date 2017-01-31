#pragma once

#include <QtCore>
#include <QVariant>
#include <QDebug>
#include <QList>
#include <QFile>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include "IOLibrary/AbstractRaw.h"

const QString header_txt = "header";
const QString offset_txt = "offset";
const QString footer_txt = "footer";
const QString tailsize_txt = "tailsize";
const QString textdata_txt = "textdata";
const QString hexdata_txt = "hexdata";

const QString maxfilesize_txt = "maxfilesize";
const QString extension_txt = "extension";

struct SignatureHandle
{
	QString value_string;
	int value_int = 0;
	bool bHex = false;
};



using ArrayOfHeader = QVector<SignatureHandle>;

struct JsonFileStruct
{
	QString name;
	ArrayOfHeader headers;
	SignatureHandle footer;
	qlonglong maxfilesize = 0;
	QString extension;
};

void ReadHadersOffset(const QJsonArray & json_array, ArrayOfHeader &header_array)
{
	for (int i = 0; i < json_array.size(); ++i)
	{
		auto theHeader = json_array.at(i);
		SignatureHandle headerOffset;
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
			headerOffset.value_string = text_value.toString();

			auto offset_value = theHeader.toObject().value(offset_txt);
			if (!offset_value.isUndefined())
				headerOffset.value_int = offset_value.toInt();

			header_array.append(headerOffset);
		}
	}

}

void ReadFooter(const QJsonObject footer_object, SignatureHandle & footer)
{
	auto text_value = footer_object.value(hexdata_txt);
	if (!text_value.isUndefined())
	{
		footer.bHex = true;
		footer.value_string = text_value.toString();
	}
	else
	{
		text_value = footer_object.value(textdata_txt);
		if (text_value.isUndefined())
			return;
		footer.value_string = text_value.toString();
	}

	auto tail_size = footer_object.value(tailsize_txt);
	if (!tail_size.isUndefined())
		footer.value_int = tail_size.toInt();
}

void ReadJsonFIle(const QByteArray & byte_data, QList<JsonFileStruct> & parsedResult)
{
	QJsonDocument json_doc = QJsonDocument::fromJson(byte_data);

	auto root = json_doc.object();
	auto signatureKeys = root.keys();

	for (auto signature_name : signatureKeys)
	{
		JsonFileStruct jsonFileStruct;
		jsonFileStruct.name = signature_name;
		auto object_value = root.value(signature_name);
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

			parsedResult.append(jsonFileStruct);

		}
		qInfo() << endl;
	}

}
void ReadJsonFile(const QString & jsonFileName , QList<JsonFileStruct> & parsedResult)
{
	QFile file(jsonFileName);
	file.open(QIODevice::ReadOnly);
	auto byte_data = file.readAll();
	ReadJsonFIle(byte_data, parsedResult);
}
IO::DataArray::Ptr JsonToDataArray(SignatureHandle signHandle)
{
	IO::DataArray::Ptr data_array = nullptr;
	if (signHandle.bHex)
	{
		if (signHandle.value_string.length() % 2 != 0)
			return nullptr;
		auto byte_array = QByteArray::fromHex(signHandle.value_string.toLatin1());
		data_array = IO::makeDataArray(byte_array.size());
		memcpy(data_array->data(), byte_array.data(), data_array->size());

	}
	else
	{
		data_array = IO::makeDataArray(signHandle.value_string.length());
		memcpy(data_array->data(), signHandle.value_string.constData(), data_array->size());
	}
	return data_array;
}

IO::FileStruct::Ptr toFileStruct(const JsonFileStruct & jsonFileStruct)
{
	auto file_struct = IO::makeFileStruct(jsonFileStruct.name.toStdString());
	for (auto theHeader : jsonFileStruct.headers)
	{
		auto data_array = JsonToDataArray(theHeader);

		file_struct->addSignature(data_array, theHeader.value_int);
	}

	if (!jsonFileStruct.footer.value_string.isEmpty())
	{
		auto data_array = JsonToDataArray(jsonFileStruct.footer);
		file_struct->addFooter(data_array);
		file_struct->setFooterTailEndSize(jsonFileStruct.footer.value_int);
	}
	return file_struct;
}