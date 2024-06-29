#pragma once

template<typename T>
class Vector
{
private:
	static const short INITIAL_CAPACITY = 4;
	static const short RESIZE_COEF = 2;

	T* data;
	size_t size;
	size_t capacity;

	void copyFrom(const Vector<T> other);
	void moveFrom(Vector<T>&& other);
	void free();

	void resize(size_t newCapcity);

	void upsizeIfNeeded();
	void downsizeIfNeeded();
public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);
	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(Vector<T>&& other) noexcept;
	~Vector();

	size_t getSize() const;

	void pushBack(const T& element);
	void pushBack(T&& element);
	void pushAt(size_t idx, const T& element);
	void pushAt(size_t idx, T&& element);
	T popBack();
	T popAt(size_t idx);

	bool contains(const T& element);
	bool empty() const;
	void clear();

	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;

	class Iterator {
	private:
		T* currentElement;
		Iterator(T* element) : currentElement{ element } {}
	public:
		Iterator& operator++()
		{
			if (currentElement == nullptr)
				return *this;
			currentElement++;
			return *this;
		}
		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}
		T& operator*()
		{
			return *currentElement;
		}
		bool operator==(const Iterator& other) const {
			return other.currentElement == currentElement;
		}
		bool operator!=(const Iterator& other) const {
			return !(*this == other);
		}
		friend class Vector<T>;
	};
	Iterator begin()
	{
		if (empty())
		{
			throw std::logic_error("Vector was empty");
		}

		return Iterator(&data[0]);
	}
	Iterator end() {
		return Iterator(data + size);
	}

	class ConstIterator
	{
	private:
		const T* currentElement; // указател към константа памет!
		ConstIterator(T* element) : currentElement{ element } {}
	public:
		ConstIterator& operator++()
		{
			if (currentElement == nullptr)
				return *this;

			currentElement++;
			return *this;
		}
		ConstIterator operator++(int)
		{
			Iterator temp = *this;
			++(*this);
			return temp;
		}
		const T& operator*() const
		{
			return *currentElement;
		}
		bool operator==(const ConstIterator& other) const {
			return other.currentElement == currentElement;
		}
		bool operator!=(const ConstIterator& other) const {
			return !(*this == other);
		}
		friend class Vector<T>;
	};
	ConstIterator cbegin() const
	{
		if (empty())
		{
			throw std::logic_error("Vector was empty");
		}

		return ConstIterator(&data[0]);
	}
	ConstIterator cend() const {
		return ConstIterator(data + size);
	}
};

template<typename T>
void Vector<T>::copyFrom(const Vector<T> other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];
	for (size_t i = 0; i < size; i++)
		data[i] = other.data[i];
}

template<typename T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;

	data = other.data;
	other.data = nullptr;
}

template<typename T>
void Vector<T>::free()
{
	delete[] data;
}

template<typename T>
void Vector<T>::resize(size_t newCapcity)
{
	capacity = newCapcity;

	T* newData = new T[capacity];
	for (size_t i = 0; i < size; i++)
		newData[i] = std::move(data[i]); // faster than copying!

	delete[] data;
	data = newData;
}

template<typename T>
void Vector<T>::upsizeIfNeeded()
{
	if (size == capacity)
	{
		resize(capacity * RESIZE_COEF);
	}
}

template<typename T>
void Vector<T>::downsizeIfNeeded()
{
	if (size * RESIZE_COEF * RESIZE_COEF <= capacity)
	{
		resize(capacity / RESIZE_COEF);
	}
}

template<typename T>
Vector<T>::Vector() : Vector(INITIAL_CAPACITY)
{
}

template<typename T>
Vector<T>::Vector(size_t capacity) : capacity(capacity)
{
	data = new T[capacity];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
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
Vector<T>::Vector(Vector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
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
size_t Vector<T>::getSize() const
{
	return size;
}

template<typename T>
void Vector<T>::pushBack(const T& element)
{
	upsizeIfNeeded();
	data[size++] = element;
}

template<typename T>
void Vector<T>::pushBack(T&& element)
{
	upsizeIfNeeded();
	data[size++] = std::move(element);
}

template<typename T>
void Vector<T>::pushAt(size_t idx, const T& element)
{
	if (idx > size)
	{
		throw std::out_of_range("Index was out of range!");
	}

	upsizeIfNeeded();

	for (size_t i = size; i > idx; i--)
	{
		data[i] = std::move(data[i - 1]);
	}

	data[idx] = element;
	size++;
}

template<typename T>
void Vector<T>::pushAt(size_t idx, T&& element)
{
	if (idx > size)
	{
		throw std::out_of_range("Index was out of range!");
	}

	upsizeIfNeeded();

	for (size_t i = size; i > idx; i--)
	{
		data[i] = std::move(data[i - 1]); // faster than copying!
	}
	
	data[idx] = std::move(element);
	size++;
}

template<typename T>
T Vector<T>::popBack()
{
	if (empty())
	{
		throw std::logic_error("Vector is already empty!");
	}

	downsizeIfNeeded();

	return data[--size];
}

template<typename T>
T Vector<T>::popAt(size_t idx)
{
	if (idx >= size)
	{
		throw std::out_of_range("Index was out of range!");
	}

	downsizeIfNeeded();

	T temp = data[idx];

	size--;
	for (size_t i = idx; i < size; i++)
	{
		data[i] = std::move(data[i + 1]); // faster than copying!
	}

	return temp;
}

template<typename T>
bool Vector<T>::contains(const T& element)
{
	for (size_t i = 0; i < size; i++)
	{
		if (data[i] == element)
		{
			return true;
		}
	}
	
	return false;
}

template<typename T>
bool Vector<T>::empty() const
{
	return size == 0;
}

template<typename T>
void Vector<T>::clear()
{
	delete[] data;
	data = new T[INITIAL_CAPACITY];

	size = 0;
}

template<typename T>
T& Vector<T>::operator[](size_t idx)
{
	if (idx >= size)
	{
		throw std::out_of_range("Index was out of range!");
	}

	return data[idx];
}

template<typename T>
const T& Vector<T>::operator[](size_t idx) const
{
	if (idx >= size)
	{
		throw std::out_of_range("Index was out of range!");
	}

	return data[idx];
}