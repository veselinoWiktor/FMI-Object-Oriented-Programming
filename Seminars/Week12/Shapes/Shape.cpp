#include "Shape.h"
#include <cmath>

void Shape::copyFrom(const Shape& other)
{
	pointsCount = other.pointsCount;
	points = new Point[pointsCount];
	for (size_t i = 0; i < pointsCount; i++)
		points[i] = other.points[i];
}

void Shape::moveFrom(Shape&& other)
{
	pointsCount = other.pointsCount;
	points = other.points;
	delete[] other.points;
}

void Shape::free()
{
	delete[] points;
}

Shape::Point::Point(int x, int y) : x(x), y(y)
{
}

double getDistance(const Shape::Point& p1, const Shape::Point & p2)
{
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;

	return sqrt(dx * dx + dy * dy);
}

Shape::Shape(size_t pointsCount) : pointsCount(pointsCount)
{
	points = new Point[pointsCount];
}

Shape::Shape(const Shape& other)
{
	copyFrom(other);
}

Shape::Shape(Shape&& other) noexcept
{
	moveFrom(std::move(other));
}

Shape& Shape::operator=(const Shape& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Shape& Shape::operator=(Shape&& other) noexcept
{
	if (this != &other)
	{
		free();
		copyFrom(std::move(other));
	}

	return *this;
}

Shape::~Shape()
{
	free();
}

const Shape::Point& Shape::getPoint(size_t index) const
{
	if (index >= pointsCount)
	{
		throw std::out_of_range("Shape::getPoint(); Index was out of range!");
	}

	return points[index];
}

void Shape::setPoint(size_t index, int x, int y)
{
	if (index >= pointsCount)
	{
		throw std::out_of_range("Shape::setPoint(); Index was out of range!");
	}

	points[index].x = x;
	points[index].y = y;
}

double Shape::getPer() const
{
	double per = 0;
	for (size_t i = 0; i < pointsCount - 1; i++)
	{
		per += getDistance(points[i], points[i + 1]);
	}
	
	per += getDistance(points[pointsCount - 1], points[0]);
	return per;
}
