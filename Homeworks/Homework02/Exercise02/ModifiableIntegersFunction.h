#pragma once
#include <iostream>

namespace Constants
{
	constexpr const int FUNCTION_VALUES_COUNT = 65536;
	constexpr const int FUNCTION_ZERO_INDEX = 32768;
}

class ModifiableIntegersFunction
{
private:
	int16_t (*function)(int16_t) = nullptr;
	int16_t functionValues[Constants::FUNCTION_VALUES_COUNT];

	int16_t* disabledPoints = nullptr;
	size_t disabledCapacity = 0;
	size_t disabledCount = 0;

	void copyFrom(const ModifiableIntegersFunction& other);
	void free();

	void resize();

	void initFunctionData();
	void setFunction(int16_t (*functionPredicate)(int16_t));

	bool isDisabled(int16_t _x) const;

public:
	ModifiableIntegersFunction() = default;
	ModifiableIntegersFunction(int16_t (*functionPredicate)(int16_t));
	ModifiableIntegersFunction(const ModifiableIntegersFunction& other);
	ModifiableIntegersFunction& operator=(const ModifiableIntegersFunction& other);
	~ModifiableIntegersFunction();

	void changePoint(int16_t _x, int16_t _y);

	void disablePoint(int16_t _x);

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

