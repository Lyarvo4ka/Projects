#include "StdAfx.h"
#include "RawMakerSaver.h"
#include "System.h"


CRawMakerSaver::CRawMakerSaver(void)
{

}


CRawMakerSaver::~CRawMakerSaver(void)
{

}

void CRawMakerSaver::Init()
{
	SetDefaults();
}
BOOL CRawMakerSaver::SaveToFile(CString _FileName)
{
	CStdioFile writeFile;
	if (writeFile.Open(_FileName,CFile::modeCreate|CFile::modeWrite) == TRUE)
	{
		writeFile.WriteString(PrepereString( Keywords::InputFile,GetInputFile() ));
		writeFile.WriteString(PrepereString( Keywords::OutputFolder,GetOutputFolder() ));
		writeFile.WriteString(PrepereString( Keywords::HeaderOffset,GetHeaderOffset() ));
		writeFile.WriteString(PrepereString( Keywords::HeaderSignature,GetHeaderSignature() ));
		writeFile.WriteString(PrepereString( Keywords::FooterSignature,GetFooterSignature() ));
		writeFile.WriteString(PrepereString( Keywords::FooterOffset,GetFooterOffset() ));
		writeFile.WriteString(PrepereString( Keywords::MinSize,GetMinSize() ));
		writeFile.WriteString(PrepereString( Keywords::MaxSize,GetMaxSize() ));
		writeFile.WriteString(PrepereString( Keywords::Extension,GetExtension() ));
		writeFile.WriteString(PrepereString( Keywords::Offset,GetOffset() ));

		writeFile.Close();
		return TRUE;
	}
	return FALSE;
}

void CRawMakerSaver::SetDefaults()
{
	Set(Keywords::InputFile, DefaultsValues::InputFile);
	Set(Keywords::OutputFolder, DefaultsValues::OutputFolder);
	Set(Keywords::HeaderOffset,DefaultsValues::HeaderOffset);
	Set(Keywords::HeaderSignature,DefaultsValues::HeaderSignature);
	Set(Keywords::FooterSignature,DefaultsValues::FooterSignature);
	Set(Keywords::FooterOffset,DefaultsValues::FooterOffset);
	Set(Keywords::MinSize,DefaultsValues::MinSize);
	Set(Keywords::MaxSize,DefaultsValues::MaxSize);
	Set(Keywords::Extension, DefaultsValues::Extension);
	Set(Keywords::Offset, DefaultsValues::Offset);
}





//void CSerialization::SetDefault()
//{
//	SetInputFile(DefaultsValues::InputFile);
//	SetOutputFolder(DefaultsValues::OutputFolder);
//	SetHeaderOffset(DefaultsValues::HeaderOffset);
//	SetHeaderSignature(DefaultsValues::HeaderSignature);
//	SetFooterSignature(DefaultsValues::FooterSignature);
//	SetFooterOffset(DefaultsValues::FooterOffset);
//	SetMinSize(DefaultsValues::MinSize);
//	SetMaxSize(DefaultsValues::MaxSize);
//	SetExtension(DefaultsValues::Extension);
//}
//void CSerialization::CreateKeywords()
//{
//	m_MapKeyword.insert(PairKeyword(Keywords::InputFile,DefaultsValues::InputFile));
//	m_MapKeyword.insert(PairKeyword(Keywords::OutputFolder,DefaultsValues::OutputFolder));
//	m_MapKeyword.insert(PairKeyword(Keywords::HeaderOffset,DefaultsValues::HeaderOffset));
//	m_MapKeyword.insert(PairKeyword(Keywords::HeaderSignature,DefaultsValues::HeaderSignature));
//	m_MapKeyword.insert(PairKeyword(Keywords::FooterSignature,DefaultsValues::FooterSignature));
//	m_MapKeyword.insert(PairKeyword(Keywords::FooterOffset,DefaultsValues::FooterOffset));
//	m_MapKeyword.insert(PairKeyword(Keywords::MinSize,DefaultsValues::MinSize));
//	m_MapKeyword.insert(PairKeyword(Keywords::MaxSize,DefaultsValues::MaxSize));
//	m_MapKeyword.insert(PairKeyword(Keywords::Extension,DefaultsValues::Extension));
//}


// SET
void CRawMakerSaver::SetInputFile(const CString &_InputFile)
{
	Set(Keywords::InputFile,_InputFile);
}
void CRawMakerSaver::SetOutputFolder(const CString &_OutputFolder)
{
	Set(Keywords::OutputFolder,_OutputFolder);
}
void CRawMakerSaver::SetHeaderOffset(const CString &_HeaderOffset)
{
	Set(Keywords::HeaderOffset,_HeaderOffset);
}
void CRawMakerSaver::SetHeaderSignature(const CString & _HeaderSignature)
{
	Set(Keywords::HeaderSignature,_HeaderSignature);
}
void CRawMakerSaver::SetFooterSignature(const CString & _FooterSignature)
{
	Set(Keywords::FooterSignature,_FooterSignature);
}
void CRawMakerSaver::SetFooterOffset(const CString &_FooterOffset)
{
	Set(Keywords::FooterOffset,_FooterOffset);
}
void CRawMakerSaver::SetMinSize(const CString &_MinSize)
{
	Set(Keywords::MinSize,_MinSize);
}
void CRawMakerSaver::SetMaxSize(const CString &_MaxSize)
{
	Set(Keywords::MaxSize,_MaxSize);
}
void CRawMakerSaver::SetExtension(const CString &_Extension)
{
	Set(Keywords::Extension,_Extension);
}
void CRawMakerSaver::SetOffset( const CString offset )
{
	Set( Keywords::Offset , offset );
}

// GET
const CString CRawMakerSaver::GetInputFile() const
{
	const CString sResult(GetValue(Keywords::InputFile));
	return (sResult != L"") ? sResult : System::GetCurrentDir();
}
const CString CRawMakerSaver::GetOutputFolder() const
{
	const CString sResult(GetValue(Keywords::OutputFolder));
	return (sResult != L"") ? sResult : System::GetCurrentDir();
}
const CString CRawMakerSaver::GetHeaderOffset() const
{
	const CString sResult(GetValue(Keywords::HeaderOffset));
	return (sResult != L"") ? sResult : DefaultsValues::HeaderOffset;
}
const CString CRawMakerSaver::GetHeaderSignature() const
{
	const CString sResult(GetValue(Keywords::HeaderSignature));
	return (sResult != L"") ? sResult : DefaultsValues::HeaderSignature;
}
const CString CRawMakerSaver::GetFooterSignature() const
{
	return GetValue(Keywords::FooterSignature);
}
const CString CRawMakerSaver::GetFooterOffset() const
{
	const CString sResult(GetValue(Keywords::FooterOffset));
	return (sResult != L"") ? sResult : DefaultsValues::FooterOffset;
}
const CString CRawMakerSaver::GetMinSize() const
{
	const CString sResult(GetValue(Keywords::MinSize));
	return (sResult != L"") ? sResult : DefaultsValues::MinSize;
}
const CString CRawMakerSaver::GetMaxSize() const
{
	const CString sResult(GetValue(Keywords::MaxSize));
	return (sResult != L"") ? sResult : DefaultsValues::MaxSize;
}
const CString CRawMakerSaver::GetExtension() const
{
	const CString sResult(GetValue(Keywords::Extension));
	return (sResult != L"") ? sResult : DefaultsValues::Extension;
}
const CString CRawMakerSaver::GetOffset() const
{
	const CString sResult(GetValue(Keywords::Offset));
	return (sResult != L"") ? sResult : DefaultsValues::Offset;
}