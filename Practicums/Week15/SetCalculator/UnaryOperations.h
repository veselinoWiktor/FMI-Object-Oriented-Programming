#pragma once
#include "SetExpression.h"

class UnaryOperation : public SetExpression
{
protected:
	SetExpression* expr;
public:
	UnaryOperation(SetExpression* expr);
	~UnaryOperation();
};

class Negation : public UnaryOperation
{
public:
	Negation(SetExpression* expr);
	bool isElementIn(const Element& element) const override;
	SetExpression* clone() const override;
};