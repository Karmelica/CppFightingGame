#pragma once
#include <string>
#include "Entity.h"

class Player : public Entity {
public:
	explicit Player(const std::string& newName, float newMaxHealth = 25.f, int newDamage = 3, int newArmor = 10);

	void LevelUp();
	void SelectItem(const std::vector<Item*>* itemPool);
};
