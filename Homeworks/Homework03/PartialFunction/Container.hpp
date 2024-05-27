#pragma once
#include <iostream>

template<class Base, class Factory>
class Container
{
private:
	Base** data;
	size_t size;
	size_t capacity;

	void copyFrom(const Container<Base, Factory>& other);
	void moveFrom(Container<Base, Factory>&& other);
	void free();

	void resize(size_t newCap);

public:
	Container();

	Container(const Container<Base, Factory>& other);
	Container(Container<Base, Factory>&& other) noexcept;
	Container<Base, Factory>& operator=(const Container<Base, Factory>& other);
	Container<Base, Factory>& operator=(Container<Base, Factory>&& other) noexcept;
	~Container();

	void add(const Base& elem);
	void add(const char* str);

	const Base* operator[](size_t index) const;
	Base* operator[](size_t index);

	size_t getSize() const;
};

template<class Base, class Factory>
void Container<Base, Factory>::copyFrom(const Container<Base, Factory>& other)
{
	capacity = other.capacity;
	size = other.size;
	data = new Base * [capacity];
	for (size_t i = 0; i < size; i++)
	{
		data[i] = other.data[i]->clone();
	}
}

template<class Base, class Factory>
void Container<Base, Factory>::moveFrom(Container<Base, Factory>&& other)
{
	data = other.data;
	other.data = nullptr;
}

template<class Base, class Factory>
void Container<Base, Factory>::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete data[i];
	}
	delete[] data;
}

template<class Base, class Factory>
void Container<Base, Factory>::resize(size_t newCap)
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

template<class Base, class Factory>
Container<Base, Factory>::Container() : size(0), capacity(8)
{
	data = new Base * [capacity] {nullptr};
}

template<class Base, class Factory>
Container<Base, Factory>::Container(const Container<Base, Factory>& other)
{
	copyFrom(other);
}

template<class Base, class Factory>
Container<Base, Factory>::Container(Container<Base, Factory>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class Base, class Factory>
Container<Base, Factory>& Container<Base, Factory>::operator=(const Container<Base, Factory>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<class Base, class Factory>
Container<Base, Factory>& Container<Base, Factory>::operator=(Container<Base, Factory>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<class Base, class Factory>
Container<Base, Factory>::~Container()
{
	free();
}

template<class Base, class Factory>
void Container<Base, Factory>::add(const Base& elem)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	data[size++] = elem.clone();
}


template<class Base, class Factory>
void Container<Base, Factory>::add(const char* str)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	Base* ptr = Factory::create(str);

	if (ptr)
	{
		data[size++] = ptr;
	}
}

template<class Base, class Factory>
const Base* Container<Base, Factory>::operator[](size_t index) const
{
	if (index >= size)
	{
		throw std::out_of_range("Container::operator[](size_t index); Index was out of range!");
	}

	return data[index];
}

template<class Base, class Factory>
Base* Container<Base, Factory>::operator[](size_t index)
{
	if (index >= size)
	{
		throw std::out_of_range("Container::operator[](size_t index); Index was out of range!");
	}

	return data[index];
}

template<class Base, class Factory>
size_t Container<Base, Factory>::getSize() const
{
	return size;
}
