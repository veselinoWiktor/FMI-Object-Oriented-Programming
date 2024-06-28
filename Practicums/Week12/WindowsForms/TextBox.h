#pragma once
#include "Control.h"

class TextBox : public Control
{
private:
	char* text = nullptr;

	void copyFrom(const TextBox& other);
	void moveFrom(TextBox&& other);
	void free();
public:
	TextBox();
	TextBox(unsigned int height, unsigned int width, unsigned int xLocation, unsigned int yLocation, const char* data);
	TextBox(const TextBox& other);
	TextBox& operator=(const TextBox& other);
	TextBox(TextBox&& other) noexcept;
	TextBox& operator=(TextBox&& other) noexcept;
	~TextBox();

	const char* getText() const;

	void setDataDialog(const char* data) override;
	Control* clone() const override;
};

