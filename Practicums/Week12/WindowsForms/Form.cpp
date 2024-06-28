#include "Form.h"

void Form::copyFrom(const Form& other)
{
	controls = new Control * [other.capacity] {nullptr};
	for (size_t i = 0; i < other.count; i++)
		controls[i] = other.controls[i]->clone();

	count = other.count;
	capacity = other.capacity;
}

void Form::moveFrom(Form&& other)
{
	controls = other.controls;
	other.controls = nullptr;

	count = other.count;
	capacity = other.capacity;
}

void Form::free()
{
	for (size_t i = 0; i < count; i++)
		delete controls[i];
	delete[] controls;
}

void Form::resize(size_t newCap)
{
	Control** newControls = new Control * [newCap] {nullptr};
	for (size_t i = 0; i < count; i++)
	{
		newControls[i] = controls[i];
	}

	delete[] controls;
	controls = newControls;
}

Form::Form() : Control(), count(0), capacity(4)
{
	controls = new Control * [capacity] {nullptr};
}

Form::Form(unsigned int height, unsigned int width, unsigned int xLocation, unsigned int yLocation)
	: Control(height, width, xLocation, yLocation), count(0), capacity(4)
{
	controls = new Control * [capacity] {nullptr};
}

Form::Form(const Form& other) : Control(other)
{
	copyFrom(other);
}

Form& Form::operator=(const Form& other)
{
	if (this != &other)
	{
		Control::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

Form::Form(Form&& other) noexcept : Control(std::move(other))
{
	moveFrom(std::move(other));
}

Form& Form::operator=(Form&& other) noexcept
{
	if (this != &other)
	{
		Control::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Form::~Form()
{
	free();
}

size_t Form::getCount() const
{
	return count;
}

void Form::setControlHeight(size_t ctrlIdx, unsigned int height)
{
	if (ctrlIdx >= count)
	{
		throw std::out_of_range("Index was out of range!");
	}

	controls[ctrlIdx]->setHeight(height);
}

void Form::setControlWidth(size_t ctrlIdx, unsigned int width)
{
	if (ctrlIdx >= count)
	{
		throw std::out_of_range("Index was out of range!");
	}

	controls[ctrlIdx]->setWidth(height);
}

void Form::setControlXLocation(size_t ctrlIdx, unsigned int xLocation)
{
	if (ctrlIdx >= count)
	{
		throw std::out_of_range("Index was out of range!");
	}

	if (xLocation < this->xLocation || xLocation > this->xLocation + this->width )
	{
		throw std::logic_error("The control got out of the form");
	}

	controls[ctrlIdx]->setXLocation(xLocation);
}

void Form::setControlYLocation(size_t ctrlIdx, unsigned int yLocation)
{
	if (ctrlIdx >= count)
	{
		throw std::out_of_range("Index was out of range!");
	}

	if (yLocation < this->yLocation || yLocation > this->yLocation + this->height)
	{
		throw std::logic_error("The control got out of the form");
	}

	controls[ctrlIdx]->setYLocation(yLocation);
}

void Form::setControlLocation(size_t ctrlIdx, unsigned int xLocation, unsigned int yLocation)
{
	setControlXLocation(ctrlIdx, xLocation);
	setControlYLocation(ctrlIdx, yLocation);
}

void Form::addControl(const Control* control)
{
	if (!control)
	{
		throw std::logic_error("Control was nullptr!");
	}

	if (count == capacity)
	{
		resize(capacity * 2);
	}

	controls[count++] = control->clone();
}

void Form::setDataDialog(const char* data)
{
	std::stringstream ss(data);
	size_t idx = 0;
	ss >> idx;

	if (idx >= count)
	{
		throw std::out_of_range("Index was out of range!");
	}
	
	ss.ignore();
	char buff[1024];
	ss.get(buff, 1024);

	controls[idx]->setDataDialog(buff);
}

Control* Form::clone() const
{
	return new Form(*this);
}


