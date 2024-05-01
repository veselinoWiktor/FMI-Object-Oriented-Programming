#pragma once
#include "String.h"

namespace RestaurantConstnats
{
	constexpr const int MAX_NAME_LENGTH = 25;
}

class Retaurant
{
	char name[RestaurantConstnats::MAX_NAME_LENGTH + 1];
	String* products;
	unsigned productsCount;

public:
};