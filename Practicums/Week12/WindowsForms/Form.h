#pragma once
#include "Control.h"
#include <sstream>

class Form : public Control
{
private:
	Control** controls = nullptr;
	size_t count = 0;
	size_t capacity = 4;

	void copyFrom(const Form& other);
	void moveFrom(Form&& other);
	void free();

	void resize(size_t newCap);
public:
	Form();
	Form(unsigned int height, unsigned int width, unsigned int xLocation, unsigned int yLocation);
	Form(const Form& other);
	Form& operator=(const Form& other);
	Form(Form&& other) noexcept;
	Form& operator=(Form&& other) noexcept;
	~Form();

	size_t getCount() const;

	void setControlHeight(size_t ctrlIdx, unsigned int height);
	void setControlWidth(size_t ctrlIdx, unsigned int width);
	void setControlXLocation(size_t ctrlIdx, unsigned int xLocation);
	void setControlYLocation(size_t ctrlIdx, unsigned int yLocation);
	void setControlLocation(size_t ctrlIdx, unsigned int xLocation, unsigned int yLocation);


	void addControl(const Control* control);

	void setDataDialog(const char* data) override; //this is the change method
	Control* clone() const override;
};

