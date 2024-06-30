#pragma once
#include "Set.h"

template <typename Function>
class SetByCriteria : public Set
{
private:
	Function func;
public:
	SetByCriteria(const Function& func);
	SetByCriteria(Function&& func);

	bool accepts(unsigned int n) const override;
	Set* clone() const override;
};

template<typename Function>
SetByCriteria<Function>::SetByCriteria(const Function& func) : func(func)
{
}

template<typename Function>
SetByCriteria<Function>::SetByCriteria(Function&& func) : func(std::move(func))
{
}

template<typename Function>
bool SetByCriteria<Function>::accepts(unsigned int n) const
{
	return func(n);
}

template<typename Function>
Set* SetByCriteria<Function>::clone() const
{
	return new SetByCriteria<Function>(func);
}
