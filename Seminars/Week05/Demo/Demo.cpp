#include <iostream>

class Test1
{
private:
    int a = 0;
    int b = 0;

public:
    Test1(int c, int d) : a(c), b(d){}
};

void f(Test1 test)
{

}

int main()
{
    Test1 t1(3, 4);
    Test1 t2(5, 6);

    t2 = t1;
}
