#include "Entity.h"

#include <vector>

#include "Core.h"
#include "Enum.h"
#include "Item.h"

void Entity::CalculateStatsFromItems() {
	//Health
	float healthPercent = 1.f;
	CurrentMaxHealth = BaseMaxHealth;

	for (const auto& item : Items) {
		CurrentMaxHealth += item.first->maxHealth * item.second;
		switch (item.first->special)
		{
		case none:
			break;
		case PercentHealthIncrease:
			healthPercent += 0.05f * item.second;
			break;
		case HealthToDamage:
			break;
		case ArmorToDamage:
			break;
		case EnemyHealthPercent:
			break;
		}
	}
	CurrentMaxHealth *= healthPercent;
	CurrentHealth = CurrentMaxHealth;

	//Armor
	CurrentArmor =  BaseArmor;
	for (const auto& item : Items) {
		CurrentArmor += item.first->armor * item.second;
	}

	//CurrentSpeed
	CurrentSpeed = BaseSpeed;
	for (const auto& item : Items) {
		CurrentSpeed += item.first->speed * item.second;
	}
}

float Entity::CalculateDamage(Entity* target, int critChance, bool didCrit) const
{
	float targetHealthDamage;
	float baseDamage = Damage;
	for (const auto& item : Items) {
		baseDamage += item.first->damage * item.second;
		switch (item.first->special) {
		case none:
			break;
		case HealthToDamage:
			baseDamage += (CurrentMaxHealth * 0.01f) * (5 + item.second);
			break;
		case ArmorToDamage:
			baseDamage += (CurrentArmor * 0.01f) * (1 + item.second);
			break;
		case EnemyHealthPercent:
			targetHealthDamage = (target->CurrentMaxHealth * 0.01f) * (5 + item.second);
			baseDamage += targetHealthDamage;
			break;
		default: 
			break;
		}
	}
	float totalDamage = baseDamage;

	if (didCrit) {
		totalDamage *= CalculateCritDamageMultip(critChance);
	}

	for (const auto& item : Items) {
		totalDamage *= 1 + (item.first->damageMultip * item.second);
	}

	return totalDamage;
}

float Entity::CalculateCritDamageMultip(int critChance)
{
	if (critChance > 100)
		return 1.5f + static_cast<float>(critChance - 100) * 0.005f;
	return 1.5f;
}

int Entity::CalculateCritChance() const
{
	int totalCritChance = CritChance;
	for (const auto& item : Items) {
		totalCritChance += item.first->crit * item.second;
	}
	return totalCritChance;
}

float Entity::CalculateReduction() const
{
	int totalArmor = CurrentArmor;
	for (const auto& item : Items) {
		totalArmor += item.first->armor * item.second;
	}
	return 1 - totalArmor / (totalArmor + Core::ArmorConstant);
}

std::string Entity::GiveRandomItem(const std::vector<Item*>* itemPool) {
	const int r = rand() % itemPool->size();
	Item* item = itemPool->at(r);
	AddItem(item);
	return item->name;
}

void Entity::Heal(const float health)
{
	CurrentHealth += health;
	CurrentHealth = std::min(CurrentHealth, CurrentMaxHealth);
}

void Entity::TakeDamage(const float damage)
{
	CurrentHealth -= damage;
}

void Entity::SetSpeed(int newSpeed)
{
	CurrentSpeed = newSpeed;
}

void Entity::SetArmor(int newArmor)
{
	CurrentArmor = newArmor;
}

void Entity::SetMaxHealth(float newMaxHealth)
{
	CurrentMaxHealth = newMaxHealth;
}

void Entity::AddItem(Item* newItem)
{
	if (!Items.contains(newItem)) {
		Items.insert_or_assign(newItem, 1);
	}
	else {
		Items.at(newItem)++;
	}
}
