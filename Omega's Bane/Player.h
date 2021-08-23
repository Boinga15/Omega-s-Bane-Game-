#include<string>
#include<vector>

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	Player(int selectedClass);

	int health;
	int maxHealth;
	int shield;
	int maxShield;
	double strength;
	int speed;
	int gold;
	int selectedClass;
	int stamina;
	int maxStamina;

	bool TakeDamage(int damage, bool penetrating);

	std::string actions[5] = {"", "", "", "", ""};
	std::vector<std::vector<std::string>> statuses;
	std::vector<std::string> potions;
};

#endif