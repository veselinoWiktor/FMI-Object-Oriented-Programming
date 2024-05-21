#pragma once
#include <iostream>

struct A {
	int a;
	int b;
};

class UniquePointer
{
private:
	A* ptr;

	void free();
	void moveFrom(UniquePointer&& other);

public:
	UniquePointer(A* pointer);

	UniquePointer(const UniquePointer& other) = delete;
	UniquePointer(UniquePointer&& other) noexcept;

	UniquePointer& operator=(const UniquePointer& other) = delete;
	UniquePointer& operator=(UniquePointer&& other) noexcept;

	~UniquePointer() noexcept;

	const A& operator*() const;
	A& operator*();
};

