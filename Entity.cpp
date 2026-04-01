#include "Entity.h"

#include <algorithm>
#include <vector>

#include "Core.h"
#include "Enum.h"
#include "Item.h"

void Entity::CalculateStatsFromItems() {
	//Health
	float healthPercent = 1.f;
	CurrentMaxHealth = BaseMaxHealth;

	for (const auto& item : Items) {
		CurrentMaxHealth += item.first->MaxHealth * item.second;
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
		CurrentArmor += item.first->Armor * item.second;
	}
	
	//Damage
	CurrentDamage =  Damage;
	for (const auto& item : Items) {
		CurrentDamage += item.first->Damage * item.second;
	}

	//CurrentAttackCooldown
	CurrentAttackCooldown = BaseAttackCooldown;
	for (const auto& item : Items) {
		CurrentAttackCooldown += item.first->Cdr * item.second;
	}
	CurrentAttackCooldown = std::max(CurrentAttackCooldown, 0.1f);
}

float Entity::CalculateDamage(Entity* target, int critChance, bool didCrit) const
{
	float targetHealthDamage;
	float baseDamage = CurrentDamage;
	for (const auto& item : Items) {
		switch (item.first->special) {
		case none:
			break;
		case HealthToDamage:
			baseDamage += (CurrentMaxHealth * 0.01f) * (5 + item.second);
			break;
		case ArmorToDamage:
			baseDamage += (CurrentArmor * 0.01f) * (5 + item.second);
			break;
		case EnemyHealthPercent:
			targetHealthDamage = (target->CurrentMaxHealth * 0.05f) * item.second;
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
		totalDamage *= 1 + (item.first->DamageMultip * item.second);
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
		totalCritChance += item.first->Crit * item.second;
	}
	return totalCritChance;
}

float Entity::CalculateReduction() const
{
	const int totalArmor = CurrentArmor;
	return 1 - static_cast<float>(totalArmor) / (static_cast<float>(totalArmor) + Core::ArmorConstant);
}

std::string Entity::GiveRandomItem(const std::vector<Item*>* itemPool) {
	const int r = rand() % itemPool->size();
	Item* item = itemPool->at(r);
	AddItem(item);
	return item->Name;
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
	CurrentAttackCooldown = newSpeed;
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
