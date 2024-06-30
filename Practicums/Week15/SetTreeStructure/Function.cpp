#include "Function.h"

void Function::copyFrom(const Function& other)
{
	size = other.size;
	data = new unsigned int[size];
	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i];
}

void Function::moveFrom(Function&& other)
{
	size = other.size;

	data = other.data;
	other.data = nullptr;
}

void Function::free()
{
	delete[] data;
}

Function::Function() : size(0), data(nullptr)
{
}

Function::Function(const unsigned int* data, size_t size) : size(size)
{
	this->data = new unsigned int[size];
	for (size_t i = 0; i < size; i++)
	{
		this->data[i] = data[i];
	}
}

Function::Function(const Function& other)
{
	copyFrom(other);
}


Function::Function(Function&& other) noexcept
{
	moveFrom(std::move(other));
}

Function& Function::operator=(const Function& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}


Function& Function::operator=(Function&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Function::~Function()
{
	free();
}

bool Function::contains(unsigned int x) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == x)
		{
			return true;
		}
	}
	return false;
}

bool Function::operator()(unsigned int x) const
{
	return contains(x);
}
