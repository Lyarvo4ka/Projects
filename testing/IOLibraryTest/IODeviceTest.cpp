#include <boost/test/unit_test.hpp>

#include "IOLibrary/IODevice.h"
#include "MockDevice.h"

using namespace IO;

struct F_DiskDevice
{
	F_DiskDevice()
	{
		ListDrives drive_list = ReadPhysicalDrives();

		if (auto disk0 = drive_list.find_by_number(0))
			disk_device0 = new DiskDevice(disk0);
		else
			disk_device0 = new DiskDevice(nullptr);

		null_device = new DiskDevice(nullptr);

	}
	~F_DiskDevice()
	{
		delete disk_device0;
		delete null_device;
	}
	DiskDevice * disk_device0;
	DiskDevice * null_device;
};

BOOST_FIXTURE_TEST_SUITE(TestDiskDevice , F_DiskDevice)

BOOST_AUTO_TEST_CASE(TestOpenDiskDevice)
{
	auto open_result = disk_device0->Open(OpenMode::OpenWrite);
	BOOST_CHECK_EQUAL(open_result, true);
	BOOST_CHECK_EQUAL(disk_device0->isOpen(), open_result);


	open_result = null_device->Open(OpenMode::OpenWrite);
	BOOST_CHECK_EQUAL(open_result, false);
	BOOST_CHECK_EQUAL(null_device->isOpen(), open_result);

}


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE(TestgetBytesForBlock)
{
	BOOST_CHECK_EQUAL(getBytesForBlock(0, 0, 0), 0);
	BOOST_CHECK_EQUAL(getBytesForBlock(1023, 1024, 256), 1);
	BOOST_CHECK_EQUAL(getBytesForBlock(0, 512, 1024), 512);

}

BOOST_FIXTURE_TEST_SUITE(TestDiskDeviceMock, F_MockDiskDevice)
BOOST_AUTO_TEST_CASE(TestOpen)
{
	BOOST_CHECK_EQUAL(mock_diskdevice_->Open(OpenMode::OpenRead), true);

	MockDiskDevice null_devie(nullptr);
	BOOST_CHECK_EQUAL(null_devie.Open(OpenMode::OpenRead), false);
}
BOOST_AUTO_TEST_CASE(TestDiskDeviceReadBlockNoOpened)
{
	BOOST_CHECK_EQUAL(mock_diskdevice_->ReadBlock(nullptr, 0), 0);
}
BOOST_AUTO_TEST_SUITE_END()
//BOOST_AUTO_TEST_CASE(test_name1)
//{
//	IO::File ioFile(L"d:\\test_folder\\1.docx");
//
//}
//
//BOOST_AUTO_TEST_SUITE_END()