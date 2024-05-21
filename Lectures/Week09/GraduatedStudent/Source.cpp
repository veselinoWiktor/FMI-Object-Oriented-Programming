#include <iostream>
#include "GraduatedStudent.h"

int main()
{
	int grades[3] = { 6,6,6 };
	GraduatedStudent viktor("Viktor", grades, 3, "I'm the best");
	GraduatedStudent gosho = viktor;
	gosho.setName("Gosho");
	GraduatedStudent pesho = std::move(viktor);
	pesho.setName("Pesho");
	pesho.setQuote("I always win");

	std::cout << gosho << std::endl << pesho << std::endl;
}