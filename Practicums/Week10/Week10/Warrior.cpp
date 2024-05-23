#include "Warrior.h"

Warrior::Warrior(const String& name, unsigned HP, unsigned deffence, unsigned attackDamage, const Item& item)
	: Hero(name, HP, deffence)
{
	setAttackDamage(attackDamage);
	setItem(item);
}

void Warrior::setAttackDamage(unsigned newAttackDamage)
{
	attackDamage = newAttackDamage;
}

unsigned Warrior::getAttackDamage() const
{
	return attackDamage;
}

void Warrior::setItem(const Item& newItem)
{
	item = newItem;
}

const Item& Warrior::getItem() const
{
	return item;
}

void Warrior::attack(Hero& target) const
{
	target.setHP((attackDamage * 100 / target.getDeffence()));
}

void Warrior::deffend()
{
	setDeffence(getDeffence() * 2);
}
