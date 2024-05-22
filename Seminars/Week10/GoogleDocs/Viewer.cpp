#include "Viewer.h"
#include <iostream>

void Viewer::view(const Document& document)
{
	std::cout << document.getContent() << std::endl;
}
