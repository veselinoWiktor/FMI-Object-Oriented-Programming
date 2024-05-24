#include "Computer.h"

void Computer::copyFrom(const Computer& other)
{
	cpuPower = other.cpuPower;
	gpuModel = new char[strlen(other.gpuModel) + 1];
	strcpy(gpuModel, other.gpuModel);
	powerSupply = other.powerSupply;
	ramMemory = other.ramMemory;
}

void Computer::moveFrom(Computer&& other)
{
	cpuPower = other.cpuPower;
	powerSupply = other.powerSupply;
	ramMemory = other.ramMemory;
	gpuModel = other.gpuModel;
	other.gpuModel = nullptr;
}

void Computer::free()
{
	delete[] gpuModel;
}

Computer::Computer() : Computer(0, "empty", 0, 0)
{
}

Computer::Computer(double cpuPower, const char* gpuModel, size_t powerSupply, size_t ramMemory)
{
	setCPUPower(cpuPower);
	setGPUModel(gpuModel);
	setPowerSupply(powerSupply);
	setRAMMemory(ramMemory);
}

Computer::Computer(const Computer& other)
{
	copyFrom(other);
}

Computer::Computer(Computer&& other) noexcept
{
	moveFrom(std::move(other));
}

Computer& Computer::operator=(const Computer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Computer& Computer::operator=(Computer&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Computer::~Computer()
{
	free();
}

void Computer::setCPUPower(double newCPUPower)
{
	cpuPower = newCPUPower;
}

void Computer::setGPUModel(const char* newGPUModel)
{
	gpuModel = new char[strlen(newGPUModel) + 1];
	strcpy(gpuModel, newGPUModel);
}

void Computer::setPowerSupply(size_t newPowerSupply)
{
	powerSupply = newPowerSupply;
}

void Computer::setRAMMemory(size_t newRAMMemory)
{
	ramMemory = newRAMMemory;
}
