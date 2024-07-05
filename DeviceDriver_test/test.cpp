#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"
#include "TestableFlash.cpp"



class DeviceDriverFixture : public testing::Test {
public:
	DeviceDriver DD;
};

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}