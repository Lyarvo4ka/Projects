#ifndef MAINTASKWIDGET_H
#define MAINTASKWIDGET_H

#include <QObject>
#include <QMessageBox>


#include "ui_MainTaskPanel.h"

//class DMItemIdex;
//class DMTreeModel;
#include "dmtreemodel.h"

//class DiskDevice;
//
//#include <memory>
//class DiskMasterDevice;
//typedef std::tr1::shared_ptr<DiskMasterDevice> DiskMasterPtr;
//class DiskDevice;
//typedef std::tr1::shared_ptr<DiskDevice> DiskDevicePtr;
//class DiskMasterDevice;
//typedef std::tr1::shared_ptr<DiskMasterDevice> DiskMasterPtr;
//
//#include <vector>


#include "ui_ModifySectorUi.h"
#include "DiskMasterLib\dm_function.h"
class SectorModifyDialog
	: public QDialog
{
	Q_OBJECT

	static const int DefaultBuffer = 4096; 

public:
	SectorModifyDialog( QWidget *parent, DWORD id )
		: QDialog( parent )
		, id_( id )
//		, write_device_( nullptr )
	{
		ui_.setupUi( this );
		if ( auto disk_master = DMTool::getDiskMaster( id_ ) )
		{
			for ( int iCount = 0; iCount < disk_master->target_count(); ++ iCount)
			{
				//ui_.modifyDevice->add_device( disk_master->getTarget(iCount) );
				auto device = disk_master->getTarget( iCount );
				ui_.modifyDevice->add_data( displayName( device ) , identifyIcon( device ) );
			}
			for ( auto nDevice = 0; nDevice < disk_master->target_count(); ++nDevice )
				if ( auto sata_device = disk_master->getTarget(nDevice) )
					if ( DMTool::isSATA(sata_device) )
					{
						//ui_.modifyDevice->ChangeDevice( nDevice );
						ui_.modifyDevice->change_data( nDevice, displayName( sata_device ), identifyIcon( sata_device ) );
					}
		}

		connect( ui_.ModifyButton , SIGNAL ( clicked() ), this , SLOT( ModifySignature() ) );
		connect( ui_.WriteButton , SIGNAL ( clicked() ), this , SLOT( WriteSignature() ) );
		connect( ui_.VerifyButton , SIGNAL ( clicked() ), this , SLOT( VerifySignature() ) );
	}

public slots:
	void ModifySignature()
	{
		QMessageBox msgBox( this );
		msgBox.setText("<B> Модификация MBR.</B>");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setIcon(QMessageBox::Information);

		auto device = this->getCurrentDevice();
		BYTE read_buffer[DefaultBuffer];
		memset( read_buffer, 0x00 , device->getBlockSize());
		if ( this->DetectCurrentDevice() )	
		{
			if ( this->ReadMBR(read_buffer) )
			{
				WORD *val_55AA =  (WORD *) &read_buffer [ 510 ];
				if ( *val_55AA == 0x55AA || *val_55AA == 0xAA55 )
				{
					WORD old_value = *val_55AA;
					WORD new_value = *val_55AA;
					new_value = new_value >> 8 | new_value << 8;
					*val_55AA = old_value;
					if ( this->WriteMBR(read_buffer) )
					{
						memset(read_buffer , 0x00 , device->getBlockSize() );
						if ( this->ReadMBR( read_buffer ) )
						{
							if ( *val_55AA == new_value )
							{
								msgBox.setInformativeText("Сигнатура успешно модифицирована.");
							}
							else
								msgBox.setInformativeText("Чтото произошло мистическое и не получилось правильно записать на устройсто.");

							msgBox.exec();
						}

					}
					else
					{
						msgBox.setInformativeText("Не удалось записать на устройство.");
						msgBox.exec();
					}
				}
				else
				{
					msgBox.setInformativeText("Не найдена сигнатура 0x55AA.");
					msgBox.exec();
				}

			}
		//	}



		}
		else
		{
			msgBox.setInformativeText("Не удалось определить устройство.");
			msgBox.exec();
		}

	}
	void WriteSignature()
	{
		QMessageBox msgBox(this);
		msgBox.setText("<B> Запись MBR.</B>");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setIcon(QMessageBox::Information);

		auto device = this->getCurrentDevice();
		BYTE read_buffer[DefaultBuffer];
		memset( read_buffer, 0x00 , device->getBlockSize());
		if ( this->DetectCurrentDevice() )	
		{
			if ( this->ReadMBR(read_buffer) )
			{
				WORD *val_55AA =  (WORD *) &read_buffer [ 510 ];
				*val_55AA = 0xAA55;
					if ( this->WriteMBR(read_buffer) )
					{
						memset(read_buffer , 0x00 , device->getBlockSize() );
						if ( this->ReadMBR( read_buffer ) )
						{
							if ( *val_55AA == 0x55AA )
							{
								msgBox.setInformativeText("Сигнатура успешно записана.");
							}
							else
								msgBox.setInformativeText("Чтото произошло мистическое и не получилось правильно записать на устройсто.");


							msgBox.exec();
						}

					}
					else
					{
						msgBox.setInformativeText("Не удалось записать на устройство.");
						msgBox.exec();
					}
				}
				else
				{
					msgBox.setInformativeText("Не удалось прочитать с устройства.");
					msgBox.exec();
				}





		}
		else
		{
			msgBox.setInformativeText("Не удалось определить устройство.");
			msgBox.exec();
		}
		//delete [] read_buffer;
		//read_buffer = nullptr;
	}
	void VerifySignature( )
	{
		QMessageBox msgBox( this );
		msgBox.setText("<B> Проверка MBR.</B>");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setIcon(QMessageBox::Information);

		auto device = this->getCurrentDevice();
		BYTE read_buffer[DefaultBuffer];
		memset( read_buffer, 0x00 , device->getBlockSize());
		if ( this->DetectCurrentDevice() )	
		{
			if ( this->ReadMBR(read_buffer) )
			{
				WORD *val_55AA =  (WORD *) &read_buffer [ 510 ];
				QString singText = "";
				if ( *val_55AA == 0x55AA )
					msgBox.setInformativeText("Сигнатура правильная.");
				else
					msgBox.setInformativeText("Сигнатура не правильная.");

				msgBox.exec();
			}
		}
		else
		{
			msgBox.setInformativeText("Не удалось определить устройство.");
			msgBox.exec();
		}


	}
private:
	DiskDevicePtr getCurrentDevice( )
	{
		int nIndex =  ui_.modifyDevice->getCurrentIndex();
		if ( auto disk_master = DMTool::getDiskMaster( id_ ) )
			return disk_master->getTarget(nIndex);
		return nullptr;
	}
	bool DetectCurrentDevice( )
	{
		if (auto device = this->getCurrentDevice() )
			if ( !device->isDetected() )
			{
				if ( auto disk_master = DMTool::getDiskMaster( id_ ) )
				{
					if ( disk_master->Rescan(device) )
					{
						ui_.modifyDevice->change_data( ui_.modifyDevice->getCurrentIndex(), displayName( device ), identifyIcon( device ) );;
					}
				}
				return device->isDetected();
			}
			else
				return true;
		return false;
	}
	bool ReadMBR( BYTE * buffer )
	{
		assert( buffer != nullptr );
		if (auto read_device = getCurrentDevice() )
		if ( auto disk_master = DMTool::getDiskMaster( id_ ) )
		{
			//memset(buffer , 0x00 , read_device->getBlockSize() );
			ULONGLONG offset = 0;
			return false;//disk_master->ReadBlock( read_device->getPort()->number , offset , buffer , read_device->getBlockSize() ) ;
		}
		return false;

	}
	bool WriteMBR( BYTE * buffer)
	{
		assert( buffer != nullptr );
		if (auto write_device = getCurrentDevice() )
			if ( auto disk_master = DMTool::getDiskMaster( id_ ) )
			{
				ULONGLONG write_offset = 0;
				return false;//disk_master->WriteBlock( write_device->getPort()->number , write_offset , buffer , write_device->getBlockSize() );
			}

		return false;
	}
private:
	DWORD id_;
	Ui::ModifySectorUi ui_;
	//DiskDevice * write_device_;
};


#include "dtm\Abstract.h"
#include "dtm\Utilities.h"
#include "dtm\DiskMasterManager.h"

inline DMItemIdex * getIndex( const QModelIndex & model_index) 
{
	if ( !model_index.isValid())
		return nullptr;

	return static_cast< DMItemIdex * > (model_index.internalPointer());
}



class DeviceHolder;
class SelectTaskWindow;
class MainTaskWidget : public QWidget
{
	Q_OBJECT
	//static const QString errorTitle = tr("Ошибка подключения");
public:
	MainTaskWidget(QWidget *parent);
	~MainTaskWidget();
	
	void DetectConnected();


	DMItemIdex * CreateDiskMasterItem( DiskMasterDevice * disk_master);
	
	void ShowTask( DMTool::TASK_STATUS task_status);
	void ResetItemStatus( )
	{
		if (DMItemIdex * dm_index = getIndex(MainTaskUi_.treeView->currentIndex()) )
		{
			if ( auto disk_master = DMTool::getDiskMaster( dm_index->getID() ) )
			{
				disk_master->Close();
				if ( disk_master->Open() )
					dm_index->setStatus( DMTool::READY );	
				else 
					dm_index->setStatus( DMTool::NOT_READY );		

			}
		}
	}
	void changeItemState( DWORD id , DMTool::TASK_STATE state , DMTool::TASK_STATUS status )
	{
		 if ( RootIndex_)
		 {
			 if( RootIndex_->hasChildrend())
			 {
				 for ( int nIndex = 0 ; nIndex < RootIndex_->count() ; ++nIndex)
				 {
					 if ( auto * index = RootIndex_->getChild( nIndex ) )
					 {
						 if ( index->getID() == id )
						 {
							 index->setState( state );
							 index->setStatus( status );
						 }
					 }

				 }
			 }
		 }
	}
	void changeProgress( DWORD id , int position )
	{
		if ( RootIndex_)
		{
			if( RootIndex_->hasChildrend())
			{
				for ( int nIndex = 0 ; nIndex < RootIndex_->count() ; ++nIndex)
				{
					if ( auto * index = RootIndex_->getChild( nIndex ) )
					{
						if ( index->getID() == id )
						{
							index->setPorgress(position);

						}
					}

				}
			}
		}

	}
	void showSettings();
private slots:
	void AddDiskMaster( DM::DiskController * disk_master );
	void RemoveDiskMasterItem( DM::DiskController * disk_master );

signals:
	void ShowCurrentWidget( const DMItemIdex * , int);
	void LoadTask( const DMItemIdex * , const QString & );
	//void CreateTaskWidget ( const DMItemIdex * , int , PortNumbers);
	void DeviceDisappered( const DMItemIdex * );
	void SelectedItem();
	void ItemSelected( const DMItemIdex * );
private slots:
	void CopyButtonClicked();
	void VerifyButtonClicked();
	void EraseButtonClicked();
	void ModifySector();
	void ElementClicked(QModelIndex clicked_index);
	void Double_Clicked(QModelIndex clicked_index);

	void ElementSelected(const QItemSelection& selected, const QItemSelection& deselected);
	void setButtonEnable(const bool enable = true);
	void changeEnable(QModelIndex model_index);
	void UpdateTreeView();

	void LoadTask_ckicked( );
private:
	Ui::MainTaskWidget MainTaskUi_;
	DMItemIdex * RootIndex_;
	DMTreeModel * TreeModel_;
	DeviceHolder * device_holder_;
};

#endif // MAINTASKWIDGET_H
