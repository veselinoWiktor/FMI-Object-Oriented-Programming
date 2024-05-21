#include "UniquePointer.h"

void UniquePointer::free()
{
	delete ptr;
	ptr = nullptr;
}

void UniquePointer::moveFrom(UniquePointer&& other)
{
	ptr = other.ptr;
	other.ptr = nullptr;
}

UniquePointer::UniquePointer(A* pointer) : ptr(pointer)
{

}

UniquePointer::UniquePointer(UniquePointer&& other) noexcept
{
	moveFrom(std::move(other));
}

UniquePointer& UniquePointer::operator=(UniquePointer&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

UniquePointer::~UniquePointer() noexcept
{
	free();
}

const A& UniquePointer::operator*() const
{
	return *ptr;
}

A& UniquePointer::operator*()
{
	return *ptr;
}
