#pragma once
#include <iostream>
#include "Point.h"

class ModifiableIntegersFunction
{
private:
	int16_t (*function)(int16_t) = nullptr;
	Point* changedPoints = nullptr;
	size_t capacity = 0;
	size_t count = 0;

public:
	ModifiableIntegersFunction() = default;
	ModifiableIntegersFunction(int16_t (*functionPredicate)(int16_t));

	void changePoint(int16_t _x, int16_t _y);

	void disablePoint(int16_t _x, int16_t _y);

	int16_t operator()(int16_t _x);

	ModifiableIntegersFunction& operator+=(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator-=(const ModifiableIntegersFunction& other);
	//ModifiableIntegersFunction& operator+=(const ModifiableIntegersFunction& other); // think of symbol for composition
	ModifiableIntegersFunction& operator^=(const ModifiableIntegersFunction& other);

};

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
//ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs); //think of symbol for composition
ModifiableIntegersFunction operator^(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);