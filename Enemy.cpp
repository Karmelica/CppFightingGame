#include "Enemy.h"

#include <cmath>

Enemy::Enemy(std::string newName, float newMaxHealth, int newDamage, int newArmor, float newCDR)
{
	Name = newName;

	const float healthOffset = rand() % static_cast<int>(round(newMaxHealth * 1.2f)) + static_cast<int>(round(newMaxHealth * 0.8f));
	BaseMaxHealth = healthOffset;
	CurrentHealth = BaseMaxHealth;

	Damage = newDamage;
	BaseArmor = newArmor;
	BaseAttackCooldown = newCDR;
}
