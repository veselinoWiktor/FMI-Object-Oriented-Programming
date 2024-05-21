#pragma once
#include "Restaurant.h"

class FoodPanda
{
private:
	Restaurant* restaurants;
	size_t restaurantsCount;
	size_t restaurantsCapacity;

	void copyFrom(const FoodPanda& other);
	void moveFrom(FoodPanda&& other);
	void free();

	void resize(size_t newCapacity);

	Restaurant& findRestaurantByName(const String& restaurantName);
public:
	FoodPanda();
	FoodPanda(const Restaurant* restaurants, size_t restaurantsCount);
	FoodPanda(const FoodPanda& other);
	FoodPanda(FoodPanda&& other);
	
	FoodPanda& operator=(const FoodPanda& other);
	FoodPanda& operator=(FoodPanda&& other);

	~FoodPanda();

	void setRestaurants(const Restaurant* newRestaurants, size_t newRestaurantsCount);
	const Restaurant* getRestaurants() const;
	size_t getRestaurantsCount() const;

	void addRestaurant(const Restaurant& restaurant);
	void addRestaurant(Restaurant&& restaurant);

	void addProductToRestaurant(const String& restaurantName, const String& product);
	void addProductToRestaurant(const String& restaurantName, String&& product);

	void giveOrderToRestaurant(const String& restaurantName, const Order& order);
	void giveOrderToRestaurant(const String& restaurantName, Order&& order);

};

