#pragma once
#include "Vehicle.h"

class Garage //heterogenous collection
{
private:
	Vehicle** vehicles = nullptr;
	size_t count = 0;
	size_t capacity = 4;

	void copyFrom(const Garage& other);
	void moveFrom(Garage&& other);
	void free();

public:
	Garage();
	Garage(size_t capacity);
	Garage(const Garage& other);
	Garage& operator=(const Garage& other);
	Garage(Garage&& other) noexcept;
	Garage& operator=(Garage&& other) noexcept;
	~Garage();

	void addVehicle(const Vehicle* vehicle);
	void removeVehicle(const char* brand, const char* model, const char* VIN);
	void printVehiclesCount() const;
	size_t getFreeSpace() const;
	const Vehicle* getMostEffective(unsigned int km);
};

