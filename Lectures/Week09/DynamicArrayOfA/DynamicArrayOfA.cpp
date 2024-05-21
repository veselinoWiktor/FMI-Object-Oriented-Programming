#include "DynamicArrayOfA.h"

void DynamicArray::free()
{
	delete[] data;
	capacity = size = 0;
}

void DynamicArray::copyFrom(const DynamicArray& other)
{
	capacity = other.capacity;
	size = other.size;
	data = new A[capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

void DynamicArray::moveFrom(DynamicArray&& other)
{
	capacity = other.capacity;
	other.capacity = 0;

	size = other.size;
	other.size = 0;

	data = other.data;
	other.data = nullptr;
}

void DynamicArray::resize(size_t newCap)
{
	capacity = newCap;

	A* temp = new A[capacity];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
}

DynamicArray::DynamicArray() : size(0), capacity(8)
{
	data = new A[capacity];
}

DynamicArray::DynamicArray(size_t _size) : size(0)
{
	capacity = nextPowerOfTwo(_size);
	data = new A[capacity];
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
		size--;
	else
		throw std::length_error("Already empty!");

	if (size * 4 <= capacity && capacity > 1)
		resize(capacity / 2);
}

void DynamicArray::setAtIndex(const A& element, size_t index)
{
	if (index > size)
	{
		throw std::out_of_range("DynamicArray::setAtIndex(); index was out of range!");
	}

	if (size == capacity)
	{
		resize(capacity * 2);
	}

	for (size_t i = index; i < size; i++)
	{
		data[i + 1] = data[i];
	}

	data[index] = element;
}

void DynamicArray::setAtIndex(A&& element, size_t index)
{
	if (index > size)
	{
		throw std::out_of_range("DynamicArray::setAtIndex(A&& element, size_t index); index was out of range!");
	}

	if (size == capacity)
	{
		resize(capacity * 2);
	}

	for (size_t i = index; i < size; i++)
	{
		data[i + 1] = data[i];
	}

	data[index] = std::move(element);
}

size_t DynamicArray::getSize() const
{
	return size;
}

bool DynamicArray::isEmpty() const
{
	return (size == 0);
}

const A& DynamicArray::operator[](size_t index) const
{
	if (index >= size)
	{
		throw std::out_of_range("DynamicArray::operator[](size_t index) const; index was out of range!");
	}
	
	return data[index];
}

A& DynamicArray::operator[](size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("DynamicArray::operator[](size_t index); index was out of range!");
	}

	return data[index];
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
