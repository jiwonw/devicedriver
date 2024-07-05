#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"
#include "TestableFlash.cpp"

class DeviceDriverFixture : public testing::Test {
protected:
	void SetUp() override {
	}

public:
	TestableFlash TEST_FLASH;
	DeviceDriver dd{&TEST_FLASH};
};

TEST_F(DeviceDriverFixture, �б�_5������������) {

	EXPECT_CALL(TEST_FLASH, read, (long address), ())
		.Times(5);

	dd.read(0);
}

TEST_F(DeviceDriverFixture, �б�_5�����������;ƴ�) {
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

TEST_F(DeviceDriverFixture, ����_�а���) {
	// Arrange
	EXPECT_CALL(TEST_FLASH, read, (long address), ())
		.Times(1)
		.WillOnce(testing::Return(0xff));
	EXPECT_CALL(TEST_FLASH, write, (long address, unsigned char data), ())
		.Times(1);

	// Act
	dd.write(0, 0x1234);
}

TEST_F(DeviceDriverFixture, ����_�̹̾��ο���) {
	// Arrange
	EXPECT_CALL(TEST_FLASH, read, (long address), ())
		.Times(1)
		.WillOnce(testing::Return(0x1234));
	EXPECT_CALL(TEST_FLASH, write, (long address, unsigned char data), ())
		.Times(0);

	// Act
	// EXPECT_THROW(dd.write(0, 0x1234), exception, "WriteFailException");
	try {
		dd.write(0, 0x1234);
	}
	catch (exception& e)
	{
		// Assert
		EXPECT_EQ(string("WriteFailException"), e.what());
	}
}
