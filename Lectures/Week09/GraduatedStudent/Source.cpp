#include <iostream>
#include "GraduatedStudent.h"

int main()
{
	int grades[3] = { 6,6,6 };
	GraduatedStudent viktor("Viktor", grades, 3, "I'm the best");
	GraduatedStudent gosho = viktor;
}