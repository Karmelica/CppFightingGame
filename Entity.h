#pragma once
#include <map>
#include <string>
#include <vector>

class Item;

class Entity {
public:
	std::map<Item*, int> Items;
	std::string Name;
	float CurrentHealth;
	float CurrentMaxHealth;
	float BaseMaxHealth;
	float BaseAttackCooldown = 3;
	float CurrentAttackCooldown = 0;
	int Damage;
	int CurrentDamage;
	int CurrentArmor;
	int BaseArmor;
	int CritChance = 1;

	int CalculateCritChance() const;
	float CalculateReduction() const;
	float CalculateDamage(Entity* target, int critChance, bool didCrit) const;
	void CalculateStatsFromItems();
	static float CalculateCritDamageMultip(int critChance);
	std::string GiveRandomItem(const std::vector<Item*>* itemPool);

	void Heal(float health);
	void TakeDamage(float damage);
	void SetSpeed(int newSpeed);
	void SetArmor(int newArmor);
	void SetMaxHealth(float newMaxHealth);
	void AddItem(Item* newItem);
};
