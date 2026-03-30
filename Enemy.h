#pragma once
#include <string>
#include "Entity.h"

class Enemy : public Entity {
public:
	explicit Enemy(std::string newName, float newMaxHealth = 20.f, int newDamage = 2, int newArmor = 10, int newSpeed = 0);
};
