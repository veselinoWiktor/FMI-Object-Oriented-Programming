#pragma once

class Worker
{
public:

	virtual void print() const = 0;
	virtual size_t getWorkers() const = 0;
	virtual Worker* clone() const = 0;
	virtual ~Worker() = default;
};