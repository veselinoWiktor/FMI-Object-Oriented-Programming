#pragma once
#include <iostream>

class Circle;
class Triangle;
class Rectangle;

class Shape
{
private:
	void copyFrom(const Shape& other);
	void moveFrom(Shape&& other);
	void free();

protected:
	struct Point
	{
		int x = 0;
		int y = 0;
		Point() = default;
		Point(int x, int y);
	};

	friend double getDistance(const Point& p1, const Point& p2);

	Point* points = nullptr;
	size_t pointsCount = 0;
public:
	Shape(size_t pointsCount);
	Shape(const Shape& other);
	Shape(Shape&& other) noexcept;
	Shape& operator=(const Shape& other);
	Shape& operator=(Shape&& other) noexcept;
	virtual ~Shape();

	const Point& getPoint(size_t index) const;
	void setPoint(size_t index, int x, int y);

	virtual double getArea() const = 0;
	virtual double getPer() const;
	virtual bool isPointIn(int x, int y) const = 0;

	virtual bool intersect(const Shape*) const = 0;
	virtual bool intersectWithCircle(const Circle*) const = 0;
	virtual bool intersectWithTriangle(const Triangle*) const = 0;
	virtual bool intersectWithRectangle(const Rectangle*) const = 0;
	
};

