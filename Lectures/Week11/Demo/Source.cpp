#include <iostream>

class Base
{
public:
	virtual void f()
	{
		std::cout << "Base::f()";
	}
};

class Der : public Base
{
public:
	void f()
	{
		std::cout << "Der::f()";
	}
};

int main()
{
	Der d;
	d.f();
	Base* ptr = &d;
	ptr->f();
}