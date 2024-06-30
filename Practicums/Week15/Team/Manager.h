#pragma once
#include "Employee.h"
class Manager : public Employee
{
private:
	char* position;

	Worker** subordinates;
	size_t size;
	size_t capacity;

	void copyFrom(const Manager& other);
	void moveFrom(Manager&& other);
	void free();

	void resize(size_t newCapacity);
public:
	Manager(const char* name, double salary, const char* position);
	Manager(const Manager& other);
	Manager& operator=(const Manager& other);
	Manager(Manager&& other) noexcept;
	Manager& operator=(Manager&& other) noexcept;
	~Manager();

	void addSubordinate(Worker* subordinate);
	void print() const override;
	size_t getWorkers() const override;
	Worker* clone() const override;
};

