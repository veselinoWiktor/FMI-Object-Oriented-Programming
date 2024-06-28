#pragma once
#include <iostream>
#pragma warning (disable:4996)

class Control
{
protected:
	unsigned int height;
	unsigned int width;
	// with height and width and top left point we can find any other point of the control!!!
	unsigned int xLocation; // x of top left point of the control
	unsigned int yLocation; // y of top left point of the control

public:
	Control();
	Control(unsigned height, unsigned width,
			unsigned xLocation, unsigned yLocation);
	virtual ~Control() = default;

	void setHeight(unsigned int height);
	void setWidth(unsigned int width);

	void setXLocation(unsigned int xLocation);
	void setYLocation(unsigned int yLocation);

	void setLocation(unsigned int xLocation, unsigned int yLocation);

	unsigned int getHeight() const;
	unsigned int getWidth() const;
	unsigned int getXLocation() const;
	unsigned int getYLocation() const;
	
	virtual void setDataDialog(const char* data) = 0;
	virtual Control* clone() const = 0;
};

