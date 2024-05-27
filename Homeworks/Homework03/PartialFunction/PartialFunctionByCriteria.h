#pragma once
#include "PartialFunction.h"

template<typename Function>
class PartialFunctionByCriteria : public PartialFunction
{
private:
	Function function;
public:
	PartialFunctionByCriteria(const Function& function);

	
};

