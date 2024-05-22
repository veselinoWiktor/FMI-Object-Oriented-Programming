#include "MyString.h"
#include <iostream>

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	data = new char[size + 1];
	strcpy(data, other.data);
}

void MyString::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
}

MyString::MyString(const char* _data)
{
	size = strlen(_data);
	data = new char[size + 1];
	strcpy(data, _data);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

MyString::~MyString()
{
	free();
}

size_t MyString::length() const
{
	return size;
}

const char* MyString::c_str() const
{
	return data;
}
