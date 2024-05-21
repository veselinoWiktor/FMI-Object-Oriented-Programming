#pragma once
#include <iostream>
#include "String.h"

class StringVector
{
	String* data;
	size_t size;
	size_t capacity;

	void copyFrom(const StringVector& other);
	void moveFrom(StringVector&& other);
	void free();

	void resize(size_t newCapacity);

	void shiftLeft(size_t index);
	void shiftRight(size_t index);
public:
	StringVector();
	StringVector(const String* strings, size_t count);
	StringVector(const StringVector& other);
	StringVector(StringVector&& other) noexcept;

	StringVector& operator=(const StringVector& other);
	StringVector& operator=(StringVector&& other) noexcept;

	~StringVector() noexcept;

	void push_back(const String& string);
	void push_back(String&& string);

	void pop_back();

	void insert(const String& string, size_t index);
	void insert(String&& string, size_t index);

	void erase(size_t index);

	void clear();

	const String& operator[](size_t index) const;
	String& operator[](size_t index);

	bool isEmpty() const;
	size_t count() const;
};

