#pragma once
#include <string>
#include <vector>

#include "Enum.h"
#include "Item.h"

class Player;
class Enemy;
class Entity;

class Core {
	float playerCD = 0.f;
	float enemyCD = 0.f;
	float enemyHealth = 20.f;
	int enemyDamage = 2;
	int enemyArmor = 10;
	float enemyCooldown = 3.5f;
	int stage = 0;

	std::vector<Item*> itemPool = std::vector<Item*>();
	int levelUpTarget = 1;
	int levelUpCurrent = 0;

	std::string fightLog;

	Player* player = nullptr;
	Enemy* enemy = nullptr;

	static bool ChanceRoll(int totalChance, int myPercentChance);
	void Fight(Entity* attacker, Entity* target);
	void AssignWithValue(Item* newItem, int chance);

	void AssignItems();
	void StartRound();
	void LogStats() const;
	bool fightFinished = false;
	bool playerWon = false;
public:
	bool LoopEnded;
	static constexpr float ArmorConstant = 400.f;

    void Start();
	void Update(float deltaTime);
	void End();
};