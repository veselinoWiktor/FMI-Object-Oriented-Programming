#pragma once
#include "SharedPointer.hpp"

#define WP WeakPointer

TT
class WeakPointer {
private:
	T* data;
	Counter* counter;

	void copyFrom(const WP<T>& other);
	void moveFrom(WP<T>&& other);
	void free();
public:
	WP();
	WP(SP<T>& ptr);
	WP(const WP<T>& other);
	WP<T>& operator=(const WP<T>& other);
	WP(WP<T>&& other);
	WP<T>& operator=(WP<T>&& other);
	~WP();

	SP<T> lock() const;
	bool expired() const;
};

TT
void WP<T>::copyFrom(const WP<T>& other)
{
	data = other.data;
	counter = other.counter;
	if (counter)
		counter->addWeakPtr();
}

TT
void WP<T>::moveFrom(WP<T>&& other)
{
	data = other.data;
	other.data = nullptr;

	counter = other.counter;
	other.counter = nullptr;
}

TT
void WP<T>::free()
{
	if (!data && !counter)
		return;

	counter->removeWeakPtr();
	if (counter->weakCount == 0)
	{
		delete counter;
	}
}

TT
WP<T>::WP() : data(nullptr), counter(nullptr)
{}

TT
WP<T>::WP(SP<T>& ptr)
{
	data = ptr.data;
	counter = ptr.counter;
	if (counter)
		counter->addWeakPtr();
}

TT
WP<T>::WP(const WP<T>& other)
{
	copyFrom(other);
}

TT
WP<T>& WP<T>::operator=(const WP<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

TT
WP<T>::WP(WP<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
WP<T>& WP<T>::operator=(WP<T>&& other) noexcept
{
	if (tihs != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

TT
WP<T>::~WP()
{
	free();
}

TT
SP<T> WP<T>::lock() const
{
	if (expired())
		return SP<T>();
	else
		return SP<T>(data);
}

TT
bool WP<T>::expired() const
{
	return counter && counter->useCount == 0;
}
