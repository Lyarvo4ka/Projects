#include "erasetask.h"
#include "dmtreemodel.h"


/************************************************************************/
/*							 EraseTabWidget								*/
/************************************************************************/
//
//EraseTabWidget::EraseTabWidget(QWidget *parent, DMItemIdex * dm_index )
//	: BaseTabWidget(parent)
//	, dm_index_(dm_index)
//	, disk_master_(nullptr)
//	, curDevice_ (nullptr)
//	, abstract_erase_( nullptr )
//	, erase_pattern_ ( DM_EraseParam::kErasePattern_00 )
//{
//	eraseWidgetUi_.setupUi(this);
//
//	disk_master_ = toDiskMaster (dm_index->getDevice());
//	if (disk_master_)
//	{
//		eraseWidgetUi_.deviceWidget->setWidgetName( QString::fromLocal8Bit("Устройство для затирания:") );
//		connect( eraseWidgetUi_.deviceWidget, SIGNAL ( deviceIndexChanged ( int ) ), this, SLOT (device_changed(int) ) );
//		add_devices( );
//	}
//
//
//	ShowDetectionInfo(false);
//	connect ( eraseWidgetUi_.rangeWidget, SIGNAL(DetectDevicePressed( PortArray )), this, SLOT( StartDetectDevices( PortArray ) ) );
//	eraseWidgetUi_.taskInfoWidget->setDiskMasterName( "DiskMasterUsb Board id = " + QString::number( disk_master_->getID() ) );
//}
//EraseTabWidget::~EraseTabWidget()
//{
//	qDebug("Destructor [\'EraseTabWidget\']");
//}
//bool EraseTabWidget::isEqual(const DMItemIdex * dm_index)
//{
//	return compareItemIndexes(dm_index_,dm_index);
//}
//bool EraseTabWidget::isEqual(const DiskMasterPtr2 & disk_master)
//{
//	return isDM_InIndex(dm_index_,disk_master);
//}
//QString EraseTabWidget::getTabName() const
//{
//	return EraseTaskText;
//}
//void EraseTabWidget::setProgress(const int position)
//{
//	eraseWidgetUi_.progressBar->setValue(position);
//	if (dm_index_)
//		dm_index_->setPorgress(position);
//}
//void EraseTabWidget::setEnableAllView( bool bEnable )
//{
//	eraseWidgetUi_.deviceWidget->setEnabled(bEnable);
//	eraseWidgetUi_.rangeWidget->setEnabled(bEnable);
//	eraseWidgetUi_.groupEraseParams->setEnabled(bEnable);
//	eraseWidgetUi_.startButton->setEnabled(bEnable);
//	eraseWidgetUi_.cancelButton->setEnabled(bEnable);
//	eraseWidgetUi_.taskInfoWidget->setEnabled(bEnable);
//}
//void EraseTabWidget::setRangeData()
//{
//	eraseWidgetUi_.rangeWidget->setRange(curDevice_);
//}
//void EraseTabWidget::ShowDetectionInfo( bool bShow )
//{
//	EnableDetectionInfo ( eraseWidgetUi_.detectDriveText , eraseWidgetUi_.lcdNumber , bShow );
//}
//void EraseTabWidget::add_devices( )
//{
//	AddTargets(disk_master_ , eraseWidgetUi_.deviceWidget);
//}
//void EraseTabWidget::device_changed( int nIndex )
//{
//	curDevice_ = disk_master_->getTarget( nIndex );
//	eraseWidgetUi_.deviceWidget->set_device(curDevice_);
//	setRangeData();
//}
//void EraseTabWidget::start_clicked()
//{
//	setEnableAllView(false);
//	eraseWidgetUi_.cancelButton->setEnabled(true);
//	setProgress(0);
//	dm_index_->setState(DMItemIdex::started);
//	dm_index_->setStatus(DMItemIdex::erasing);
//	AppendLogText( QString::fromLocal8Bit("Задача затирания начата.") );
//
//	abstract_erase_ = new QuickEraseTask(disk_master_,this);
//	connect (abstract_erase_, SIGNAL(new_device( const DM::PORT * )), this, SLOT(DeviceDetected(const DM::PORT *)));
//	connect (abstract_erase_, SIGNAL(update_lba( const qlonglong)), this, SLOT(current_lba( const qlonglong)));
//	connect (abstract_erase_, SIGNAL( finish_task( const qlonglong ) ), this, SLOT( task_finished( const qlonglong )) );
//	connect (abstract_erase_, SIGNAL( break_task(const qlonglong) ), this, SLOT( task_breaked(const qlonglong) ));
//	connect (abstract_erase_, SIGNAL( not_detected(const DM::PORT *, int) ), this, SLOT( DeviceNotDetected(const DM::PORT *, int) ) );
//
//	if ( eraseWidgetUi_.rangeWidget->isChecked() )
//	{
//		DataRange data_block;
//		data_block.SourceOffset_ = eraseWidgetUi_.rangeWidget->getOffset();
//		data_block.TargetOffset_ = 0;
//		data_block.SectorsCount_ = eraseWidgetUi_.rangeWidget->getSectorsCount();
//		eraseWidgetUi_.currentSector->setText("0 / " + QString::number(data_block.SectorsCount_));
//
//		abstract_erase_->StartTaskEx(nullptr, curDevice_->getPort(), data_block , erase_pattern_);
//	}
//	else
//	{
//		eraseWidgetUi_.currentSector->setText("0");
//		abstract_erase_->StartTask(nullptr, curDevice_->getPort(), erase_pattern_ );
//	}
//
//}
//void EraseTabWidget::cancel_clicked()
//{
//	if (abstract_erase_)
//	{
//		abstract_erase_->AbortTask();
//	}
//}
//void EraseTabWidget::current_lba( const qlonglong currectSector )
//{
//	int progressValue = (int) (currectSector * 100) / ( abstract_erase_->getSectorsCount() ) ;
//
//	if ( progressValue >= 0 && progressValue <= 100)
//	{
//		setProgress(progressValue);
//	}
//	QString currSectorStr(QString::number(currectSector) + "/" + QString::number(abstract_erase_->getSectorsCount()));
//	eraseWidgetUi_.currentSector->setText(currSectorStr);
//}
//void EraseTabWidget::task_finished( const qlonglong lastSector )
//{
//	current_lba(lastSector);
//	setProgress(100);
//	QString outputText( QString::fromLocal8Bit( "Задача \"Затирания\" успешно завершена.\n" ) );
//	AppendLogText(outputText);
//	QMessageBox msgBox;
//	msgBox.setText(outputText);
//	msgBox.exec();
//	dm_index_->setState(DMItemIdex::completed);
//	dm_index_->setStatus(DMItemIdex::ready);
//	setEnableAllView(true);
//	if (abstract_erase_)
//	{
//		abstract_erase_->exit();
//		delete abstract_erase_;
//		abstract_erase_ = nullptr;
//	}
//}
//void EraseTabWidget::task_breaked( const qlonglong last_lba )
//{
//	current_lba(last_lba);
//	QString outputText( QString::fromLocal8Bit( "Задача \"Затирания\" была прервана.\n" ) );
//	AppendLogText(outputText);
//	QMessageBox msgBox;
//	msgBox.setText(outputText);
//	msgBox.exec();
//	dm_index_->setState(DMItemIdex::completed);
//	dm_index_->setStatus(DMItemIdex::ready);
//	setEnableAllView(true);
//	if (abstract_erase_)
//	{
//		abstract_erase_->exit();
//		delete abstract_erase_;
//		abstract_erase_ = nullptr;
//	}
//
//}
//void EraseTabWidget::erase0clicked()
//{
//	erase_pattern_ = DM_EraseParam::kErasePattern_00;
//}
//void EraseTabWidget::erase1clicked()
//{
//	erase_pattern_ = DM_EraseParam::kErasePattern_FF;
//}
//void EraseTabWidget::eraseRandClicked()
//{
//	erase_pattern_ = DM_EraseParam::kErasePattern_Random;
//}
