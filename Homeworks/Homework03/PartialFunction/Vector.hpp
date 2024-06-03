#pragma once

template<typename T>
class Vector
{
private:
	T* data = nullptr;
	unsigned capacity = 0;
	unsigned size = 0;

	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
	void free();

	void resize();

	void setSize(unsigned _size);
	void setCapacity();
	void initData(const T* newData);

	void shiftLeftByOne(unsigned atIdx);
	void shiftRightByOne(unsigned atIdx);
public:
	Vector(const T* data, unsigned _size);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);
	~Vector();

	unsigned getSize() const;
	bool isEmpty() const;
	unsigned push_back(T&& obj);
	unsigned push_back(const T& obj);
	void pop_back();

	void erase(unsigned idx);
	void insert(T&& obj, unsigned idx);
	void insert(const T& obj, unsigned idx);

	void clear();

	T& operator[](unsigned idx);
	const T& operator[](unsigned idx) const;
};

template<typename T>
void Vector<T>::free()
{
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];

	for (int i = 0; i < size; i++)
	{
		data[i] = other.data[i];
	}
}

template<typename T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nulltpr;
}

template<typename T>
void Vector<T>::resize()
{
	capacity *= 2;
	T* newData = new T[capacity];

	for (int i = 0; i < size; i++)
	{
		newData[i] = data[i];
	}

	delete[] data;
	data = newData;
}

template<typename T>
void Vector<T>::setSize(unsigned _size)
{
	size = _size;
}

template<typename T>
void Vector<T>::setCapacity()
{
	capacity = std::max(getNextPowerOfTwo(size), (unsigned)16);
}

template<typename T>
void Vector<T>::initData(const T* newData)
{
	data = new T[capacity];
	for (unsigned i = 0; i < size; i++)
	{
		data[i] = newData[i];
	}
}

template<typename T>
void Vector<T>::shiftLeftByOne(unsigned atIdx)
{
	for (int i = atIdx; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}
}

template<typename T>
void Vector<T>::shiftRightByOne(unsigned atIdx)
{
	if (size == capacity)
	{
		resize();
	}

	for (int i = atIdx; i < size; i++)
	{
		data[i + 1] = data[i];
	}
}

template<typename T>
Vector<T>::Vector(const T* data, unsigned _size)
{
	setSize(_size);
	setCapacity();
	initData(data);
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>::Vector(Vector<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
unsigned Vector<T>::getSize() const
{
	return size;
}

template<typename T>
bool Vector<T>::isEmpty() const
{
	return size == 0;
}

template<typename T>
unsigned Vector<T>::push_back(T&& obj)
{
	insert(std::move(obj), size);
	return size - 1;
}

template<typename T>
unsigned Vector<T>::push_back(const T& obj)
{
	insert(obj, size);
	return size - 1;
}

template<typename T>
void Vector<T>::pop_back()
{
	if (isEmpty())
	{
		throw std::logic_error("There are no elements in the Vector<T>");
	}

	erase(size - 1);
}

template<typename T>
void Vector<T>::erase(unsigned idx)
{
	if (idx >= size)
	{
		throw std::out_of_range("Index was out of range");
	}

	shiftLeftByOne(idx);

	size--;
}

template<typename T>
void Vector<T>::insert(T&& obj, unsigned idx)
{
	if (idx > size)
	{
		throw std::out_of_range("Index was out of range");
	}

	shiftRightByOne(idx);

	data[idx] = std::move(obj);
	size++;
}

template<typename T>
void Vector<T>::insert(const T& obj, unsigned idx)
{
	if (idx > size)
	{
		throw std::out_of_range("Index was out of range");
	}

	shiftRightByOne(idx);

	data[idx] = obj;
	size++;
}

template<typename T>
void Vector<T>::clear()
{
	free();

	capacity = 16;
	data = new T[capacity];
}

template<typename T>
T& Vector<T>::operator[](unsigned idx)
{
	return data[idx];
}

template<typename T>
const T& Vector<T>::operator[](unsigned idx) const
{
	return data[idx];
}