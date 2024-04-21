#pragma once

class String
{
private:
	char* data;
	unsigned length;
	unsigned capacity;

	void free();
	void copyFrom(const String& other);
	void moveFrom(String&& other);
public:
	String();
	String(const char* str);
	String(const String& other);
	String(String&& other) noexcept;
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	~String();
};

unsigned nextPowerOfTwo(unsigned num)
{
	unsigned step = 1;

	while ((num >> step) > 0)
	{
		num |= (num >> step);
		step <<= 1;
	}

	return num + 1;
}

