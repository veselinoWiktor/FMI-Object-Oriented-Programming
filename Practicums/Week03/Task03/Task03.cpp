#include <iostream>
#include <fstream>

namespace Constants
{
    constexpr int MAX_NAME_SIZE = 50;
    constexpr int MAX_PHONE_SIZE = 20;
    constexpr int MAX_ADDRESS_SIZE = 100;
    constexpr int MAX_PIZZAS_IN_DELIVERY = 100;
    constexpr int MAX_ORDERS = 100;
    
    const char fileName[] = "PizzaOrders.dat";
}

enum class PizzaType
{
    Margarita = 0,
    Capricciosa,
    Kalzone,
    QuattroStagioni,
    QuattroFormaggi,
    Vegetariana,
    Marinara
};

enum class PizzaSize
{
    S = 0,
    M,
    L
};

struct Pizza {
    PizzaType pizzaType;
    PizzaSize pizzaSize;
    double prize = 0;
};

struct Order {
    char name[Constants::MAX_NAME_SIZE];
    char phone[Constants::MAX_PHONE_SIZE];
    char address[Constants::MAX_ADDRESS_SIZE];
    double totalPrize = 0;

    Pizza pizzas[Constants::MAX_PIZZAS_IN_DELIVERY];
    size_t pizzasCount = 0;
};

struct PizzaOrderList {
    Order orders[Constants::MAX_ORDERS];
    size_t ordersSize = 0;
};

void savePizza(std::ofstream& ofs, const Pizza& pizza)
{
    if (!ofs.is_open())
    {
        return;
    }

    ofs.write((const char*)&pizza, sizeof(pizza));
}

void savePizza(const char* fileName, const Pizza& pizza)
{
    std::ofstream ofs(fileName, std::ios::binary);
    savePizza(ofs, pizza);
    ofs.close();
}

void savePizzaOrder(std::ofstream& ofs, const Order& order)
{
    if (!ofs.is_open())
    {
        return;
    }

    ofs.write((const char*)&order.address, sizeof(order.address));
    ofs.write((const char*)&order.name, sizeof(order.name));
    ofs.write((const char*)&order.phone, sizeof(order.phone));
    ofs.write((const char*)&order.pizzasCount, sizeof(order.pizzasCount));
    for (size_t i = 0; i < order.pizzasCount; i++)
    {
        savePizza(ofs, order.pizzas[i]);
    }
}

void savePizzaOrder(const char* filename, const Order& order)
{
    std::ofstream ofs(filename, std::ios::binary);
    savePizzaOrder(ofs, order);
    ofs.close();
}

void savePizzaOrderList(std::ofstream& ofs, const PizzaOrderList& list)
{
    if (!ofs.is_open())
    {
        return;
    }

    ofs.write((const char*)&list.ordersSize, sizeof(list.ordersSize));
    for (size_t i = 0; i < list.ordersSize; i++)
    {
        savePizzaOrder(ofs, list.orders[i]);
    }
}

void savePizzaOrderList(const char* fileName, const PizzaOrderList& list)
{
    std::ofstream ofs(fileName, std::ios::binary);
    savePizzaOrderList(ofs, list);
    ofs.close();
}

//Pizza readPizza(std::ifstream& ifs)
//{
//    Pizza pizza{};
//    if (!ifs.is_open())
//    {
//        return pizza;
//    }
//
//    ifs.read((char*)&pizza, sizeof(Pizza));
//    return pizza;
//}

//Pizza readPizza(std::ifstream& ifs)
//{
//    if (!ifs.is_open())
//    {
//        return {};
//    }
//  
//    Pizza pizza;
//    ifs.read((char*)&pizza, sizeof(Pizza));
//    return pizza;
//}

Pizza readPizza(std::ifstream& ifs)
{
    if (!ifs.is_open())
    {
        return {};
    }

    Pizza pizza;
    ifs.read((char*)&pizza, sizeof(Pizza));
    return pizza;
}

Pizza readPizza(const char* fileName)
{
    std::ifstream ifs(fileName, std::ios::binary);
    Pizza pizza = readPizza(ifs);
    ifs.close();
    return pizza;
}

Order readOrder(std::ifstream& ifs)
{
    Order order;
    if (!ifs.is_open())
    {
        return {};
    }

    ifs.read((char*)&order.address, sizeof(order.address));
    ifs.read((char*)&order.name, sizeof(order.name));
    ifs.read((char*)&order.phone, sizeof(order.phone));
    ifs.read((char*)&order.pizzasCount, sizeof(order.pizzasCount));
    order.totalPrize = 0;
    for (size_t i = 0; i < order.pizzasCount; i++)
    {
        order.pizzas[i] = readPizza(ifs);
        order.totalPrize += order.pizzas[i].prize;
    }
    return order;
}

Order readOrder(const char* fileName)
{
    std::ifstream ifs(fileName, std::ios::binary);
    Order order = readOrder(ifs);
    ifs.close();
    return order;
}

PizzaOrderList readPizzaOrderList(std::ifstream& ifs)
{
    if (!ifs.is_open())
    {
        return {};
    }

    PizzaOrderList pizzaOrderList;
    ifs.read((char*)&pizzaOrderList.ordersSize, sizeof(pizzaOrderList.ordersSize));
    for (size_t i = 0; i < pizzaOrderList.ordersSize; i++)
    {
        pizzaOrderList.orders[i] = readOrder(ifs);
    }
    return pizzaOrderList;
}

PizzaOrderList readPizzaOrderList(const char fileName[])
{
    std::ifstream ifs(fileName, std::ios::binary);
    PizzaOrderList pizzaOrderList = readPizzaOrderList(ifs);
    ifs.close();
    return pizzaOrderList;
}

void sortByAddress(PizzaOrderList& pizzaOrderList)
{
    for (size_t i = 0; i < pizzaOrderList.ordersSize - 1; i++)
    {
        int minIdx = i;

        for (size_t j = i + 1; j < pizzaOrderList.ordersSize; j++)
        {
            if (strcmp(pizzaOrderList.orders[j].address, pizzaOrderList.orders[minIdx].address) > 0)
            {
                minIdx = j;
            }
        }

        if (minIdx != i)
        {
            std::swap(pizzaOrderList.orders[minIdx], pizzaOrderList.orders[i]);
        }
    }
}

int main()
{
    std::ifstream ifs(Constants::fileName, std::ios::binary);
    PizzaOrderList pol = readPizzaOrderList(ifs);
    ifs.close();

    sortByAddress(pol);
    savePizzaOrderList("SortedPizzaOrders.dat", pol);



    //pol.ordersSize = 2;

    //Order order1;
    //strcpy_s(order1.name, "Viktor");
    //strcpy_s(order1.phone, "0886084298");
    //strcpy_s(order1.address, "Polikraishte");
    //order1.pizzasCount = 2;

    //Pizza pizza1;
    //pizza1.prize = 15;
    //pizza1.pizzaType = PizzaType::Margarita;
    //pizza1.pizzaSize = PizzaSize::L;
    //Pizza pizza2;
    //pizza2.prize = 10;
    //pizza2.pizzaType = PizzaType::Capricciosa;
    //pizza2.pizzaSize = PizzaSize::L;

    //order1.pizzas[0] = pizza1;
    //order1.pizzas[1] = pizza2;

    //pol.orders[0] = order1;

    ////second order
    //Order order2;
    //strcpy_s(order2.name, "Desi");
    //strcpy_s(order2.phone, "0882924233");
    //strcpy_s(order2.address, "Tarnovo");
    //order2.pizzasCount = 1;

    //Pizza pizza3;
    //pizza3.prize = 15;
    //pizza3.pizzaType = PizzaType::QuattroFormaggi;
    //pizza3.pizzaSize = PizzaSize::M;

    //order2.pizzas[0] = pizza3;

    //pol.orders[1] = order2;

    //savePizzaOrderList(Constants::fileName, pol);
}
