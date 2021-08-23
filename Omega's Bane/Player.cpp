#include<random>
#include<ctime>
#include "Player.h"

// Constructor for player.
Player::Player(int selectedClass) {  // Here we set the player's stats.
	this->selectedClass = selectedClass;
	this->gold = 0;
	this->maxStamina = 100;
	this->stamina = this->maxStamina;
	switch (selectedClass) {  // Here's where you can add more classes.
	case 1:
		this->maxHealth = 10;  // The maximum health of the player.
		this->health = this->maxHealth;
		this->maxShield = 10; // The maximum shield of the player.
		this->shield = 0;
		this->strength = 1.25;  // Base damage of attacks.
		this->speed = 5;  // Chance to dodge or flee (Maximum: 100)
		this->actions[0] = "Strike";  // First action.
		this->actions[1] = "Bow Shot";  // Second action.
		this->actions[2] = "Charge";  // Third action.
		this->actions[3] = "Crushing Blow"; // Fourth action.
		this->actions[4] = "Defensive Stance"; // Fifth action.
		break;
	case 2:
		this->maxHealth = 7;  // The maximum health of the player.
		this->health = this->maxHealth;
		this->maxShield = 3; // The maximum shield of the player.
		this->shield = 0;
		this->strength = 0.75;  // Base damage of attacks.
		this->speed = 50;  // Chance to dodge or flee (Maximum: 100)
		this->actions[0] = "Strike";  // First action.
		this->actions[1] = "Bow Shot";  // Second action.
		this->actions[2] = "Shift";  // Third action.
		this->actions[3] = "Fury Strike"; // Fourth action.
		this->actions[4] = "Spitfire"; // Fifth action.
		break;
	case 3:
		this->maxHealth = 5;  // The maximum health of the player.
		this->health = this->maxHealth;
		this->maxShield = 5; // The maximum shield of the player.
		this->shield = 0;
		this->strength = 1;  // Base damage of attacks.
		this->speed = 30;  // Chance to dodge or flee (Maximum: 100)
		this->actions[0] = "Strike";  // First action.
		this->actions[1] = "Bow Shot";  // Second action.
		this->actions[2] = "Restore";  // Third action.
		this->actions[3] = "Homing Bolt"; // Fourth action.
		this->actions[4] = "Total Restoration"; // Fifth action.
		break;
	}
}

// Code that handles the player taking damage.
bool Player::TakeDamage(int damage, bool penetrating) {
	if (penetrating || this->shield <= 0) {
		this->health -= damage;
	} else {
		this->shield -= damage;
		if (this->shield < 0) {
			this->health -= (this->shield * -1);
			this->shield = 0;
		}
	}

	if (this->health <= 0) {
		return true;
	} else {
		return false;
	}
}