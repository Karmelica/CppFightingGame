#include "Item.h"

Item::Item(std::string newName, float newMaxHealth, int newDamage, float newDamageMultip, int newArmor, int newCrit,
	int newSpeed, Special newSpecial)
{
	name = newName;
	maxHealth = newMaxHealth;
	damage = newDamage;
	damageMultip = newDamageMultip;
	armor = newArmor;
	crit = newCrit;
	speed = newSpeed;
	special = newSpecial;
}

