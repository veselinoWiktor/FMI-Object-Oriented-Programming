#pragma once
#include "Hero.h"
#include "Item.h"

class Warrior : public Hero
{
private:
	unsigned attackDamage = 0;
	Item item;
public:
	Warrior(const String& name, unsigned HP, unsigned deffence, unsigned attackDamage, const Item& item);

	void setAttackDamage(unsigned newAttackDamage);
	unsigned getAttackDamage() const;

	void setItem(const Item& newItem);
	const Item& getItem() const;

	void attack(Hero& target) const;
	void deffend();
};
