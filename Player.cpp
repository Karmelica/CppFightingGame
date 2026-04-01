#include "Player.h"

#include <format>
#include <iostream>

#include "Item.h"

Player::Player(const std::string& newName, float newMaxHealth, int newDamage, int newArmor)
{
	Name = newName;
	BaseMaxHealth = newMaxHealth;
	CurrentHealth = BaseMaxHealth;
	Damage = newDamage;
	BaseArmor = newArmor;
}

void Player::LevelUp()
{
	BaseMaxHealth += 30;
	Damage += 2;
	BaseArmor += 10;
	BaseAttackCooldown -= 0.01f;
	printf("\033[1;7m%-26s", "Level up! New base stats:");
	printf("\nMaxHealth: %-15.f", BaseMaxHealth);
	printf("\nDamage: %-18d", Damage);
	printf("\nArmor: %-19d", BaseArmor);
	printf("\nSpeed: %-19.2f\033[0m\n\n", BaseAttackCooldown);
}

void Player::SelectItem(const std::vector<Item*>* itemPool) {
	char ans;
	std::vector<Item*>* itemsToSelect = new std::vector<Item*>();
	printf("| Select item |");
	Item* randomItem = itemPool->at(rand() % itemPool->size());
	itemsToSelect->push_back(randomItem);

	do {
		randomItem = itemPool->at(rand() % itemPool->size());
	} while (randomItem == itemsToSelect->at(0));
	itemsToSelect->push_back(randomItem);

	do {
		randomItem = itemPool->at(rand() % itemPool->size());
	} while (randomItem == itemsToSelect->at(0) || randomItem == itemsToSelect->at(1));
	itemsToSelect->push_back(randomItem);

	printf("\n 1. %s\n 2. %s\n 3. %s\n", itemsToSelect->at(0)->Name.c_str(), itemsToSelect->at(1)->Name.c_str(), itemsToSelect->at(2)->Name.c_str());

	do {
		std::cin >> ans;
		std::cin.ignore(1);
	} while (ans < 49 || ans > 51);
	Item* selectedItem = itemsToSelect->at(ans - 49);
	AddItem(selectedItem);
}

