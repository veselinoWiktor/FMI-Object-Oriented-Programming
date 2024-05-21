#include "StudentCollection.h"

void StudentCollection::copyFrom(const StudentCollection& other)
{
	size = other.size;
	capacity = other.capacity;
	count = other.count;
	firstFreeIndex = other.firstFreeIndex;

	students = new Student * [capacity];
	for (size_t i = 0; i < size; i++)
	{
		if (!other.students[i])
		{
			students[i] = nullptr; //this check
		}
		else
		{
			students[i] = new Student(*other.students[i]); //!!!
		}
	}
}

void StudentCollection::moveFrom(StudentCollection&& other)
{
	size = other.size;
	capacity = other.capacity;
	count = other.count;
	firstFreeIndex = other.firstFreeIndex;
	other.size = other.capacity = other.count = other.firstFreeIndex = 0;

	students = other.students;
	other.students = nullptr;
}

void StudentCollection::free()
{
	for (size_t i = 0; i < size; i++)
	{
		delete students[i];
	}
	delete[] students;
}

void StudentCollection::resize(size_t newCap)
{
	capacity = newCap;
	Student** temp = new Student * [capacity];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = students[i];
	}
	delete[] students;
	students = temp;
}

void StudentCollection::goToNextFreeIndex()
{
	for (size_t i = firstFreeIndex + 1; i < capacity; i++)
	{
		if (!students[i])
		{
			firstFreeIndex = i;
			return;
		}
	}
	firstFreeIndex = capacity;
}

size_t StudentCollection::getLastFreeIndex() const
{
	for (size_t i = size - 1; i >= 0; i--)
	{
		if (!students[i])
		{
			return i + 1; //why?
		}
	}
	return 0;
}

StudentCollection::StudentCollection() : capacity(16)
{
	students = new Student * [capacity] {nullptr}; //don't forget nullptr
}

StudentCollection::StudentCollection(const StudentCollection& other)
{
	copyFrom(other);
}

StudentCollection::StudentCollection(StudentCollection&& other) noexcept
{
	moveFrom(std::move(other));
}

StudentCollection& StudentCollection::operator=(const StudentCollection& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

StudentCollection& StudentCollection::operator=(StudentCollection&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

StudentCollection::~StudentCollection()
{
	free();
}

unsigned StudentCollection::addAtFirstFree(const Student& student)
{
	if (count == capacity)
	{
		resize(capacity * 2);
	}

	students[firstFreeIndex] = new Student(student);
	count++;
	goToNextFreeIndex();

	if (firstFreeIndex >= size)
	{
		size++; //why?
	}
}

unsigned StudentCollection::addAtFirstFree(Student&& student)
{
	if (count == capacity)
	{
		resize(capacity * 2);
	}

	students[firstFreeIndex] = new Student(std::move(student));
	count++;
	goToNextFreeIndex();

	if (firstFreeIndex >= size)
	{
		size++; //why?
	}
}

void StudentCollection::setAtIdx(const Student& student, size_t idx)
{
	while (idx >= capacity)
	{
		resize(capacity * 2);
	}

	if (students[idx] == nullptr)
	{
		students[idx] = new Student(student);
		count++;

		if (idx == firstFreeIndex)
		{
			goToNextFreeIndex();
		}
	}
	else
	{
		*students[idx] = student; //Here we already have a student so we need op=
	}

	if (idx >= size)
	{
		size = idx + 1;//Why?
	}
}

void StudentCollection::setAtIdx(Student&& student, size_t idx)
{
	while (idx >= capacity)
	{
		resize(capacity * 2);
	}

	if (students[idx] == nullptr)
	{
		students[idx] = new Student(std::move(student));
		count++;

		if (idx == firstFreeIndex)
		{
			goToNextFreeIndex();
		}
	}
	else
	{
		*students[idx] = std::move(student); //Here we already have a student so we need op=
	}

	if (idx >= size)
	{
		size = idx + 1;//Why?
	}
}

void StudentCollection::removeAtIdx(size_t idx)
{
	if (idx >= size)
	{
		throw std::out_of_range("StudentCollection::removeAtIdx(); Index was out of range!");
	}

	if (students[idx] != nullptr)
	{
		count--;
		delete students[idx];
		students[idx] = nullptr;

		if (idx < firstFreeIndex)
		{
			firstFreeIndex = idx;
		}

		size = getLastFreeIndex();
	}

	if (size * 4 <= capacity)
	{
		resize(capacity / 2);
	}
}

bool StudentCollection::containsAt(size_t idx) const
{
	return idx <= capacity && students[idx] != nullptr;
}

size_t StudentCollection::getNumberInClass(const String& name) const
{
	for (size_t i = 0; i < capacity; i++)
	{
		if (students[i] != nullptr && name == students[i]->getName())
		{
			return i + 1;
		}
	}

	throw std::invalid_argument("No such student!");
}




