#include "Manager.h"

int main()
{
	Manager m("Viktor", 20000, "CEO");

	Manager* m2 = new Manager("Gosho", 2000, "Manager");
	Worker* e1 = new Employee("Petar", 1000);
	Worker* e2 = new Employee("Tristan", 1000);

	m2->addSubordinate(e1);
	m2->addSubordinate(e2);

	m.addSubordinate(m2);

	m.print();
}