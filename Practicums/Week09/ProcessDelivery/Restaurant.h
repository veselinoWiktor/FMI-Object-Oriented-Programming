#pragma once
#include "String.h"
#include "Order.h"
#include "../StringVector/StringVector.h"

namespace
{
	constexpr const int MAX_NAME_LENGTH = 25;
}

class Restaurant
{
	char name[MAX_NAME_LENGTH + 1];
	StringVector products;

	Order* orders;
	size_t ordersCount;
	size_t ordersCapacity;

	void copyFrom(const Restaurant& other);
	void moveFrom(Restaurant&& other);
	void free();

	void resize(size_t newCapacity);

	void checkOrder(const Order& order) const;
public:
	Restaurant();
	Restaurant(char name[MAX_NAME_LENGTH + 1],
		const String* products, size_t productsCount,
		const Order* orders, size_t ordersCount);
	Restaurant(char name[MAX_NAME_LENGTH + 1], const StringVector products,
		const Order* orders, size_t ordersCount);
	Restaurant(const Restaurant& other);
	Restaurant(Restaurant&& other) noexcept;
	Restaurant& operator=(const Restaurant& other);
	Restaurant& operator=(Restaurant&& other);
	~Restaurant();


	void setName(char newName[MAX_NAME_LENGTH + 1]);
	const char* getName() const;

	void setProducts(const String* newProducts, size_t newProductsCount);
	void setProducts(const StringVector& newProducts);
	const StringVector& getProducts() const;

	void setOrders(const Order* newOrders, size_t newOrdersCount);
	const Order* getOrders() const;
	size_t getOrdersCount() const;

	void addProduct(const String& product);
	void addProduct(String&& product);

	void recieveOrder(const Order& order);
	void recieveOrder(Order&& order);
};