#include <iostream>
#include <cstring>

enum class PetType {
	cat,
	dog,
	rabbit,
	fish,
	other
};

void printPetType(const PetType& petType)
{
	switch (petType)
	{
	case PetType::cat:
		std::cout << "cat";
		break;
	case PetType::dog:
		std::cout << "dog";
		break;
	case PetType::rabbit:
		std::cout << "rabbit";
		break;
	case PetType::fish:
		std::cout << "fish";
		break;
	case PetType::other:
		std::cout << "other";
		break;
	}
}

struct Pet {
	PetType petType;
	unsigned short age;
	char name[20];
};

void printPet(const Pet& pet)
{
	std::cout << pet.name << std::endl;
	std::cout << pet.age << std::endl;
	printPetType(pet.petType);
	std::cout << std::endl;
}

void initializePet(Pet& pet, PetType type, unsigned short age, char name[20])
{
	pet.petType = type;
	pet.age = age;
	strcpy_s(pet.name, name);
}

void readPet(Pet& myPet)
{
	//read pet fields
	//initializePet(myPet, ,,,,) // read fields
}

Pet createPet(PetType type, unsigned short age, char name[20])
{
	Pet myPet{ type, age, "" };
	std::cin >> myPet.age;
	strcpy_s(myPet.name, name);

	return myPet;
}

int main()
{
	Pet myFirstPet{ PetType::cat, 2, "cat" }; // :: оператор за резолюция
	printPet(myFirstPet);

	Pet* myOtherPet = new Pet{ PetType::cat, 2, "cat" };
	printPet(*myOtherPet);
	myOtherPet->age;
	(*myOtherPet).petType;

	delete myOtherPet;

	//static arrays with structs
	Pet myPets[3];
	for (int i = 0; i < 3; i++)
	{
		readPet(myPets[i]);
		std::cout << myPets[i].age;
	}

	//dynamic arrays with structs
	int n;
	std::cin >> n;

	Pet* myOtherPets = new Pet[n];
	delete[] myOtherPets;
}

