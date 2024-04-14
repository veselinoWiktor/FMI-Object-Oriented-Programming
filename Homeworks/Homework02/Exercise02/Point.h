#pragma once
#include <iostream>


struct Point
{
	int16_t x = 0;
	int16_t y = 0;
	bool isUndefined = true;

	Point() = default;
	explicit Point(int16_t _x, int16_t _y) : x(_x), y(_y), isUndefined(false) {};
};