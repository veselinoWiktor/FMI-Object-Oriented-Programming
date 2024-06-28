#include "CheckBox.h"

void CheckBox::copyFrom(const CheckBox& other)
{
	checked = other.checked;

	text = new char[std::strlen(other.text) + 1];
	std::strcpy(text, other.text);
}

void CheckBox::moveFrom(CheckBox&& other)
{
	checked = other.checked;

	text = other.text;
	other.text = nullptr;
}

void CheckBox::free()
{
	delete[] text;
}

CheckBox::CheckBox() : Control()
{
	setText("");
}

CheckBox::CheckBox(unsigned int height, unsigned int width, unsigned int xLocation, unsigned int yLocation, bool isChecked, const char* text)
	: Control(height, width, xLocation, yLocation), checked(isChecked)
{
	setText(text);
}

CheckBox::CheckBox(const CheckBox& other) : Control(other)
{
	copyFrom(other);
}

CheckBox& CheckBox::operator=(const CheckBox& other)
{
	if (this != &other)
	{
		Control::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

CheckBox::CheckBox(CheckBox&& other) noexcept : Control(std::move(other))
{
	moveFrom(std::move(other));
}

CheckBox& CheckBox::operator=(CheckBox&& other) noexcept
{
	if (this != &other)
	{
		Control::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

CheckBox::~CheckBox()
{
	free();
}

void CheckBox::setText(const char* text)
{
	if (!text || this->text == text)
	{
		return;
	}

	this->text = new char[std::strlen(text) + 1];
	std::strcpy(this->text, text);
}

const char* CheckBox::getText() const
{
	return text;
}

bool CheckBox::isChecked() const
{
	return checked;
}

void CheckBox::setDataDialog(const char* data)
{
	if (!data)
	{
		return;
	}

	if (std::strcmp(data, "true") == 0)
	{
		checked = true;
	}
	else
	{
		checked = false;
	}
}

Control* CheckBox::clone() const
{
	return new CheckBox(*this);
}
