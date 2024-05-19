#pragma once
#include <iostream>

class String
{
private:
	char* _data;
	size_t _size;
	size_t _capacity;

	void resize(size_t newCapacity);

	void copyFrom(const String& other);
	void free();

public:
	String();
	String(const char* data);

	String(const String& other);
	String& operator=(const String& other);
	~String();

	size_t getCapacity() const;
	size_t getSize() const;
	const char* c_str() const;

	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	String& operator+=(const String& other);

	friend std::istream& operator>>(std::istream& is, String& obj);
	friend std::ostream& operator<<(std::ostream& os, const String& obj);
};

String operator+(const String& lhs, const String& rhs);

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);


