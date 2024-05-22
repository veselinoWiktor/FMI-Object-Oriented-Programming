#pragma once

class MultiSet
{
private:
	unsigned char* set = nullptr;
	size_t maxNum = 0;

	void copyFrom(const MultiSet& other);
	void free();

	size_t getArrSize(int n);
	size_t getBucket(int n);
	size_t getIndex(int n);
	int getCount(int n);
public:
	MultiSet() = default;
	MultiSet(size_t maxNum);
	MultiSet(const MultiSet& other);
	~MultiSet();
	MultiSet& operator=(const MultiSet& other);

	void add(unsigned num);
	void erase(unsigned num);
	int get(unsigned num);
	void print();

	MultiSet sectionSet(const MultiSet& first, const MultiSet& second);
	MultiSet unionSet(const MultiSet& first, const MultiSet& second);
};