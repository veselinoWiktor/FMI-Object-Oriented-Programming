#pragma once
#include "Vehicle.h"

class Bike : public Vehicle
{
private:
	float engineDisplacment = 0;
	
	void setEngineDispalcment(float engineDisplacement);
public:
	Bike(const char* brand, const char* model, const char* VIN, unsigned int maxKmsAtOnce, unsigned averageSpeed, float engineDisplacment);
	float getEngineDisplacment() const;

	unsigned int getEffectivness(unsigned int kms) const override;
	const char* getType() const override;
	Vehicle* clone() const override;
};

