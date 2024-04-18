#include "StringVector.h"

int main()
{
	String str("viktor");
	String str2("e gotin");
	String strArr[] = { str, str2 };
	StringVector sv(strArr, 2);

	std::cout << sv.getSize() << std::endl;
	sv.pop_back();
	std::cout << sv.getSize() << std::endl;
}