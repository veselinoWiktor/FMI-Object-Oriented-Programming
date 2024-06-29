#include "Circle.h"

const double PI = 3.1415;

Circle::Circle(int x, int y, double radius) : Shape(1), radius(radius)
{
	setPoint(0, x, y);
}

double Circle::getArea() const
{
	return PI * radius * radius;
}

double Circle::getPer() const
{
	return	2 * PI * radius;
}

bool Circle::isPointIn(int x, int y) const
{
	Point p(x, y);
	return getDistance(points[0], p) <= radius;
}

bool Circle::intersect(const Shape* other) const
{
	return other->intersectWithCircle(this);
}

bool Circle::intersectWithCircle(const Circle* other) const
{
	std::cout << "Intersect circle with circle" << std::endl;

	// Some logic ...

	return true;
}

bool Circle::intersectWithTriangle(const Triangle*) const
{
	std::cout << "Intersect circle with triangle" << std::endl;

	// Some logic ...

	return true;
}

bool Circle::intersectWithRectangle(const Rectangle*) const
{
	std::cout << "Intersect circle with rectangle" << std::endl;

	// Some logic ...

	return true;
}
