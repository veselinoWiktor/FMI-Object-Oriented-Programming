#include "Control.h"

Control::Control()
{
	setHeight(20);
	setWidth(30);

	setLocation(0, 0);
}

Control::Control(unsigned height, unsigned width, unsigned xLocation, unsigned yLocation)
	: height(height), width(width), xLocation(xLocation), yLocation(yLocation)
{
	setHeight(height);
	setWidth(width);
	setLocation(xLocation, yLocation);
}

void Control::setHeight(unsigned int height)
{
	this->height = height;
}

void Control::setWidth(unsigned int width)
{
	this->width = width;
}

void Control::setXLocation(unsigned int xLocation)
{
	this->xLocation = xLocation;
}

void Control::setYLocation(unsigned int yLocation)
{
	this->yLocation = yLocation;
}

void Control::setLocation(unsigned int xLocation, unsigned int yLocation)
{
	setXLocation(xLocation);
	setYLocation(yLocation);
}

unsigned int Control::getHeight() const
{
	return height;
}

unsigned int Control::getWidth() const
{
	return width;
}

unsigned int Control::getXLocation() const
{
	return xLocation;
}

unsigned int Control::getYLocation() const
{
	return yLocation;
}

