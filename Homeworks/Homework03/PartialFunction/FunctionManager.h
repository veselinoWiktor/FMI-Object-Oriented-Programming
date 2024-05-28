#pragma once
#include "PartialFunction.h"
#include "String.h"
#include <fstream>
#include <iostream>

class FunctionManager
{
private:
	PartialFunction* partialFunction;

	PartialFunction* loadFunction(const String& functionFilePath);
public:
	void run();
};

