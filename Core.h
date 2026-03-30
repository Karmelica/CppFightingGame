#pragma once
#include <string>
#include <vector>

#include "Enum.h"
#include "Item.h"

class Player;
class Enemy;
class Entity;

class Core {
	float enemyHealth = 20.f;
	int enemyDamage = 2;
	int enemyArmor = 10;
	int enemySpeed = 0;

	int stage = 0;
	bool fightFinished = false;
	bool playerWon = false;

	std::vector<Item*> itemPool = std::vector<Item*>();

	std::string fightLog;

	Player* player = nullptr;
	Enemy* enemy = nullptr;
	int levelUpTarget = 1;
	int levelUpCurrent = 0;

	static bool ChanceRoll(int totalChance, int myPercentChance);
	void Fight(Entity* attacker, Entity* target, Action action);
	static bool SpeedCompare(Player* player, Enemy* enemy);
	void AssignWithValue(Item* newItem, int chance);

	void AssignItems();
	void StartRound();
	void LogStats() const;
public:
	static constexpr float ArmorConstant = 400.f;
	bool LoopEnded;

    void Start();
	void Update();
	void End();
};