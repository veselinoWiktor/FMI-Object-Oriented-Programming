#pragma once
#include <iostream>

template<typename T>
class Optional {
private:
	T* value = nullptr;

	void copyFrom(const Optional<T>& other);
	void moveFrom(Optional<T>&& other);
	void free();
public:
	Optional() = default;
	Optional(const T& value);
	Optional(const Optional<T>& other);
	Optional(Optional<T>&& other) noexcept;
	Optional<T>& operator=(const Optional<T>& other);
	Optional<T>& operator=(Optional<T>&& other) noexcept;
	~Optional();

	bool hasValue() const;
	const T& getValue() const;
	void setValue(const T& newValue);
	void setValue(T&& newValue);
	void clear();
};

template<typename T>
void Optional<T>::copyFrom(const Optional<T>& other)
{
	if (other.hasValue())
	{
		this->value = new T(other.value);
	}
	else
	{
		this->value = nullptr;
	}
}

template<typename T>
void Optional<T>::moveFrom(Optional<T>&& other)
{
	value = other.value;
	other.value = nullptr;
}

template<typename T>
void Optional<T>::free()
{
	delete value;
}

template<typename T>
Optional<T>::Optional(const T& value)
{
	this->value = new T(value);
}

template<typename T>
Optional<T>::Optional(const Optional<T>& other)
{
	copyFrom(other);
}

template<typename T>
Optional<T>::Optional(Optional<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
Optional<T>& Optional<T>::operator=(const Optional<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Optional<T>& Optional<T>::operator=(Optional<T>&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template<typename T>
Optional<T>::~Optional()
{
	free();
}

template<typename T>
bool Optional<T>::hasValue() const
{
	return value != nullptr;
}

template<typename T>
const T& Optional<T>::getValue() const
{
	return value;
}

template<typename T>
void Optional<T>::setValue(const T& newValue)
{
	if (hasValue(value))
	{
		clear();
	}
	value = new T(newValue);
}

template<typename T>
void Optional<T>::setValue(T&& newValue)
{
	if (hasValue(value))
	{
		clear();
	}
	value = new T(std::move(newValue));
}

template<typename T>
void Optional<T>::clear()
{
	free();
}
