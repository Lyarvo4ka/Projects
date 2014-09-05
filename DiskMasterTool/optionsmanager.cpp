#include "optionsmanager.h"

//DevicePresenter::DevicePresenter(IOptionsView * option_view , DMOptionsData * option_data  , QObject * parent )
//	: QObject( parent )
//	, data_( option_data )
//{
//
//}
DevicePresenter::DevicePresenter(IOptionsView * option_view , QObject * parent )
	: QObject( parent )
	, option_view_( option_view )
	, data_( new DMOptionsData() )
{
	if ( QObject * view = dynamic_cast< QObject * > ( option_view_ ))
	{
		connect( view , SIGNAL( ChirpChanged( int ) ) , this , SLOT( Chirp_changed( int ) ) );
		connect( view , SIGNAL( EndBeepChanged( int ) ) , this , SLOT( EndBeep_changed( int ) ) );
		connect( view , SIGNAL( CRCBeepChanged( int ) ) , this , SLOT( CRCBeep_changed( int ) ) );
	}
}
DevicePresenter::~DevicePresenter()
{

}
