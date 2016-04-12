#ifndef TESTCOPYRANGE_H
#define TESTCOPYRANGE_H

#include <QObject>
#include <QtTest>

#include "copyrangewidget.h"



class TestCopyRange : public QObject
{
	Q_OBJECT

public:
	TestCopyRange(QObject *parent = nullptr);
	~TestCopyRange();

private slots:
	void rangeTest()
	{
		CopyRangeWidget range_widget( nullptr );
		auto range_data = range_widget.getRange();
		QFETCH( qlonglong , src_offset );
		QFETCH( qlonglong , dst_offset );
		QFETCH( qlonglong , sec_count );
		QFETCH( qlonglong , src_size );
		QFETCH( qlonglong , dst_size );
		QFETCH( bool , valid );


		QString str_error;
		range_data->setRange( src_offset , dst_offset , sec_count );
		//QCOMPARE( range_data->validate( src_size , dst_size , str_error) , valid );
		bool bResult = range_data->validate( src_size , dst_size , str_error);
		QVERIFY2(bResult == valid , qPrintable( str_error ) );
		
	}
	void rangeTest_data( )
	{
		QTest::addColumn< qlonglong > ( "src_offset" );
		QTest::addColumn< qlonglong > ( "dst_offset" );
		QTest::addColumn< qlonglong > ( "sec_count" );
		QTest::addColumn< qlonglong > ( "src_size" );
		QTest::addColumn< qlonglong > ( "dst_size" );
		QTest::addColumn< bool > ( "valid" );

		QTest::newRow("valid , normal") << (qlonglong) 100 << (qlonglong) 20 << (qlonglong) 50 << (qlonglong) 100 << (qlonglong) 100 << true;
		QTest::newRow("invalid , source offset less then 0") << (qlonglong) -10 << (qlonglong) 20 << (qlonglong) 100 << (qlonglong) 100 << (qlonglong) 100 << false;
		QTest::newRow("invalid , target offset less then 0") << (qlonglong) 10 << (qlonglong) -20 << (qlonglong) 100 << (qlonglong) 100 << (qlonglong) 100 << false;
		QTest::newRow("invalid , sector count less then 0") <<  (qlonglong) 10 << (qlonglong) 20 << (qlonglong) -100 << (qlonglong) 100 << (qlonglong) 100 << false;
		QTest::newRow("invalid , source offset more than source size") <<  (qlonglong) 30 << (qlonglong) 20 << (qlonglong) 80 << (qlonglong) 100 << (qlonglong) 100 << false;
		QTest::newRow("invalid , target offset more than target size") <<  (qlonglong) 20 << (qlonglong) 30 << (qlonglong) 80 << (qlonglong) 100 << (qlonglong) 100 << false;
	}
};




#endif // TESTCOPYRANGE_H
