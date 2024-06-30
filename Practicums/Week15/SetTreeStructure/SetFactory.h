#pragma once
#include "Set.h"
#include "Function.h"
#include "UnionOfSets.h"
#include "IntersectionOfSets.h"
#include "SetByCriteria.hpp"
#include <fstream>

class SetFactory
{
	static Set* createSetByCriteria(std::ifstream& ifs, int N);
	static Set* createUnionOfSets(std::ifstream& ifs, int N);
	static Set* createIntersectionOfSets(std::ifstream& ifs, int N);
public:
	static Set* createSet(const char* filePath);
};

