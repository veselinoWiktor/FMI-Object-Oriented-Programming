#include <iostream>
//
//struct A {
//	A() {
//		std::cout << "A()" << std::endl;
//	}
//
//	A(const A& other)
//	{
//		std::cout << "CC of A()" << std::endl;
//	}
//
//	A(A&& other) noexcept
//	{
//		std::cout << "MC of A()" << std::endl;
//	}
//
//	A& operator=(const A& other)
//	{
//		std::cout << "C op= of A()" << std::endl;
//	}
//
//	A& operator=(A&& other) noexcept
//	{
//		std::cout << "M op= of A()" << std::endl;
//	}
//	 
//	~A()
//	{
//		std::cout << "~A()" << std::endl;
//	}
//};
//
//void f(A obj) {};
//void g(A& obj) {};
//void h(const A& obj) {};
//void t(A&& obj) {};
//
//int main()
//{
//	A obj;
//
//	std::cout << "---------------" << std::endl;
//
//	f(obj); //CC of A(); ~A();
//	g(obj); //nothing nothing;
//	h(obj); //nothing nothing
//	//t(obj); //not compile
//
//	std::cout << "---------------" << std::endl;
//
//	f(std::move(obj)); //"MC of A(); ~A();"
//	//g(std::move(obj)); //not compile
//	h(std::move(obj)); // extends life of A
//	t(std::move(obj)); // nothing
//
//	std::cout << "---------------" << std::endl;
//
//	f(A()); // A() ~A()
//	//g(A()); not compile
//	h(A()); // A() ~A()
//	t(A()); // A() ~A()
//
//	std::cout << "---------------" << std::endl;
//
//	f(std::move(A())); //"A() MC of A() ~A() ~A()
//	//g(std::move(A())); //not compile
//	h(std::move(A()));	//A() ~A()
//	t(std::move(A()));	//A() ~A()
//
//	std::cout << "---------------" << std::endl;
//}

//struct A {
//    char ch1;
//    char ch2;
//
//    virtual ~A() = default;
//};
//
//
//struct B : A {
//    char ch1;
//};
//
//#include <cstddef>
//#include <Type.h>
//
//int main()
//{
//    using RecordType = const char*;
//    static A* create(RecordType str);
//}

#include "Form.h"
#include "TextBox.h"
#include "CheckBox.h"
#include "RadioButton.h"

int main()
{
	/// +------------------------------------------------------------------------+
	/// |                                FACTORY                                 |
	/// +------------------------------------------------------------------------+

	Control* c1 = new CheckBox(30, 30, 10, 10, true, "check box1");
	Control* c2 = new TextBox(30, 100, 50, 10, "hello");
	Control* c3 = new RadioButton(40, 140, 10, 50, 6, 4);


	/// +------------------------------------------------------------------------+
	/// |                                  Form                                  |
	/// +------------------------------------------------------------------------+
	

	Form form(100, 160, 0, 0);
	form.addControl(c1);
	form.addControl(c2);
	form.addControl(c3);

	try
	{
		form.setControlXLocation(0, 200);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}


	// +------------------------------------------------------------------------+
	// |                                Sketch                                  |
	// +------------------------------------------------------------------------+

	// +-------------------------------+----------------------------------------> xAxis
	// |  +----+  +------------------+ |
	// |  |    |  |                  |<+-------- TextBox
	// |  +----+  +------------------+ |
	// |     ^                         |<------- Form
	// |  +--+-----------------------+ | 
	// |  |  |                       | |
	// |  |  |                       |<+-------- RadioButton
	// |  +--+-----------------------+ |
	// +-----+-------------------------+
	// |	 |
	// |	 |
	// |	 |
	// |     +---- CheckBox
	// |
	// |
	// |
	// |
	// |
	// |
	// |
	// |
	// y Axis

}