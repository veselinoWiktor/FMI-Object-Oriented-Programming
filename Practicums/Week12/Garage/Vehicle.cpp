#include "Vehicle.h"

void Vehicle::copyFrom(const Vehicle& other)
{
	brand = new char[std::strlen(other.brand) + 1];
	std::strcpy(brand, other.brand);

	model = new char[std::strlen(other.model) + 1];
	std::strcpy(model, other.model);

	VIN = new char[std::strlen(other.VIN) + 1];
	std::strcpy(VIN, other.VIN);

	axlesCount = other.axlesCount;
	size = other.size;
	maxKmsAtOnce = other.maxKmsAtOnce;
	averageSpeed = other.averageSpeed;
}

void Vehicle::moveFrom(Vehicle&& other)
{
	brand = other.brand;
	other.brand = nullptr;

	model = other.model;
	other.model = nullptr;

	VIN = other.VIN;
	other.VIN = nullptr;

	axlesCount = other.axlesCount;
	size = other.size;
	maxKmsAtOnce = other.maxKmsAtOnce;
	averageSpeed = other.averageSpeed;
}

void Vehicle::free()
{
	delete[] brand;
	delete[] model;
	delete[] VIN;
}

void Vehicle::setBrand(const char* brand)
{
	if (!brand || this->brand == brand)
	{
		return;
	}

	delete[] this->brand;
	this->brand = new char[std::strlen(brand) + 1];
	std::strcpy(this->brand, brand);
}

void Vehicle::setModel(const char* model)
{
	if (!model || this->model == model)
	{
		return;
	}

	delete[] this->model;
	this->model = new char[std::strlen(model) + 1];
	std::strcpy(this->model, model);
}

void Vehicle::setVIN(const char* VIN)
{
	if (!VIN || this->VIN == VIN)
	{
		return;
	}

	delete[] this->VIN;
	this->VIN = new char[std::strlen(VIN) + 1];
	std::strcpy(this->VIN, VIN);
}

void Vehicle::setAxlesCount(unsigned int axlesCount)
{
	this->axlesCount = axlesCount;
}

void Vehicle::setSize(unsigned int size)
{
	this->size = size;
}

void Vehicle::setMaxKmsAtOnce(unsigned int maxKmsAtOnce)
{
	this->maxKmsAtOnce = maxKmsAtOnce;
}

void Vehicle::setAverageSpeed(unsigned int averageSpeed)
{
	this->averageSpeed = averageSpeed;
}

Vehicle::Vehicle(const char* brand, const char* model, const char* VIN, unsigned int axlesCount,
	unsigned int size, unsigned int maxKmsAtOnce, unsigned int averageSpeed)
{
	setBrand(brand);
	setModel(model);
	setVIN(VIN);
	setAxlesCount(axlesCount);
	setSize(size);
	setMaxKmsAtOnce(maxKmsAtOnce);
	setAverageSpeed(averageSpeed);
}

Vehicle::Vehicle(const Vehicle& other)
{
	copyFrom(other);
}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Vehicle::Vehicle(Vehicle&& other) noexcept
{
	moveFrom(std::move(other));
}

Vehicle& Vehicle::operator=(Vehicle&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Vehicle::~Vehicle()
{
	free();
}

const char* Vehicle::getBrand() const
{
	return brand;
}

const char* Vehicle::getModel() const
{
	return model;
}

const char* Vehicle::getVIN() const
{
	return VIN;
}

unsigned int Vehicle::getAxlesCount() const
{
	return axlesCount;
}

unsigned int Vehicle::getSize() const
{
	return size;
}

unsigned int Vehicle::getMaxKmsAtOnce() const
{
	return maxKmsAtOnce;
}

unsigned int Vehicle::getAverageSpeed() const
{
	return averageSpeed;
}
