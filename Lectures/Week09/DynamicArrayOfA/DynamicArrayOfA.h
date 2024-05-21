#pragma once
#include <iostream>

struct A {
	int a = 4;
	int b = 5;
};

class DynamicArray
{
private:
	A* data;
	size_t size;
	size_t capacity;
	
	void free();
	void copyFrom(const DynamicArray& other);
	void moveFrom(DynamicArray&& other);

	void resize(size_t newCap);

public:
	DynamicArray();
	DynamicArray(size_t _size);
	DynamicArray(const DynamicArray& other);
	DynamicArray(DynamicArray&& other) noexcept;

	DynamicArray& operator=(const DynamicArray& other);
	DynamicArray& operator=(DynamicArray&& other) noexcept;

	~DynamicArray() noexcept;

	void pushBack(const A& newElem);
	void pushBack(A&& newElem);

	void popBack();

	void setAtIndex(const A& element, size_t index);
	void setAtIndex(A&& element, size_t index);

	size_t getSize() const;
	bool isEmpty() const;

	const A& operator[](size_t index) const;
	A& operator[](size_t index);
};

size_t nextPowerOfTwo(size_t n);

