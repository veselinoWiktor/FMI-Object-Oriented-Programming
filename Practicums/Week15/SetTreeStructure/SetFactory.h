#pragma once
#include "Set.h"
#include "Function.h"
#include "UnionOfSets.h"
#include "IntersectionOfSets.h"
#include "SetByCriteria.hpp"
#include <fstream>

class SetFactory
{
	static Function* createFunction(std::ifstream& ifs, int N);
public:
	static Set* createSet(const char* filePath);
};

