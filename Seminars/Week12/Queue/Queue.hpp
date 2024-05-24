#pragma once
#include <iostream>
#include <exception>

template<typename T>
class Queue {
private:
	T* data;
	size_t capacity;
	size_t size;

	size_t get;
	size_t put;

	void resize(size_t newCapacity);

	void copyFrom(const Queue<T>& other);
	void moveFrom(Queue<T>&& other);
	void free();
public:
	Queue();
	Queue(const Queue<T>& other);
	Queue(Queue<T>&& other) noexcept;
	Queue<T>& operator=(const Queue<T>& other);
	Queue<T>& operator=(Queue<T>&& other) noexcept;
	~Queue();

	void push(const T& obj);
	void push(T&& obj);
	void pop();
	const T& peek() const;

	bool isEmpty() const;
};

template<typename T>
void Queue<T>::resize(size_t newCapacity)
{
	capacity = newCapacity;
	T* temp = new T[capacity];
	for (size_t i = 0; i < capacity; i++)
	{
		temp[i] = data[i];
		(++get) %= capacity;
	}
	get = 0;
	put = size;
	delete[] data;
	data = temp;
}

template<typename T>
void Queue<T>::copyFrom(const Queue<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	get = other.get;
	put = other.put;
	data = new T[capacity];
	for (size_t i = 0; i < capacity; i++)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
void Queue<T>::moveFrom(Queue<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	get = other.get;
	put = other.put;
	data = other.data;
	other.data = nulltpr;
}

template<typename T>
void Queue<T>::free()
{
	delete[] data;
}

template<typename T>
Queue<T>::Queue()
{
	capacity = 4;
	data = new T * [capacity];
	size = 0;
	get = put = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other)
{
	copyFrom(other);
}

template<typename T>
inline Queue<T>::Queue(Queue<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
Queue<T>::~Queue()
{
	free();
}

template<typename T>
void Queue<T>::push(const T& obj)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}

	data[put] = obj;
	(++put) %= capacity;
	size++;
}

template<typename T>
void Queue<T>::push(T&& obj)
{
	if (size == capacity)
	{
		resize(capacity * 2);
	}
	data[put] = std::move(obj);
	(++put) %= capacity;
	size++;
}

template<typename T>
void Queue<T>::pop()
{
	if (isEmpty())
	{
		throw std::logic_error("Queue<T>::pop(); Queue is empty!");
	}
	(++get) %= capacity;
	size--;
}

template<typename T>
const T& Queue<T>::peek() const
{
	if (isEmpty())
	{
		throw std::logic_error("Queue<T>::peek(); Queue is empty!");
	}
	return data[get];
}

template<typename T>
bool Queue<T>::isEmpty() const
{
	return size == 0;
}


