#include <iostream>

class Base
{
public:
	int x = 0; // (2)
	void f() {};
private:
	int y = 0;
};

class Der : public Base
{
public:
	void g()
	{
		f();
		//y++; // can't access Base::y because it's in private memebers
		x--; // will decrease (1)
		Base::x--; // will decrease (2)
	}
	int x = 0; //(1)
	// this x shadows the x in Base;
};

static int exampleMain()
{
	Der obj;
	obj.g();
	std::cout << obj.Base::x << obj.x;
	//first print Base::x than Der::x;

	return 1;
}