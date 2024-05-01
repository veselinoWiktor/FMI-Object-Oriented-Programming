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

void DynamicArray::pushBack(const A& newElem)
{
	setAtIndex(newElem, size);
}

void DynamicArray::pushBack(A&& newElem)
{
	setAtIndex(std::move(newElem), size);
}

void DynamicArray::popBack()
{
	if (size)
		arr[size--] = A();
	else
		throw std::length_error("Already empty!");
	
	if (size * 4 <= capacity && capacity > 1)
		resize(capacity / 2);
}

void DynamicArray::setAtIndex(const A& element, size_t index)
{
	if (index > size)
	{
		throw std::out_of_range("Index was out of range!");
	}

	if (size >= capacity)
	{
		resize(capacity * 2);
	}

	arr[index] = element;
	size++;
}

void DynamicArray::setAtIndex(A&& element, size_t index)
{
	if (index > size)
	{
		throw std::out_of_range("Index was out of range!");
	}

	if (size >= capacity)
	{
		resize(capacity * 2);
	}

	arr[index] = std::move(element);
	size++;
}

size_t DynamicArray::getSize() const
{
	return size;
}

bool DynamicArray::isEmpty() const
{
	return size == 0;
}

const A& DynamicArray::operator[](size_t index) const
{
	if (index > size)
		throw std::out_of_range("Index was out of range!");

	return arr[index];
}

A& DynamicArray::operator[](size_t index)
{
	if (index > size)
		throw std::out_of_range("Index was out of range!");

	return arr[index];
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
