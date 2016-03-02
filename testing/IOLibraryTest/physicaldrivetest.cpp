#include <boost/test/unit_test.hpp>

#include "IOLibrary/physicaldrive.h"

IO::PhysicalDrivePtr create_physical_drive(uint32_t drive_number)
{
	auto physical_drive = std::make_shared<IO::PhysicalDrive>();
	physical_drive->setDriveNumber(drive_number);
	physical_drive->setDriveName(L"Physical drive " + std::to_wstring(drive_number));
	physical_drive->setNumberSectors(1000);
	physical_drive->setBytesPerSector(512);
	return physical_drive;

}
struct F_DriveList
{
	F_DriveList()
	{
		auto physical_drive0 = create_physical_drive(0);
		auto physical_drive1 = create_physical_drive(1);

		auto physical_drive2 = create_physical_drive(2);

		drivelist.add(physical_drive0);
		drivelist.add(physical_drive1);
		drivelist.add(physical_drive2);
	}
	~F_DriveList()
	{
		drivelist.remove_all();
	}

	IO::PhysicalDriveList drivelist;
};


BOOST_FIXTURE_TEST_CASE(TestAddInDriveList, F_DriveList)
{
	auto physical_drive1 = create_physical_drive(1);


	drivelist.add(physical_drive1);
	BOOST_CHECK_EQUAL(drivelist.getSize(), 3);

	auto physical_drive3 = create_physical_drive(3);
	drivelist.add(physical_drive3);
	BOOST_CHECK_EQUAL(drivelist.getSize(), 4);
}

BOOST_FIXTURE_TEST_CASE(TestFindByNumberFromDriveList, F_DriveList)
{
	uint32_t drive_number = 0;
	BOOST_CHECK_EQUAL(drivelist.find_by_number(drive_number)->getDriveNumber(), drive_number);
	drive_number = 2;
	BOOST_CHECK_EQUAL(drivelist.find_by_number(drive_number)->getDriveNumber(), drive_number);
	drive_number = 3;
	auto find_drive = drivelist.find_by_number(drive_number);
	BOOST_TEST_CHECK(!find_drive);
}

BOOST_FIXTURE_TEST_CASE(TestRemoveFromDriveList, F_DriveList)
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

BOOST_AUTO_TEST_CASE(TestGetDevicePath)
{
	IO::DriveAttributesReader drive_attributes;
	drive_attributes.readDriveAttributes(0);
	drive_attributes.readDriveAttributes(1);
	drive_attributes.readDriveAttributes(2);
	drive_attributes.readDriveAttributes(3);
	drive_attributes.readDriveAttributes(4);



}

//BOOST_AUTO_TEST_CASE(TestGetDeviceName)
//{
//	IO::DriveAttributesReader drive_attributes;
//	drive_attributes.GetDeviceName(0);
//	drive_attributes.GetDeviceName(1);
//
//}
