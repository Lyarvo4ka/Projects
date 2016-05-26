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

BOOST_AUTO_TEST_CASE(Test_isMultiple)
{
	BOOST_CHECK_EQUAL(isMultiple(1024, 0), false);
	BOOST_CHECK_EQUAL(isMultiple(1024, 512), true);
	BOOST_CHECK_EQUAL(isMultiple(1000, 512), false);
	BOOST_CHECK_EQUAL(isMultiple(10, 512), false);
}


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

BOOST_AUTO_TEST_CASE(TestcalcBlockSize)
{
	BOOST_CHECK_EQUAL(IO::calcBlockSize(0, 0, 0), 0);
	BOOST_CHECK_EQUAL(IO::calcBlockSize(1023, 1024, 256), 1);
	BOOST_CHECK_EQUAL(IO::calcBlockSize(0, 512, 1024), 512);
	uint64_t current = 5368709120;
	uint64_t size = 5368709140;
	BOOST_CHECK_EQUAL(IO::calcBlockSize(current, size, 256), size - current);


}

BOOST_FIXTURE_TEST_SUITE(TestDiskDeviceMock, F_MockDiskDevice)

BOOST_AUTO_TEST_CASE(TestOpen)
{
	BOOST_CHECK_EQUAL(disk_device_->Open(OpenMode::OpenRead), true);
}

BOOST_AUTO_TEST_CASE(TestOpenWithNullDevice)
{
	DiskDevice null_device(nullptr);
	BOOST_CHECK_EQUAL(null_device.Open(OpenMode::OpenRead), false);

}

BOOST_AUTO_TEST_CASE(TestDiskDeviceReadBlockNoOpened)
{
	uint8_t buff;
	BOOST_CHECK_EQUAL(disk_device_->ReadBlock(&buff, sizeof(uint8_t)), 0);
}

BOOST_AUTO_TEST_CASE(TestDiskDeviceReadBlockWithNullData)
{
	disk_device_->Open(OpenMode::OpenRead);
	BOOST_CHECK_EQUAL(disk_device_->ReadBlock(nullptr, 1), 0);
}

BOOST_AUTO_TEST_CASE(TestDiskDeviceReadBlockWithNullSize)
{
	disk_device_->Open(OpenMode::OpenRead);
	uint8_t buff;
	BOOST_CHECK_EQUAL(disk_device_->ReadBlock(&buff, 0), 0);
}

BOOST_AUTO_TEST_CASE(TestDiskDeviceReadBlockNotMuliplyBPS)
{
	disk_device_->Open(OpenMode::OpenRead);
	const uint32_t buff_size = 10;
	uint8_t buff[buff_size];
	BOOST_CHECK_EQUAL(disk_device_->ReadBlock(buff, buff_size), 0);
}

BOOST_AUTO_TEST_CASE(TestDiskDeviceReadBlockFine)
{
	disk_device_->Open(OpenMode::OpenRead);
	const uint32_t buff_size = 1024;
	uint8_t buff[buff_size];
	uint32_t expected = buff_size;
	BOOST_CHECK_EQUAL(disk_device_->ReadBlock(buff, buff_size), expected);
}

BOOST_AUTO_TEST_CASE(TestDiskDeviceReadDataNormally)
{
	disk_device_->Open(OpenMode::OpenRead);
	const uint32_t buff_size = 51200;
	uint8_t buff[buff_size];
	uint32_t expected = buff_size;
	disk_device_->setPosition(0);

	BOOST_CHECK_EQUAL(disk_device_->ReadData(buff, buff_size), expected);
	BOOST_CHECK_EQUAL(disk_device_->getPosition(), expected);
}

BOOST_AUTO_TEST_CASE(Test_DiskDevice_ReadDataNotAlignedLessSectorSize)
{
	disk_device_->Open(OpenMode::OpenRead);

	const uint32_t buff_size = 2;
	uint8_t buff[buff_size];
	uint32_t expected = buff_size;
	BOOST_CHECK_EQUAL(disk_device_->ReadDataNotAligned(buff, buff_size), expected);
	BOOST_CHECK_EQUAL(disk_device_->getPosition(), expected);
}

BOOST_AUTO_TEST_CASE(Test_DiskDevice_ReadDataNotAlignedMoreSectorSize)
{
	disk_device_->Open(OpenMode::OpenRead);

	const uint32_t buff_size = 514;
	uint8_t buff[buff_size];
	uint32_t expected = buff_size;
	uint32_t pos = 2;
	disk_device_->setPosition(pos);
	BOOST_CHECK_EQUAL(disk_device_->ReadDataNotAligned(buff, buff_size), expected);
	BOOST_CHECK_EQUAL(disk_device_->getPosition(), pos+ buff_size);
}

BOOST_AUTO_TEST_SUITE_END()
