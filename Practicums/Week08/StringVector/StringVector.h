#pragma once
#include "String.h"

class StringVector
{
private:
	String* data = nullptr;
	unsigned capacity = 0;
	unsigned size = 0;

	void free();
	void copyFrom(const StringVector& other);

	void resize();

	void setSize(unsigned _size);
	void setCapacity();
	void initData(const String* strings);

	void shiftLeftByOne(unsigned atIdx);
	void shiftRightByOne(unsigned atIdx);
public:
	StringVector(const String* strings, unsigned _size);
	StringVector(const StringVector& other);
	StringVector& operator=(const StringVector& other);
	~StringVector();

	unsigned getSize() const;
	bool isEmpty() const;
	unsigned push_back(const String& str);
	void pop_back();

	void erase(unsigned idx);
	void insert(const String& str, unsigned idx);

	void clear();

	String& operator[](unsigned idx);
	const String& operator[](unsigned idx) const;
};