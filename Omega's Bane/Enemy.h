#include<string>
#include<vector>

#pragma once
#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
public:
	Enemy(std::string name, int health, int shield, double strength, int speed, int goldMin, int goldMax, std::vector<std::string> attacks);
	std::string name;
	int maxHealth;
	int health;
	int maxShield;
	int shield;
	int speed;
	int goldRewardMinimum;
	int goldRewardMaximum;
	double strength;
	bool isActive;
	std::vector<std::string> attacks;

	bool TakeDamage(int damage, bool penetrating);
};

std::vector<std::vector<Enemy>> CreateEnemies();
Enemy GetElite(int currentFloor);
Enemy GetBoss(int currentFloor);

#endif