#include "Function.h"

void Funciton::copyFrom(const Funciton& other)
{
	size = other.size;
	data = new unsigned int[size];
	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i];
}

void Funciton::moveFrom(Funciton&& other)
{
	size = other.size;

	data = other.data;
	other.data = nullptr;
}

void Funciton::free()
{
	delete[] data;
}

Funciton::Funciton() : size(0), data(nullptr)
{
}

Funciton::Funciton(const unsigned int* data, size_t size) : size(size)
{
	this->data = new unsigned int[size];
	for (size_t i = 0; i < size; i++)
	{
		this->data[i] = data[i];
	}
}

Funciton::Funciton(const Funciton& other)
{
	copyFrom(other);
}


Funciton::Funciton(Funciton&& other) noexcept
{
	moveFrom(std::move(other));
}

Funciton& Funciton::operator=(const Funciton& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}


Funciton& Funciton::operator=(Funciton&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Funciton::~Funciton()
{
	free();
}

bool Funciton::contains(unsigned int x) const
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

bool Funciton::operator()(unsigned int x) const
{
	return contains(x);
}
