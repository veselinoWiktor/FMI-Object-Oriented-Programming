#include "Rectangle.h"

Rectangle::Rectangle(int x1, int y1, int x3, int y3) : Shape(4)
{
	setPoint(0, x1, y1);
	setPoint(1, x1, y3);
	setPoint(2, x3, y3);
	setPoint(3, x3, y1);
}

double Rectangle::getArea() const
{
	return getDistance(points[0], points[1]) * getDistance(points[1], points[2]);
}

bool Rectangle::isPointIn(int x, int y) const
{
	return points[0].x <= x && points[0].y <= y
		&& points[2].x >= x && points[2].y >= y;
}

bool Rectangle::intersect(const Shape* other) const
{
	return other->intersectWithRectangle(this);
}

bool Rectangle::intersectWithCircle(const Circle* other) const
{
	std::cout << "Intersect rectangle with circle" << std::endl;

	// Some logic ...

	return true;
}

bool Rectangle::intersectWithTriangle(const Triangle*) const
{
	std::cout << "Intersect rectangle with triangle" << std::endl;

	// Some logic ...

	return true;
}

bool Rectangle::intersectWithRectangle(const Rectangle*) const
{
	std::cout << "Intersect rectangle with rectangle" << std::endl;

	// Some logic ...

	return true;
}
