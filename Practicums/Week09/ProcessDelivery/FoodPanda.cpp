#include "FoodPanda.h"
#include "Utils.h"

void FoodPanda::copyFrom(const FoodPanda& other)
{
	restaurantsCount = other.restaurantsCount;
	restaurantsCapacity = other.restaurantsCapacity;
	restaurants = new Restaurant[restaurantsCapacity];
	for (size_t i = 0; i < restaurantsCount; i++)
	{
		restaurants[i] = other.restaurants[i];
	}
}

void FoodPanda::moveFrom(FoodPanda&& other)
{
	restaurantsCount = other.restaurantsCount;
	restaurantsCapacity = other.restaurantsCapacity;
	other.restaurantsCount = other.restaurantsCapacity = 0;

	restaurants = other.restaurants;
	other.restaurants = nullptr;
}

void FoodPanda::free()
{
	delete[] restaurants;
}

void FoodPanda::resize(size_t newCapacity)
{
	restaurantsCapacity = newCapacity;
	Restaurant* temp = new Restaurant[restaurantsCapacity];
	for (size_t i = 0; i < restaurantsCount; i++)
	{
		temp[i] = restaurants[i];
	}
	delete[] restaurants;
	restaurants = temp;
}

Restaurant& FoodPanda::findRestaurantByName(const String& restaurantName)
{
	for (size_t i = 0; i < restaurantsCount; i++)
	{
		if (restaurants[i].getName() == restaurantName)
		{
			return restaurants[i];
		}
	}
	
	throw std::invalid_argument("FoodPanda::findRestaurantByName(); Invalid restaurant name!");
}

FoodPanda::FoodPanda() : restaurantsCount(0), restaurantsCapacity(8)
{
	restaurants = new Restaurant[restaurantsCapacity];
}

FoodPanda::FoodPanda(const Restaurant* restaurants, size_t restaurantsCount)
{
	setRestaurants(restaurants, restaurantsCount);
}

FoodPanda::FoodPanda(const FoodPanda& other)
{
	copyFrom(other);
}

FoodPanda::FoodPanda(FoodPanda&& other)
{
	moveFrom(std::move(other));
}

FoodPanda& FoodPanda::operator=(const FoodPanda& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

FoodPanda& FoodPanda::operator=(FoodPanda&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

FoodPanda::~FoodPanda()
{
	free();
}

void FoodPanda::setRestaurants(const Restaurant* newRestaurants, size_t newRestaurantsCount)
{
	restaurantsCount = newRestaurantsCount;
	restaurantsCapacity = std::max(Utils::nextPowerOfTwo(restaurantsCount), 8ull);
	restaurants = new Restaurant[restaurantsCapacity];
	for (size_t i = 0; i < restaurantsCount; i++)
	{
		restaurants[i] = newRestaurants[i];
	}
}

const Restaurant* FoodPanda::getRestaurants() const
{
	return restaurants;
}

size_t FoodPanda::getRestaurantsCount() const
{
	return restaurantsCount;
}

void FoodPanda::addRestaurant(const Restaurant& restaurant)
{
	if (restaurantsCount == restaurantsCapacity)
	{
		resize(restaurantsCapacity * 2);
	}

	restaurants[restaurantsCount++] = restaurant;
}

void FoodPanda::addRestaurant(Restaurant&& restaurant)
{
	if (restaurantsCount == restaurantsCapacity)
	{
		resize(restaurantsCapacity * 2);
	}

	restaurants[restaurantsCount++] = std::move(restaurant);
}

void FoodPanda::addProductToRestaurant(const String& restaurantName, const String& product)
{
	findRestaurantByName(restaurantName).addProduct(product);
}

void FoodPanda::addProductToRestaurant(const String& restaurantName, String&& product)
{
	findRestaurantByName(restaurantName).addProduct(std::move(product));
}

void FoodPanda::giveOrderToRestaurant(const String& restaurantName, const Order& order)
{
	findRestaurantByName(restaurantName).recieveOrder(order);
}

void FoodPanda::giveOrderToRestaurant(const String& restaurantName, Order&& order)
{
	findRestaurantByName(restaurantName).recieveOrder(std::move(order));
}
