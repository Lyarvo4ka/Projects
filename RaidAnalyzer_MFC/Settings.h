#pragma once

#include <string>
using std::wstring;

namespace settings
{

	const wstring WorkPathDefault = L"C:\\JPG\\";
	const int FileCountDefault = 1024;
	const int MinBlockDefault = 512;
	const int MaxBlockDefault = 524288;

class CSettings
{
public:
	static CSettings * getSetting()
	{
		if ( ! instance_ )
			instance_ = new CSettings();
		return instance_;
	}

	void Remove()
	{
		if ( instance_ )
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

	void Initialize()
	{
		workPath_ = WorkPathDefault;
		fileCount_ = FileCountDefault;
		minBlock_ = MinBlockDefault;
		maxBlock_ = MaxBlockDefault;
	}
	void setWorkPath( const wstring & string_path )
	{
		workPath_ = string_path;
	}
	const wstring & getWorkFolder() const
	{
		return workPath_;
	}
	void setFileCount( int file_count )
	{
		fileCount_ = file_count;
	}
	int getFileCount() const
	{
		return fileCount_;
	}
	void setMinBlock( int min_block)
	{
		minBlock_ = min_block;
	}
	int getMinBlock() const
	{
		return minBlock_;
	}
	void setMaxBlock( int max_block )
	{
		maxBlock_ = max_block;
	}
	int getMaxBlock() const
	{
		return maxBlock_;
	}
protected:
	CSettings(void)
		: workPath_ ( WorkPathDefault )
		, fileCount_ ( FileCountDefault )
		, minBlock_ ( MinBlockDefault )
		, maxBlock_ ( MaxBlockDefault )
	{

	}
	CSettings( const CSettings & );
	void operator = ( const CSettings & );
	~CSettings(void)
	{
		TRACE( "dtor [CSetting].\n" );
	}

private:
	static CSettings * instance_;
	wstring workPath_;
	int fileCount_;
	int minBlock_;
	int maxBlock_;
};

}

