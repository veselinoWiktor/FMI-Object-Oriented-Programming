#pragma once
#include <fstream>

class String
{
private:
	char* data;
	unsigned length;
	unsigned capacity;

	void free();
	void copyFrom(const String& other);
	void moveFrom(String&& other);

	void resize();

	explicit String(unsigned length);
public:
	String();
	String(const char* str);
	String(const String& other);
	String(String&& other) noexcept;
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	~String();

	unsigned getLength() const;
	const char* c_str() const;

	String& operator+=(const String& other);

	char& operator[](unsigned idx);
	const char& operator[](unsigned idx) const;

	friend std::ostream& operator<<(std::ostream& os, const String& obj);
	friend std::istream& operator>>(std::istream& is, String& obj);
	friend String operator+(const String& lhs, const String& rhs);
};

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);

unsigned nextPowerOfTwo(unsigned num);

