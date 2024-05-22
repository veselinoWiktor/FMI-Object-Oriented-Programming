#pragma once

enum class Major
{
	Undefined,
	Informatics,
	ComputerScience,
	InformaticSystems,
	SoftwareEngineering
};

struct Student
{
	char name[100] = "";
	unsigned fn = 0;
	Major major = Major::Undefined;
};

const char* getMajorStr(Major m);
