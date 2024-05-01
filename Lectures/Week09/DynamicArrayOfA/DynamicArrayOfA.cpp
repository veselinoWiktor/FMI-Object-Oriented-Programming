#include "DynamicArrayOfA.h"
#include <iostream>

void DynamicArray::free()
{
	delete[] arr;
	arr = nullptr;
	size = capacity = 0;
}

void DynamicArray::copyFrom(const DynamicArray& other)
{
	capacity = other.capacity;
	size = other.size;

	arr = new A[capacity];

	for (size_t i = 0; i < size; i++)
	{
		arr[i] = other.arr[i];
	}
}

void DynamicArray::moveFrom(DynamicArray&& other)
{
	capacity = other.capacity;
	size = other.size;
	other.capacity = other.size = 0;

	arr = other.arr;
	other.arr = nullptr;
}

void DynamicArray::resize(size_t newCap)
{
	A* temp = arr;
	arr = new A[newCap];

	for (size_t i = 0; i < size; i++)
		arr[i] = temp[i];

	capacity = newCap;
	delete[] temp;
}

DynamicArray::DynamicArray() : DynamicArray(8)
{
}

DynamicArray::DynamicArray(size_t _capacity) : size(0)
{
	capacity = nextPowerOfTwo(_capacity);
	arr = new A[capacity];
}

DynamicArray::DynamicArray(const DynamicArray& other)
{
	copyFrom(other);
}

DynamicArray::DynamicArray(DynamicArray&& other) noexcept
{
	moveFrom(std::move(other));
}

DynamicArray& DynamicArray::operator=(const DynamicArray& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

DynamicArray::~DynamicArray() noexcept
{
	free();
}

size_t nextPowerOfTwo(size_t n)
{
	size_t step = 1;

	while ((n >> step) > 0)
	{
		n |= (n >> step);
		step <<= 1;
	}

	return n + 1;
}
