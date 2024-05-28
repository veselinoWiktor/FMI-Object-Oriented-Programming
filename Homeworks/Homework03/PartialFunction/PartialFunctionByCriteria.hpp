#pragma once
#include "PartialFunction.h"
#include "Pair.hpp"

template<typename Function>
class PartialFunctionByCriteria : public PartialFunction
{
private:
	Function function;	
public:
	PartialFunctionByCriteria(const Function& function);

	int getFunctionValue(int x) const override;
	bool isFunctionDefinedIn(int x) const override;
	PartialFunction* clone() const override;

	int operator()(int x) const;
};

template<typename Function>
PartialFunctionByCriteria<Function>::PartialFunctionByCriteria(const Function& function)
	: function(function)
{
}

template<typename Function>
int PartialFunctionByCriteria<Function>::getFunctionValue(int x) const
{
	return this->operator()(x);
}

template<typename Function>
bool PartialFunctionByCriteria<Function>::isFunctionDefinedIn(int x) const
{
	return function(x).getFirst();
}

template<typename Function>
PartialFunction* PartialFunctionByCriteria<Function>::clone() const
{
	return new PartialFunctionByCriteria(*this);
}

template<typename Function>
int PartialFunctionByCriteria<Function>::operator()(int x) const
{
	return function(x).getSecond();
}
