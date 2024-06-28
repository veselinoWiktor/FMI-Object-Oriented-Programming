#include <iostream>
#include "Garage.h"
#include "Car.h"
#include "CargoBus.h"
#include "Bike.h"

int main()
{
	/// +------------------------------------------------------------------------+
	/// |                                FACTORY                                 |
	/// +------------------------------------------------------------------------+

	Vehicle* vh1 = new Car("BMW", "X3", "352188519341", 1000, 100, 300, 500);
	Vehicle* vh2 = new Bike("BMX", "TheBes", "68127517124", 400, 200, 1899.0);
	Vehicle* vh3 = new CargoBus("Ford", "Transit", "29185817274", 1000, 80, 4500);

	/// +------------------------------------------------------------------------+
	/// |                                 GARAGE                                 |
	/// +------------------------------------------------------------------------+

	Garage garage(3);
	garage.addVehicle(vh1);
	garage.addVehicle(vh2);
	garage.addVehicle(vh3);

	garage.printVehiclesCount();
	std::cout << "Free space:" << garage.getFreeSpace() << std::endl;

	garage.removeVehicle("BMX", "TheBes", "68127517124");
	garage.printVehiclesCount();
	std::cout << "Free space:" << garage.getFreeSpace() << std::endl;

	garage.addVehicle(vh2);
	garage.printVehiclesCount();
	std::cout << "Free space:" << garage.getFreeSpace() << std::endl;

	const Vehicle* mostEffective = garage.getMostEffective(200);
	std::cout << mostEffective->getBrand() << std::endl;
	std::cout << mostEffective->getModel() << std::endl;
	std::cout << mostEffective->getVIN() << std::endl;
}