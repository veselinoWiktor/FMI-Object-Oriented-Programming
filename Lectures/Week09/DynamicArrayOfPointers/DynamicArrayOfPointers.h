#pragma once

struct A
{
	int x = 3;
	int y = 2;
};

class DynamicArrayOfPointers
{
private:
	A** data = nullptr;
	size_t capacity = 0;
	size_t count = 0;

	void free();
	void copyFrom(const DynamicArrayOfPointers& other);
	void moveFrom(DynamicArrayOfPointers&& other);

	void resize(size_t newCapacity);

	int getFirstFreeIndex() const;
public:
	DynamicArrayOfPointers();
	DynamicArrayOfPointers(const DynamicArrayOfPointers& other);
	DynamicArrayOfPointers(DynamicArrayOfPointers&& other) noexcept;

	DynamicArrayOfPointers& operator=(const DynamicArrayOfPointers& other);
	DynamicArrayOfPointers& operator=(DynamicArrayOfPointers&& other) noexcept;

	~DynamicArrayOfPointers() noexcept;

	void addAtFirstFreeIndex(const A& newElem);
	void addAtFirstFreeIndex(A&& newElem);

	void setAtIndex(const A& obj, size_t index);
	void setAtIndex(A&& obj, size_t index);

	void pop_back();
	void removeAt(size_t index);

	bool containsAt(size_t index) const;

	size_t size() const;

	const A& operator[](size_t index) const;
	A& operator[](size_t index);

};

