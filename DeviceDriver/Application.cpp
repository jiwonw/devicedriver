#include <iostream>
#include "DeviceDriver.h"

class Application
{
public:
	Application(DeviceDriver *dd)
		: dd{dd}
	{
	}
	void ReadAndPrint(long startAddr, long endAddr)
	{
		for (long addr = startAddr; addr <= endAddr; addr++)
		{
			cout << dd->read(addr) << endl;
		}

	}
	void WriteAll(int value) {
		long startAddr = 0x0;
		long endAddr = 0x4;
		for (long addr = startAddr; addr <= endAddr; addr++)
		{
			dd->write(addr, value);
		}
	}
private:
	DeviceDriver *dd;
};