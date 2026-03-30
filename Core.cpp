// \033[*;*;*m
//         foreground background
//black        30         40
//red          31         41
//green        32         42
//yellow       33         43
//blue         34         44
//magenta      35         45
//cyan         36         46
//white        37         47

//reset             0  (everything back to normal)
//bold/bright       1  (often a brighter shade of the same colour)
//underline         4
//inverse           7  (swap foreground and background colours)
//bold/bright off  21
//underline off    24
//inverse off      27

#include "Core.h"
#include <iostream>
#include <cstdio>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <vector>
#include "Enemy.h"
#include "Entity.h"
#include "Player.h"


bool Core::ChanceRoll(int totalChance, int myPercentChance) {
	return (rand() % totalChance + 1) <= myPercentChance;
}

void Core::Fight(Entity* attacker, Entity* target, Action action) {
	const int critChance = attacker->CalculateCritChance();
	const bool didCrit = ChanceRoll(100, critChance);
	const std::string crit = didCrit ? " for: \033[1;7mCRITICAL " : " for: ";
	const float damage = attacker->CalculateDamage(target, critChance, didCrit);
	const float reduction = target->CalculateReduction();
	const float totalDamage = damage * reduction;
	float healing;
	switch (action) {
	case Hit:
		target->TakeDamage(totalDamage);
		fightLog += std::format("{} hit {}{}{}\033[0m. \n", attacker->Name, target->Name, crit, std::to_string(static_cast<int>(round(totalDamage))));
		break;
	case Heal:
		healing = attacker->CurrentMaxHealth * 0.01f;
		attacker->Heal(healing);
		fightLog += attacker->Name + " healed for " + std::to_string(static_cast<int>(ceil(healing))) + "\033[0m. " + "\n";
		break;
	}
}

bool Core::SpeedCompare(Player* player, Enemy* enemy) {
	const int playerSpeed = (rand() % 100 + 1) + player->CurrentSpeed;
	const int enemySpeed = (rand() % 100 + 1) + enemy->CurrentSpeed;
	return playerSpeed >= enemySpeed;
}

//value 0 - 100
void Core::AssignWithValue(Item* newItem, int chance = 1) {
	for (int i = 0; i < chance; i++) {
		itemPool.push_back(newItem);
	}
}

void Core::AssignItems() {
	Item* newItem = new Item("\033[31mOne Piece (Increase all stats!)\033[0m", 300, 10, 1.f, 200, 20, 20);
	AssignWithValue(newItem, 1);
	newItem = new Item("\033[33mDrill (Deal damage based on enemy health)\033[0m", 0, 0, 0, 0, 0, 0, EnemyHealthPercent);
	AssignWithValue(newItem, 10);
	newItem = new Item("\033[33mShiny Stone (Gain damage based on your armor)\033[0m", 0, 0, 0, 100, 0, 0, ArmorToDamage);
	AssignWithValue(newItem, 10);
	newItem = new Item("\033[33mBad Apple (Gain damage based on your health)\033[0m", 0, 0, 0, 0, 0, 0, HealthToDamage);
	AssignWithValue(newItem, 10);
	newItem = new Item("\033[34mPerfect Dinner (Percentage health increase)\033[0m", 25, 0, 0, 0, 0, 0, PercentHealthIncrease);
	AssignWithValue(newItem, 20);
	newItem = new Item("\033[34mHealthmig (Gain health & armor)\033[0m", 50, 0, 0, 50, 0, 0);
	AssignWithValue(newItem, 20);
	newItem = new Item("\033[34mCritter (Gain crit chance & multiply damage)\033[0m", 0, 0, 0.4f, 0, 5, 0);
	AssignWithValue(newItem, 20);
	newItem = new Item("\033[32mGlasses (Gain crit chance)\033[0m", 0, 0, 0, 0, 10, 0);
	AssignWithValue(newItem, 50);
	newItem = new Item("\033[32mDamage Boost (Multiply damage)\033[0m", 0, 1, 0.3f, 0, 0, 0);
	AssignWithValue(newItem, 50);
	newItem = new Item("\033[32mChestplate (Gain armor)\033[0m", 0, 0, 0, 100, 0, 0);
	AssignWithValue(newItem, 50);
	newItem = new Item("\033[37mDamage Potion (Gain damage)\033[0m", 0, 2, 0, 0, 0, 0);
	AssignWithValue(newItem, 80);
	newItem = new Item("\033[37mHealth Potion (Gain health)\033[0m", 20, 0, 0, 0, 0, 0);
	AssignWithValue(newItem, 80);
	newItem = new Item("\033[37mSpeed Potion (Increase speed)\033[0m", 0, 0, 0, 0, 0, 2);
	AssignWithValue(newItem, 80);
}

void Core::StartRound()
{
	stage++;
	enemy = new Enemy("Enemy", enemyHealth, enemyDamage, enemyArmor, enemySpeed);
	for (int i = 0; i < stage; i++) {
		enemy->GiveRandomItem(&itemPool);
	}
	player->CalculateStatsFromItems();
	enemy->CalculateStatsFromItems();
}

void Core::LogStats() const
{
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(300ms);
	system("cls");

	printf("%s\n", fightLog.c_str());

	char str[50];

	int n = sprintf_s(str, "\033[32m [Health: %.2f]\033[0m", player->CurrentMaxHealth);
	printf("%-40s", str);
	printf("\033[31m [Health: %.2f]\033[0m\n", enemy->CurrentMaxHealth);

	n = sprintf_s(str, "\033[32m [CurrentSpeed: %d]\033[0m", player->CurrentSpeed + 50);
	printf("%-40s", str);
	printf("\033[31m [CurrentSpeed: %d]\033[0\n", enemy->CurrentSpeed + 50);

	n = sprintf_s(str, "\033[32m [Damage: %d]\033[0m", player->Damage);
	printf("%-40s", str);
	printf("\033[31m [Damage: %d]\033[0m\n", enemy->Damage);

	n = sprintf_s(str, "\033[32m [Armor(%%): %d(%.1f)]\033[0m", player->CurrentArmor, (1 - player->CalculateReduction()) * 100);
	printf("%-40s", str);
	printf("\033[31m [Armor(%%): %d(%.1f)]\033[0m\n", enemy->CurrentArmor, (1 - enemy->CalculateReduction()) * 100);

	n = sprintf_s(str, "\033[32m [Crit Chance/Damage: %d/%.2f]\033[0m", player->CalculateCritChance(),
		Entity::CalculateCritDamageMultip(player->CalculateCritChance()));
	printf("%-40s", str);
	printf("\033[31m [Crit Chance/Damage: %d/%.2f]\033[0m\n\n", enemy->CalculateCritChance(),
	       Entity::CalculateCritDamageMultip(enemy->CalculateCritChance()));

	n = sprintf_s(str, "\033[32m Player HP: %.2f%%\033[0m", player->CurrentHealth / player->CurrentMaxHealth * 100.f);
	printf("%-40s", str);
	printf("\033[31m Enemy HP: %.2f%%\033[0m\n\n", enemy->CurrentHealth / enemy->CurrentMaxHealth * 100.f);

	printf("Round: %d\n\n", stage);
}

 void Core::Start() {

	 srand(time(nullptr));
	 AssignItems();

	 player = new Player("Player");
	 StartRound();

	 printf("%20s", "Press enter to start");
	 std::cin.ignore(1);
	 std::cout << "\n";
 }

void Core::Update()
{
	if (enemy == nullptr || player == nullptr) {
		return;
	}

	if (player->CurrentHealth > 0.f && enemy->CurrentHealth > 0.f) {
		if (SpeedCompare(player, enemy)) {
			Fight(player, enemy, Hit);
		}
		else {
			Fight(enemy, player, static_cast<Action>(rand() % 2));
		}

		LogStats();
	}
	else {
		fightFinished = true;
	}

	if (!fightFinished)return;

	if (enemy->CurrentHealth <= 0.f) {
		printf("Enemy died\n\n");
		playerWon = true;
	}
	if (player->CurrentHealth <= 0.f) {
		printf("Player died\n\n");
		playerWon = false;
	}


	if (playerWon)
	{
		levelUpCurrent++;
		if (levelUpCurrent == levelUpTarget) {
			player->LevelUp();
			levelUpTarget++;
			levelUpCurrent = 0;
		}
		if (stage % 3 == 0) {
			player->SelectItem(&itemPool);
		}
		else {
			printf("Got: %s. Press enter to continue ", player->GiveRandomItem(&itemPool).c_str());
			std::cin.ignore(1);
		}
		StartRound();
	}
	fightLog = "";
	fightFinished = false;


	if (player->CurrentHealth <= 0.f) LoopEnded = true;
}

void Core::End()
{
	std::cin.ignore();
	system("cls");
}
