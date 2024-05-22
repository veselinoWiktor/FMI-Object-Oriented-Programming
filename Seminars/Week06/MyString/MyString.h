#pragma once

class MyString
{
private:
	char* data = nullptr;
	size_t size = 0;

	void copyFrom(const MyString& other);
	void free();

public:
	MyString() = default;
	MyString(const char* _data);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	size_t length() const;
	const char* c_str() const;
};