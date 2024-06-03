#pragma once

class PartialFunction
{
public:
	PartialFunction() = default;
	PartialFunction(const PartialFunction& other) = default;
	PartialFunction(PartialFunction&& other) noexcept = default;
	PartialFunction& operator=(const PartialFunction& other) = default;
	PartialFunction& operator=(PartialFunction&& other) noexcept = default;
	~PartialFunction() = default;
	virtual int getFunctionValue(int x) const = 0;
	virtual bool isFunctionDefinedIn(int x) const = 0;
	virtual PartialFunction* clone() const = 0;
};

