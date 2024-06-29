#pragma once
#include "PolymorphicPtr.hpp"
#include "Vector.hpp"

#define PC PolymorphicContainer

TT
class PolymorphicContainer {
	Vector<PP<T>> data;
public:
	void add(T* elem);

	PP<T>& operator[](size_t idx);
	const PP<T>& operator[](size_t idx) const;

	void execute(size_t idx, void(*func)(T*));
	void execute(size_t idx, void(*func)(const T*)) const;
};

TT
void PC<T>::add(T* elem)
{
	data.pushBack(elem);
}

TT
PP<T>& PC<T>::operator[](size_t idx)
{
	return data[idx];
}

TT
const PP<T>& PC<T>::operator[](size_t idx) const
{
	return data[idx];
}

TT
void PC<T>::execute(size_t idx, void(*func)(T*)) {
	func(data[idx].get());
}

TT
void PC<T>::execute(size_t idx, void(*func)(const T*)) const
{
	func(data[idx].get());
}