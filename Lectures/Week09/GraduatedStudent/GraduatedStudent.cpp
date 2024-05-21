#include "GraduatedStudent.h"
#pragma warning (disable : 4996)

void GraduatedStudent::copyFrom(const GraduatedStudent& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	gradesCount = other.gradesCount;
	grades = new int[gradesCount];
	for (size_t i = 0; i < gradesCount; i++)
	{
		grades[i] = other.grades[i];
	}

	strcpy(quote, other.quote);
}

void GraduatedStudent::moveFrom(GraduatedStudent&& other)
{
	name = other.name;
	other.name = nullptr;

	gradesCount = other.gradesCount;
	other.grades = 0;

	grades = other.grades;
	other.grades = nullptr;

	strcpy(quote, other.quote);
	strcpy(other.quote, "");
}

void GraduatedStudent::free()
{
	delete[] name;
	delete[] grades;
}

GraduatedStudent::GraduatedStudent(const char* name, const int* grades, size_t gradesCount, const char* quote)
{
	setName(name);
	setGrades(grades, gradesCount);
	setQuoute(quote);
}

GraduatedStudent::GraduatedStudent(const GraduatedStudent& other)
{
	copyFrom(other);
}

GraduatedStudent::GraduatedStudent(GraduatedStudent&& other)
{
	moveFrom(std::move(other));
}

GraduatedStudent& GraduatedStudent::operator=(const GraduatedStudent& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

GraduatedStudent& GraduatedStudent::operator=(GraduatedStudent&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

void GraduatedStudent::setName(const char* newName)
{
	if (!newName || name == newName) // setName(getName())!!!!
	{
		return;
	}
	delete[] name;
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}

void GraduatedStudent::setGrades(const int* newGrades, size_t newGradesCount)
{
	if (!newGrades || grades == newGrades)
	{
		return;
	}

	delete[] grades;
	gradesCount = newGradesCount;
	grades = new int[gradesCount];

	for (size_t i = 0; i < gradesCount; i++)
	{
		grades[i] = newGrades[i];
	}
}

void GraduatedStudent::setQuoute(const char* newQuote)
{
	if (!newQuote || strlen(newQuote) > 30)
	{
		return;
	}

	strcpy(quote, newQuote);
}

const char* GraduatedStudent::getName() const
{
	return name;
}

const int* GraduatedStudent::getGrades() const
{
	return grades;
}

size_t GraduatedStudent::getGradesCount() const
{
	return gradesCount;
}

const char* GraduatedStudent::getQuote() const
{
	return quote;
}
