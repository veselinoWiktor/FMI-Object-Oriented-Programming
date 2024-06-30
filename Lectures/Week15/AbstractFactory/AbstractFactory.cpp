#include <iostream>

class AirBag {};
class EUSafetyStandardAirBag : public AirBag {};
class USASafetyStandardAirBag : public AirBag {};

class TurnSignal {};
class YellowTurnSignal : public TurnSignal {};
class RedTurnSignal : public TurnSignal {};

class CarPartsFactory
{
public:
    virtual AirBag* createAirBag() const = 0;
    virtual TurnSignal* createTurnSignal() const = 0;
    // ... more parts

    virtual ~CarPartsFactory() = default;
};

class EUCarPartsFactory : public CarPartsFactory
{
public:
    AirBag* createAirBag() const override
    {
        return new EUSafetyStandardAirBag();
    }
    TurnSignal* createTurnSignal() const override
    {
        return new YellowTurnSignal();
    }
};

class USACarPartsFactory : public CarPartsFactory
{
public:
    AirBag* createAirBag() const override
    {
        return new USASafetyStandardAirBag();
    }
    TurnSignal* createTurnSignal() const override
    {
        return new RedTurnSignal();
    }
};

CarPartsFactory* createPartsFactory(bool isEU)
{
    if (isEU)
        return new EUCarPartsFactory();
    else
        return new USACarPartsFactory();
}

void createCar(CarPartsFactory* factory)
{
    AirBag* airBag = factory->createAirBag();
    TurnSignal* turnSignal = factory->createTurnSignal();
    //... more

    delete airBag;
    delete turnSignal;
}

int main()
{
    CarPartsFactory* factory = createPartsFactory(true);
    createCar(factory);
    delete factory;
}
