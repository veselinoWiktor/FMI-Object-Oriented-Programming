#include <iostream>
#include <fstream>

constexpr int BUFFER_SIZE = 24;

int main()
{
	/*std::ofstream myFile("example.txt");

	if (!myFile.is_open())
	{
		std::cout << "Error" << std::endl;
		return 1;
	}

	int a = 4;
	int b = 6;

	myFile << a << " " << b << std::endl;
	myFile.close();*/


	std::ifstream myIFile("example.txt");
	if (!myIFile.is_open())
	{
		std::cout << "Error"; 
		return 1;
	}

	int c, d;
	char buffer[BUFFER_SIZE];
	while (!myIFile.eof())
	{
		myIFile.getline(buffer, BUFFER_SIZE);
		std::cout << buffer << std::endl;
	}
	/*myIFile >> c >> d;
	std::cout << c << " " << d;*/
	myIFile.close();


	/*int a, b;
	std::cin >> a >> b;

	std::cout << a << " " << b << std::endl;
	
	std::cout.flush();*/
}
