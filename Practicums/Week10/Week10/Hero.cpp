#include "Hero.h"

Hero::Hero(const String& name, unsigned HP, unsigned deffence)
{
	setName(name);
	setHP(HP);
	setDeffence(deffence);
}

void Hero::setName(const String& newName)
{
	name = newName;
}

const String& Hero::getName() const
{
	return name;
}

void Hero::setHP(unsigned newHP)
{
	HP = newHP;
}

unsigned Hero::getHP() const
{
	return HP;
}

void Hero::setDeffence(unsigned newDeffence)
{
	deffence = newDeffence;
}

unsigned Hero::getDeffence() const
{
	return deffence;
}

void Hero::attack(Hero& target) const
{
	target.HP -= ATTACK_DAMAGE * 100 / target.deffence;
}

void Hero::deffend()
{
	deffence += DEFFENCE_ADDITION;
}


