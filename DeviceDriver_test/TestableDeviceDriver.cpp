#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.h"

class TestableDeviceDriver :public DeviceDriver
{
public:
	TestableDeviceDriver()
		: DeviceDriver{ nullptr }
	{};
	MOCK_METHOD(int, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, int data), (override));
};