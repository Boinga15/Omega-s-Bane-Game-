#include "Enemy.h"

// Enemy constructor.
Enemy::Enemy(std::string name, int health, int shield, double strength, int speed, int goldMin, int goldMax, std::vector<std::string> attacks) {
	this->name = name;
	this->maxHealth = health;
	this->health = this->maxHealth;
	this->maxShield = shield;
	this->shield = shield;
	this->speed = speed;
	this->goldRewardMinimum = goldMin;
	this->goldRewardMaximum = goldMax;
	this->attacks = attacks;
	this->strength = strength;
	this->isActive = true;
}

// Generates all the basic enemies for the floors.
std::vector<std::vector<Enemy>> CreateEnemies() {
	std::vector<std::vector<Enemy>> enemies;
	Enemy enemy("Zombie", 5, 0, 1, 5, 3, 6, { "Bite" });
	// Floor 1 (Upper caverns):
	std::vector<Enemy> enemies1;
	enemy = Enemy("Zombie", 20, 0, 1, 5, 3, 6, { "Bite" });
	enemies1.push_back(enemy);
	enemy = Enemy("Skeleton", 25, 10, 1, 2, 2, 8, { "Strike" });
	enemies1.push_back(enemy);
	enemy = Enemy("Bore Worm", 30, 30, 1.2, 8, 5, 10, { "Bite", "Defend" });
	enemies1.push_back(enemy);
	enemies.push_back(enemies1);

	// Floor 2 (Caves):
	std::vector<Enemy> enemies2;
	enemy = Enemy("Mutant", 35, 0, 1.2, 3, 6, 10, { "Fury Strike", "Strike" });
	enemies2.push_back(enemy);
	enemy = Enemy("Cave Spider", 30, 10, 1, 10, 8, 13, { "Toxin Bite", "Fury Strike" });
	enemies2.push_back(enemy);
	enemy = Enemy("Wolf", 45, 15, 2, 30, 6, 12, { "Bite", "Strike" });
	enemies2.push_back(enemy);
	enemies.push_back(enemies2);

	// Floor 3 (Depths):
	std::vector<Enemy> enemies3;
	enemy = Enemy("Lost Soul", 15, 30, 1.3, 20, 8, 15, { "Charge", "Defend" });
	enemies3.push_back(enemy);
	enemy = Enemy("Undead Adventurer", 40, 30, 1.3, 20, 8, 15, { "Strike", "Bow Shot", "Defend" });
	enemies3.push_back(enemy);
	enemy = Enemy("Giant Slime", 70, 0, 2, 0, 12, 16, { "Stomp", "Regenerate" });
	enemies3.push_back(enemy);
	enemies.push_back(enemies3);

	// Floor 4 (Crystal Cavern):
	std::vector<Enemy> enemies4;
	enemy = Enemy("Crystal Crab", 30, 60, 2, 5, 11, 17, { "Stomp", "Charge", "Defend", "Fury Strike" });
	enemies4.push_back(enemy);
	enemy = Enemy("Thief", 40, 20, 1.5, 35, 13, 20, { "Strike", "Shift" });
	enemies4.push_back(enemy);
	enemy = Enemy("Inferno Wasp", 60, 0, 1.2, 10, 13, 20, { "Charge", "Regenerate", "Toxin Bite" });
	enemies4.push_back(enemy);
	enemies.push_back(enemies4);

	// Floor 5 (Secret Base):
	std::vector<Enemy> enemies5;
	enemy = Enemy("Corrupted Defender", 70, 40, 2.5, 8, 15, 25, { "Charge", "Strike", "Fury Strike", "Defend" });
	enemies5.push_back(enemy);
	enemy = Enemy("Corrupted Juggernaut", 100, 0, 3, 0, 20, 30, { "Strike" });
	enemies5.push_back(enemy);
	enemy = Enemy("Corrupted Mage", 40, 10, 1.5, 20, 18, 27, { "Shift", "Area Regenerate", "Laser" });
	enemies5.push_back(enemy);
	enemies.push_back(enemies5);

	// Floor 6 (Void):
	std::vector<Enemy> enemies6;
	enemy = Enemy("Void Demon", 50, 50, 3, 20, 30, 80, { "Strike", "Shift", "Regenerate", "Laser", "Charge" });
	enemies6.push_back(enemy);
	enemies.push_back(enemies6);

	return enemies;
}

// Generate all of the elites.
Enemy GetElite(int currentFloor) {
	switch (currentFloor) {
	case 1:
		return Enemy("Stone Monster", 40, 20, 2, 0, 30, 30, { "Strike", "Stomp" });
		break;
	case 2:
		return Enemy("Queen Spider", 80, 0, 2, 0, 40, 40, { "Toxin Bite", "Area Regenerate", "Charge" });
		break;
	case 3:
		return Enemy("King Slime", 120, 0, 2.5, 5, 60, 60, { "Stomp", "Charge" });
		break;
	case 4:
		return Enemy("Undead Leader", 100, 50, 3, 10, 80, 80, { "Strike", "Defend", "Regenerate" });
		break;
	case 5:
		return Enemy("Phi", 50, 100, 2, 30, 110, 110, { "Laser", "Shift", "Regenerate" });
		break;
	case 6:
		return Enemy("Wall of Souls", 150, 0, 3, 0, 150, 150, { "Charge", "Fury Strike", "Laser" });
		break;
	}
}

// Generate all of the bosses.
Enemy GetBoss(int currentFloor) {
	switch (currentFloor) {
	case 1:
		return Enemy("Stone Golem", 80, 0, 2.5, 0, 35, 35, { "Strike", "Stomp", "Charge" });
		break;
	case 2:
		return Enemy("The Caretaker", 80, 40, 3, 15, 45, 45, { "Shift", "Area Regenerate", "Strike" });
		break;
	case 3:
		return Enemy("Cerberus", 150, 0, 3, 5, 70, 70, { "Bite", "Strike", "Fury Strike", "Stomp" });
		break;
	case 4:
		return Enemy("Abandonned Hero", 100, 100, 3, 10, 90, 90, { "Strike", "Defend", "Charge", "Fury Strike", "Regenerate" });
		break;
	case 5:
		return Enemy("Tarus", 120, 50, 3.5, 50, 200, 200, { "Laser", "Charge", "Shift" });
		break;
	case 6:
		return Enemy("Omega", 300, 200, 4.5, 0, 300, 300, { "Strike", "Defend", "Fury Strike", "Anihilate" });
		break;
	}
}

// Code that handles the enemy taking damage.
bool Enemy::TakeDamage(int damage, bool penetrating) {
	if (penetrating || this->shield <= 0) {
		this->health -= damage;
	}
	else {
		this->shield -= damage;
		if (this->shield < 0) {
			this->health -= (this->shield * -1);
			this->shield = 0;
		}
	}

	if (this->health <= 0) {
		this->isActive = false;
		return true;
	}
	else {
		return false;
	}
}