#pragma once
#include "PartialFunction.h"
#include "Container.hpp"

class MinimalPartialFunction : public PartialFunction
{
	Container<PartialFunction> functions;

public:
	MinimalPartialFunction(const Container<PartialFunction>& functions);
	int getFunctionValue(int x) const override;
	bool isFunctionDefinedIn(int x) const override;
	PartialFunction* clone() const override;
	int operator()(int x) const;
};

