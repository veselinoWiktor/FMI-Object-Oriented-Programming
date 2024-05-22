class Base {
public:
	int x = 0;
	void f() {};
private:
	int y = 0;
	void g() {};
};

class Der : public Base //Der is a Base
{
public:
	int z = 0;
};

static int exampleMain()
{
	Der obj;
	obj.z++;
	obj.x++;
	obj.f();

	return 0;
}