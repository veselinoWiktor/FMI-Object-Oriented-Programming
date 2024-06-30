#pragma once
#include <iostream>

class Function
{
private:
	unsigned int* data;
	size_t size;

	void copyFrom(const Function& other);
	void moveFrom(Function&& other);
	void free();

public:
	Function();
	Function(unsigned int* data, size_t size);
	Function(const unsigned int* data, size_t size);
	Function(const Function& other);
	Function(Function&& other) noexcept;
	Function& operator=(const Function& other);
	Function& operator=(Function&& other) noexcept;
	~Function();

	bool contains(unsigned int x) const;
	bool operator()(unsigned int x) const;
};