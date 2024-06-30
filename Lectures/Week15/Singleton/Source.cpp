#include "Singleton.h"

int main() {
	{
		std::cout << "hello";
		Singleton& s1 = Singleton::getInstance();
	}
	Singleton& s2 = Singleton::getInstance();
	s2.doStuff();
	Singleton& s3 = Singleton::getInstance();
	s3.doStuff();
	Singleton& s4 = Singleton::getInstance();
}