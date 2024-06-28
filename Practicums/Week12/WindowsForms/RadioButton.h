#pragma once
#include "Control.h"

#include <sstream>

class RadioButton : public Control
{
private:
	bool* options;
	size_t optionsCount;

	size_t choosedOptIdx;
	
	void copyFrom(const RadioButton& other);
	void moveFrom(RadioButton&& other);
	void free();
public:
	RadioButton(size_t optionsCount);
	RadioButton(unsigned int height, unsigned int width, unsigned int xLocation, unsigned int yLocation,
				size_t optionsCount, size_t choosedOptIdx);
	RadioButton(const RadioButton& other);
	RadioButton& operator=(const RadioButton& other);
	RadioButton(RadioButton&& other) noexcept;
	RadioButton& operator=(RadioButton&& other) noexcept;
	~RadioButton();

	size_t getOptionsCount() const;
	size_t getChoosedOptIdx() const;

	void setDataDialog(const char* data) override;
	Control* clone() const override;
};

