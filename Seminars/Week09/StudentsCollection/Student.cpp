#include "Student.h"

Student::Student() : name("empty"), age(0)
{
}

Student::Student(const String& name, unsigned age) : name(name), age(age)
{
}

const String& Student::getName() const
{
	return name;
}

unsigned Student::getAge() const
{
	return age;
}


