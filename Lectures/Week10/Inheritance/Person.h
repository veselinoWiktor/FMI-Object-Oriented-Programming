#pragma once
#pragma warning (disable:4996)
#include <iostream>

class Person
{
private:
	char* name = nullptr;
	unsigned age = 0;

	void copyFrom(const Person& other);
	void moveFrom(Person&& other);
	void free();

protected:
	void setName(const char* name);
	void setAge(unsigned age);

public:
	Person() = default;
	Person(const char* name, unsigned age);
	Person(const Person& other);
	Person(Person&& other) noexcept;
	Person& operator=(const Person& other);
	Person& operator=(Person&& other) noexcept;
	~Person();

	const char* getName() const;
	unsigned getAge() const;

	void print() const;
};

