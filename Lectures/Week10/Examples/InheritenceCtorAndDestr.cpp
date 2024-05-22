#include <iostream>

class Base
{
private:
	int x;
public:
	Base() : x(0)
	{
		std::cout << "Base()" << std::endl;
	}

	Base(int x) : x(x)
	{
		std::cout << "Base(int x)" << std::endl;
;	}
	
	~Base()
	{
		std::cout << "~Base()" << std::endl;
	}
};

class A
{
public:
	A()
	{
		std::cout << "A()" << std::endl;
	}

	~A()
	{
		std::cout << "~A()" << std::endl;
	}
};

class B
{
public:
	B()
	{
		std::cout << "B()" << std::endl;
	}

	~B()
	{
		std::cout << "~B()" << std::endl;
	}
};

class C
{
public:
	C()
	{
		std::cout << "C()" << std::endl;
	}

	~C()
	{
		std::cout << "~C()" << std::endl;
	}
};

class Der : public Base
{
	int y;
	A obj1;
	B obj2;
	C obj3;
public:
	Der() : Base(), y(0), obj1(), obj2(), obj3()
	{
		std::cout << "Der()" << std::endl;
	}

	Der(int x, int y) : Base(x), y(0)
	{
		std::cout << "Der(int x, int y)" << std::endl;
	}

	~Der()
	{
		std::cout << "~Der()" << std::endl;
	}
};

int main()
{
	Der d(1,2);
}