#pragma once

struct A {
	int a = 4;
	int b = 5;
};

class DynamicArray
{
private:
	A* arr;
	size_t size;
	size_t capacity;
	
	void free();
	void copyFrom(const DynamicArray& other);
	void moveFrom(DynamicArray&& other);

	void resize(size_t newCap);

public:
	DynamicArray();
	DynamicArray(size_t _capacity);
	DynamicArray(const DynamicArray& other);
	DynamicArray(DynamicArray&& other) noexcept;

	DynamicArray& operator=(const DynamicArray& other);
	DynamicArray& operator=(DynamicArray&& other) noexcept;

	~DynamicArray() noexcept;
};

size_t nextPowerOfTwo(size_t n);

