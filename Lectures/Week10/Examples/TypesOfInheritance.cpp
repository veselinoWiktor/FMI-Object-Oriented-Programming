#include <iostream>

class X
{
private:
	int a = 0;
protected:
	int b = 0;
public:
	int c = 0;
};

class Base : public X {
	//void f() { std::cout << a; } // Don't have acces to private X::a
	void g() { std::cout << b; } // X::b remains protected
	void h() { std::cout << c; } // X::c remains public
};

class B : protected X
{
	//void f() { std::cout << a; } // Don't have access to private X::a
	void g() { std::cout << b; } // X::b remains protected
	void h() { std::cout << c; } // X::c becomes protected for C
};

class C : private X
{
	//void f() { std::cout << a; } // Don't have access to private X::a
	void g() { std::cout << b; } // X::b becomse private for C
	void h() { std::cout << c; } // X::c becomes private for C
};

class Y : private X
{
	//void f() { std::cout << a; } // Don't have access to private X::a
	void g() { std::cout << b; } // X::b becomse private for Y
	void h() { std::cout << c; } // X::c becomes private for Y
};

class Z : public Y
{
	//void f() { std::cout << a; } // Don't have access to private Y::a
	//void g() { std::cout << b; } // Don't have access to private Y::b
	//void h() { std::cout << c; } // Don't have access to private Y::c
};

static int exampleMain()
{
	Base publicDerived;
	B protectedDerived;
	C privateDerived;
	Z publicOfPrivateDerived;

	//publicDerived.a;		// inacessible
	//publicDerived.b;		// protected for the class
	publicDerived.c;		// public for the class

	// protectedDerived.a;  // inaccessible
	// protectedDerived.b;  // protected for the class
	// protectedDerived.c;  // protected for the class

	// privateDerived.a;	// inaccessible
	// privateDerived.b;	// private for the class
	// privateDerived.c;	// private for the class

	// publicOfPrivateDerived.a;	// inaccessible
	// publicOfPrivateDerived.b;	// inaccessible
	// publicOfPrivateDerived.c;	// inaccessible

	return 0;
}