#include <iostream>
#include <fstream>

constexpr int USER_FIELD_MAX_LENGTH = 129;
constexpr int SYSTEM_MAX_USERS = 100;

const char fileName[] = "system.txt";

struct User
{
	char name[USER_FIELD_MAX_LENGTH];
	char email[USER_FIELD_MAX_LENGTH];
	char password[USER_FIELD_MAX_LENGTH];
};

struct System
{
	User users[SYSTEM_MAX_USERS];
	size_t size = 0;
};

void myStrcpy(const char* source, char* dest)
{
	if (!source || !dest)
	{
		return;
	}
	
	while (*source)
	{
		*dest = *source;
		dest++;
		source++;
	}

	*dest = '\0';
}

void writeUserToFile(std::ofstream& ofs, const User& user)
{
	ofs << user.name << ' ' << user.email << ' ' << user.password << std::endl;
}

void readUserFromFile(std::ifstream& ifs, User& user)
{
	ifs >> user.name >> user.email >> user.password;
}

void writeSystemToFile(const System& system)
{
	std::ofstream ofs(fileName);

	if (!ofs.is_open())
	{
		return;
	}

	ofs << system.size << std::endl;
	for (int i = 0; i < system.size; i++)
	{
		writeUserToFile(ofs, system.users[i]);
	}

	ofs.close();
}

void readSystemFromFile(System& system)
{
	std::ifstream ifs(fileName);

	if (!ifs.is_open())
	{
		return;
	}

	ifs >> system.size;
	for (int i = 0; i < system.size; i++)
	{
		readUserFromFile(ifs, system.users[i]);
	}

	ifs.close();
}

void addUserToSystem(System& system, const User& user)
{
	if (system.size == SYSTEM_MAX_USERS)
	{
		return;
	}


	myStrcpy(user.name, system.users[system.size].name);
	myStrcpy(user.email, system.users[system.size].email);
	myStrcpy(user.password, system.users[system.size].password);
	system.size++;
}

int main()
{
	System system;
	User users{ "viktor", "viktor@gmail.com", "viki123" };

	addUserToSystem(system, users);
	writeSystemToFile(system);
	System system1;
	readSystemFromFile(system1);
}
