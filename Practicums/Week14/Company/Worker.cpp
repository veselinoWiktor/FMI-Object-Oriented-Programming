#include "Worker.h"

Worker::Worker() : Employee(), workMonths(0)
{
}

Worker::Worker(const char* name, int age, double salary) : Employee(name, age, salary), workMonths(0)
{
}

void Worker::work()
{
	workMonths++;
}

int Worker::getWorkMonths() const
{
	return workMonths;
}

Employee* Worker::clone() const
{
	return new Worker(*this);
}
