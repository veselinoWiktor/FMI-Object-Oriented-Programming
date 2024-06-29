#include "BinaryOperations.h"

BinaryOperation::BinaryOperation(SetExpression* left, SetExpression* right)
	: left(left), right(right)
{
}

BinaryOperation::~BinaryOperation()
{
	delete left;
	delete right;
}

Conjunction::Conjunction(SetExpression* left, SetExpression* right)
	: BinaryOperation(left, right)
{
}

bool Conjunction::isElementIn(const Element& elemet) const
{
	return left->isElementIn(elemet) && right->isElementIn(elemet);
}

SetExpression* Conjunction::clone() const
{
	return new Conjunction(left->clone(), right->clone());
}

Disjunction::Disjunction(SetExpression* left, SetExpression* right)
	: BinaryOperation(left, right)
{
}

bool Disjunction::isElementIn(const Element& element) const
{
	return left->isElementIn(element) || right->isElementIn(element);
}

SetExpression* Disjunction::clone() const
{
	return new Disjunction(left->clone(), right->clone());
}

Difference::Difference(SetExpression* left, SetExpression* right)
	:BinaryOperation(left, right)
{
}

bool Difference::isElementIn(const Element& element) const
{
	return left->isElementIn(element) && !right->isElementIn(element); // TODO maybe this is wrong
}

SetExpression* Difference::clone() const
{
	return new Difference(left->clone(), right->clone());
}

SymmetricDifference::SymmetricDifference(SetExpression* left, SetExpression* right)
	: BinaryOperation(left, right)
{
}

bool SymmetricDifference::isElementIn(const Element& element) const
{
	return (left->isElementIn(element) || right->isElementIn(element))
		&& !(left->isElementIn(element) && right->isElementIn(element));
}

SetExpression* SymmetricDifference::clone() const
{
	return new SymmetricDifference(left->clone(), right->clone());
}
