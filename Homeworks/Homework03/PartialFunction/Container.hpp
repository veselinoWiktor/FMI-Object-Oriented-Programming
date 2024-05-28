#pragma once
#include <iostream>

template<class Base>
class Container
{
private:
	Base** data;
	size_t size;
	size_t capacity;

	void copyFrom(const Container<Base>& other);
	void moveFrom(Container<Base>&& other);
	void free();

	void resize(size_t newCap);

public:
	Container();

	Container(const Container<Base>& other);
	Container(Container<Base>&& other) noexcept;
	Container<Base>& operator=(const Container<Base>& other);
	Container<Base>& operator=(Container<Base>&& other) noexcept;
	~Container();

	void add(const Base& elem);
	void add(const Base* elemPtr); //Factory created element

	const Base* operator[](size_t index) const;
	Base* operator[](size_t index);

	size_t getSize() const;
};

template<class Base>
void Container<Base, >::copyFrom(const Container<Base, >& other)
{
	capacity = other.capacity;
	size = other.size;
	data = new Base * [capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i]->clone();
	}
}

template<class Base>
void Container<Base>::moveFrom(Container<Base>&& other)
{
	data = other.data;
	other.data = nullptr;
}

template<class Base>
void Container<Base>::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete data[i];
	}
	delete[] data;
}

template<class Base>
void Container<Base>::resize(size_t newCap)
{
	capacity = newCap;
	Base** temp = new Base * [capacity] {nullptr};
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}
	delete[] data;
	data = temp;
}

template<class Base>
Container<Base>::Container() : size(0), capacity(8)
{
	data = new Base * [capacity] {nullptr};
}

template<class Base>
Container<Base>::Container(const Container<Base>& other)
{
	copyFrom(other);
}

template<class Base>
Container<Base>::Container(Container<Base>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class Base>
Container<Base>& Container<Base>::operator=(const Container<Base>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<class Base>
Container<Base>& Container<Base>::operator=(Container<Base>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<class Base>
Container<Base>::~Container()
{
	free();
}

template<class Base>
void Container<Base>::add(const Base& elem)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	data[size++] = elem.clone();
}

template<class Base>
inline void Container<Base>::add(const Base* elemPtr)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	data[size++] = elemPtr;
}

template<class Base>
const Base* Container<Base>::operator[](size_t index) const
{
	if (index >= size)
	{
		throw std::out_of_range("Container::operator[](size_t index); Index was out of range!");
	}

	return data[index];
}

template<class Base>
Base* Container<Base>::operator[](size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("Container::operator[](size_t index); Index was out of range!");
	}

	return data[index];
}

template<class Base>
size_t Container<Base>::getSize() const
{
	return size;
}
