#include "DynamicCollection.h"
#include <iostream>

void DynamicCollection::copyFrom(const DynamicCollection& other)
{
	size = other.size;
	capacity = other.capacity;

	data = new int[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

void DynamicCollection::moveFrom(DynamicCollection&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
}

void DynamicCollection::free()
{
	delete[] data;
}

void DynamicCollection::resize(size_t newCapacity)
{
	capacity = newCapacity;
	int* temp = new int[capacity];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
}

DynamicCollection::DynamicCollection(size_t capacity)
{
	size = 0;
	this->capacity = capacity;

	data = new int[capacity];

}

DynamicCollection::DynamicCollection() : DynamicCollection(8)
{
}

DynamicCollection::DynamicCollection(const DynamicCollection& other)
{
	copyFrom(other);
}

DynamicCollection::DynamicCollection(DynamicCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

DynamicCollection& DynamicCollection::operator=(const DynamicCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

DynamicCollection& DynamicCollection::operator=(DynamicCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

DynamicCollection::~DynamicCollection()
{
	free();
}
