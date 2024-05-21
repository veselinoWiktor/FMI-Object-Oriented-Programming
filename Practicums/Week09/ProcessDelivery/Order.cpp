#include "Order.h"
#include "Utils.h"

void Order::copyFrom(const Order& other)
{
	restaurantName = other.restaurantName;
	productsCount = other.productsCount;
	productsCapacity = other.productsCapacity;

	productsList = new String[productsCapacity];
	for (size_t i = 0; i < other.productsCount; i++)
	{
		productsList[i] = other.productsList[i];
	}

	deliveryTime = other.deliveryTime;
}

void Order::moveFrom(Order&& other)
{
	restaurantName = other.restaurantName;
	other.restaurantName = "";

	productsCount = other.productsCount;
	productsCapacity = other.productsCapacity;
	other.productsCount = other.productsCapacity = 0;

	productsList = other.productsList;
	other.productsList = nullptr;

	deliveryTime = other.deliveryTime;
	other.deliveryTime = 0;
}

void Order::free()
{
	delete[] productsList;
	isModified = true;
}

void Order::resize(size_t newCapacity)
{
	productsCapacity = newCapacity;
	String* temp = new String[productsCapacity];
	for (size_t i = 0; i < productsCount; i++)
	{
		temp[i] = productsList[i];
	}
	delete[] productsList;
	productsList = temp;
}

Order::Order() : productsCount(0), restaurantName(""), productsCapacity(4), deliveryTime(0)
{
	productsList = new String[productsCapacity]{ "" };
}

Order::Order(const String& restaurantName, const String* productsList, size_t productsCount)
{
	setRestaurantName(restaurantName);
	setProductsList(productsList, productsCount);
	deliveryTime = calculateDeliveryTime();
}

Order::Order(const Order& other)
{
	copyFrom(other);
}

Order::Order(Order&& other) noexcept
{
	moveFrom(std::move(other));
}

Order& Order::operator=(const Order& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Order& Order::operator=(Order&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Order::~Order()
{
	free();
}

void Order::setRestaurantName(const String& newRestaurantName)
{
	restaurantName = newRestaurantName;

	isModified = true;
}

const String& Order::getRestaurantName() const
{
	return restaurantName;
}

void Order::setProductsList(const String* newProductsList, size_t newProductsCount)
{
	productsCount = newProductsCount;
	productsCapacity = std::max(Utils::nextPowerOfTwo(productsCount), 4ull);

	productsList = new String[productsCapacity];
	for (size_t i = 0; i < productsCount; i++)
	{
		productsList[i] = newProductsList[i];
	}

	isModified = true;
}

const String* Order::getProductsList() const
{
	return productsList;
}

size_t Order::getProductsCount() const
{
	return productsCount;
}

void Order::addProduct(const String& product)
{
	if (productsCount == productsCapacity)
	{
		resize(productsCapacity * 2);
	}

	productsList[productsCount++] = product;
	isModified = true;
}

void Order::addProduct(String&& product)
{
	if (productsCount == productsCapacity)
	{
		resize(productsCapacity * 2);
	}

	productsList[productsCount++] = std::move(product);
	isModified = true;
}

size_t Order::calculateDeliveryTime() const
{
	if (!isModified)
	{
		return deliveryTime;
	}

	size_t result = 0;
	result += productsCount;
	for (size_t i = 0; i < productsCount; i++)
	{
		result += strlen(productsList[i].c_str());
	}

	isModified = false;
	return result;
}
