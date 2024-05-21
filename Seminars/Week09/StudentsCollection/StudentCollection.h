#pragma once
#include "Student.h"

class StudentCollection
{
private:
	Student** students;
	size_t count = 0;
	size_t capacity;

	size_t size = 0;
	size_t firstFreeIndex = 0;

	void copyFrom(const StudentCollection& other);
	void moveFrom(StudentCollection&& other);
	void free();

	void resize(size_t newCap);

	void goToNextFreeIndex();
	size_t getLastFreeIndex() const;

public:
	StudentCollection();

	StudentCollection(const StudentCollection& other);
	StudentCollection(StudentCollection&& other) noexcept;

	StudentCollection& operator=(const StudentCollection& other);
	StudentCollection& operator=(StudentCollection&& other) noexcept;

	~StudentCollection();

	unsigned addAtFirstFree(const Student& student);
	unsigned addAtFirstFree(Student&& student);

	void setAtIdx(const Student& student, size_t idx);
	void setAtIdx(Student&& student, size_t idx);

	void removeAtIdx(size_t idx);

	bool containsAt(size_t idx) const;
	size_t getNumberInClass(const String& name) const;
};

