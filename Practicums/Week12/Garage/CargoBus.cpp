#include "CargoBus.h"

void CargoBus::setMaxPayload(unsigned int maxPayload)
{
	this->maxPayload = maxPayload;
}

CargoBus::CargoBus(const char* brand, const char* name, const char* VIN,
	unsigned int maxKmsAtOnce, unsigned int averageSpeed, unsigned int maxPayload)
	: Vehicle(brand, name, VIN, 3, 6, maxKmsAtOnce, averageSpeed)
{
	setMaxPayload(maxPayload);
}

unsigned int CargoBus::getMaxPayload() const
{
	return maxPayload;
}

unsigned int CargoBus::getEffectivness(unsigned int kms) const
{
	//formula to calculate effectivness
	return maxKmsAtOnce * kms;
}

const char* CargoBus::getType() const
{
	return "CargoBus";
}

Vehicle* CargoBus::clone() const
{
	return new CargoBus(*this);
}
