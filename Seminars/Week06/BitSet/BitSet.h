#pragma once

class BitSet
{
	unsigned char* data = nullptr;
	unsigned maxNumber = 0;

	void copyFrom(const BitSet& other);
	void free();

	unsigned getBucketIndex(unsigned n) const;
	unsigned getBucketCount() const;
	unsigned getMask(unsigned n) const;

public:
	BitSet() = default;
	BitSet(unsigned max);
	BitSet(const BitSet& other);
	BitSet& operator=(const BitSet& other);
	~BitSet();

	bool add(unsigned n);
	bool remove(unsigned n);
	bool contains(unsigned n) const;
	void print() const;
};