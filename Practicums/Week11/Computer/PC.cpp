#include "PC.h"

const char* PC::PERIPHERAL_DEVICES = "Mouse, Keyboard, Microphone, Headphones";
const char* PC::TYPE = "PC";

PC::PC(double cpuPower, const char* gpuModel, size_t powerSupply, size_t ramMemory)
	: Computer(cpuPower, gpuModel, powerSupply, ramMemory)
{
}

void PC::printType() const
{
	std::cout << TYPE;
}

const char* PC::getPeripheralDevices() const
{
	return PERIPHERAL_DEVICES;
}
