#include "GamingConsole.h"

const char* GamingConsole::PERIPHERAL_DEVICES = "Joystick, Monitor";
const char* GamingConsole::TYPE = "Gaming Console";

GamingConsole::GamingConsole(double cpuPower, const char* gpuModel, size_t powerSupply, size_t ramMemory)
	: Computer(cpuPower, gpuModel, powerSupply, ramMemory)
{
}

void GamingConsole::printType() const
{
	std::cout << TYPE;
}

const char* GamingConsole::getPeripheralDevices() const
{
	return PERIPHERAL_DEVICES;
}