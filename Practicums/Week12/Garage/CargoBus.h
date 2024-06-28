#pragma once
#include "Vehicle.h"

class CargoBus : public Vehicle
{
private:
	unsigned int maxPayload;

	void setMaxPayload(unsigned int maxPayload);
public:
	CargoBus(const char* brand, const char* name, const char* VIN,
		unsigned int maxKmsAtOnce, unsigned int averageSpeed, unsigned int maxPayload);

	unsigned int getMaxPayload() const;

	unsigned int getEffectivness(unsigned int kms) const override;
	const char* getType() const override;
	Vehicle* clone() const override;
};

