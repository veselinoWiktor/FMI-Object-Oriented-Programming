#pragma once
#include "IntVector.h"
#include <iostream>

class VectorCommand
{
protected:
	IntVector& v;
public:
	VectorCommand(IntVector& v);
	virtual ~VectorCommand() = default;

	virtual void execute() = 0;
	virtual void undo() = 0;
};

