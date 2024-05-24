#pragma once
#include "PureNumberCollection.h"

class NormalCollection : public PureNumberCollection
{
public:
	void add(int) override;
	void remove(int) override;
	unsigned count(int) const override;
	bool contains(int) const override;
};

