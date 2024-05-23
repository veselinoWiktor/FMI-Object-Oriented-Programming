#include "Triangle.h"

Triangle::Triangle(int x1, int y1,
	int x2, int y2,
	int x3, int y3) : Shape(3)
{
	setPoint(0, x1, y1);
	setPoint(1, x2, y2);
	setPoint(2, x3, y3);
}

double Triangle::getArea() const
{
	const Point& p1 = getPointAtIndex(0);
	const Point& p2 = getPointAtIndex(1);
	const Point& p3 = getPointAtIndex(2);

	//formula with the determinant;
	return abs(p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p1.y * p2.x - p2.y * p3.x - p3.y * p1.x) / 2.00;
}

bool Triangle::isPointIn(int x, int y) const
{
	Triangle t1(getPointAtIndex(0).x, getPointAtIndex(0).y,
		getPointAtIndex(1).x, getPointAtIndex(1).y,
		x, y);
	Triangle t2(getPointAtIndex(1).x, getPointAtIndex(1).y,
		getPointAtIndex(2).x, getPointAtIndex(2).y,
		x, y);
	Triangle t3(getPointAtIndex(2).x, getPointAtIndex(2).y,
		getPointAtIndex(0).x, getPointAtIndex(0).y,
		x, y);

	return abs(t1.getArea() + t2.getArea() + t3.getArea() - getArea()) <= std::numeric_limits<double>::epsilon();
}


