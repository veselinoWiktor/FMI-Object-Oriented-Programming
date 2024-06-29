#pragma once
#include "SetExpression.h"

class Singleton : public SetExpression
{
protected:
	char ch;
public:
	Singleton(char ch);
	bool isElementIn(const Element& element) const override;
	SetExpression* clone() const override;
};

