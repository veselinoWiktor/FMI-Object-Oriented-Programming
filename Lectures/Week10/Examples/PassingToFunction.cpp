#include <iostream>

class Base
{
public:
	Base()
	{
		std::cout << "Base()" << std::endl;
	}

	Base(const Base& other)
	{
		std::cout << "Base(const Base&)" << std::endl;
	}

	Base(Base&& other) noexcept
	{
		std::cout << "Base(Base&&)" << std::endl;
	}

	Base& operator=(const Base& other)
	{
		std::cout << "operator=(const Base&)" << std::endl;
	}

	Base& operator=(Base&& other) noexcept
	{
		std::cout << "operator=(Base&&)" << std::endl;
	}

	~Base()
	{
		std::cout << "~Base()" << std::endl;
	}
};

class Der : public Base
{
public:
	Der() : Base() //By default calls the default ctor of Base, so : Base() is unnessecary
	{
		std::cout << "Der()" << std::endl;
	}

	Der(const Der& other) : Base(other)
	{
		std::cout << "Der(const Der&)" << std::endl;
	}

	Der(Der&& other) noexcept : Base(std::move(other))
	{
		std::cout << "Der(Der&&)" << std::endl;
	}

	Der& operator=(const Der& other)
	{
		if (this != &other)
		{
			Base::operator=(other);
			std::cout << "operator=(const Der&)" << std::endl;
		}

		return *this;
	}

	Der& operator=(Der&& other) noexcept
	{
		if (this != &other)
		{
			Base::operator=(std::move(other));
			std::cout << "operator=(Der&&)" << std::endl;
		}

		return *this;
	}

	~Der()
	{
		std::cout << "~Der()" << std::endl;
		// call the ~Base() after it finishes
	}
};

void acceptBaseCopy(Base base) {};
void acceptDerCopy(Der der) {};
void acceptBase(const Base& base) {};
void acceptDer(const Der& der) {};
void acceptBasePtr(const Base* basePtr) {};
void acceptDerPtr(const Der* derPtr) {};

static void exmapleMain() {
	Base a;
	Der b;

	acceptBaseCopy(a);
	acceptBaseCopy(b);
	acceptDerCopy(b);

	acceptBase(a);
	// only if b has inherited a as public
	acceptBase(b);
	acceptDer(b);

	acceptBasePtr(&a);
	acceptBasePtr(&b); // address of the derived is the same as the base

	// acceptDerPtr(&a);
	acceptDerPtr(&b);
}