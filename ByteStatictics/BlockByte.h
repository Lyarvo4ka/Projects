#pragma once

#include <windows.h>

#include <vector>
using std::vector;

#include <map>
using std::map;
using std::pair;

class CBuffer;

//const DWORD BlockSize = 8;

class OffsetList
{
public:
	OffsetList(DWORD Offset);
	~OffsetList();
	void AddOffset(DWORD Offset);
	size_t GetCount() const;
	void ClearOffsets();
private:
	vector<DWORD> OffsetArray_;
};


class BlockByte
{
	typedef pair< LONGLONG,OffsetList > PairOffset;
	typedef map< LONGLONG,OffsetList > MapOffset;
public:
	BlockByte(const int ByteSize = 8);
	~BlockByte(void);
	void SetBlockData(const BYTE * BlockData);
	void AddOffset(const BYTE * BlockData, const DWORD Offset);
	void AddOffset(const LONGLONG Value , const DWORD Offset);
	BYTE * GetBlock() const;
	size_t GetCount() const;
	LONGLONG GetValue() const;
	LONGLONG GetValueByOffset(const BYTE * pBuffer,const DWORD Offset) const;
	void ShowFounds();
	void PrintHex(const BYTE * pBytes);
	void FindOffsets(const CBuffer * pBuffer);
	void CorrectXor(const CBuffer * pBuffer, const DWORD AverageValue);
	bool GetPrevOffsets(vector<DWORD> & ArrayOffset, DWORD distance);
private:
	const int ByteSize_;
	BYTE * ByteBlock_;
	LONGLONG BlockValue_;
	vector<DWORD> BlockOffset_;
	MapOffset OffsetMap_;
};

