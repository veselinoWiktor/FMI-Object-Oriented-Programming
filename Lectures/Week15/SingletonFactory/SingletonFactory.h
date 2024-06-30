#pragma once
#include <iostream>
#include <fstream>

class Base {
public:
	virtual ~Base() = default;
};
class Der1 : public Base {};
class Der2 : public Base {};

class SingletonFactory
{
private:
	SingletonFactory();
	~SingletonFactory();
	
	size_t current = 0;
	size_t numbersCount = 0;
	size_t* numbers = nullptr;

public:
	Base* create();

	static SingletonFactory& getInstance();

	SingletonFactory(const SingletonFactory&) = delete;
	SingletonFactory& operator=(const SingletonFactory&) = delete;
};

