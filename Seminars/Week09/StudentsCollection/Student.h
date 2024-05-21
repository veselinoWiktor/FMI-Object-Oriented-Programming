#pragma once
#include "String.h"

class Student
{
private:
	String name;
	unsigned age;

public:
	Student();
	Student(const String& name, unsigned age);

	const String& getName() const;
	unsigned getAge() const;

};

