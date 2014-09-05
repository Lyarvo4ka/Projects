#include "diskmasterui.h"

#include "dmtreemodel.h"

#include "maintaskwidget.h"




DiskMasterUI::DiskMasterUI(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	MainTaskWidget * pMainTask = new MainTaskWidget(ui.mainTabWidget);

	ui.mainTabWidget->addMainTask( pMainTask );
	
	connect( pMainTask , SIGNAL ( ItemSelected( const DMItemIdex * ) ) , this , SLOT ( ItemIsSelected( const DMItemIdex *) ) );
	connect( ui.mainTabWidget , SIGNAL ( setEnabledTasks ( bool ) ) , this , SLOT ( EnableTaskActions( bool ) ) );

	connect( ui.CopyAction, SIGNAL( activated() ), pMainTask, SLOT( CopyButtonClicked() ) );
	connect( ui.VerifyAction, SIGNAL( activated () ), pMainTask, SLOT( VerifyButtonClicked() ) );
	connect( ui.EraseAction, SIGNAL( activated () ), pMainTask, SLOT( EraseButtonClicked() ) );

	connect( ui.mainTabWidget , SIGNAL ( setEnabledStart ( bool ) ) , ui.StartAction,  SLOT ( setEnabled( bool ) ) ) ;
	connect( ui.mainTabWidget , SIGNAL ( setEnabledCancel ( bool ) ) , ui.StartAction,  SLOT ( setEnabled( bool ) ) ) ;

	connect( ui.StartAction, SIGNAL( activated() ), ui.mainTabWidget, SLOT ( startTask() ) );
	connect( ui.StopTask, SIGNAL( activated() ), ui.mainTabWidget, SLOT ( cancelTask() ) );
	connect( ui.actionOpenTask , SIGNAL( activated() ), pMainTask, SLOT ( LoadTask_ckicked() ) );	

	connect( ui.actionPreferences , SIGNAL( activated() ),  ui.mainTabWidget, SLOT ( Preferences_clicked() ) );

}

DiskMasterUI::~DiskMasterUI()
{
	DMTool::DMTaskManager::GetTaskManager()->Relese();
}
void DiskMasterUI::ItemIsSelected( const DMItemIdex * selectd_index)
{
	if ( selectd_index )
	{
		if ( selectd_index->isDiskMaster() )
		{

			EnableTaskActions(true);
		}
		else
			EnableTaskActions(false);

	}
}
void DiskMasterUI::EnableTaskActions( bool bEnable )
{
	ui.CopyAction->setEnabled(bEnable);
	ui.VerifyAction->setEnabled(bEnable);
	ui.EraseAction->setEnabled(bEnable);
}

void DiskMasterUI::closeEvent( QCloseEvent * close_event )
{
	qDebug() << "Close Event";
	ui.mainTabWidget->RemoveTabs();
	close_event->accept();
}
