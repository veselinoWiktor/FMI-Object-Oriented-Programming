#include <iostream>

namespace Constants
{
	constexpr int MAX_COMPANYNAME_SIZE = 25;
	constexpr int MAX_JOBOFFERS_SIZE = 100;
}

struct JobOffer
{
	char companyName[Constants::MAX_COMPANYNAME_SIZE];
	unsigned teamSize;
	unsigned vacationDays;
	long long salary;
};

struct JobOfferList
{
	JobOffer offers[Constants::MAX_JOBOFFERS_SIZE];
	unsigned offerSize;
};

int main()
{


	std::cout << "Hello World!\n";
}
