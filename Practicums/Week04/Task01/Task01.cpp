#include <iostream>


class Teacher {
private:
    char* name;
    unsigned age;
    unsigned tenure;

public:
    Teacher() : name(nullptr), age(0), tenure(0)
    {
    };

    Teacher(const char* name, unsigned age, unsigned tenure)
    {
        setName(name);
        setAge(age);
        setTenure(tenure);
    }

    ~Teacher()
    {
        if (name != nullptr)
        {
            delete[] name;
        }
    }

    const char* getName() const
    {
        return name;
    }
    void setName(const char* value)
    {
        if (this->name != nullptr)
        {
            delete[] name;
        }

        unsigned valueLength = strlen(value);
        this->name = new char[valueLength + 1];
        strcpy(name, value);
        name[valueLength] = '\0';
    }

    unsigned getAge() const
    {
        return this->age;
    }
    void setAge(unsigned age)
    {
        this->age = age;
    }

    unsigned getTenure()
    {
        return this->tenure;
    }
    void setTenure(unsigned tenure)
    {
        this->tenure = tenure;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
