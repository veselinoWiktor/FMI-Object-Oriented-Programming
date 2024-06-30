#pragma once
#include "SetOperation.h"

class IntersectionOfSets : public SetOperation
{
public:
	IntersectionOfSets(Set** sets, size_t setsSize);

	bool accepts(unsigned int n) const override;

	Set* clone() const;
};

