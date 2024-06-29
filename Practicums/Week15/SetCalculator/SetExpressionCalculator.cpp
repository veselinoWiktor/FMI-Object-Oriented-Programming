#include "SetExpressionCalculator.h"

void SetExpressionCalculator::copyFrom(const SetExpressionCalculator& other)
{
	expr = other.expr->clone();
}

void SetExpressionCalculator::moveFrom(SetExpressionCalculator&& other)
{
	expr = other.expr;
	other.expr = nullptr;
}

void SetExpressionCalculator::free()
{
	delete expr;
}

SetExpressionCalculator::SetExpressionCalculator(StringView str)
{
	expr = expressionFactory(str);
}

SetExpressionCalculator::SetExpressionCalculator(const SetExpressionCalculator& other)
{
	copyFrom(other);
}

SetExpressionCalculator& SetExpressionCalculator::operator=(const SetExpressionCalculator& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

SetExpressionCalculator::SetExpressionCalculator(SetExpressionCalculator&& other) noexcept
{
	moveFrom(std::move(other));
}

SetExpressionCalculator& SetExpressionCalculator::operator=(SetExpressionCalculator&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

SetExpressionCalculator::~SetExpressionCalculator()
{
	free();
}

bool SetExpressionCalculator::isElementIn(const SetExpression::Element& element) const
{
	return expr->isElementIn(element);
}
