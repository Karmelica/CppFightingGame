#include "Item.h"

Item::Item(const std::string& newName, float newMaxHealth, int newDamage, float newDamageMultip, int newArmor, int newCrit,
	float newCDR, Special newSpecial)
{
	Name = newName;
	MaxHealth = newMaxHealth;
	Damage = newDamage;
	DamageMultip = newDamageMultip;
	Armor = newArmor;
	Crit = newCrit;
	Cdr = newCDR;
	special = newSpecial;
}

