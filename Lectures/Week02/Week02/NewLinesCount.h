#pragma once
#include <fstream>

unsigned getCharCountFromFile(std::ifstream& ifs, char ch);
unsigned getLinesCount(const char* filename);