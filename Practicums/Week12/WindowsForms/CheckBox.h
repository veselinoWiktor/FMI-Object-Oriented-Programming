#pragma once
#include "Control.h"

class CheckBox : public Control
{
private:
	bool checked = false;
	char* text = nullptr;

	void copyFrom(const CheckBox& other);
	void moveFrom(CheckBox&& other);
	void free();

public:
	CheckBox();
	CheckBox(unsigned int height, unsigned int width, unsigned int xLocation, unsigned int yLocation,
			 bool isChecked, const char* text);
	CheckBox(const CheckBox& other);
	CheckBox& operator=(const CheckBox& other);
	CheckBox(CheckBox&& other) noexcept;
	CheckBox& operator=(CheckBox&& other) noexcept;
	~CheckBox();

	void setText(const char* text);

	const char* getText() const;
	bool isChecked() const;

	void setDataDialog(const char* data) override;
	Control* clone() const override;

};

