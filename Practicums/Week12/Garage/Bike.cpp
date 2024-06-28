#include "Bike.h"

void Bike::setEngineDispalcment(float engineDisplacement)
{
}

Bike::Bike(const char* brand, const char* model, const char* VIN, unsigned int maxKmsAtOnce, unsigned averageSpeed, float engineDisplacment)
	:	Vehicle(brand, model, VIN, 2, 2, maxKmsAtOnce, averageSpeed)
{
	this->engineDisplacment = engineDisplacment;
}

float Bike::getEngineDisplacment() const
{
	return engineDisplacment;
}

unsigned int Bike::getEffectivness(unsigned int kms) const
{
	//formula to calculata effectivness
	return kms * maxKmsAtOnce;
}

const char* Bike::getType() const
{
	return "Bike";
}

Vehicle* Bike::clone() const
{
	return new Bike(*this);
}
