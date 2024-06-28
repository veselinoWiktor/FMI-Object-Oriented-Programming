#include "Garage.h"

void Garage::copyFrom(const Garage& other)
{
	vehicles = new Vehicle * [other.capacity];
	for (size_t i = 0; i < other.count; i++)
		vehicles[i] = other.vehicles[i]->clone();
	count = other.count;
	capacity = other.capacity;
}

void Garage::moveFrom(Garage&& other)
{
	vehicles = other.vehicles;
	other.vehicles = nullptr;

	count = other.count;
	capacity = other.capacity;
}

void Garage::free()
{
	for (size_t i = 0; i < count; i++)
	{
		delete vehicles[i];
	}
	delete[] vehicles;
}

Garage::Garage()
{
	vehicles = new Vehicle * [capacity];
}

Garage::Garage(size_t capacity) : count(0), capacity(capacity)
{
	vehicles = new Vehicle * [capacity];
}

Garage::Garage(const Garage& other)
{
	copyFrom(other);
}

Garage& Garage::operator=(const Garage& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Garage::Garage(Garage&& other) noexcept
{
	moveFrom(std::move(other));
}

Garage& Garage::operator=(Garage&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Garage::~Garage()
{
	free();
}

void Garage::addVehicle(const Vehicle* vehicle)
{
	if (count == capacity)
	{
		throw std::range_error("There is no space in the garage!");
	}

	vehicles[count++] = vehicle->clone();
}

void Garage::removeVehicle(const char* brand, const char* model, const char* VIN)
{
	if (!brand || !model || !VIN)
	{
		return;
	}

	for (size_t i = 0; i < count; i++)
	{
		if (std::strcmp(vehicles[i]->getBrand(), brand) == 0
			&& std::strcmp(vehicles[i]->getModel(), model) == 0
			&& std::strcmp(vehicles[i]->getVIN(), VIN) == 0)
		{
			delete vehicles[i];

			for (size_t j = i; j < count - 1; j++)
			{
				vehicles[j] = vehicles[j + 1];
			}

			count--;
			return;
		}
	}
}

void Garage::printVehiclesCount() const
{
	unsigned int carsCount = 0;
	unsigned int cargoBusesCount = 0;
	unsigned int bikesCount = 0;

	for (size_t i = 0; i < count; i++)
	{
		const char* currType = vehicles[i]->getType();
		if (std::strcmp(currType, "Bike") == 0)
		{
			bikesCount++;
		}
		else if (std::strcmp(currType, "Car") == 0)
		{
			carsCount++;
		}
		else if (std::strcmp(currType, "CargoBus") == 0)
		{
			cargoBusesCount++;
		}
	}

	std::cout << "Cars: " << carsCount << std::endl;
	std::cout << "Cargo Buses: " << cargoBusesCount << std::endl;
	std::cout << "Bikes: " << bikesCount << std::endl;

}

size_t Garage::getFreeSpace() const
{
	return capacity - count;
}

const Vehicle* Garage::getMostEffective(unsigned int km)
{
	unsigned int res = 0;
	long long vehicleIdx = -1;

	for (size_t i = 0; i < count; i++)
	{
		int currEff = vehicles[i]->getEffectivness(km);
		if (currEff > res)
		{
			res = currEff;
			vehicleIdx = i;
		}
	}

	return vehicles[vehicleIdx];
}
