#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	double radius = 0;

public:
	Circle(int x, int y, double radius);

	double getArea() const override;
	double getPer() const override;
	bool isPointIn(int x, int y) const override;

	bool intersect(const Shape*) const override;
	bool intersectWithCircle(const Circle*) const override;
	bool intersectWithTriangle(const Triangle*) const override;
	bool intersectWithRectangle(const Rectangle*) const override;
};

