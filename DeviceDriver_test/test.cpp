#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"
#include "TestableFlash.cpp"
#include "../DeviceDriver/Application.cpp"
#include "TestableDeviceDriver.cpp"

class DeviceDriverFixture : public testing::Test {
protected:
	void SetUp() override {
	}

public:

	testing::NiceMock<TestableFlash> TEST_FLASH;
	DeviceDriver dd{&TEST_FLASH};
};


TEST_F(DeviceDriverFixture, 읽기_5번같은데이터) {
	long addr = 0x4321;
	EXPECT_CALL(TEST_FLASH, read(addr), ())
		.Times(5);

	dd.read(addr);
}

TEST_F(DeviceDriverFixture, 읽기_5번같은데이터아님) {
	// Arrange
	EXPECT_CALL(TEST_FLASH, read, (long address), ())
		.WillOnce(testing::Return(9))
		.WillRepeatedly(testing::Return(8));

	// Act
	//EXPECT_THROW(dd.read(0), exception, "ReadFailException");
	try {
		dd.read(0);
	}
	catch (exception& e)
	{
		// Assert
		EXPECT_EQ(string("ReadFailException"), e.what());
	}
}

TEST_F(DeviceDriverFixture, 쓰기_읽고쓰기) {
	// Arrange
	long addr = 0x55;
	int data = 0x1234;
	EXPECT_CALL(TEST_FLASH, read(addr))
		.Times(1)
		.WillOnce(testing::Return(0xff));
	EXPECT_CALL(TEST_FLASH, write(addr, data), ())
		.Times(1);

	// Act
	dd.write(addr, data);
}

TEST_F(DeviceDriverFixture, 쓰기_이미쓰인영역) {
	// Arrange
	long addr = 0x55;
	int data = 0x1234;
	EXPECT_CALL(TEST_FLASH, read(addr), ())
		.Times(1)
		.WillOnce(testing::Return(0x1234));
	EXPECT_CALL(TEST_FLASH, write(addr, data), ())
		.Times(0);

	// Act
	// EXPECT_THROW(dd.write(0, 0x1234), exception, "WriteFailException");
	try {
		dd.write(addr, data);
	}
	catch (exception& e)
	{
		// Assert
		EXPECT_EQ(string("WriteFailException"), e.what());
	}
}

// ===========================

class ApplicationFixture : public testing::Test {
protected:
	void SetUp() override {
	}

public:
	testing::NiceMock<TestableFlash> TEST_FLASH;
	DeviceDriver dd{ &TEST_FLASH };
	Application App{ &dd };
};

TEST_F(ApplicationFixture, App_범위읽기) {
	// Arrange
	long startAddr = 0;
	long endAddr = 7;
	long nr_read = endAddr - startAddr + 1;

	EXPECT_CALL(TEST_FLASH, read)
		.Times(nr_read*5)
		.WillOnce(testing::Return(3))
		.WillOnce(testing::Return(3))
		.WillOnce(testing::Return(3))
		.WillOnce(testing::Return(3))
		.WillOnce(testing::Return(3))
		.WillOnce(testing::Return(2))
		.WillOnce(testing::Return(2))
		.WillOnce(testing::Return(2))
		.WillOnce(testing::Return(2))
		.WillOnce(testing::Return(2))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(1))
		.WillOnce(testing::Return(0))
		.WillOnce(testing::Return(0))
		.WillOnce(testing::Return(0))
		.WillOnce(testing::Return(0))
		.WillOnce(testing::Return(0))
		.WillRepeatedly(testing::Return(0xf));

	App.ReadAndPrint(startAddr, endAddr);
}

TEST_F(ApplicationFixture, App_범위쓰기) {
	// Arrange
	int nr_read = 5;
	int data = 0x1234;

	EXPECT_CALL(TEST_FLASH, read)
		.Times(nr_read)
		.WillRepeatedly(testing::Return(0xff));

	EXPECT_CALL(TEST_FLASH, write, (_,data), ())
		.Times(nr_read);

	App.WriteAll(data);
}

// ===========================

class ApplicationFixture2 : public testing::Test {
protected:
	void SetUp() override {
	}

public:
	TestableDeviceDriver TEST_DEVICE_DRIVER;
	Application App{ &TEST_DEVICE_DRIVER };
};


TEST_F(ApplicationFixture2, App_범위읽기) {
	// Arrange
	long startAddr = 0;
	long endAddr = 7;
	long nr_read = endAddr - startAddr + 1;

	EXPECT_CALL(TEST_DEVICE_DRIVER, read)
		.Times(nr_read);

	App.ReadAndPrint(startAddr, endAddr);
}

TEST_F(ApplicationFixture2, App_범위쓰기) {
	// Arrange
	int nr_read = 5;
	int data = 0x1234;

	EXPECT_CALL(TEST_DEVICE_DRIVER, write, (_, data), ())
		.Times(nr_read);

	App.WriteAll(data);
}