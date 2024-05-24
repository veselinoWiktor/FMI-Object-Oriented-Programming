#pragma once
#include <iostream>

class Computer
{
private:
	double cpuPower;
	char* gpuModel;
	size_t powerSupply;
	size_t ramMemory;

	void copyFrom(const Computer& other);
	void moveFrom(Computer&& other);
	void free();
protected:
	static const char* PERIPHERAL_DEVICES;
	static const char* TYPE;
public:
	Computer();
	Computer(double cpuPower, const char* gpuModel, size_t powerSupply, size_t ramMemory);
	Computer(const Computer& other);
	Computer(Computer&& other) noexcept;
	Computer& operator=(const Computer& other);
	Computer& operator=(Computer&& other) noexcept;
	virtual ~Computer();

	void setCPUPower(double newCPUPower);
	void setGPUModel(const char* newGPUModel);
	void setPowerSupply(size_t newPowerSupply);
	void setRAMMemory(size_t newRAMMemory);

	virtual void printType() const = 0;
	virtual const char* getPeripheralDevices() const = 0;
};

