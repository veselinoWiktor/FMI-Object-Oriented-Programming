#pragma once

class SelfCounting
{
private:

	//a constant, which may be different
	//for different objects
	//so it is "per object"
	const int const_val;

	static unsigned liveObjectsCount;
	static unsigned createdCount;

public:
	SelfCounting();
	SelfCounting(int val);
	SelfCounting(const SelfCounting& other);
	~SelfCounting();

	static unsigned getLiveObjectsCount();
	static unsigned getCreatedCount();
};

