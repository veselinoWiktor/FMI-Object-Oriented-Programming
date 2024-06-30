#pragma once
#include <iostream>

#define TT template<class T>
#define PP PolymorphicPtr

TT
class PolymorphicPtr {
private:
	T* data = nullptr;

	void copyFrom(const PP<T>& other);
	void moveFrom(PP<T>&& other);
	void free();
public:
	PP() = default;
	PP(T* data);

	PP(const PP<T>& other);
	PP<T>& operator=(const PP<T>& other);
	PP(PP<T>&& other) noexcept;
	PP<T>& operator=(PP<T>&& other) noexcept;
	~PP();

	T* operator->();
	const T* operator->() const;

	T& operator*();
	const T& operator*() const;

	operator bool() const;
	void reset(T* data);

	T* get();
	const T* get() const;
};

TT
void PP<T>::copyFrom(const PP<T>& other)
{
	data = other.data->clone();
}

TT
void PP<T>::moveFrom(PP<T>&& other)
{
	data = other.data;
	other.data = nullptr;
}

TT
void PP<T>::free()
{
	delete data;
}

TT
PP<T>::PP(T* data) : data(data) {}

TT
PP<T>::PP(const PP<T>& other)
{
	copyFrom(other);
}

TT
PP<T>& PP<T>::operator=(const PP<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

TT
PP<T>::PP(PP<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

TT
PP<T>& PP<T>::operator=(PP<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

TT
PP<T>::~PP()
{
	free();
}

TT
T* PP<T>::operator->()
{
	return data;
}

TT
const T* PP<T>::operator->() const
{
	return data;
}

TT
T& PP<T>::operator*()
{
	if (!data)
	{
		throw std::logic_error("Empty pointer!");
	}
	return *data;
}

TT
const T& PP<T>::operator*() const
{
	if (!data)
	{
		throw std::logic_error("Empty pointer!");
	}
	return *data;
}

TT
PP<T>::operator bool() const
{
	return data != nullptr;
}

TT
void PP<T>::reset(T* data)
{
	if (!data && this->data != data)
	{
		free();
		this->data = data;
	}
}

TT
T* PP<T>::get()
{
	return data;
}

TT
const T* PP<T>::get() const
{
	return data;
}