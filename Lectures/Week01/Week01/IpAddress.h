#pragma once
#include <iostream>

union IpAddress
{
	uint32_t address;
	unsigned char octets[4];
};

