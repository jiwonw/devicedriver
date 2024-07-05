#pragma once
#include <stdexcept>
#include "FlashMemoryDevice.h"

using namespace std;

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    virtual int read(long address);
    virtual void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
private:
    const int NR_READ_ITERATION = 5;
};