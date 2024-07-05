#pragma once
#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int firstRdata = (int)(m_hardware->read(address));

    for (int i = 0; i < NR_READ_ITERATION-1; i++)
    {
        if (firstRdata != (int)(m_hardware->read(address)))
            throw std::exception("ReadFailException");
    }

    return firstRdata;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    if((int)(m_hardware->read(address)) != 0xFF)
        throw std::exception("WriteFailException");

    m_hardware->write(address, (unsigned char)data);
}