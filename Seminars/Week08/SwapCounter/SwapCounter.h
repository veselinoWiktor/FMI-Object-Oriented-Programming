#pragma once

struct SwapCounter
{
private:
	static unsigned count;
public:
	static void swap(int& a, int& b);

	static int getCount();
	static void resetCount();
};

