#include "RadioButton.h"

void RadioButton::copyFrom(const RadioButton& other)
{
	options = new bool[other.optionsCount];
	for (size_t i = 0; i < other.optionsCount; i++)
		options[i] = other.options[i];

	optionsCount = other.optionsCount;
	choosedOptIdx = other.choosedOptIdx;
}

void RadioButton::moveFrom(RadioButton&& other)
{
	options = other.options;
	other.options = nullptr;

	optionsCount = other.optionsCount;
	choosedOptIdx = other.choosedOptIdx;
}

void RadioButton::free()
{
	delete[] options;
}

RadioButton::RadioButton(size_t optionsCount) : Control(), choosedOptIdx(0)
{
	if (optionsCount == 0)
	{
		optionsCount = 1;
	}

	options = new bool[optionsCount] { false };
	options[choosedOptIdx] = true;
}

RadioButton::RadioButton(unsigned int height, unsigned int width, unsigned int xLocation, unsigned int yLocation, size_t optionsCount, size_t choosedOptIdx)
	: Control(height, width, xLocation, yLocation)
{
	if (choosedOptIdx > optionsCount)
	{
		throw new std::logic_error("Choosed option was out of range!");
	}

	this->choosedOptIdx = choosedOptIdx;
	this->optionsCount = optionsCount;

	options = new bool[optionsCount] { false };
	options[choosedOptIdx] = true;
}

RadioButton::RadioButton(const RadioButton& other) : Control(other)
{
	copyFrom(other);
}

RadioButton& RadioButton::operator=(const RadioButton& other)
{
	if (this != &other)
	{
		Control::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

RadioButton::RadioButton(RadioButton&& other) noexcept : Control(std::move(other))
{
	moveFrom(std::move(other));
}

RadioButton& RadioButton::operator=(RadioButton&& other) noexcept
{
	if (this != &other)
	{
		Control::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

RadioButton::~RadioButton()
{
	free();
}

size_t RadioButton::getOptionsCount() const
{
	return optionsCount;
}

size_t RadioButton::getChoosedOptIdx() const
{
	return choosedOptIdx;
}

void RadioButton::setDataDialog(const char* data)
{
	std::stringstream ss(data);
	long long idx = 0;
	ss >> idx;

	if (idx < 0 || idx >= optionsCount)
	{
		return;
	}

	options[choosedOptIdx] = false;
	options[idx] = true;
	choosedOptIdx = idx;
}

Control* RadioButton::clone() const
{
	return new RadioButton(*this);
}
