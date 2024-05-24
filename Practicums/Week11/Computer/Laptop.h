#pragma once
#include "Computer.h"

class Laptop : public Computer
{
public:
	Laptop(double cpuPower, const char* gpuModel, size_t powerSupply, size_t ramMemory);
	void printType() const override;
	const char* getPeripheralDevices() const override;
};

