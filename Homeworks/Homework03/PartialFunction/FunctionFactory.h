#pragma once
#include <iostream>
#include "FunctionManager.h"


class FunctionFactory
{
	static constexpr int32_t BUFFER_SIZE = 1024;
	static char* readStringFromBinary(std::ifstream& ifs);
public:
	static PartialFunction* create(const String& functionFilePath);
};

