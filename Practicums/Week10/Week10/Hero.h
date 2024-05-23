#pragma once
#include "String.h"

class Hero
{
private:
	static const unsigned ATTACK_DAMAGE = 5;
	static const unsigned DEFFENCE_ADDITION = 15;

	String name = "empty";
	unsigned HP = 0;
	unsigned deffence = 0;
public:
	Hero() = default;
	Hero(const String& name, unsigned HP, unsigned deffence);

	void setName(const String& newName);
	const String& getName() const;

	void setHP(unsigned newHP);
	unsigned getHP() const;

	void setDeffence(unsigned newDeffence);
	unsigned getDeffence() const;

	void attack(Hero& target) const;
	void deffend();
};

