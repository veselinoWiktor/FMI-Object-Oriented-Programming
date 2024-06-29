#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Intersector.h"

int main()
{
	Shape* ptr1 = new Circle(0, 0, 1);
	Shape* ptr2 = new Rectangle(0, 0, 2, 2);

	Intersector::intersect(ptr1, ptr2);
}