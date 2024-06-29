#include <iostream>
#include <assert.h>

#include "StringView.h"

class BooleanInterpretation
{
private:
	bool values[26]{ false };

public:
	void set(char ch, bool value)
	{
		assert(ch >= 'a' && ch <= 'z');
		values[ch - 'a'] = value;
	}

	bool operator()(char ch) const
	{
		assert(ch >= 'a' && ch <= 'z');
		return values[ch - 'a'];
	}

	size_t getTrueCount() const
	{
		size_t count = 0;

		for (size_t i = 0; i < 26; i++)
		{
			if (values[i])
			{
				count++;
			}
		}

		return count;
	}

	void excludeValuesByMask(unsigned mask)
	{
		for (int i = 25; i >= 0; i--)
		{
			if (values[i])
			{
				if (mask % 2 == 0) // last bit is 0;
					values[i] = false;
				mask /= 2; // remove the last bit
			}
		}
	}
};

struct BooleanExpression
{
	BooleanExpression() = default;
	BooleanExpression(const BooleanExpression& other) = delete;
	BooleanExpression& operator=(const BooleanExpression& other) = delete;

	virtual bool eval(const BooleanInterpretation& interpret) const = 0;
	virtual BooleanExpression* clone() const = 0;
	virtual ~BooleanExpression() = default;

	virtual void populateVariables(BooleanInterpretation& interpret) const = 0;
};

struct Var : public BooleanExpression
{
private:
	char ch;
public:
	Var(char ch) : ch(ch) {}

	bool eval(const BooleanInterpretation& interpret) const override
	{
		return interpret(ch);
	}

	BooleanExpression* clone() const override
	{
		return new Var(ch);
	}

	void populateVariables(BooleanInterpretation& interpret) const override
	{
		interpret.set(ch, true);
	}
};

struct UnaryOperation : public BooleanExpression
{
protected:
	BooleanExpression* expr;
public:
	UnaryOperation(BooleanExpression* expr) : expr(expr) {}

	void populateVariables(BooleanInterpretation& interpret) const override
	{
		expr->populateVariables(interpret);
	}
};

struct Negation : public UnaryOperation
{

	Negation(BooleanExpression* expr) : UnaryOperation(expr) {}
	~Negation()
	{
		delete expr;
	}

	bool BooleanExpression::eval(const BooleanInterpretation& interpret) const override
	{
		return !expr->eval(interpret);
	}

	BooleanExpression* clone() const override
	{
		return new Negation(expr->clone());
	}
};

struct BinaryOperation : public BooleanExpression
{
protected:
	BooleanExpression* left;
	BooleanExpression* right;

public:
	BinaryOperation(BooleanExpression* left, BooleanExpression* right) : left(left), right(right) {}

	~BinaryOperation()
	{
		delete left;
		delete right;
	}

	void populateVariables(BooleanInterpretation& interpret) const override
	{
		left->populateVariables(interpret);
		right->populateVariables(interpret);
	}
};

struct Conjunction : public BinaryOperation
{
	Conjunction(BooleanExpression* left, BooleanExpression* right) : BinaryOperation(left, right) {}

	BooleanExpression* clone() const override
	{
		return new Conjunction(left->clone(), right->clone());
	}

	bool eval(const BooleanInterpretation& interpret) const override
	{
		return left->eval(interpret) && right->eval(interpret);
	}
};

struct Disjunction : public BinaryOperation
{
	Disjunction(BooleanExpression* left, BooleanExpression* right) : BinaryOperation(left, right) {}

	BooleanExpression* clone() const override
	{
		return new Disjunction(left->clone(), right->clone());
	}

	bool eval(const BooleanInterpretation& interpret) const override
	{
		return left->eval(interpret) || right->eval(interpret);
	}
};

struct Implies : public BinaryOperation
{
	Implies(BooleanExpression* left, BooleanExpression* right) : BinaryOperation(left, right) {}

	BooleanExpression* clone() const override
	{
		return new Implies(left->clone(), right->clone());
	}

	bool eval(const BooleanInterpretation& interpret) const override
	{
		return !left->eval(interpret) || right->eval(interpret);
	}
};

static BooleanExpression* expressionFactory(StringView str)
{
	str = str.substr(1, str.length() - 2); // remove the first and last brackets

	if (str.length() == 1)
	{
		return new Var(str[0]);
	}

	unsigned count = 0;
	for (int i = 0; i < str.length(); i++)
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
			case '!': return new Negation(expressionFactory(str.substr(i + 1, str.length() - i - 1))); break;
			case '&': return new Conjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1))); break;
			case '|': return new Disjunction(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1))); break;
			case '>': return new Implies(expressionFactory(str.substr(0, i)), expressionFactory(str.substr(i + 1, str.length() - i - 1))); break;
			}	
		}
	}
}

class BooleanExpressionHandler
{
private:
	BooleanInterpretation variables; // the variables that are in the expression are set to 1 here
	BooleanExpression* expr;

	void copyFrom(const BooleanExpressionHandler& other)
	{
		expr = other.expr->clone();
	}
	void moveFrom(BooleanExpressionHandler&& other) noexcept
	{
		expr = other.expr;
		other.expr = nullptr;
	}
	void free()
	{
		delete expr;
	}

	bool checkAllTruthAssignments(bool value) const
	{
		size_t varsCount = variables.getTrueCount();
		size_t powerOfTwo = 1 << varsCount;
		for (long long i = 0; i < powerOfTwo; i++)
		{
			BooleanInterpretation current = variables; // T T T
			current.excludeValuesByMask(i);
			if (expr->eval(current) != value)
				return false;
		}
		return true;
	}
public:
	BooleanExpressionHandler(const String& str)
	{
		expr = expressionFactory(str);
		expr->populateVariables(variables);
	}
	BooleanExpressionHandler(const BooleanExpressionHandler& other)
	{
		copyFrom(other);
	}
	BooleanExpressionHandler& operator=(const BooleanExpressionHandler& other)
	{
		if (this != &other)
		{
			free();
			copyFrom(other);
		}

		return *this;
	}
	BooleanExpressionHandler(BooleanExpressionHandler&& other) noexcept
	{
		moveFrom(std::move(other));
	}
	BooleanExpressionHandler& operator=(BooleanExpressionHandler&& other) noexcept
	{
		if (this != &other)
		{
			free();
			moveFrom(std::move(other));
		}

		return *this;
	}
	~BooleanExpressionHandler()
	{
		free();
	}

	bool evaluate(const BooleanInterpretation& bi) const
	{
		return expr->eval(bi);
	}
	bool isTautology() const
	{
		return checkAllTruthAssignments(true);
	}
	bool isContradiction() const
	{
		return checkAllTruthAssignments(false);
	}
};