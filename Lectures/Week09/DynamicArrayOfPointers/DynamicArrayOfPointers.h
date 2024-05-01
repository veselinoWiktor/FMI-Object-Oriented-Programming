#pragma once

struct A
{
	int x = 3;
	int y = 2;
};

class DynamicArrayOfPointers
{
private:
	A** _data;
	size_t _capacity;
	size_t _count;

	void free();
	void copyFrom(const DynamicArrayOfPointers& other);
	void moveFrom(DynamicArrayOfPointers&& other);

	void resize(size_t newCapacity);

public:
	DynamicArrayOfPointers();
	DynamicArrayOfPointers(const DynamicArrayOfPointers& other);
	DynamicArrayOfPointers(DynamicArrayOfPointers&& other) noexcept;

	DynamicArrayOfPointers& operator=(const DynamicArrayOfPointers& other);
	DynamicArrayOfPointers& operator=(DynamicArrayOfPointers&& other) noexcept;

	~DynamicArrayOfPointers() noexcept;
};

