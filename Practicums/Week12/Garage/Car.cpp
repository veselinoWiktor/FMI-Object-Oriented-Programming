#include "Car.h"

void Car::setHorsePower(unsigned int horsePower)
{
	this->horsePower = horsePower;
}

void Car::setTorque(unsigned int torque)
{
	this->torque = torque;
}

Car::Car(const char* brand, const char* model, const char* VIN, 
	unsigned int maxKmsAtOnce, unsigned int averageSpeed, unsigned int horsePower, unsigned int torque)
	:Vehicle(brand, model, VIN, 2, 4, maxKmsAtOnce, averageSpeed)
{
	setHorsePower(horsePower);
	setTorque(torque);
}

unsigned int Car::getHorsePower() const
{
	return horsePower;
}

unsigned int Car::getTorque() const
{
	return torque;
}

unsigned int Car::getEffectivness(unsigned int kms) const
{
	//formula to calculate effectivness
	return maxKmsAtOnce * kms;
}

const char* Car::getType() const
{
	return "Car";
}

Vehicle* Car::clone() const
{
	return new Car(*this);
}
