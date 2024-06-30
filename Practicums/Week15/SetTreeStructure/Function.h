#pragma once

class Funciton
{
private:
	unsigned int* data;
	size_t size;

	void copyFrom(const Funciton& other);
	void moveFrom(Funciton&& other);
	void free();

public:
	Funciton();
	Funciton(const unsigned int* data, size_t size);
	Funciton(const Funciton& other);
	Funciton(Funciton&& other) noexcept;
	Funciton& operator=(const Funciton& other);
	Funciton& operator=(Funciton&& other) noexcept;
	~Funciton();

	bool contains(unsigned int x) const;
	bool operator()(unsigned int x) const;
};