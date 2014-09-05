#ifndef OPTIONSMANAGER_H
#define OPTIONSMANAGER_H

#include <QObject>

#include "IOptionsView.h"


#include "DiskMasterLib\dm_device.h"

class DMOptionsData
{
public:
	explicit DMOptionsData()
		: options_ ( new DM::DM_OPTION )
	{
		toDefault();
	}
	explicit DMOptionsData( DM::DM_OPTION * option )
		: options_ ( option )
	{
		toDefault();

	}
	~DMOptionsData()
	{
		if ( options_ )
		{
			delete options_;
			options_ = nullptr;
		}
	}
	void toDefault()
	{
		options_->NumRepeatRd = DM_DEFAULT_OPT_READ_COUNT;
		options_->RdTimeLimit = DM_DEFAULT_OPT_READ_TIMEOUT;
		options_->ShkPwrLimit = DM_DEFAULT_OPT_SHAKE_POWER_LIMIT;
		options_->Chirp = DM_DEFAULT_OPT_CHIRP;
		options_->CrcBeep = DM_DEFAULT_OPT_CRC_BEEP;
		options_->EndBeep = DM_DEFAULT_OPT_END_BEEP;
		options_->BadMarker = DM_DEFAULT_OPT_BAD_MARKER;
		block_size_ = DM_BLOCK_SIZE;
	}
	//	 set
	void setNumberReadBads( WORD repeat_count )
	{
		options_->NumRepeatRd = repeat_count;
	}
	void setChirp( WORD chirp )
	{
		options_->Chirp = chirp;
	}
	void setCRCBeep( WORD CRC_beep )
	{
		options_->CrcBeep = CRC_beep;
	}
	void setEndBeep( WORD END_Beep )
	{
		options_->EndBeep = END_Beep;
	}
	void setBlockSize( WORD block_size )
	{
		block_size_ = block_size;
	}
	// get

	WORD numberReadBads() const
	{
		return options_->NumRepeatRd;
	}
	bool validate() 
	{
		return false;
	}
	const DM::DM_OPTION * option() const
	{
		return options_;
	}
	WORD block_size() const
	{
		return block_size_;
	}
private:
	DM::DM_OPTION * options_;
	WORD block_size_;
};

class GlobalOptionsData
{
public:
	GlobalOptionsData(const QString & work_folder)
		: globalFolder_( work_folder )
	{

	}
	void setGlobalFolder( const QString & work_folder )
	{
		globalFolder_ = work_folder;
	}
	QString getGlobalFolder() const 
	{
		return globalFolder_;
	}
private:
	QString globalFolder_;
};

class CopyOptionsData
{
	CopyOptionsData()
		: jumpSize_( DMTool::DefaultJumpSize)
		, direction_( DMTool::FORWARD_TASK )
		, isRead_Unread_( )
	{

	}
	void setJumpSize( qlonglong jump_size )
	{
		jumpSize_ = jump_size;
	}
	qlonglong jumpSize() const 
	{
		return jumpSize_;
	}
	void setDirection( DMTool::DIRECTION direction )
	{
		direction_ = direction;
	}
	DMTool::DIRECTION direction() const
	{
		return direction_;
	}
private:
	qlonglong jumpSize_;
	DMTool::DIRECTION direction_; 
	int isRead_Unread_;
};

//struct SectorCopySetting
//{
//	SectorCopySetting()
//		: direction_ ( ForwardTask )
//		, jump_size_( DefaultJumpSize )
//		, isRead_unread ( Qt::Checked )
//		, dm_option_( new DMOptionsData() )
//		//, copy_mode_ ( enFullCopy )
//	{
//	}
//	int direction_;		// forward or backward
//	qlonglong jump_size_;	// 'size' in sectors to jump when bad sector is appeared
//	int isRead_unread;		// starting read unread sectors when previous task finished.
//	int copy_mode_;
//	DMOptionsData * dm_option_;
//};
//
//class DM_Settings
//{
//	typedef std::map< DWORD , SectorCopySetting > CopySettingsMap;
//	typedef std::pair< DWORD , SectorCopySetting > CopySettingsPair;
//
//public:
//	static DM_Settings * getSettings()
//	{
//		static DM_Settings instance_;
//		return &instance_;
//	}
//	QString getFolderName() const
//	{
//		return globalFolderName_;
//	}
//	QString getTaskName() const
//	{
//		return taskName_;
//	}
//	void setCopySetting( DWORD id , const SectorCopySetting & copySettings )
//	{
//		auto findIter = copySettingsMap_.find( id );
//		if ( findIter == copySettingsMap_.end() )
//			copySettingsMap_.insert( CopySettingsPair( id , copySettings) );
//		else
//			findIter->second = copySettings;
//	}
//	SectorCopySetting & getCopySettings( DWORD id ) 
//	{
//		auto findIter = copySettingsMap_.find( id );
//		if ( findIter == copySettingsMap_.end() )
//		{
//			//SectorCopySetting copySettings;
//			copySettingsMap_.insert( CopySettingsPair( id , SectorCopySetting() ) );			
//			findIter =  copySettingsMap_.find( id );
//		}
//
//		return findIter->second;
//	}
//private:
//	DM_Settings()
//	{
//
//	}
//	~DM_Settings()
//	{
//
//	}
//	DM_Settings( const DM_Settings &);
//	void operator = (const DM_Settings &);
//private:
//	QString globalFolderName_;
//	QString taskName_;
//
//	CopySettingsMap copySettingsMap_;
//};



class DevicePresenter : public QObject
{
	Q_OBJECT

public:
	//explicit DevicePresenter(IOptionsView * option_view , DMOptionsData * option_data  , QObject * parent = nullptr );
	explicit DevicePresenter(IOptionsView * option_view , QObject * parent = nullptr );
	~DevicePresenter();

	const DMOptionsData * options() const
	{
		return data_;
	}

private slots:
	void Chirp_changed( int iChirp )
	{
		data_->setChirp( (WORD) iChirp );
	}

	void EndBeep_changed( int iBeepValue )
	{
		data_->setCRCBeep( (WORD) iBeepValue );
	}

	void CRCBeep_changed( int iBeepValue )
	{
		data_->setEndBeep( (WORD) iBeepValue);
	}

private:
	IOptionsView * option_view_;
	DMOptionsData *data_;

};

#endif // OPTIONSMANAGER_H
