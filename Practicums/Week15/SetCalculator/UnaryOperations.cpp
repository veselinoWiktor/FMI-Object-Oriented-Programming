#include "UnaryOperations.h"

UnaryOperation::UnaryOperation(SetExpression* expr) : expr(expr)
{
}

UnaryOperation::~UnaryOperation()
{
	delete expr;
}

Negation::Negation(SetExpression* expr) : UnaryOperation(expr)
{
}

bool Negation::isElementIn(const Element& element) const
{
	return !expr->isElementIn(element);
}

SetExpression* Negation::clone() const
{
	return new Negation(expr->clone());
}
