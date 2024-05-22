#include <iostream>

enum class RecatanglePositions {
    outside = -1,
    partlyOutside,
    inside,
};

struct Point
{
    double x;
    double y;
};

struct Rectangle
{
    Point bottomLeft;
    Point topRight;
};

double myAbs(double num)
{
    if (num < 0)
    {
        return -num;
    }
    return num;
}

void findSidesLength(const Rectangle& rectangle, double& xSide, double& ySide)
{
    Point bottomRight{ rectangle.topRight.x, rectangle.bottomLeft.y };

    xSide = myAbs(bottomRight.x - rectangle.bottomLeft.x);
    ySide = myAbs(bottomRight.y - rectangle.topRight.y);
}

double findPerimeter(const Rectangle& rectangle)
{
    double firstSide = 0;
    double secondSide = 0;

    findSidesLength(rectangle, firstSide, secondSide);

    return 2 * (firstSide + secondSide);
}

double findArea(const Rectangle& rectangle)
{
    double firstSide = 0;
    double secondSide = 0;

    findSidesLength(rectangle, firstSide, secondSide);

    return firstSide * secondSide;
}

RecatanglePositions whereIsRectanglePositioned(const Rectangle& firstRectangle, const Rectangle& secondRectangle)
{
    if (firstRectangle.topRight.x <= secondRectangle.topRight.x
        && firstRectangle.topRight.y <= secondRectangle.topRight.y
        && firstRectangle.bottomLeft.x >= firstRectangle.bottomLeft.x
        && firstRectangle.bottomLeft.y >= firstRectangle.bottomLeft.y)
    {
        return RecatanglePositions::inside;
    }

    else if (firstRectangle.topRight.x <= secondRectangle.topRight.x
        && firstRectangle.topRight.y <= secondRectangle.topRight.y
        && firstRectangle.topRight.x >= secondRectangle.bottomLeft.x
        && firstRectangle.topRight.y >= secondRectangle.bottomLeft.y)
    {
        return RecatanglePositions::partlyOutside;
    }
    else if (firstRectangle.bottomLeft.x >= secondRectangle.bottomLeft.x
        && firstRectangle.bottomLeft.y >= secondRectangle.bottomLeft.y
        && firstRectangle.bottomLeft.x <= secondRectangle.topRight.x
        && firstRectangle.bottomLeft.y <= secondRectangle.topRight.y)
    {
        return RecatanglePositions::partlyOutside;
    }
    else
    {
        return RecatanglePositions::outside;
    }
}

int main()
{
    std::cout << "Hello World!\n";
}

