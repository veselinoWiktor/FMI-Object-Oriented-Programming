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
	ModifiableIntegersFunction& operator^(int power); // f^k - even -1, because f-1 would return inverse function

	bool isInjective() const;
	bool isSurjective() const;
	bool isBijective() const;

	void serialize(const char* filename) const;
	void desrialize(const char* filename);

	void draw() const;
};

ModifiableIntegersFunction operator+(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
ModifiableIntegersFunction operator-(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
ModifiableIntegersFunction operator*(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);//composition

//are two functions parallel
bool operator||(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs); 

bool operator==(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator!=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator<(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator<=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator>(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);
bool operator>=(const ModifiableIntegersFunction& lhs, const ModifiableIntegersFunction& rhs);

