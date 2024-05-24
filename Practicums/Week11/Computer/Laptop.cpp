#include "Laptop.h"

const char* Laptop::PERIPHERAL_DEVICES = "Mouse pad, Keyboard, Monitor";
const char* Laptop::TYPE = "Laptop";

Laptop::Laptop(double cpuPower, const char* gpuModel, size_t powerSupply, size_t ramMemory)
	: Computer(cpuPower, gpuModel, powerSupply, ramMemory)
{
}

void Laptop::printType() const
{
	std::cout << TYPE;
}

const char* Laptop::getPeripheralDevices() const
{
	return PERIPHERAL_DEVICES;
}
