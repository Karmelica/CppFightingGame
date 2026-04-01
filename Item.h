#pragma once
#include <string>
#include "Enum.h"

class Item {
public:
	std::string Name;
	float MaxHealth;
	int Damage;
	float DamageMultip;
	int Armor;
	float Cdr;
	int Crit;
	Special special;

	Item(const std::string& newName, float newMaxHealth, int newDamage, float newDamageMultip, int newArmor, int newCrit, float newCDR, Special newSpecial = none);

	bool operator<(const Item& other) const {
		return Name < other.Name;
	}

	bool operator==(const Item& other) const {
		return Name == other.Name;
	}
};
