#pragma once
#include "Person.h"

class Student : public Person
{
private:
	size_t fn = 0;
public:
	Student() = default;
	Student(const char* name, unsigned age, size_t fn);

	size_t getFn() const;
	void setFn(size_t fn);
};

