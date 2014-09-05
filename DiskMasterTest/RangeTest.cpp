

#define BOOST_TEST_MODULE CopyRangeTestModule

#include <boost/test/unit_test.hpp>

#include "copyrangewidget.h"

BOOST_AUTO_TEST_CASE( CopyRangeDataTest )
{
	int argc = 0;

	QApplication a(argc , nullptr );

	CopyRangeData range_data;
	range_data.Initialize();

	range_data.setSourceOffset( 1 );
	BOOST_CHECK_EQUAL( range_data.getSourceOffset() , 1 );

	range_data.setTargetOffset( 2 );
	BOOST_CHECK_EQUAL( range_data.getTargetOffset() , 2 );

	range_data.setSectorCount( 3 );
	BOOST_CHECK_EQUAL( range_data.getSectorCount() , 3 );

	range_data.Initialize();
	range_data.setRange( 1 , 2 , 3 );
	BOOST_CHECK_EQUAL( range_data.getSourceOffset() , 1 );
	BOOST_CHECK_EQUAL( range_data.getTargetOffset() , 2 );
	BOOST_CHECK_EQUAL( range_data.getSectorCount() , 3 );

	range_data.Initialize();

	range_data.setRange( 0 , 0 , 100 );
	QString strErr;
	BOOST_CHECK( range_data.validate( 100 , 100 , strErr ) );


	//range_widget.
}

BOOST_AUTO_TEST_CASE( CopyRangeWidgetTest )
{
	int argc = 0;

	QApplication a(argc , nullptr );

	CopyRangeWidget range_widget( nullptr );

	range_widget.setSourceOffset( 1 );
	BOOST_CHECK_EQUAL( range_widget.getSourceOffset() , 1 );

	range_widget.setTargetOffset( 2 );
	BOOST_CHECK_EQUAL( range_widget.getTargetOffset() , 2 );

	range_widget.setSectorCount( 3 );
	BOOST_CHECK_EQUAL( range_widget.getSectorsCount() , 3 );

	range_widget.setRange( 4 , 5 , 6 );
	BOOST_CHECK_EQUAL( range_widget.getSourceOffset() , 4 );
	BOOST_CHECK_EQUAL( range_widget.getTargetOffset() , 5 );
	BOOST_CHECK_EQUAL( range_widget.getSectorsCount() , 6 );

	range_widget.setRange( 0 , 0 , 100 );
	QString strErr;
	BOOST_CHECK( range_widget.validate( 100 , 100 , strErr ) );

}