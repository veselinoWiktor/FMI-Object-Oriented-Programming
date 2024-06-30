#include <iostream>

class Base {};

class Der1 : public Base {};
class Der2 : public Base {};

//Factory Method start
class BaseFactory
{
public:
	virtual Base* create() const = 0;
	virtual ~BaseFactory() = default;
};

class Der1Factory : public BaseFactory
{
public:
	Base* create() const override
	{
		return new Der1();
	}
};

class Der2Factory : public BaseFactory
{
public:
	Base* create() const override
	{
		return new Der2();
	}
};
//Factory Method end

//Normal Factory
BaseFactory* createFactory(bool useDer1)
{
	if (useDer1)
		return new Der1Factory();
	else
		return new Der2Factory();
}

void runApp(BaseFactory* factory)
{
	//do something
}

int main()
{
	BaseFactory* factory = createFactory(true);
	runApp(factory);
	delete factory;
}
