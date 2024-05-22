#include <iostream>
#include <fstream>

const char FILENAME[] = "result.txt";

void printDifference()
{
	std::ifstream ifs(FILENAME);
	if (!ifs.is_open())
	{
		return;
	}

	int sum;
	int	product;
	ifs >> sum >> product;

	std::cout << sum - product;
	ifs.close();
}

int main()
{
	int a, b, c;
	std::cin >> a >> b >> c;

	std::ofstream ofs(FILENAME);
	if (!ofs.is_open())
	{
		return 1;
	}
	ofs << (a + b + c) << " " << (a * b * c);
	ofs.close();

	printDifference();
}
