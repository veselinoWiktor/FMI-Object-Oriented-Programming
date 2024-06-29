#pragma once
#include <iostream>

#define TT template<class T>
#define SP SharedPointer
#define C Counter

struct Counter
{
	unsigned useCount = 0;
	unsigned weakCount = 0;

	void removeSharedPtr()
	{
		useCount--;
		if (useCount == 0)
		{
			weakCount--;
		}
	}

	void removeWeakPtr()
	{
		weakCount--;
	}

	void addSharedPtr()
	{
		useCount++;
		if (useCount == 1)
		{
			weakCount++;
		}
	}

	void addWeakPtr()
	{
		weakCount++;
	}
};

TT
class SharedPointer
{
	TT friend class WeakPointer;

	T* data;
	Counter* counter;

	void copyFrom(const SP<T>& other);
	void moveFrom(SP<T>&& other);
	void free();
public:
	SP();
	SP(T* data);
	SP(const SP<T>& other);
	SP<T>& operator=(const SP<T>& other);
	SP(SP<T>&& other) noexcept;
	SP<T>& operator=(SP<T>&& other) noexcept;
	~SP();

	T& operator*();
	const T& operator*() const;

	T* operator->();
	const T* operator->() const;

	T* get();
	const T* get() const;

	operator bool() const;
};

TT
void SP<T>::copyFrom(const SP<T>& other)
{
	data = other.data;
	counter = other.counter;
	if (counter)
		counter->addSharedPtr();
}

TT
void SP<T>::moveFrom(SP<T>&& other)
{
	data = other.data;
	other.data = nullptr;

	counter = other.counter;
	other.counter = nullptr;
}

TT
void SP<T>::free()
{
	if (!data && !counter)
		return;
	
	counter->removeSharedPtr();
	if (counter->useCount == 0)
		delete data;
	if (counter->weakCount == 0)
		delete counter
}

TT
SP<T>::SP() : data(nullptr), counter(nullptr) {}

TT
SP<T>::SP(T* data)
{
	this->data = data;
	if (this->data)
	{
		counter = new Counter();
		counter->addSharedPtr();
	}
}

TT
SP<T>::SP(const SP<T>& other)
{
	copyFrom(other);
}

TT
SP<T>& SP<T>::operator=(const SP<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

TT
SP<T>::SP(SP<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
SP<T>& SP<T>::operator=(SP<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

TT
SP<T>::~SP()
{
	free();
}

TT
T& SP<T>::operator*()
{
	if (!data)
		throw std::runtime_error("Ptr not set!");
	return *data;
}

TT
const T& SP<T>::operator*() const
{
	if (!data)
		throw std::runtime_error("Ptr not set!");
	return *data;
}

TT
T* SP<T>::operator->()
{
	return data;
}

TT
const T* SP<T>::operator->() const
{
	return data;
}

TT
T* SP<T>::get()
{
	return data;
}

TT
const T* SP<T>::get() const
{
	return data;
}

TT
SP<T>::operator bool() const
{
	return data != nullptr;
}
