#pragma once
#include "SetOperation.h"

class UnionOfSets : public SetOperation
{
public:
	UnionOfSets(Set** sets, size_t setsSize);

	bool accepts(unsigned int n) const override;

	Set* clone() const override;
};