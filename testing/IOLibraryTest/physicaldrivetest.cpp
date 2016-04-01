//#define BOOST_TEST_MODULE physical_drive_test
#include <boost/test/unit_test.hpp>
#include "MockDevice.h"

struct F_DriveList
{
	F_DriveList()
	{
		auto physical_drive0 = create_fake_physical_drive(0);
		auto physical_drive1 = create_fake_physical_drive(1);

		auto physical_drive2 = create_fake_physical_drive(2);

		drivelist.add(physical_drive2);
		drivelist.add(physical_drive0);
		drivelist.add(physical_drive1);
	}
	~F_DriveList()
	{
		drivelist.remove_all();
	}

	ListDrives drivelist;
}; 

BOOST_FIXTURE_TEST_SUITE(TestPhysicalDrive , F_DriveList)

BOOST_AUTO_TEST_CASE(TestAddInDriveList)
{
	auto physical_drive1 = create_fake_physical_drive(1);


	drivelist.add(physical_drive1);
	BOOST_CHECK_EQUAL(drivelist.getSize(), 3);

	auto physical_drive3 = create_fake_physical_drive(3);
	drivelist.add(physical_drive3);
	BOOST_CHECK_EQUAL(drivelist.getSize(), 4);
}

BOOST_AUTO_TEST_CASE(TestFindByNumberFromDriveList )
{
	uint32_t drive_number = 0;
	BOOST_CHECK_EQUAL(drivelist.find_by_number(drive_number)->getDriveNumber(), drive_number);
	drive_number = 2;
	BOOST_CHECK_EQUAL(drivelist.find_by_number(drive_number)->getDriveNumber(), drive_number);
	drive_number = 3;
	auto find_drive = drivelist.find_by_number(drive_number);
	BOOST_TEST_CHECK(!find_drive);
}

BOOST_AUTO_TEST_CASE(TestRemoveFromDriveList)
{
	drivelist.remove(1);
	auto find_drive = drivelist.find_by_number(1);
	BOOST_TEST_CHECK(!find_drive);
	auto drive_count = drivelist.getSize();
	drivelist.remove(5);
	BOOST_TEST_CHECK(drivelist.getSize(), drive_count);
	drivelist.remove_all();
	BOOST_CHECK_EQUAL(drivelist.getSize(), 0);
}
BOOST_AUTO_TEST_CASE(TestSortDriveList)
{
	drivelist.sort();
	BOOST_CHECK_EQUAL(drivelist.index(0)->getDriveNumber(), 0);
}

BOOST_AUTO_TEST_SUITE_END()

//BOOST_AUTO_TEST_CASE(TestReadAllDrives)
//{
//	PhysicalDriveList driveList;
//	driveList.ReadAllDrives();
//	
//	uint32_t drive_number = 0;
//	while (true)
//	{
//		auto physical_drive = driveList.find_by_number(drive_number);
//		if (!physical_drive)
//			break;
//		ShowPhysicalDriveInfo(physical_drive);
//
//		++drive_number;
//	}
//
//}
//BOOST_AUTO_TEST_CASE(TestReadSerialFromSmart)
//{
	//PhysicalDriveList driveList;
	//driveList.ReadAllDrives();

	//uint32_t drive_number = 0;
	//while (auto physical_drive = driveList.find_by_number(drive_number))
	//{
	//	std::string serial_number;
	//	DriveAttributesReader attr_reader;
	//	attr_reader.readSerialFromSmart(physical_drive->getPath(), serial_number);
	//	++drive_number;
	//}

//}

//BOOST_AUTO_TEST_CASE(TestGetDeviceName)
//{
//	IO::DriveAttributesReader drive_attributes;
//	drive_attributes.GetDeviceName(0);
//	drive_attributes.GetDeviceName(1);
//
//}


//