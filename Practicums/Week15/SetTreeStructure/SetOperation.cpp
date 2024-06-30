#include "SetOperation.h"
#include <iostream>

void SetOperation::copyFrom(const SetOperation& other)
{
	size = other.size;
	capacity = other.capacity;

	data = new Set * [capacity];
	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i]->clone();
}

void SetOperation::moveFrom(SetOperation&& other)
{
	size = other.size;
	capacity = other.capacity;

	data = other.data;
	other.data = nullptr;
}

void SetOperation::free()
{
	for (size_t i = 0; i < size; i++)
		delete data[i];
	delete[] data;
}

void SetOperation::resize(size_t newCapacity)
{
	capacity = newCapacity;
	Set** temp = new Set * [capacity];
	for (size_t i = 0; i < size; i++)
		temp[i] = data[i];
	delete[] data;
	data = temp;
}

void SetOperation::addSet(Set* set)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	data[size++] = set;
}

Set** SetOperation::cloneData() const
{
	Set** copyData = new Set * [size];
	for (size_t i = 0; i < size; i++)
		copyData[i] = data[i]->clone();

	return copyData;
}

SetOperation::SetOperation() : size(0), capacity(4)
{
	data = new Set * [capacity];
}

SetOperation::SetOperation(const SetOperation& other)
{
	copyFrom(other);
}

SetOperation& SetOperation::operator=(const SetOperation& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

SetOperation::SetOperation(SetOperation&& other) noexcept
{
	moveFrom(std::move(other));
}

SetOperation& SetOperation::operator=(SetOperation&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

SetOperation::~SetOperation()
{
	free();
}
