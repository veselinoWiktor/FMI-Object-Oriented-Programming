#pragma once
#include "Set.h"
#include "SetFactory.h"
#include <iostream>

class SetCalculator
{
private:
	Set* set;

	void copyFrom(const SetCalculator& other);
	void moveFrom(SetCalculator&& other);
	void free();
public:
	SetCalculator(const char* filePath);
	SetCalculator(const SetCalculator& other);
	SetCalculator& operator=(const SetCalculator& other);
	SetCalculator(SetCalculator&& other) noexcept;
	SetCalculator& operator=(SetCalculator&& other);
	~SetCalculator();

	bool accepts(unsigned int x);
};

