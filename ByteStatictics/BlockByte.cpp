#include "StdAfx.h"
#include "BlockByte.h"
#include "Buffer.h"

OffsetList::OffsetList(DWORD Offset)
{
	OffsetArray_.push_back(Offset);
}
OffsetList::~OffsetList()
{

}
void OffsetList::AddOffset(DWORD Offset)
{
	OffsetArray_.push_back(Offset);
}
size_t OffsetList::GetCount() const
{
	return OffsetArray_.size();
}
void OffsetList::ClearOffsets()
{
	OffsetArray_.clear();
}


BlockByte::BlockByte(const int ByteSize)
	: ByteSize_(ByteSize)
	, ByteBlock_(NULL)
{
}
BlockByte::~BlockByte(void)
{

}
void BlockByte::SetBlockData(const BYTE * BlockData)
{
}
void BlockByte::AddOffset(const BYTE * BlockData, const DWORD Offset)
{
	BYTE miniBuff[8];
	memcpy(miniBuff,BlockData,ByteSize_);
	LONGLONG * p64Value = (LONGLONG*)BlockData;
	LONGLONG * lValue = (LONGLONG*)miniBuff;
	auto MapIter = OffsetMap_.find(* p64Value);
	if (MapIter == OffsetMap_.end())
		OffsetMap_.insert(PairOffset(*p64Value, OffsetList(Offset)));
	else
		MapIter->second.AddOffset(Offset);
}
void BlockByte::AddOffset(const LONGLONG Value , const DWORD Offset)
{
	auto MapIter = OffsetMap_.find(Value);
	if (MapIter == OffsetMap_.end())
		OffsetMap_.insert(PairOffset(Value, OffsetList(Offset)));
	else
		MapIter->second.AddOffset(Offset);

}
BYTE * BlockByte::GetBlock() const
{
	return ByteBlock_;
}
size_t BlockByte::GetCount() const
{
	return OffsetMap_.size();
}
LONGLONG BlockByte::GetValue() const
{
	return BlockValue_;
}
LONGLONG BlockByte::GetValueByOffset(const BYTE * pBuffer, const DWORD Offset) const
{
	const LONGLONG * pValue = reinterpret_cast<const LONGLONG *> (&pBuffer[Offset]);
	return * pValue;
}
void BlockByte::ShowFounds()
{
	auto MapIter = OffsetMap_.begin();

	int iCount = 0;
	while(MapIter != OffsetMap_.end())
	{
		const BYTE * pBytes = reinterpret_cast< const BYTE* > ( &MapIter->first );
		if (MapIter->second.GetCount() < 48)
		{
			PrintHex(pBytes);
			printf(" count = %d\r\n",MapIter->second.GetCount());

			++iCount;
		}

		++MapIter;
	}

	printf("\r\nCount = %d",iCount);
}
void BlockByte::PrintHex(const BYTE * pBytes)
{
	for (int iByte = 0; iByte < ByteSize_; ++ iByte)
		printf("%X",pBytes[iByte]);
}
void BlockByte::FindOffsets(const CBuffer * pBuffer)
{
	if (pBuffer->GetSize() == 0 )
		return;
	const BYTE * pDataBuffer = pBuffer->GetBuffer();
	if (pDataBuffer == NULL)
		return;

	DWORD CurrentPos = 0;
	LONGLONG lValue = 0;


	while (CurrentPos < pBuffer->GetSize())
	{
		/*const BYTE * pValue = static_cast<const BYTE *> (&pDataBuffer[CurrentPos]);*/
		lValue = GetValueByOffset(pDataBuffer,CurrentPos);
		this->AddOffset(lValue,CurrentPos);


		CurrentPos += pBuffer->GetSize();
	}

}
void BlockByte::CorrectXor(const CBuffer * pBuffer, const DWORD AverageValue)
{
	if (pBuffer->GetSize() == 0 )
		return;
	const BYTE * pDataBuffer = pBuffer->GetBuffer();
	if (pDataBuffer == NULL)
		return;

	DWORD CurrentPos = 0;
	LONGLONG lValue = 0;
	
	auto Iter = OffsetMap_.begin();
	while (CurrentPos < pBuffer->GetSize())
	{
		lValue = GetValueByOffset(pDataBuffer,CurrentPos);
		Iter = OffsetMap_.find(lValue);

		if (Iter != OffsetMap_.end())
		{
			if (Iter->second.GetCount() < AverageValue)
			{

			}
			else
				continue;

		}
		CurrentPos += pBuffer->GetSize();
	}
}

bool GetPrevOffsets(vector<DWORD> & ArrayOffset, DWORD distance);
