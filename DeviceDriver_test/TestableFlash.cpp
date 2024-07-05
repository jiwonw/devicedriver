#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/FlashMemoryDevice.h"

class TestableFlash :public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};