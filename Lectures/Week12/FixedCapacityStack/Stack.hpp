#pragma once
#include <iostream>
#define TTC template<class T, const unsigned C>
#define S Stack

TTC
class Stack
{
private:
	T data[C];
	size_t size = 0;
public:
	void push(const T& obj);
	void push(T&& obj);
	void pop();
	const T& peek() const;
	bool isEmpty() const;
};

TTC
void S<T, C>::push(const T& obj)
{
	if (size >= C)
		return;
	data[size++] = obj;
}

TTC
void S<T, C>::push(T&& obj)
{
	if (size >= C)
		return;
	data[size++] = std::move(obj);
}

TTC
void S<T, C>::pop()
{
	if (isEmpty())
		throw std::logic_error("Empty stack!");
	size--;
}

TTC
const T& S<T, C>::peek() const
{
	if (isEmpty())
		throw std::logic_error("Empty stack!");
	return data[size - 1];
}

TTC
bool S<T, C>::isEmpty() const
{
	return size == 0;
}
