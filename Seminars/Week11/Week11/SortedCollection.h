#pragma once
#include "PureNumberCollection.h"

class SortedCollection : public PureNumberCollection
{
	int lowerBound(int x) const;
	int upperBound(int x) const;
public:
	void add(int elem) override;
	void remove(int elem) override;
	unsigned count(int elem) const override;
	bool contains(int elem) const override;
};

