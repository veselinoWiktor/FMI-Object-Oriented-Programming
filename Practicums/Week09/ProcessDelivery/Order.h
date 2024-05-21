#pragma once
#include "String.h"

class Order
{
private:
	String restaurantName;

	size_t deliveryTime;
	mutable bool isModified = true;

	void copyFrom(const Order& other);
	void moveFrom(Order&& other);
	void free();

	String* productsList;
	size_t productsCount;
	size_t productsCapacity;
	void resize(size_t newCapacity);
public:
	Order();
	Order(const String& restaurantName, const String* productsList, size_t productsCount);
	Order(const Order& other);
	Order(Order&& other) noexcept;

	Order& operator=(const Order& other);
	Order& operator=(Order&& other) noexcept;

	~Order() noexcept;

	void setRestaurantName(const String& newRestaurantName);
	const String& getRestaurantName() const;

	void setProductsList(const String* newProductsList, size_t newProductsCount);
	const String* getProductsList() const;
	size_t getProductsCount() const;

	void addProduct(const String& product);
	void addProduct(String&& product);

	size_t calculateDeliveryTime() const;
};