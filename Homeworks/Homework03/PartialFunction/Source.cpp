#include<iostream>
#include "FunctionManager.h"

int main()
{
    FunctionManager fm;
    fm.run();
}



























/*PartialFunctionByCriteria<int (*)(int)> f(function);
std::cout << "f(1) = " << f(1).getSecond();*/
/*std::ofstream ofs("func.dat", std::ios::binary);

uint16_t l = 3;
ofs.write((const char*)&l, sizeof(uint16_t));
l = 3;
ofs.write((const char*)&l, sizeof(uint16_t));

char buff[] = "first.dat";
ofs.write((const char*)buff, 10 * sizeof(char));
char buff2[] = "second.dat";
ofs.write((const char*)buff2, 11 * sizeof(char));
char buff3[] = "third.dat";
ofs.write((const char*)buff3, 10 * sizeof(char));*/

/*int32_t n = 0;
ofs.write((const char*)&n, sizeof(int32_t));
n = 5;
ofs.write((const char*)&n, sizeof(int32_t));
n = 6;
ofs.write((const char*)&n, sizeof(int32_t));
n = 7;
ofs.write((const char*)&n, sizeof(int32_t));
n = 5;
ofs.write((const char*)&n, sizeof(int32_t));
n = 6;
ofs.write((const char*)&n, sizeof(int32_t));
n = 7;
ofs.write((const char*)&n, sizeof(int32_t));
n = 0;
ofs.write((const char*)&n, sizeof(int32_t));
n = 3;
ofs.write((const char*)&n, sizeof(int32_t));
n = 3;
ofs.write((const char*)&n, sizeof(int32_t));
n = 3;
ofs.write((const char*)&n, sizeof(int32_t));
n = 4;
ofs.write((const char*)&n, sizeof(int32_t));
n = 4;
ofs.write((const char*)&n, sizeof(int32_t));
n = 0;
ofs.write((const char*)&n, sizeof(int32_t));*/

//ofs.close();