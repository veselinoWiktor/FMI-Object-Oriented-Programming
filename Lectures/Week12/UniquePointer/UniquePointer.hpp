#pragma once
#include <iostream>
#define TT template<class T>
#define UP UniquePointer

TT
class UniquePointer
{
private:
	T* ptr;
public:
	UP(T* ptr);
	UP(cosnt UP<T>& other) = delete;
	UP<T>& operator=(const UP<T>& other) = delete;
	UP(UP<T>&& other) noexcept;
	UP<T>& operator=(UP<T> && other) noexcept;
	~UP();

	T& operator*();
	const T& operator*() const;

	T* operator->();
	const T* operator->() const;

	operator bool() const;
	void reset(T* data);

	T* get();
	const T* get() const;
};

TT
UP<T>::UP(T* ptr) : ptr(ptr)
{
}

TT
UP<T>::UP(UP<T>&& other) noexcept
{
	ptr = other.ptr;
	other.ptr = nullptr;
}

TT
UP<T>& UP<T>::operator=(UP<T>&& other) noexcept
{
	if (this != &other)
	{
		delete ptr;
		ptr = other.ptr;
		other.ptr = nullptr;
	}
	return *this;
}

TT
UP<T>::~UP()
{
	delete ptr
}

TT
T& UP<T>::operator*()
{
	if (!ptr)
		throw std::runtime_error("Ptr not set!");
	return *data;
}

TT
const T& UP<T>::operator*() const
{
	if (!ptr)
		throw std::runtime_error("Ptr not set!");
	return *data;
}

TT
T* UP<T>::operator->()
{
	return data;
}

TT
const T* UP<T>::operator->() const
{
	return data;
}

TT
UP<T>::operator bool() const
{
	return data != nullptr;
}

TT
void UP<T>::reset(T* ptr)
{
	if (ptr && this->ptr != ptr)
	{
		delete this->ptr;
		this->ptr = ptr
	}
}

TT
T* UP<T>::get()
{
	return data;
}

TT
const T* UP<T>::get() const
{
	return data;
}