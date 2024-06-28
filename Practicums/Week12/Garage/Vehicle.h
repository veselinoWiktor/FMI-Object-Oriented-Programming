#pragma once
#include <iostream>
#pragma warning (disable: 4996)

class Vehicle
{
protected:
	char* brand = nullptr;
	char* model = nullptr;
	char* VIN = nullptr;
	unsigned int axlesCount = 0;
	unsigned int size = 0;
	unsigned int maxKmsAtOnce = 0;
	unsigned int averageSpeed = 0;

	void copyFrom(const Vehicle& other);
	void moveFrom(Vehicle&& other);
	void free();

	void setBrand(const char* brand);
	void setModel(const char* model);
	void setVIN(const char* VIN);
	void setSize(unsigned int size);
	void setAxlesCount(unsigned int axlesCount);
	void setMaxKmsAtOnce(unsigned int maxKmsAtOnce);
	void setAverageSpeed(unsigned int averageSpeed);
public:
	Vehicle() = default;
	Vehicle(const char* brand, const char* model, const char* VIN, unsigned int axlesCount,
		unsigned int size, unsigned int maxKmsAtOnce, unsigned int averageSpeed);
	Vehicle(const Vehicle& other);
	Vehicle& operator=(const Vehicle& other);
	Vehicle(Vehicle&& other) noexcept;
	Vehicle& operator=(Vehicle&& other) noexcept;
	virtual ~Vehicle(); // Polymorphic hierarchy

	const char* getBrand() const;
	const char* getModel() const;
	const char* getVIN() const;
	unsigned int getAxlesCount() const;
	unsigned int getSize() const;
	unsigned int getMaxKmsAtOnce() const;
	unsigned int getAverageSpeed() const;

	virtual unsigned int getEffectivness(unsigned int kms) const = 0;
	virtual const char* getType() const = 0;
	virtual Vehicle* clone() const = 0; // will be used in heterogenous container
};

