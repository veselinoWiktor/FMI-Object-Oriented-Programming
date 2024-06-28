#include "TextBox.h"
#pragma warning (disable:4996)

void TextBox::copyFrom(const TextBox& other)
{
	text = new char[strlen(other.text) + 1];
	strcpy(text, other.text);
}

void TextBox::moveFrom(TextBox&& other)
{
	text = other.text;
	other.text = nullptr;
}

void TextBox::free()
{
	delete[] text;
}

TextBox::TextBox() : Control()
{
	setDataDialog("");
}

TextBox::TextBox(unsigned int height, unsigned int width, unsigned int xLocation, unsigned int yLocation, const char* data)
	: Control(height, width, xLocation, yLocation)
{
	setDataDialog(data);
}

TextBox::TextBox(const TextBox& other) : Control(other)
{
	copyFrom(other);
}

TextBox& TextBox::operator=(const TextBox& other)
{
	if (this != &other)
	{
		Control::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

TextBox::TextBox(TextBox&& other) noexcept : Control(std::move(other))
{
	moveFrom(std::move(other));
}

TextBox& TextBox::operator=(TextBox&& other) noexcept
{
	if (this != &other)
	{
		Control::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

TextBox::~TextBox()
{
	free();
}

const char* TextBox::getText() const
{
	return text;
}

void TextBox::setDataDialog(const char* data)
{
	if (!data || text == data)
	{
		return;
	}

	text = new char[std::strlen(data) + 1];
	std::strcpy(text, data);
}

Control* TextBox::clone() const
{
	return new TextBox(*this);
}
