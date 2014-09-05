#pragma once

#include "Imports.h"
#include <string>
using std::string;

#define MAKE_USER_ERROR(ErrorCode) ( (DWORD) ErrorCode & 0x10000000)

#define ERROR_MORE_THEN_DEVICE MAKE_USER_ERROR(1)


namespace Errors
{
	static const string sBytesPerSectorNullEng = "Error.\t Bytes per sector is 0.";
	static const string sBytesPerSectorNullRus = "Ошибка.\t Размер сектора равен 0.";

	static const string sOutOffRangeEng = "Error.\t Input range more than physical available.";
	static const string sOutOffRangeRus = "Ошибка.\t Введенный диапазон превышает доступное количество секторов.";


	static const string sMaxTransferSizeNullEng = "Error.\t Max transfer length is 0.";
	static const string sMaxTransferSizeNullRus = "Ошибка.\t Размер блок равен 0.";

	static const string sErrorOpenDeviceEng = "Error open device.";
	static const string sErrorOpenDeviceRus = "Ошибка.\t Невозможно открыть устройство.";

	static const string sMoreThenDeviceSizeEng = "Error.\t Write position is more then maximum available.";
	static const string sMoreThenDeviceSizeRus = "Ошибка.\t Невозможно записать за пределами доступного объема.";

	static const string sNoSelectedDeviceEng = "Error.\t Device is not selected.";
	static const string sNoSelectedDeviceRus = "Ошибка.\t Устройство не выбрано.";

	static const string sStartSectorMoreEng = "Error.\t Start sector is more then amount of sectors.";
	static const string sStartSectorMoreRus = "Ошибка.\t Начальный сектор за пределами доступного объема.";

	static const string sEnCaseMoreZZZEng = "Error.\t The maximum \"ZZZ\" for EnCase file.\r\nError last character is (\"[\").";
	static const string sEnCaseMoreZZZRus = "Ошибка.\t Максимально допустимое расширение файла EnCase \"ZZZ\".\r\nОшибочный символ (\"[\").";

	static const string sErrorOpenFileEng = "Error.\t Cannot open file.";
	static const string sErrorOpenFileRus = "Ошибка.\t Невозможно открыть файл.";
	
	static const string sVerifyCorrectPathEng = "Please verify path to file.\r\n\r\n";
	static const string sVerifyCorrectPathRus = "Проверьте правильность пути к файлу.\r\n\r\n";

	static const string sErrorReadSectorsEng = "Error.\t Can't read sectors %ld (%d bytes).";
	static const string sErrorReadSectorsRus = "Error.\t Не удается прочитать с сектора %ld (%d байт).";

	static const string sErrorReadSectorEng = "Error.\t Can't read sector:\t%ld.";
	static const string sErrorReadSectorRus = "Ошибка.\t Не удается прочитать сектор:\t%ld.";

	static const string GetErrorMessage(DWORD _ErrorCode)
	{
		string			sError;
		static char	errorBuffer[512];
		if (!FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, NULL, _ErrorCode, 0, errorBuffer, 511, NULL))
		{
			// if we fail, call ourself to find out why and return that error
			return GetErrorMessage(GetLastError());
		}
		return string(errorBuffer);
	}

};


