#pragma once
#include <iostream>

class Singleton
{
private:
	Singleton();
	~Singleton();
public:
	static Singleton& getInstance();

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	void doStuff() const;
};

