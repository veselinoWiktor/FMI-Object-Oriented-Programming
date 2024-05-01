#include "DynamicArrayOfPointers.h"
#include<iostream>

void DynamicArrayOfPointers::free()
{
	for (size_t i = 0; i < _capacity; i++)
		delete[] _data[i];

	delete[] _data;
}

void DynamicArrayOfPointers::copyFrom(const DynamicArrayOfPointers& other)
{
	_count = other._count;
	_capacity = other._capacity;

	_data = new A*[_capacity];
	for (size_t i = 0; i < _capacity; i++)
	{
		if (other._data[i] == nullptr)
			_data[i] = nullptr;
		else
			_data[i] = new A(*other._data[i]);
	}
}

void DynamicArrayOfPointers::moveFrom(DynamicArrayOfPointers&& other)
{
	_data = other._data;
	other._data = nullptr;

	_count = other._count;
	other._count = 0;

	_capacity = other._capacity;
	other._capacity = 0;
}

void DynamicArrayOfPointers::resize(size_t newCapacity)
{
	A** temp = _data;

	A** _data = new A*[newCapacity] {nullptr};

	for (size_t i = 0; i < _capacity; i++)
		_data[i] = temp[i];

	delete[] temp;

	_capacity = newCapacity;
}

DynamicArrayOfPointers::DynamicArrayOfPointers() : _count(0)
{
	_capacity = 16;
	_data = new A*[_capacity] {nullptr};
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
