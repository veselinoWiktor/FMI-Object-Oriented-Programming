#pragma once

class PartialFunction
{
public:
	virtual int getFunctionValue(int x) const = 0;
	virtual bool isFunctionDefinedIn(int x) const = 0;
	virtual PartialFunction* clone() const = 0;
};

