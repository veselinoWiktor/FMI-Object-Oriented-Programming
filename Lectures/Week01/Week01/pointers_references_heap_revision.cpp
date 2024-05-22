#include "pointers_references_heap_revision.h"
#include <iostream>

void example01()
{
	int a = 7;
	int* ptr = new int(18); //heap memory

	delete ptr; //free heap memory
}

void example02()
{
	int a = 7;
	int* ptr = &a;
	
	delete ptr; //compile time error, cannot delete static memory;
}

void example03()
{
	int arr[10]; //here should always stay constexpr value, or literal.
	int n;
	std::cin >> n;
	int* ptr = new int[n]; //here should always stay runtime defined value.
	delete[] ptr; //for array allocated memory, should always free memory with delete[]
}

void example04(int a)// here the value of a passed by copy
{
	a++; //increments the copy of a
}// here the copy will be removed

void example05(int& a) // a is passed by reference
{
	a++; //increment the value of the outside a
}

void example06(int* p) //p is pointer
{
	if (!p)
		return;

	(*p)--; //the value at address of p is decrease by one;
}
