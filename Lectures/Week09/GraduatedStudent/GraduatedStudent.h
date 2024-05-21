#pragma once
#include <iostream>

class GraduatedStudent
{
private:
	char* name = nullptr;
	int* grades = nullptr;
	size_t gradesCount = 0;
	char quote[30 + 1] = "";

	void copyFrom(const GraduatedStudent& other);
	void moveFrom(GraduatedStudent&& other);
	void free();

public:
	GraduatedStudent(const char* _name,
		const int* _grades,
		size_t _gradesCount,
		const char* _quote);

	GraduatedStudent(const GraduatedStudent& other);
	GraduatedStudent(GraduatedStudent&& other);

	GraduatedStudent& operator=(const GraduatedStudent& other);
	GraduatedStudent& operator=(GraduatedStudent&& other);

	void setName(const char* newName);
	void setGrades(const int* newGrades, size_t newGradesCount);
	void setQuote(const char* newQuote);

	const char* getName() const;
	const int* getGrades() const;
	size_t getGradesCount() const;
	const char* getQuote() const;
};

std::ostream& operator<<(std::ostream& os, const GraduatedStudent& obj);
