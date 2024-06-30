#pragma once
#include "PolymorphicPtr.hpp"

#define FPC FixedPolymorphicContainer
#define TTC template<class T, const unsigned C>

template<class T, const unsigned C>
class FixedPolymorphicContainer
{
	PP<T> data[C];
	size_t size = 0;

	bool isValidIndex(size_t idx);
public:
	void add(T* element);

	PP<T>& operator[](size_t idx);
	const PP<T>& operator[](size_t idx) const;

	void execute(size_t idx, void(*func)(T*));
	void execute(size_t idx, void(*func)(const T*)) const;
};

TTC
bool FPC<T, C>::isValidIndex(size_t idx)
{
	return idx < size;
}

TTC
void FPC<T, C>::add(T* elem)
{
	if (size >= C)
		throw std::runtime_error("No place for more objects!");
	data[size++] = elem;
}

TTC
PP<T>& FPC<T, C>::operator[](size_t idx)
{
	if (!isValidIndex(idx))
		throw std::out_of_range("Invalid index!");
	return data[idx];
}

TTC
const PP<T>& FPC<T, C>::operator[](size_t idx) const
{
	if (!isValidIndex(idx))
		throw std::out_of_range("Invalid index!");
	return data[idx];
}

TTC
void FPC<T, C>::execute(size_t idx, void(*func)(T*))
{
	if (!isValidIndex(idx))
		throw std::out_of_range("Invalid index!");
	func(data[idx].get());
}

TTC
void FPC<T, C>::execute(size_t idx, void(*func)(const T*)) const
{
	if (!isValidIndex(idx))
		throw std::out_of_range("Invalid index!");
	func(data[idx].get());
}
