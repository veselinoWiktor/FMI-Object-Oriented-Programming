#pragma once
#include "PartialFunction.h"
#include "Container.hpp"

class MaximalPartialFunction : public PartialFunction
{
	Container<PartialFunction> functions;

public:
	MaximalPartialFunction(const Container<PartialFunction>& functions);
	int getFunctionValue(int x) const override;
	bool isFunctionDefinedIn(int x) const override;
	PartialFunction* clone() const override;
	int operator()(int x) const;
};

