#include "Restaurant.h"
#include "Utils.h"

void Restaurant::copyFrom(const Restaurant& other)
{
	strcpy(name, other.name);
	products = other.products;
	ordersCount = other.ordersCount;
	ordersCapacity = other.ordersCapacity;

	orders = new Order[ordersCapacity];
	for (size_t i = 0; i < ordersCount; i++)
	{
		orders[i] = other.orders[i];
	}
}

void Restaurant::moveFrom(Restaurant&& other)
{
	strcpy(name, other.name);
	strcpy(other.name, "");

	products = other.products;
	other.products.clear();

	ordersCount = other.ordersCount;
	ordersCapacity = other.ordersCapacity;
	other.ordersCount = other.ordersCapacity = 0;

	orders = other.orders;
	other.orders = nullptr;
}

void Restaurant::free()
{
	delete[] orders;
}

void Restaurant::resize(size_t newCapacity)
{
	ordersCapacity = newCapacity;
	Order* temp = new Order[ordersCapacity];
	for (size_t i = 0; i < ordersCount; i++)
	{
		temp[i] = orders[i];
	}
	delete[] orders;
	orders = temp;
}

void Restaurant::checkOrder(const Order& order) const
{
	if (name != order.getRestaurantName())
	{
		throw std::invalid_argument("Order is for another restaurant!");
	}

	bool isFound;
	size_t orderProductsCount = order.getProductsCount();
	size_t restaurantProductsCount = products.count();
	for (size_t i = 0; i < orderProductsCount; i++)
	{
		isFound = false;
		for (size_t j = 0; j < restaurantProductsCount; j++)
		{
			if (order.getProductsList()[i] == products[j])
			{
				isFound = true;
				break;
			}
		}
		if (!isFound)
		{
			throw std::invalid_argument("Order products are different from restaurant products!");
		}
	}
}

Restaurant::Restaurant() : name(""), products()
{
}

Restaurant::Restaurant(char name[MAX_NAME_LENGTH + 1],
	const String* products, size_t productsCount,
	const Order* orders, size_t ordersCount)
{
	setName(name);
	setProducts(products, productsCount);
	setOrders(orders, ordersCount);
}

Restaurant::Restaurant(char name[MAX_NAME_LENGTH + 1], const StringVector products,
	const Order* orders, size_t ordersCount)
{
	setName(name);
	setProducts(products);
	setOrders(orders, ordersCount);
}

Restaurant::Restaurant(const Restaurant& other)
{
	copyFrom(other);
}

Restaurant::Restaurant(Restaurant&& other) noexcept
{
	moveFrom(std::move(other));
}

Restaurant& Restaurant::operator=(const Restaurant& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Restaurant& Restaurant::operator=(Restaurant&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Restaurant::~Restaurant()
{
	free();
}

void Restaurant::setName(char newName[MAX_NAME_LENGTH + 1])
{
	strcpy(name, newName);
}

const char* Restaurant::getName() const
{
	return name;
}

void Restaurant::setProducts(const String* newProducts, size_t newProductsCount)
{
	products = StringVector(newProducts, newProductsCount);
}

void Restaurant::setProducts(const StringVector& newProducts)
{
	products = newProducts;
}

const StringVector& Restaurant::getProducts() const
{
	return products;
}

void Restaurant::setOrders(const Order* newOrders, size_t newOrdersCount)
{
	ordersCount = newOrdersCount;
	ordersCapacity = std::max(Utils::nextPowerOfTwo(ordersCount), 4ull);

	orders = new Order[ordersCapacity];
	for (size_t i = 0; i < ordersCount; i++)
	{
		orders[i] = newOrders[i];
	}
}

const Order* Restaurant::getOrders() const
{
	return orders;
}

size_t Restaurant::getOrdersCount() const
{
	return ordersCount;
}

void Restaurant::addProduct(const String& product)
{
	products.push_back(product);
}

void Restaurant::addProduct(String&& product)
{
	products.push_back(std::move(product));
}

void Restaurant::recieveOrder(const Order& order)
{
	checkOrder(order);
	if (ordersCount == ordersCapacity)
	{
		resize(ordersCapacity * 2);
	}

	orders[ordersCount++] = order;
}

void Restaurant::recieveOrder(Order&& order)
{
	checkOrder(order);
	if (ordersCount == ordersCapacity)
	{
		resize(ordersCapacity * 2);
	}

	orders[ordersCount++] = std::move(order);
}
