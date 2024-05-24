#pragma once
#include "Computer.h"

class GamingConsole : public Computer
{
public:
	GamingConsole(double cpuPower, const char* gpuModel, size_t powerSupply, size_t ramMemory);
	void printType() const override;
	const char* getPeripheralDevices() const override;
};

