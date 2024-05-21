#include "DynamicArrayOfPointers.h"
#include <iostream>

void DynamicArrayOfPointers::free()
{
	for (size_t i = 0; i < capacity; i++)
	{
		delete data[i];
	}

	delete[] data;
}

void DynamicArrayOfPointers::copyFrom(const DynamicArrayOfPointers& other)
{
	capacity = other.capacity;
	count = other.count;

	data = new A * [capacity];
	for (size_t i = 0; i < capacity; i++)
	{
		if (other.data[i] == nullptr)
		{
			data[i] = nullptr;
		}
		else
		{
			data[i] = new A(*other.data[i]);
		}
	}
}

void DynamicArrayOfPointers::moveFrom(DynamicArrayOfPointers&& other)
{
	capacity = other.capacity;
	other.capacity = 0;

	count = other.count;
	other.count = 0;

	data = other.data;
	other.data = nullptr;
}

void DynamicArrayOfPointers::resize(size_t newCapacity)
{
	capacity = newCapacity;

	A** temp = new A * [capacity] {nullptr};
	for (size_t i = 0; i < capacity; i++)
	{
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
}

int DynamicArrayOfPointers::getFirstFreeIndex() const
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (!data[i])
		{
			return i;
		}
	}

	return -1;
}

DynamicArrayOfPointers::DynamicArrayOfPointers()
{
	capacity = 8;
	data = new A * [capacity];
}

DynamicArrayOfPointers::DynamicArrayOfPointers(const DynamicArrayOfPointers& other)
{
	copyFrom(other);
}

DynamicArrayOfPointers::DynamicArrayOfPointers(DynamicArrayOfPointers&& other) noexcept
{
	moveFrom(std::move(other));
}

DynamicArrayOfPointers& DynamicArrayOfPointers::operator=(const DynamicArrayOfPointers& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

DynamicArrayOfPointers& DynamicArrayOfPointers::operator=(DynamicArrayOfPointers&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

DynamicArrayOfPointers::~DynamicArrayOfPointers() noexcept
{
	free();
}

void DynamicArrayOfPointers::addAtFirstFreeIndex(const A& newElem)
{
	if (count == capacity)
	{
		resize(capacity * 2);
	}

	int firstFreeIndex = getFirstFreeIndex();

	if (firstFreeIndex == -1)
	{
		return;
	}

	data[firstFreeIndex] = new A(newElem);
	count++;
}

void DynamicArrayOfPointers::addAtFirstFreeIndex(A&& newElem)
{
	if (count == capacity)
	{
		resize(capacity * 2);
	}

	int firstFreeIndex = getFirstFreeIndex();

	if (firstFreeIndex == -1)
	{
		return;
	}

	data[firstFreeIndex] = new A(std::move(newElem));
	count++;
}

void DynamicArrayOfPointers::setAtIndex(const A& obj, size_t index)
{
	while (index >= capacity)
	{
		resize(capacity * 2);
	}

	if (data[index] != nullptr)
	{
		data[index]->operator=(obj);
	}
	else
	{
		data[index] = new A(obj);
		count++;
	}
}

void DynamicArrayOfPointers::setAtIndex(A&& obj, size_t index)
{
	while (index >= capacity)
	{
		resize(capacity * 2);
	}

	if (data[index] != nullptr)
	{
		*data[index] = std::move(obj);
	}
	else
	{
		data[index] = new A(std::move(obj));
		count++;
	}
}

void DynamicArrayOfPointers::pop_back()
{
	if (count == 0)
	{
		return;
	}

	delete data[count - 1];
	count--;
}

void DynamicArrayOfPointers::removeAt(size_t index)
{
	if (index >= capacity)
	{
		return;
	}

	delete data[index];
	data[index] = nullptr;
	count--;
}

bool DynamicArrayOfPointers::containsAt(size_t index) const
{
	return index < capacity && data[index] != nullptr;
}

size_t DynamicArrayOfPointers::size() const
{
	return count;
}

const A& DynamicArrayOfPointers::operator[](size_t index) const
{
	if (index >= capacity)
	{
		throw std::out_of_range("DynamicArrayOfPointers::operator[](); index was out of range!");
	}
	else if (!data[index])
	{
		throw std::invalid_argument("DynamicArrayOfPointers::operator[](); index was nullptr!");
	}

	return *data[index];
}

A& DynamicArrayOfPointers::operator[](size_t index)
{
	if (index >= capacity)
	{
		throw std::out_of_range("DynamicArrayOfPointers::operator[](); index was out of range!");
	}
	else if (!data[index])
	{
		throw std::invalid_argument("DynamicArrayOfPointers::operator[](); index was nullptr!");
	}

	return *data[index];
}
