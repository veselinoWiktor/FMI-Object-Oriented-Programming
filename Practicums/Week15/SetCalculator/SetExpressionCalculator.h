#pragma once
#include "StringView.h"
#include "Singleton.h"
#include "UnaryOperations.h"
#include "BinaryOperations.h"
#include "SetExpression.h"

SetExpression* expressionFactory(StringView str)
{
	str = str.substr(1, str.length() - 2);

	if (str.length() == 1)
	{
		return new Singleton(str[0]);
	}

	int count = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			count++;
		}
		else if (str[i] == ')')
		{
			count--;
		}
		else if (count == 0)
		{
			switch (str[i])
			{
			case '!': return new Negation(expressionFactory(str.substr(i + 1, str.length() - i - 1)));
			case 'v': return new Disjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
			case '^': return new Conjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
			case '\\': return new Difference(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));
			case 'x': return new SymmetricDifference(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1)));

			default:
				break;
			}
		}
	}
}

class SetExpressionCalculator
{
private:
	SetExpression* expr;

	void copyFrom(const SetExpressionCalculator& other);
	void moveFrom(SetExpressionCalculator&& other);
	void free();
public:
	SetExpressionCalculator(StringView str);
	SetExpressionCalculator(const SetExpressionCalculator& other);
	SetExpressionCalculator& operator=(const SetExpressionCalculator& other);
	SetExpressionCalculator(SetExpressionCalculator&& other) noexcept;
	SetExpressionCalculator& operator=(SetExpressionCalculator&& other) noexcept;
	~SetExpressionCalculator();

	bool isElementIn(const SetExpression::Element& element) const;
};

