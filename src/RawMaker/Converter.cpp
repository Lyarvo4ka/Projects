#include "StdAfx.h"
#include "Converter.h"


CConverter::CConverter(void)
{
}


CConverter::~CConverter(void)
{
}


string CConverter::ToString(CString _String)
{
	int iLength = WideCharToMultiByte(CP_ACP,NULL,(LPCWSTR)_String.GetBuffer(),-1,NULL,NULL,NULL,NULL);
	string SignatureTemp;
	string Signature;
	BYTE cHex = 0;
	BYTE TempHex = 0;
	BYTE chA = 'A' - 10;
	BYTE ch0 = '0';
	if (iLength)
	{
		BYTE *pChar = new BYTE[iLength];
		iLength = WideCharToMultiByte(CP_ACP,NULL,(LPCWSTR)_String.GetBuffer(),-1,(LPSTR)pChar,iLength,NULL,NULL);
		for (int i = 0; i < iLength-1; i+=2)
		{
			if (isDigit(pChar[i]))
				cHex = pChar[i] - ch0;
			else
			{
				BYTE ch = pChar[i];
				TempHex = ch - chA;
				cHex = TempHex;
			}
			cHex <<= 4;
			if (isDigit(pChar[i+1]))
				cHex += pChar[i+1] - ch0;
			else
			{
				BYTE ch = pChar[i+1];
				TempHex = ch - chA;
				cHex += TempHex;
			}
			Signature.push_back(cHex);
		}

		delete pChar;
	}
	return Signature;
}

bool CConverter::isDigit(BYTE &_rDigitChar)
{
	return (_rDigitChar >= '0' && _rDigitChar <= '9') ? true : false;
}

bool CConverter::isHex(BYTE &_rHexChar)
{
	return (_rHexChar >= 'A' && _rHexChar <= 'F') ? true : false;
}


void CConverter::WideStrToByteStr(CString &_sourceStr, string &_destinationStr)
{
	int iLength = WideCharToMultiByte(CP_ACP,NULL,(LPCWSTR)_sourceStr.GetBuffer(),-1,NULL,NULL,NULL,NULL);
	if (iLength)
	{
		BYTE *pChar = new BYTE[iLength];
		iLength = WideCharToMultiByte(CP_ACP,NULL,(LPCWSTR)_sourceStr.GetBuffer(),-1,(LPSTR)pChar,iLength,NULL,NULL);
		_destinationStr.push_back( *pChar );
		delete pChar;
	}
}
