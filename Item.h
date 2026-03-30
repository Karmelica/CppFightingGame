#pragma once
#include <string>
#include "Enum.h"

class Item {
public:
	std::string name;
	float maxHealth;
	int damage;
	float damageMultip;
	int armor;
	int speed;
	int crit;
	Special special;

	Item(std::string newName, float newMaxHealth, int newDamage, float newDamageMultip, int newArmor, int newCrit, int newSpeed, Special newSpecial = none);

	bool operator<(const Item& other) const {
		return name < other.name;
	}

	bool operator==(const Item& other) const {
		return name == other.name;
	}
};
