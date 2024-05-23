#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	double radius;
public:
	Circle(int x, int y, int radius);
	double getArea() const override;
	double getPer() const override;
	bool isPointIn(int x, int y) const override;
};

