#pragma once
#include "Vehicle.h"

class Car : public Vehicle
{
private:
	unsigned int horsePower;
	unsigned int torque;

	void setHorsePower(unsigned int horsePower);
	void setTorque(unsigned int torque);
public:
	Car(const char* brand, const char* model, const char* VIN, unsigned int maxKmsAtOnce, unsigned int averageSpeed, unsigned int horsePower, unsigned int torque);

	unsigned int getHorsePower() const;
	unsigned int getTorque() const;

	unsigned int getEffectivness(unsigned int kms) const override;
	const char* getType() const override;
	Vehicle* clone() const override;
};

