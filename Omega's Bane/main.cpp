/*
Omega's Bane.
Version 1.0
Made by Boinga15.

Contributers:
None so far.
*/

// Importing libraries
#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <math.h>
#include <stdlib.h>

#include "Player.h"
#include "Attacks.h"
#include "Enemy.h"

using namespace std;

void hub();

Player player(0);
// Temporary enemies (Changing does nothing):
Enemy enemy1("Zombie", 5, 0, 1, 5, 3, 6, { "Bite" });
Enemy enemy2("Zombie", 5, 0, 1, 5, 3, 6, { "Bite" });
Enemy enemy3("Zombie", 5, 0, 1, 5, 3, 6, { "Bite" });

vector<vector<Enemy>> enemies;

bool availableUpgrades[5] = { true, true, true, true, true };  // Armour, Health, Stamina, Speed, Strength

int currentFloor = 0;
int roomsExplored = 0;
bool hasDiscoveredShop = false;
bool hasFoundBoss = false;
int eliteStatus = 0; // 0: Undiscovered. 1: Found. 2: Dead.
int turnsOfEnemy = 0;
int turnsOfTreasure = 0;
int chanceOfAttack = 5;
 
// Used to receive inputs from the player.
int getInput() {
	int op;
	cin >> op;
	if (cin.fail()) {
		cin.clear();
		cin.ignore(100, '\n');
		return -1; // Failed case.
	} else {
		return op;
	}
}

//The game over screen.
void gameOver() {
	system("cls");
	cout << "YOU DIED." << endl;
	cout << "Your soul wanders the endless void forever..." << endl;
	cout << "Last floor reached: " << currentFloor << endl;
	cout << "Final stats:" << endl;
	cout << "=============================================================================" << endl;
	cout << "Health: (";
	for (int i = 0; i < player.maxHealth; i++) {
		if (i + 1 > player.health) {
			cout << " ";
		}
		else {
			cout << "|";
		}
	}
	cout << ")" << endl;

	cout << "Shield: (";
	for (int i = 0; i < player.maxShield; i++) {
		if (i + 1 > player.shield) {
			cout << " ";
		}
		else {
			cout << "|";
		}
	}
	cout << ")" << endl;
	cout << "=============================================================================" << endl;
	cout << "Strength: " << player.strength << endl;
	cout << "Speed: " << player.speed << endl;
	cout << "Gold: " << player.gold << endl;
	cout << "=============================================================================" << endl;

	for (int i = 0; i < 5; i++) {
		cout << player.actions[i] << " (" << GetStaminaCost(player.actions[i]) << " stamina):" << endl;
		cout << GetAttackDescription(player.actions[i]) << "\n" << endl;
	}
	cout << "Stamina: " << player.maxStamina << endl;
	cout << "=============================================================================" << endl;
	if (player.potions.size() > 0) {
		cout << "Potions:" << endl;
		for (int i = 0; i < player.potions.size(); i++) {
			cout << "- " << player.potions[i] << " -" << endl;
		}
		cout << "=============================================================================" << endl;
	}
	cout << endl;
	system("pause");
	exit;
}

// Below three functions check if the player encounters the shop, boss, or elite while exploring.
bool checkForShop() {
	if (roomsExplored >= 5 && !hasDiscoveredShop) {
		if (1 + rand() % 3 == 2) {
			return true;
		}
	}
	return false;
}

bool checkForBoss() {
	if (roomsExplored >= 7 && !hasFoundBoss) {
		if (1 + rand() % (10 - (roomsExplored - 7)) == 1) {
			return true;
		}
	}
	return false;
}

bool checkForElite() {
	if (roomsExplored >= 10 && eliteStatus == 0) {
		if (1 + rand() % 8 == 3) {
			return true;
		}
	}
	return false;
}

// Function that handles player using actions.
void useAction(int AttackID) {
	bool hasSelected = false;
	int goldEarned = 0;
	// Switch that checks for the different actions.
	switch (AttackID) {
	case 0:
		if (player.stamina >= 10) {
			player.stamina -= 10;
			while (!hasSelected) {
				cout << "Select your target:" << endl;
				if (enemy1.isActive) {
					cout << "1: " << enemy1.name << endl;
				}
				if (enemy2.isActive) {
					cout << "2: " << enemy2.name << endl;
				}
				if (enemy3.isActive) {
					cout << "3: " << enemy3.name << endl;
				}
				cout << "4: Cancel attack." << endl;
				int op = getInput();

				system("cls");
				switch (op) {
				case 1:
					if (enemy1.isActive) {
						if (10 + rand() % 100 >= enemy1.speed) {
							cout << "You struck " << enemy1.name << " and dealt " << ceil(player.strength * 1) << " damage!" << endl;
							if (enemy1.TakeDamage(ceil(player.strength * 1), false)) {
								cout << enemy1.name << " collapses dead!" << endl;
								goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						else {
							cout << "You tried to strike " << enemy1.name << ", but you missed!" << endl;
						}
						hasSelected = true;
					} else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 2:
					if (enemy2.isActive) {
						if (10 + rand() % 100 >= enemy2.speed) {
							cout << "You struck " << enemy2.name << " and dealt " << ceil(player.strength * 1) << " damage!" << endl;
							if (enemy2.TakeDamage(ceil(player.strength * 1), false)) {
								cout << enemy2.name << " collapses dead!" << endl;
								goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						else {
							cout << "You tried to strike " << enemy2.name << ", but you missed!" << endl;
						}
						hasSelected = true;
					} else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 3:
					if (enemy3.isActive) {
						if (10 + rand() % 100 >= enemy3.speed) {
							cout << "You struck " << enemy3.name << " and dealt " << ceil(player.strength * 1) << " damage!" << endl;
							if (enemy3.TakeDamage(ceil(player.strength * 1), false)) {
								cout << enemy3.name << " collapses dead!" << endl;
								goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						else {
							cout << "You tried to strike " << enemy3.name << ", but you missed!" << endl;
						}
						hasSelected = true;
					} else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 4:
					player.stamina += 10;
					hasSelected = true;
					break;
				default:
					cout << "Error: That was not a valid option.\n" << endl;
					break;
				}
			}
		} else {
			cout << "You don't have enough stamina!" << endl;
		}
		break;
	case 1:
		if (player.stamina >= 15) {
			player.stamina -= 15;
			while (!hasSelected) {
				cout << "Select your target:" << endl;
				if (enemy1.isActive) {
					cout << "1: " << enemy1.name << endl;
				}
				if (enemy2.isActive) {
					cout << "2: " << enemy2.name << endl;
				}
				if (enemy3.isActive) {
					cout << "3: " << enemy3.name << endl;
				}
				cout << "4: Cancel attack." << endl;
				int op = getInput();

				system("cls");
				switch (op) {
				case 1:
					if (enemy1.isActive) {
						if (rand() % 80 >= enemy1.speed) {
							cout << "You fire an arrow at " << enemy1.name << " and dealt " << ceil(player.strength * 1.5) << " damage!" << endl;
							if (enemy1.TakeDamage(ceil(player.strength * 1.5), false)) {
								cout << enemy1.name << " collapses dead!" << endl;
								goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						else {
							cout << "You tried fire an arrow at " << enemy1.name << ", but you missed!" << endl;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 2:
					if (enemy2.isActive) {
						if (rand() % 80 >= enemy2.speed) {
							cout << "You fire an arrow at " << enemy2.name << " and dealt " << ceil(player.strength * 1.5) << " damage!" << endl;
							if (enemy2.TakeDamage(ceil(player.strength * 1.5), false)) {
								cout << enemy2.name << " collapses dead!" << endl;
								goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						else {
							cout << "You tried to fire an arrow at " << enemy2.name << ", but you missed!" << endl;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 3:
					if (enemy3.isActive) {
						if (rand() % 80 >= enemy3.speed) {
							cout << "You fire an arrow at " << enemy3.name << " and dealt " << ceil(player.strength * 1.5) << " damage!" << endl;
							if (enemy3.TakeDamage(ceil(player.strength * 1.5), false)) {
								cout << enemy3.name << " collapses dead!" << endl;
								goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						else {
							cout << "You tried to fire an arrow at " << enemy3.name << ", but you missed!" << endl;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 4:
					player.stamina += 15;
					hasSelected = true;
					break;
				default:
					cout << "Error: That was not a valid option.\n" << endl;
					break;
				}
			}
		}
		else {
			cout << "You don't have enough stamina!" << endl;
		}
		break;
	case 2:
		if (player.stamina >= 20) {
			player.stamina -= 20;
			cout << "You charge at the enemies with your sword and shield out front!" << endl;
			if (enemy1.isActive) {
				if (20 + rand() % 100 >= enemy1.speed) {
					cout << "You hit " << enemy1.name << ", dealing " << ceil(player.strength * 2) << " damage to them!" << endl;
					if (enemy1.TakeDamage(ceil(player.strength * 2), false)) {
						cout << enemy1.name << " collapses dead!" << endl;
						goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
						cout << "+" << goldEarned << " gold earned!" << endl;
						player.gold += goldEarned;
					}
					cout << "You take 2 damage in return." << endl;
					player.TakeDamage(2, false);
				}
				else {
					cout << "You miss " + enemy1.name << "." << endl;
				}
			}

			if (enemy2.isActive) {
				if (20 + rand() % 100 >= enemy2.speed) {
					cout << "You hit " << enemy2.name << ", dealing " << ceil(player.strength * 2) << " damage to them!" << endl;
					if (enemy2.TakeDamage(ceil(player.strength * 2), false)) {
						cout << enemy2.name << " collapses dead!" << endl;
						goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
						cout << "+" << goldEarned << " gold earned!" << endl;
						player.gold += goldEarned;
					}
					cout << "You take 2 damage in return." << endl;
					player.TakeDamage(2, false);
				}
				else {
					cout << "You miss " + enemy2.name << "." << endl;
				}
			}

			if (enemy3.isActive) {
				if (20 + rand() % 100 >= enemy3.speed) {
					cout << "You hit " << enemy3.name << ", dealing " << ceil(player.strength * 2) << " damage to them!" << endl;
					if (enemy3.TakeDamage(ceil(player.strength * 2), false)) {
						cout << enemy3.name << " collapses dead!" << endl;
						goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
						cout << "+" << goldEarned << " gold earned!" << endl;
						player.gold += goldEarned;
					}
					cout << "You take 2 damage in return." << endl;
					player.TakeDamage(2, false);
				}
				else {
					cout << "You miss " + enemy3.name << "." << endl;
				}
			}
		}
		else {
			cout << "You don't have enough stamina!" << endl;
		}
		break;
	case 3:
		if (player.stamina >= 30) {
			player.stamina -= 30;
			while (!hasSelected) {
				cout << "Select your target:" << endl;
				if (enemy1.isActive) {
					cout << "1: " << enemy1.name << endl;
				}
				if (enemy2.isActive) {
					cout << "2: " << enemy2.name << endl;
				}
				if (enemy3.isActive) {
					cout << "3: " << enemy3.name << endl;
				}
				cout << "4: Cancel attack." << endl;
				int op = getInput();

				system("cls");
				switch (op) {
				case 1:
					if (enemy1.isActive) {
						cout << "You teleport behind " << enemy1.name << " and dealt " << (ceil(player.strength * 0.5)) * 5 << " damage!" << endl;
						if (enemy1.TakeDamage((ceil(player.strength * 0.5)) * 5, false)) {
							cout << enemy1.name << " collapses dead!" << endl;
							goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 2:
					if (enemy2.isActive) {
						cout << "You teleport behind " << enemy2.name << " and dealt " << (ceil(player.strength * 0.5)) * 5 << " damage!" << endl;
						if (enemy2.TakeDamage((ceil(player.strength * 0.5)) * 5, false)) {
							cout << enemy2.name << " collapses dead!" << endl;
							goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 3:
					if (enemy3.isActive) {
						cout << "You teleport behind " << enemy3.name << " and dealt " << (ceil(player.strength * 0.5)) * 5 << " damage!" << endl;
						if (enemy3.TakeDamage((ceil(player.strength * 0.5)) * 5, false)) {
							cout << enemy3.name << " collapses dead!" << endl;
							goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 4:
					player.stamina += 30;
					hasSelected = true;
					break;
				default:
					cout << "Error: That was not a valid option.\n" << endl;
					break;
				}
			}
		}
		else {
			cout << "You don't have enough stamina!" << endl;
		}
		break;
	case 4:
		if (player.stamina >= 25) {
			player.stamina -= 25;
			cout << "You restore a bit of your health, gaining " << ceil(player.maxHealth * 0.05) << " health." << endl;
			player.health += ceil(player.maxHealth * 0.05);
			if (player.health > player.maxHealth) {
				player.health = player.maxHealth;
			}
		} else {
			cout << "You don't have enough stamina!" << endl;
		}
		break;
	case 5:
		if (player.stamina >= 20) {
			player.stamina -= 20;
			while (!hasSelected) {
				cout << "Select your target:" << endl;
				if (enemy1.isActive) {
					cout << "1: " << enemy1.name << endl;
				}
				if (enemy2.isActive) {
					cout << "2: " << enemy2.name << endl;
				}
				if (enemy3.isActive) {
					cout << "3: " << enemy3.name << endl;
				}
				cout << "4: Cancel attack." << endl;
				int op = getInput();

				system("cls");
				switch (op) {
				case 1:
					if (enemy1.isActive) {
						if (rand() % 55 >= enemy1.speed) {
							cout << "You hit " << enemy1.name << " at a critical point and dealt " << ceil(player.strength * 2.5) << " damage!" << endl;
							if (enemy1.TakeDamage(ceil(player.strength * 2.5), false)) {
								cout << enemy1.name << " collapses dead!" << endl;
								goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						else {
							cout << "You tried to fire at " << enemy1.name << ", but you missed!" << endl;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 2:
					if (enemy2.isActive) {
						if (rand() % 55 >= enemy2.speed) {
							cout << "You hit " << enemy2.name << " at a critical point and dealt " << ceil(player.strength * 2.5) << " damage!" << endl;
							if (enemy2.TakeDamage(ceil(player.strength * 2.5), false)) {
								cout << enemy2.name << " collapses dead!" << endl;
								goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						else {
							cout << "You tried to fire at " << enemy2.name << ", but you missed!" << endl;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 3:
					if (enemy3.isActive) {
						if (rand() % 55 >= enemy3.speed) {
							cout << "You hit " << enemy3.name << " at a critical point and dealt " << ceil(player.strength * 2.5) << " damage!" << endl;
							if (enemy3.TakeDamage(ceil(player.strength * 2.5), false)) {
								cout << enemy3.name << " collapses dead!" << endl;
								goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						else {
							cout << "You tried to fire at " << enemy3.name << ", but you missed!" << endl;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 4:
					player.stamina += 20;
					hasSelected = true;
					break;
				default:
					cout << "Error: That was not a valid option.\n" << endl;
					break;
				}
			}
		}
		else {
			cout << "You don't have enough stamina!" << endl;
		}
		break;
	case 6:
		if (player.stamina >= 50) {
			player.stamina -= 50;
			while (!hasSelected) {
				cout << "Select your target:" << endl;
				if (enemy1.isActive) {
					cout << "1: " << enemy1.name << endl;
				}
				if (enemy2.isActive) {
					cout << "2: " << enemy2.name << endl;
				}
				if (enemy3.isActive) {
					cout << "3: " << enemy3.name << endl;
				}
				cout << "4: Cancel attack." << endl;
				int op = getInput();

				system("cls");
				switch (op) {
				case 1:
					if (enemy1.isActive) {
						cout << "You rush " << enemy1.name << "." << endl;
						for (int i = 0; i < 5; i++) {
							if (rand() % 80 >= enemy1.speed) {
								cout << "Hit! (" << ceil(player.strength * 1) << " damage)." << endl;
								enemy1.TakeDamage(ceil(player.strength * 1), false);
							}
						}
						if (enemy1.health <= 0) {
							cout << enemy1.name << " collapsed dead!" << endl;
							goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 2:
					if (enemy2.isActive) {
						cout << "You rush " << enemy2.name << "." << endl;
						for (int i = 0; i < 5; i++) {
							if (rand() % 80 >= enemy2.speed) {
								cout << "Hit! (" << ceil(player.strength * 1) << " damage)." << endl;
								enemy2.TakeDamage(ceil(player.strength * 1), false);
							}
						}
						if (enemy2.health <= 0) {
							cout << enemy2.name << " collapsed dead!" << endl;
							goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 3:
					if (enemy3.isActive) {
						cout << "You rush " << enemy3.name << "." << endl;
						for (int i = 0; i < 5; i++) {
							if (rand() % 80 >= enemy3.speed) {
								cout << "Hit! (" << ceil(player.strength * 1) << " damage)." << endl;
								enemy3.TakeDamage(ceil(player.strength * 1), false);
							}
						}
						if (enemy3.health <= 0) {
							cout << enemy3.name << " collapsed dead!" << endl;
							goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 4:
					player.stamina += 50;
					hasSelected = true;
					break;
				default:
					cout << "Error: That was not a valid option.\n" << endl;
					break;
				}
			}
		}
		else {
			cout << "You don't have enough stamina!" << endl;
		}
		break;
	case 7:
		if (player.stamina >= 70) {
			player.stamina -= 70;
			cout << "You slam on the ground, causing the entire cave to shake." << endl;
			if (enemy1.isActive) {
				if ( rand() % 60 >= enemy1.speed) {
					cout << enemy1.name << "is hit, dealing " << ceil(player.strength * 3) << " damage to them!" << endl;
					if (enemy1.TakeDamage(ceil(player.strength * 3), false)) {
						cout << enemy1.name << " collapses dead!" << endl;
						goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
						cout << "+" << goldEarned << " gold earned!" << endl;
						player.gold += goldEarned;
					}
				}
				else {
					cout << enemy1.name << " dodges." << endl;
				}
			}

			if (enemy2.isActive) {
				if (rand() % 60 >= enemy2.speed) {
					cout << enemy2.name << "is hit, dealing " << ceil(player.strength * 3) << " damage to them!" << endl;
					if (enemy2.TakeDamage(ceil(player.strength * 3), false)) {
						cout << enemy2.name << " collapses dead!" << endl;
						goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
						cout << "+" << goldEarned << " gold earned!" << endl;
						player.gold += goldEarned;
					}
				}
				else {
					cout << enemy2.name << " dodges." << endl;
				}
			}

			if (enemy3.isActive) {
				if (rand() % 60 >= enemy3.speed) {
					cout << enemy3.name << "is hit, dealing " << ceil(player.strength * 3) << " damage to them!" << endl;
					if (enemy3.TakeDamage(ceil(player.strength * 3), false)) {
						cout << enemy3.name << " collapses dead!" << endl;
						goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
						cout << "+" << goldEarned << " gold earned!" << endl;
						player.gold += goldEarned;
					}
				}
				else {
					cout << enemy3.name << " dodges." << endl;
				}
			}
		}
		else {
			cout << "You don't have enough stamina!" << endl;
		}
		break;
	case 8:
		if (player.stamina >= 25) {
			player.stamina -= 25;
			cout << "You restore a bit of your shield, gaining " << ceil(player.maxShield * 0.05) << " shield." << endl;
			player.shield += ceil(player.maxShield * 0.05);
			if (player.shield > player.maxShield) {
				player.shield = player.maxShield;
			}
		}
		else {
			cout << "You don't have enough stamina!" << endl;
		}
		break;
	case 9:
		if (player.stamina >= 70) {
			player.stamina -= 70;
			while (!hasSelected) {
				cout << "Select your target:" << endl;
				if (enemy1.isActive) {
					cout << "1: " << enemy1.name << endl;
				}
				if (enemy2.isActive) {
					cout << "2: " << enemy2.name << endl;
				}
				if (enemy3.isActive) {
					cout << "3: " << enemy3.name << endl;
				}
				cout << "4: Cancel attack." << endl;
				int op = getInput();

				system("cls");
				switch (op) {
				case 1:
					if (enemy1.isActive) {
						cout << "You clap your hands together in front of " << enemy1.name << "." << endl;
						if (rand() % 100 >= enemy1.speed) {
							cout << "The shockwave hits " << enemy1.name << ", dealing " << ceil(player.strength * 2) << " penetrating damage!" << endl;
							enemy1.TakeDamage(ceil(player.strength * 2), true);
							if (enemy2.isActive) {
								cout << enemy2.name << " takes " << ceil(player.strength * 1) << " damage!" << endl;
								enemy2.TakeDamage(ceil(player.strength * 1), false);
							}
							if (enemy3.isActive) {
								cout << enemy3.name << " takes " << ceil(player.strength * 1) << " damage!" << endl;
								enemy3.TakeDamage(ceil(player.strength * 1), false);
							}
						} else {
							cout << "Nothing happens." << endl;
						}
						if (enemy1.health <= 0) {
							cout << enemy1.name << " collapsed dead!" << endl;
							goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						if (enemy2.health <= 0 && enemy2.isActive) {
							cout << enemy2.name << " collapsed dead!" << endl;
							goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						if (enemy3.health <= 0 && enemy3.isActive) {
							cout << enemy3.name << " collapsed dead!" << endl;
							goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 2:
					if (enemy2.isActive) {
						cout << "You clap your hands together in front of " << enemy2.name << "." << endl;
						if (rand() % 100 >= enemy2.speed) {
							cout << "The shockwave hits " << enemy2.name << ", dealing " << ceil(player.strength * 2) << " penetrating damage!" << endl;
							enemy2.TakeDamage(ceil(player.strength * 2), true);
							if (enemy1.isActive) {
								cout << enemy1.name << " takes " << ceil(player.strength * 1) << " damage!" << endl;
								enemy1.TakeDamage(ceil(player.strength * 1), false);
							}
							if (enemy3.isActive) {
								cout << enemy3.name << " takes " << ceil(player.strength * 1) << " damage!" << endl;
								enemy3.TakeDamage(ceil(player.strength * 1), false);
							}
						} else {
							cout << "Nothing happens." << endl;
						}
						if (enemy2.health <= 0) {
							cout << enemy2.name << " collapsed dead!" << endl;
							goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						if (enemy1.health <= 0 && enemy1.isActive) {
							cout << enemy1.name << " collapsed dead!" << endl;
							goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						if (enemy3.health <= 0 && enemy3.isActive) {
							cout << enemy3.name << " collapsed dead!" << endl;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 3:
					if (enemy3.isActive) {
						cout << "You clap your hands together in front of " << enemy3.name << "." << endl;
						if (rand() % 100 >= enemy3.speed) {
							cout << "The shockwave hits " << enemy3.name << ", dealing " << ceil(player.strength * 2) << " penetrating damage!" << endl;
							enemy3.TakeDamage(ceil(player.strength * 2), true);
							if (enemy2.isActive) {
								cout << enemy2.name << " takes " << ceil(player.strength * 1) << " damage!" << endl;
								enemy2.TakeDamage(ceil(player.strength * 1), false);
							}
							if (enemy1.isActive) {
								cout << enemy1.name << " takes " << ceil(player.strength * 1) << " damage!" << endl;
								enemy1.TakeDamage(ceil(player.strength * 1), false);
							}
						} else {
							cout << "Nothing happens." << endl;
						}
						if (enemy3.health <= 0) {
							cout << enemy1.name << " collapsed dead!" << endl;
							goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						if (enemy2.health <= 0 && enemy2.isActive) {
							cout << enemy2.name << " collapsed dead!" << endl;
							goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						if (enemy1.health <= 0 && enemy1.isActive) {
							cout << enemy1.name << " collapsed dead!" << endl;
							goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
							cout << "+" << goldEarned << " gold earned!" << endl;
							player.gold += goldEarned;
						}
						hasSelected = true;
					}
					else {
						cout << "Error: That was an invalid option.\n" << endl;
					}
					break;
				case 4:
					player.stamina += 70;
					hasSelected = true;
					break;
				default:
					cout << "Error: That was not a valid option.\n" << endl;
					break;
				}
			}
		}
		else {
			cout << "You don't have enough stamina!" << endl;
		}
		break;
		case 10:
			if (player.stamina >= 60) {
				player.stamina -= 60;
				cout << "You pull out your crossbow and unleash a wave of bolts on the crowd." << endl;
				for (int i = 0; i < 3; i++) {
					if (rand() % 50 > 10) {
						cout << "All enemies are hit once, taking " << ceil(player.strength * 1.5) << " damage each!" << endl;
						if (enemy1.isActive) {
							enemy1.TakeDamage(ceil(player.strength * 1.5), false);
							if (enemy1.health <= 0) {
								cout << enemy1.name << " collapsed dead!" << endl;
								goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						if (enemy2.isActive) {
							enemy2.TakeDamage(ceil(player.strength * 1.5), false);
							if (enemy2.health <= 0) {
								cout << enemy2.name << " collapsed dead!" << endl;
								goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
						if (enemy3.isActive) {
							enemy3.TakeDamage(ceil(player.strength * 1.5), false);
							if (enemy3.health <= 0) {
								cout << enemy3.name << " collapsed dead!" << endl;
								goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
						}
					}
				}
			} else {
				cout << "You don't have enough stamina!" << endl;
			}
			break;
		case 11:
			if (player.stamina >= 50) {
				player.stamina -= 50;
				cout << "You restore some of your health and shield, gaining " << ceil(player.maxHealth * 0.3) << " health and " << ceil(player.maxShield * 0.3) << " shield." << endl;
				player.health += ceil(player.maxHealth * 0.3);
				if (player.health > player.maxHealth) {
					player.health = player.maxHealth;
				}
				player.shield += ceil(player.maxShield * 0.3);
				if (player.shield > player.maxShield) {
					player.shield = player.maxShield;
				}
			} else {
				cout << "You don't have enough stamina!" << endl;
			}
			break;
		case 12:
			if (player.stamina >= 30) {
				player.stamina -= 30;
				while (!hasSelected) {
					cout << "Select your target:" << endl;
					if (enemy1.isActive) {
						cout << "1: " << enemy1.name << endl;
					}
					if (enemy2.isActive) {
						cout << "2: " << enemy2.name << endl;
					}
					if (enemy3.isActive) {
						cout << "3: " << enemy3.name << endl;
					}
					cout << "4: Cancel attack." << endl;
					int op = getInput();

					system("cls");
					switch (op) {
					case 1:
						if (enemy1.isActive) {
							if (rand() % 80 >= enemy1.speed) {
								cout << "You hit " << enemy1.name << " with a mace and dealt " << ceil(player.strength * 2) << " penetrating damage!" << endl;
								if (enemy1.TakeDamage(ceil(player.strength * 2), true)) {
									cout << enemy1.name << " collapses dead!" << endl;
									goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
									cout << "+" << goldEarned << " gold earned!" << endl;
									player.gold += goldEarned;
								}
							}
							else {
								cout << "You tried to hit " << enemy1.name << " with a mace, but you missed!" << endl;
							}
							hasSelected = true;
						}
						else {
							cout << "Error: That was an invalid option.\n" << endl;
						}
						break;
					case 2:
						if (enemy2.isActive) {
							if (rand() % 80 >= enemy2.speed) {
								cout << "You hit " << enemy2.name << " with a mace and dealt " << ceil(player.strength * 2) << " penetrating damage!" << endl;
								if (enemy2.TakeDamage(ceil(player.strength * 2), true)) {
									cout << enemy2.name << " collapses dead!" << endl;
									goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
									cout << "+" << goldEarned << " gold earned!" << endl;
									player.gold += goldEarned;
								}
							}
							else {
								cout << "You tried to hit " << enemy2.name << " with a mace, but you missed!" << endl;
							}
							hasSelected = true;
						}
						else {
							cout << "Error: That was an invalid option.\n" << endl;
						}
						break;
					case 3:
						if (enemy3.isActive) {
							if (rand() % 80 >= enemy3.speed) {
								cout << "You hit " << enemy3.name << " with a mace and dealt " << ceil(player.strength * 2) << " penetrating damage!" << endl;
								if (enemy3.TakeDamage(ceil(player.strength * 2), true)) {
									cout << enemy3.name << " collapses dead!" << endl;
									goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
									cout << "+" << goldEarned << " gold earned!" << endl;
									player.gold += goldEarned;
								}
							}
							else {
								cout << "You tried to hit " << enemy3.name << " with a mace, but you missed!" << endl;
							}
							hasSelected = true;
						}
						else {
							cout << "Error: That was an invalid option.\n" << endl;
						}
						break;
					case 4:
						player.stamina += 30;
						hasSelected = true;
						break;
					default:
						cout << "Error: That was not a valid option.\n" << endl;
						break;
					}
				}
			}
			else {
				cout << "You don't have enough stamina!" << endl;
			}
			break;
		case 13:
			if (player.stamina >= 20) {
				player.stamina -= 20;
				while (!hasSelected) {
					cout << "Select your target:" << endl;
					if (enemy1.isActive) {
						cout << "1: " << enemy1.name << endl;
					}
					if (enemy2.isActive) {
						cout << "2: " << enemy2.name << endl;
					}
					if (enemy3.isActive) {
						cout << "3: " << enemy3.name << endl;
					}
					cout << "4: Cancel attack." << endl;
					int op = getInput();

					system("cls");
					switch (op) {
					case 1:
						if (enemy1.isActive) {
							cout << "You fire a homing bolt at " << enemy1.name << " and deal " << ceil(player.strength * 1.5) << " damage!" << endl;
							if (enemy1.TakeDamage(ceil(player.strength * 1.5), true)) {
								cout << enemy1.name << " collapses dead!" << endl;
								goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
							hasSelected = true;
						}
						else {
							cout << "Error: That was an invalid option.\n" << endl;
						}
						break;
					case 2:
						if (enemy2.isActive) {
							cout << "You fire a homing bolt at " << enemy2.name << " and deal " << ceil(player.strength * 1.5) << " damage!" << endl;
							if (enemy2.TakeDamage(ceil(player.strength * 1.5), true)) {
								cout << enemy2.name << " collapses dead!" << endl;
								goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
							hasSelected = true;
						}
						else {
							cout << "Error: That was an invalid option.\n" << endl;
						}
						break;
					case 3:
						if (enemy3.isActive) {
							cout << "You fire a homing bolt at " << enemy3.name << " and deal " << ceil(player.strength * 1.5) << " damage!" << endl;
							if (enemy3.TakeDamage(ceil(player.strength * 1.5), true)) {
								cout << enemy3.name << " collapses dead!" << endl;
								goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
							hasSelected = true;
						}
						else {
							cout << "Error: That was an invalid option.\n" << endl;
						}
						break;
					case 4:
						player.stamina += 20;
						hasSelected = true;
						break;
					default:
						cout << "Error: That was not a valid option.\n" << endl;
						break;
					}
				}
			}
			else {
				cout << "You don't have enough stamina!" << endl;
			}
			break;
		case 14:
			if (player.stamina >= 100) {
				player.stamina -= 100;
				while (!hasSelected) {
					cout << "Select your target:" << endl;
					if (enemy1.isActive) {
						cout << "1: " << enemy1.name << endl;
					}
					if (enemy2.isActive) {
						cout << "2: " << enemy2.name << endl;
					}
					if (enemy3.isActive) {
						cout << "3: " << enemy3.name << endl;
					}
					cout << "4: Cancel attack." << endl;
					int op = getInput();

					system("cls");
					switch (op) {
					case 1:
						if (enemy1.isActive) {
							cout << "You obliterated " << enemy1.name << " and dealt " << ceil(player.strength * 10) << " damage!" << endl;
							if (enemy1.TakeDamage(ceil(player.strength * 10), false)) {
								cout << enemy1.name << " collapses dead!" << endl;
								goldEarned = (enemy1.goldRewardMinimum + rand() % enemy1.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
							hasSelected = true;
						}
						else {
							cout << "Error: That was an invalid option.\n" << endl;
						}
						break;
					case 2:
						if (enemy2.isActive) {
							cout << "You obliterated " << enemy2.name << " and dealt " << ceil(player.strength * 10) << " damage!" << endl;
							if (enemy2.TakeDamage(ceil(player.strength * 10), false)) {
								cout << enemy2.name << " collapses dead!" << endl;
								goldEarned = (enemy2.goldRewardMinimum + rand() % enemy2.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
							hasSelected = true;
						}
						else {
							cout << "Error: That was an invalid option.\n" << endl;
						}
						break;
					case 3:
						if (enemy3.isActive) {
							cout << "You obliterated " << enemy3.name << " and dealt " << ceil(player.strength * 10) << " damage!" << endl;
							if (enemy3.TakeDamage(ceil(player.strength * 10), false)) {
								cout << enemy3.name << " collapses dead!" << endl;
								goldEarned = (enemy3.goldRewardMinimum + rand() % enemy3.goldRewardMaximum);
								cout << "+" << goldEarned << " gold earned!" << endl;
								player.gold += goldEarned;
							}
							hasSelected = true;
						}
						else {
							cout << "Error: That was an invalid option.\n" << endl;
						}
						break;
					case 4:
						player.stamina += 100;
						hasSelected = true;
						break;
					default:
						cout << "Error: That was not a valid option.\n" << endl;
						break;
					}
				}
			}
			else {
				cout << "You don't have enough stamina!" << endl;
			}
			break;
	}
	system("pause");
	system("cls");
}

// Function that handles enemy attack (Efficiency may be lacking due to repetition of else if).
void EnemyAttack(Enemy enemy, string AttackName, int enemyID) {  // Enemy attacks
	if (AttackName == "Bite") {
		if (rand() % 100 >= player.speed) {
			cout << enemy.name << " bit you, dealing " << ceil(enemy.strength) << " damage!" << endl;
			player.TakeDamage(ceil(enemy.strength), false);
		} else {
			cout << enemy.name << " tried to bite you but missed!" << endl;
		}
	} else if (AttackName == "Strike") {
		if (10 + rand() % 100 >= player.speed) {
			cout << enemy.name << " struck you, dealing " << ceil(enemy.strength * 0.9) << " damage!" << endl;
			player.TakeDamage(ceil(enemy.strength * 0.9), false);
		}
		else {
			cout << enemy.name << " tried to strike you but missed!" << endl;
		}
	} else if (AttackName == "Defend") {
		cout << enemy.name << " defends themselves, gaining " << ceil(enemy.maxShield * 0.1) << " shield!" << endl;
		enemy.shield += ceil(enemy.maxShield * 0.1);
		if (enemy.shield > enemy.maxShield) {
			enemy.shield = enemy.maxShield;
		}
		switch (enemyID) {
		case 1:
			enemy1 = enemy;
			break;
		case 2:
			enemy2 = enemy;
			break;
		case 3:
			enemy3 = enemy;
			break;
		}
	} else if (AttackName == "Fury Strike") {
		cout << enemy.name << " rushes you and launches several attacks!" << endl;
		for (int i = 0; i < 3; i++) {
			if (rand() % 80 >= player.speed) {
				cout << "Hit (" << ceil(enemy.strength * 0.6) << " damage)!" << endl;
				player.TakeDamage(ceil(enemy.strength * 0.6), false);
			} else {
				cout << "Miss!" << endl;
			}
		}
	} else if (AttackName == "Toxin Bite") {
		if (rand() % 90 >= player.speed) {
			cout << enemy.name << " bit you, dealing " << ceil(enemy.strength * 1.2) << " penetrating damage!" << endl;
			player.TakeDamage(ceil(enemy.strength * 1.2), true);
		}
		else {
			cout << enemy.name << " tried to toxic bite you but missed!" << endl;
		}
	} else if (AttackName == "Charge") {
		cout << enemy.name << " charged directly at you!" << endl;
		if (rand() % 90 >= player.speed) {
			cout << "Hit (" << ceil(enemy.strength * 1.5) << " damage)!" << endl;
			player.TakeDamage(ceil(enemy.strength * 1.5), false);
		}
		else {
			cout << "Miss!" << endl;
		}
	} else if (AttackName == "Bow Shot") {
		if (rand() % 80 >= player.speed) {
			cout << enemy.name << " fired an arrow at you, dealing " << ceil(enemy.strength * 1.5) << " damage!" << endl;
			player.TakeDamage(ceil(enemy.strength * 1.5), false);
		}
		else {
			cout << enemy.name << " tried to fire an arrow at you you but missed!" << endl;
		}
	}
	else if (AttackName == "Stomp") {
		if (10 + rand() % 100 >= player.speed) {
			cout << enemy.name << " leapt up and slammed on the ground, causing you to take " << ceil(enemy.strength * 2) << " damage!" << endl;
			player.TakeDamage(ceil(enemy.strength * 2), false);
		} else {
			cout << enemy.name << " leapt up and slammed on the ground, but you managed to avoid the shockwave." << endl;
		}
	} else if (AttackName == "Regenerate") {
		cout << enemy.name << " regenerates themselves, healing " << ceil(enemy.maxHealth * 0.1) << " health!" << endl;
		enemy.health += ceil(enemy.maxHealth * 0.1);
		if (enemy.health > enemy.maxHealth) {
			enemy.health = enemy.maxHealth;
		}
		switch (enemyID) {
		case 1:
			enemy1 = enemy;
			break;
		case 2:
			enemy2 = enemy;
			break;
		case 3:
			enemy3 = enemy;
			break;
		}
	} else if (AttackName == "Shift") {
		cout << enemy.name << " teleports behind you and strikes you multiple times, dealing " << 3 * (ceil(enemy.strength * 0.7)) << endl;
		player.TakeDamage(3 * (ceil(enemy.strength * 0.7)), false);
	} else if (AttackName == "Area Regenerate") {
		cout << enemy.name << " casts an area regenerate spell, healing everyone on their side!" << endl;
		if (enemy1.isActive) {
			cout << enemy1.name << " gained " << ceil(enemy1.maxHealth * 0.1) << " health." << endl;
			enemy1.health += ceil(enemy1.maxHealth * 0.1);
			if (enemy1.health > enemy1.maxHealth) {
				enemy1.health = enemy1.maxHealth;
			}
		}
		if (enemy2.isActive) {
			cout << enemy2.name << " gained " << ceil(enemy2.maxHealth * 0.1) << " health." << endl;
			enemy2.health += ceil(enemy2.maxHealth * 0.1);
			if (enemy2.health > enemy2.maxHealth) {
				enemy2.health = enemy2.maxHealth;
			}
		}
		if (enemy3.isActive) {
			cout << enemy3.name << " gained " << ceil(enemy3.maxHealth * 0.1) << " health." << endl;
			enemy3.health += ceil(enemy3.maxHealth * 0.1);
			if (enemy3.health > enemy3.maxHealth) {
				enemy3.health = enemy3.maxHealth;
			}
		}
	} else if (AttackName == "Laser") {
		if (rand() % 100 >= player.speed) {
			cout << enemy.name << " fires a laser at you, " << ceil(enemy.strength * 2) << " penetrating damage!" << endl;
			player.TakeDamage(ceil(enemy.strength * 2), true);
		}
		else {
			cout << enemy.name << " tried to fire a laser at you but missed!" << endl;
		}
	} else {
		if (rand() % 90 >= player.speed) {
			cout << enemy.name << " basically anihilates you, dealing " << ceil(enemy.strength * 6) << " damage!" << endl;
			player.TakeDamage(ceil(enemy.strength * 6), false);
		}
		else {
			cout << enemy.name << " tried to anihilate you but missed!" << endl;
		}
	}
}

// Function that handles the player using a potion.
void usePotion() {
	bool hasSelected = false;
	while (!hasSelected) {
		cout << "Your potions:" << endl;
		for (int i = 0; i < player.potions.size(); i++) {
			cout << i + 1 << ": " << player.potions[i] << endl;
		}
		cout << player.potions.size() + 1 << ": Back." << endl;
		cout << "\nSelect a potion to use: ";
		int op = getInput();

		system("cls");
		if (op >= 1 && op <= player.potions.size()) {
			cout << "You used the " << player.potions[op - 1] << "!" << endl;
			if (player.potions[op - 1] == "Health Potion") {
				cout << "You regained " << ceil(player.maxHealth * 0.25) << " health!" << endl;
				player.health += ceil(player.maxHealth * 0.25);
				if (player.health > player.maxHealth) {
					player.health = player.maxHealth;
				}
			} else if (player.potions[op - 1] == "Shield Potion") {
				cout << "You regained " << ceil(player.maxShield * 0.25) << " shield!" << endl;
				player.shield += ceil(player.maxShield * 0.25);
				if (player.shield > player.maxShield) {
					player.shield = player.maxShield;
				}
			} else if (player.potions[op - 1] == "Stamina Potion") {
				cout << "You regained " << ceil(player.maxStamina * 0.25) << " stamina!" << endl;
				player.stamina += ceil(player.maxStamina * 0.25);
				if (player.stamina > player.maxStamina) {
					player.stamina = player.maxStamina;
				}
			} else if (player.potions[op - 1] == "Strong Health Potion") {
				cout << "You regained " << ceil(player.maxHealth * 0.5) << " health!" << endl;
				player.health += ceil(player.maxHealth * 0.5);
				if (player.health > player.maxHealth) {
					player.health = player.maxHealth;
				}
			}
			else if (player.potions[op - 1] == "Strong Shield Potion") {
				cout << "You regained " << ceil(player.maxShield * 0.5) << " shield!" << endl;
				player.shield += ceil(player.maxShield * 0.5);
				if (player.shield > player.maxShield) {
					player.shield = player.maxShield;
				}
			}
			else if (player.potions[op - 1] == "Strong Stamina Potion") {
				cout << "You regained " << ceil(player.maxStamina * 0.5) << " stamina!" << endl;
				player.stamina += ceil(player.maxStamina * 0.5);
				if (player.stamina > player.maxStamina) {
					player.stamina = player.maxStamina;
				}
			}
			player.potions.erase(player.potions.begin() + (op - 1));
		} else if (op == player.potions.size() + 1) {
			hasSelected = true;
		} else {
			cout << "That was not a valid option.\n" << endl;
		}
	}
}

// Function that handles basic combat GUI.
void Combat() {
	bool BattleOver = false;
	if (player.selectedClass == 1) {
		player.shield += ceil(player.maxShield / 2);
		if (player.shield > player.maxShield) {
			player.shield = player.maxShield;
		}
	}

	bool playerTurnDone = false;
	while (!BattleOver) {
		system("cls");
		if (!enemy1.isActive && !enemy2.isActive && !enemy3.isActive) {
			cout << "You won!" << endl;
			chanceOfAttack = 5;
			player.stamina = player.maxStamina;
			if (player.selectedClass == 3) {
				player.health += ceil(player.maxHealth * 0.2);
				if (player.health > player.maxHealth) {
					player.health = player.maxHealth;
				}
			}
			system("pause");
			system("cls");
			BattleOver = true;
			break;
			hub();
		}
		cout << "You:" << endl;
		cout << "Health: (";
		for (int i = 0; i < player.maxHealth; i++) {
			if (i + 1 > player.health) {
				cout << " ";
			}
			else {
				cout << "|";
			}
		}
		cout << ")" << endl;

		cout << "Shield: (";
		for (int i = 0; i < player.maxShield; i++) {
			if (i + 1 > player.shield) {
				cout << " ";
			}
			else {
				cout << "|";
			}
		}
		cout << ")" << endl;
		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << player.actions[i] << " (" << GetStaminaCost(player.actions[i]) << " stamina):" << endl;
			cout << GetAttackDescription(player.actions[i]) << "\n" << endl;
		}
		cout << "=============================================================================" << endl;
		cout << endl;
		if (enemy1.isActive) {
			cout << enemy1.name << ":" << endl;
			cout << "Health: (";
			for (int i = 0; i < enemy1.maxHealth; i++) {
				if (i + 1 > enemy1.health) {
					cout << " ";
				}
				else {
					cout << "|";
				}
			}
			cout << ")" << endl;

			if (enemy1.maxShield > 0) {
				cout << "Shield: (";
				for (int i = 0; i < enemy1.maxShield; i++) {
					if (i + 1 > enemy1.shield) {
						cout << " ";
					}
					else {
						cout << "|";
					}
				}
				cout << ")" << endl;
				
			}
			cout << endl;
		}
		if (enemy2.isActive) {
			cout << enemy2.name << ":" << endl;
			cout << "Health: (";
			for (int i = 0; i < enemy2.maxHealth; i++) {
				if (i + 1 > enemy2.health) {
					cout << " ";
				}
				else {
					cout << "|";
				}
			}
			cout << ")" << endl;

			if (enemy2.maxShield > 0) {
				cout << "Shield: (";
				for (int i = 0; i < enemy2.maxShield; i++) {
					if (i + 1 > enemy2.shield) {
						cout << " ";
					}
					else {
						cout << "|";
					}
				}
				cout << ")" << endl;
			}
			cout << endl;
		}
		if (enemy3.isActive) {
			cout << enemy3.name << ":" << endl;
			cout << "Health: (";
			for (int i = 0; i < enemy3.maxHealth; i++) {
				if (i + 1 > enemy3.health) {
					cout << " ";
				}
				else {
					cout << "|";
				}
			}
			cout << ")" << endl;
			if (enemy3.maxShield > 0) {
				cout << "Shield: (";
				for (int i = 0; i < enemy3.maxShield; i++) {
					if (i + 1 > enemy3.shield) {
						cout << " ";
					}
					else {
						cout << "|";
					}
				}
				cout << ")" << endl;	
			}
			cout << endl;
		}
		cout << "Your turn." << endl;
		cout << "You have " << player.stamina << " stamina left.\n" << endl;
		cout << "1: " << player.actions[0] << "." << endl;
		cout << "2: " << player.actions[1] << "." << endl;
		cout << "3: " << player.actions[2] << "." << endl;
		cout << "4: " << player.actions[3] << "." << endl;
		cout << "5: " << player.actions[4] << "." << endl;
		if (player.potions.size() != 0) {
			cout << "6: Use a potion." << endl;
			cout << "7: Flee." << endl;
			cout << "8: End turn." << endl;
		} else {
			cout << "6: Flee." << endl;
			cout << "7: End turn" << endl;
		}
		int op = getInput();

		system("cls");
		switch (op) {
		case 1:
			useAction(GetAttackID(player.actions[0]));
			break;
		case 2:
			useAction(GetAttackID(player.actions[1]));
			break;
		case 3:
			useAction(GetAttackID(player.actions[2]));
			break;
		case 4:
			useAction(GetAttackID(player.actions[3]));
			break;
		case 5:
			useAction(GetAttackID(player.actions[4]));
			break;
		case 6:
			if (player.potions.size() != 0) {
				usePotion();
			} else { // Fleeing from battles.
				cout << "You attempt to flee from the battle." << endl;
				if (rand() % 100 < player.speed) {
					cout << "You successfully ran from the battle!" << endl;
					BattleOver = true;
				} else {
					cout << "You failed to flee from the battle!" << endl;
					playerTurnDone = true;
					system("pause");
				}
			}
			break;
		case 7:
			if (player.potions.size() != 0) {
				cout << "You attempt to flee from the battle." << endl;
				if (rand() % 100 < player.speed) {
					cout << "You successfully ran from the battle!" << endl;
					BattleOver = true;
				}
				else {
					cout << "You failed to flee from the battle!" << endl;
					playerTurnDone = true;
					system("pause");
				}
			}
			else {
				playerTurnDone = true;
			}
			break;
		case 8:
			if (player.potions.size() != 0) {
				playerTurnDone = true;
			} else {
				cout << "Error: That wasn't a valid option.\n" << endl;
			}
			break;
		default:
			cout << "Error: That wasn't a valid option.\n" << endl;
			break;
		}
		if (playerTurnDone) {
			system("cls");
			cout << "Enemy turn!" << endl;
			int selectedAttack = 0;
			
			if (enemy1.isActive) {
				selectedAttack = (1 + rand() % enemy1.attacks.size()) - 1;
				EnemyAttack(enemy1, enemy1.attacks[selectedAttack], 1);
				if (player.health <= 0) {
					cout << "You fell to the floor, dead..." << endl;
					system("pause");
					gameOver();
				}
				cout << endl;
			}
			if (enemy2.isActive) {
				selectedAttack = (1 + rand() % enemy2.attacks.size()) - 1;
				EnemyAttack(enemy2, enemy2.attacks[selectedAttack], 2);
				if (player.health <= 0) {
					cout << "You fell to the floor, dead..." << endl;
					system("pause");
					gameOver();
				}
				cout << endl;
			}
			if (enemy3.isActive) {
				selectedAttack = (1 + rand() % enemy3.attacks.size()) - 1;
				EnemyAttack(enemy3, enemy3.attacks[selectedAttack], 3);
				if (player.health <= 0) {
					cout << "You fell to the floor, dead..." << endl;
					system("pause");
					gameOver();
				}
				cout << endl;
			}
			system("pause");
			system("cls");
			playerTurnDone = false;
			if (player.selectedClass == 2) {
				player.stamina += ceil(player.maxStamina * 0.75);
			} else {
				player.stamina += ceil(player.maxStamina * 0.5);
			}
			if (player.stamina > player.maxStamina) {
				player.stamina = player.maxStamina;
			}
		}
	}
}

// Funciton that handles randomising the type of potion the player gets.
void GetRandomPotion() {
	srand(time(0));
	int potion = 1 + rand() % 6;
	switch (potion) {
	case 1:
		cout << "You found a health potion!" << endl;
		player.potions.push_back("Health Potion");
		break;
	case 2:
		cout << "You found a shield potion!" << endl;
		player.potions.push_back("Shield Potion");
		break;
	case 3:
		cout << "You found a stamina potion!" << endl;
		player.potions.push_back("Stamina Potion");
		break;
	case 4:
		cout << "You found a strong health potion!" << endl;
		player.potions.push_back("Strong Health Potion");
		break;
	case 5:
		cout << "You found a strong shield potion!" << endl;
		player.potions.push_back("Strong Shield Potion");
		break;
	case 6:
		cout << "You found a strong stamina potion!" << endl;
		player.potions.push_back("Strong Stamina Potion");
		break;
	}
}

// Function that handles both the player getting a random action and then replacing actions.
void GetNewAttack(string attackName) {
	bool hasAction = false;
	for (int i = 0; i < 5; i++) {
		if (player.actions[i] == attackName) {
			hasAction = true;
			break;
		}
	}
	if (!hasAction) {
		bool hasSelected = false;
		bool wantsToReplace = false;
		while (!hasSelected) {
			cout << "Would you like to replace one of your current actions with this action?" << endl;
			cout << "1: Yes." << endl;
			cout << "2: No." << endl;
			cout << "\n" << attackName << " (" << GetStaminaCost(attackName) << " stamina):" << endl;
			cout << GetAttackDescription(attackName) << "\n" << endl;
			int op = getInput();

			system("cls");
			switch (op) {
			case 1:
				wantsToReplace = true;
				hasSelected = true;
				break;
			case 2:
				hasSelected = true;
				break;
			default:
				cout << "Error: That wasn't a valid option.\n" << endl;
				break;
			}
		}

		if (wantsToReplace) {
			hasSelected = false;
			while (!hasSelected) {
				cout << "Select the action you want to replace with " << attackName << " (" << GetStaminaCost(attackName) << " stamina)." << endl;
				cout << GetAttackDescription(attackName) << "\n" << endl;
				cout << "=============================================================================" << endl;

				for (int i = 0; i < 5; i++) {
					cout << i + 1 << ": " << player.actions[i] << " (" << GetStaminaCost(player.actions[i]) << " stamina):" << endl;
					cout << GetAttackDescription(player.actions[i]) << "\n" << endl;
				}
				cout << "=============================================================================" << endl;
				cout << "Enter 6 to cancel." << endl;
				int op = getInput();

				system("cls");
				switch (op) {
				case 1:
					cout << "You replaced " << player.actions[0] << " with " << attackName << "." << endl;
					player.actions[0] = attackName;
					hasSelected = true;
					break;
				case 2:
					cout << "You replaced " << player.actions[1] << " with " << attackName << "." << endl;
					player.actions[1] = attackName;
					hasSelected = true;
					break;
				case 3:
					cout << "You replaced " << player.actions[2] << " with " << attackName << "." << endl;
					player.actions[2] = attackName;
					hasSelected = true;
					break;
				case 4:
					cout << "You replaced " << player.actions[3] << " with " << attackName << "." << endl;
					player.actions[3] = attackName;
					hasSelected = true;
					break;
				case 5:
					cout << "You replaced " << player.actions[4] << " with " << attackName << "." << endl;
					player.actions[4] = attackName;
					hasSelected = true;
					break;
				case 6:
					cout << "You decided not to replace one of your actions." << endl;
					hasSelected = true;
					break;
				default:
					cout << "Error: That wasn't a valid option.\n" << endl;
					break;
				}
			}
		} else {
			cout << "You drop the scroll, happy with your current actions." << endl;
		}

	} else {
		cout << "You already have the action, so you drop the scroll and move on." << endl;
	}
}

// Function that handles exploration GUI.
void explore() {
	cout << "You explore the place." << endl;
	roomsExplored += 1;
	if (checkForBoss()) {
		if (currentFloor == 6) {
			cout << "You discover Omega's location. You mark its location on your map." << endl;
		}
		else {
			cout << "You discover the way down, but know it's guarded by a powerful force. You mark its location on your map." << endl;
		}
		hasFoundBoss = true;
	} else if (checkForShop()) {
		if (currentFloor == 6) {
			cout << "You found a shop in the void! You mark its location on your map." << endl;
		}
		else if (currentFloor == 5) {
			cout << "You found a shop in the base! You mark its location on your map." << endl;
		}
		else {
			cout << "You found a shop in the caverns! You mark its location on your map." << endl;
		}
		hasDiscoveredShop = true;
	} else if (checkForElite()) {
		cout << "You discover a lair that belongs to a powreful beast. You mark its location on your map." << endl;
		eliteStatus = 1;
	} else {
		int randomExploration = 1 + rand() % 100;
		if (randomExploration < 40) {
			cout << "You found nothing of interest." << endl;
			turnsOfEnemy = 0;
			turnsOfTreasure = 0;
		} else if (randomExploration < 70) {
			if (turnsOfEnemy >= 2) {
				cout << "You found nothing of interest." << endl;
				turnsOfEnemy = 0;
				turnsOfTreasure = 0;
			} else {
				turnsOfEnemy += 1;
				enemy1 = enemies[currentFloor - 1][rand() % enemies[currentFloor - 1].size()];
				enemy2 = enemies[currentFloor - 1][rand() % enemies[currentFloor - 1].size()];
				enemy3 = enemies[currentFloor - 1][rand() % enemies[currentFloor - 1].size()];

				if (roomsExplored < 20) {
					enemy3.isActive = false;
				}
				if (roomsExplored < 10) {
					enemy2.isActive = false;
				}
				bool canStealth = false;
				if (1 + rand() % 4 != 2) {
					canStealth = true;
				}
				if (canStealth) {
					bool hasSelected = false;
					while (!hasSelected) {
						cout << "You enter a room and see a " << enemy1.name;
						if (enemy2.isActive) {
							cout << ", " << enemy2.name;
						}
						if (enemy3.isActive) {
							cout << ", " << enemy3.name;
						}
						cout << " and some dead corpses in a room." << endl;
						cout << "They haven't spotted you yet. Do you wish to engage?" << endl;
						cout << "1: Yes." << endl;
						cout << "2: No." << endl;
						int op = getInput();

						system("cls");
						switch (op) {
						case 1:
							cout << "You charge right into battle!" << endl;
							system("pause");
							Combat();
							hasSelected = true;
							break;
						case 2:
							cout << "You sneak past them, avoiding combat." << endl;
							hasSelected = true;
							break;
						default:
							cout << "Error: That wasn't a valid option.\n" << endl;
							break;
						}
					}
				} else {
					cout << "You enter a room and see a " << enemy1.name;
					if (enemy2.isActive) {
						cout << ", " << enemy2.name;
					}
					if (enemy3.isActive) {
						cout << ", " << enemy3.name;
					}
					cout << " and some dead corpses in a room." << endl;
					cout << "They've spotted you! Combat is inevitable!" << endl;
					system("pause");
					Combat();
				}
			}
		} else {
			if (turnsOfTreasure >= 2) {
				cout << "You found nothing of interest." << endl;
				turnsOfEnemy = 0;
				turnsOfTreasure = 0;
			} else {
				turnsOfTreasure += 1;
				cout << "You discover a chest and open it." << endl;
				int treasureFound = 1 + rand() % 3;
				int goldFound = 0;
				switch (treasureFound) {
				case 1: // Gold.
					goldFound = currentFloor * (6 + rand() % 12);
					cout << "You found " << goldFound << " gold!" << endl;
					player.gold += goldFound;
					break;
				case 2: // Potion.
					GetRandomPotion();
					break;
				case 3: // Action.
					string action = GetRandomAttack();
					cout << "You found a scroll describing a move called " << action << "." << endl;
					GetNewAttack(action);
					break;
				}
			}
		}
	}
	cout << "\n" << endl;
	system("pause");
	system("cls");
}

// Function that handles resting (Both GUI and Code).
void rest() {
	bool restDone = false;
	while (!restDone) {
		bool hasSelected = false;
		while(!hasSelected) {
			cout << "You are currently resting near a bonfire." << endl;
			cout << "=============================================================================" << endl;
			cout << "Health: (";
			for (int i = 0; i < player.maxHealth; i++) {
				if (i + 1 > player.health) {
					cout << " ";
				}
				else {
					cout << "|";
				}
			}
			cout << ")" << endl;

			cout << "Shield: (";
			for (int i = 0; i < player.maxShield; i++) {
				if (i + 1 > player.shield) {
					cout << " ";
				}
				else {
					cout << "|";
				}
			}
			cout << ")" << endl;
			cout << "=============================================================================" << endl;
			cout << "1: Rest." << endl;
			cout << "2: Repair Armour." << endl;
			cout << "3: Finish Rest." << endl;
			int op = getInput();

			system("cls");
			switch (op) {
			case 1:
				cout << "You go to sleep." << endl;
				cout << "+" << ceil(player.maxHealth * 0.1) << " health." << endl;
				player.health += ceil(player.maxHealth * 0.1);
				if (player.health > player.maxHealth) {
					player.health = player.maxHealth;
				}
				if (rand() % 100 <= chanceOfAttack) {
					chanceOfAttack = 5;
					enemy1 = enemies[currentFloor - 1][rand() % enemies[currentFloor - 1].size()];
					enemy2 = enemies[currentFloor - 1][rand() % enemies[currentFloor - 1].size()];
					enemy3 = enemies[currentFloor - 1][rand() % enemies[currentFloor - 1].size()];

					if (roomsExplored < 20) {
						enemy3.isActive = false;
					}
					if (roomsExplored < 10) {
						enemy2.isActive = false;
					}
					cout << "You wake up and see " << enemy1.name;
					if (enemy2.isActive) {
						cout << ", " << enemy2.name;
					}
					if (enemy3.isActive) {
						cout << ", " << enemy3.name;
					}
					cout << " charging right at you!" << endl;
					system("pause");
					Combat();
				} else {
					chanceOfAttack += 10;
					cout << "You wake up without any issues." << endl;
					system("pause");
					system("cls");
				}
				break;
			case 2:
				cout << "You take about an hour reforging your armour." << endl;
				cout << "+" << ceil(player.maxShield * 0.2) << " shield." << endl;
				player.shield += ceil(player.maxShield * 0.2);
				if (player.shield > player.maxShield) {
					player.shield = player.maxShield;
				}
				if (rand() % 100 <= chanceOfAttack) {
					chanceOfAttack = 5;
					enemy1 = enemies[currentFloor - 1][rand() % enemies[currentFloor - 1].size()];
					enemy2 = enemies[currentFloor - 1][rand() % enemies[currentFloor - 1].size()];
					enemy3 = enemies[currentFloor - 1][rand() % enemies[currentFloor - 1].size()];

					if (roomsExplored < 20) {
						enemy3.isActive = false;
					}
					if (roomsExplored < 10) {
						enemy2.isActive = false;
					}
					cout << "You finish, but hear " << enemy1.name;
					if (enemy2.isActive) {
						cout << ", " << enemy2.name;
					}
					if (enemy3.isActive) {
						cout << ", " << enemy3.name;
					}
					cout << " charging right at you!" << endl;
					system("pause");
					Combat();
				}
				else {
					chanceOfAttack += 10;
					cout << "You finish without any issues." << endl;
					system("pause");
					system("cls");
				}
				break;
			case 3:
				cout << "You get up and put out the bonfire." << endl;
				restDone = true;
				hasSelected = true;
				system("pause");
				system("cls");
				break;
			default:
				cout << "Error: That was not a valid option.\n" << endl;
				break;
			}
		}
	}
}

// Function that handles the shop (GUI and Code).
void shop() {
	bool hasFinished = false;
	cout << "Shopkeeper: What can I do for you?\n" << endl;
	while (!hasFinished) {
		cout << "Gold: " << player.gold << " gold." << endl;
		cout << "1: Buy Health Potion (" << 15 * currentFloor << " gold)." << endl;
		cout << "2: Buy Shield Potion (" << 10 * currentFloor << " gold)." << endl;
		cout << "3: Buy Stamina Potion (" << 15 * currentFloor << " gold)." << endl;
		if (availableUpgrades[0]) {
			cout << "4: Upgrade Armour (" << 20 * currentFloor << " gold)." << endl;
		}
		if (availableUpgrades[1]) {
			cout << "5: Upgrade Health (" << 30 * currentFloor << " gold)." << endl;
		}
		if (availableUpgrades[2]) {
			cout << "6: Upgrade Stamina (" << 35 * currentFloor << " gold)." << endl;
		}
		if (availableUpgrades[3]) {
			cout << "7: Upgrade Speed (" << 40 * currentFloor << " gold)." << endl;
		}
		if (availableUpgrades[4]) {
			cout << "8: Upgrade Strength (" << 60 * currentFloor << " gold)." << endl;
		}
		if (currentFloor >= 3) {
			cout << "9: Buy Strong Health Potion (" << 30 * currentFloor << " gold)." << endl;
			cout << "10: Buy Strong Shield Potion (" << 20 * currentFloor << " gold)." << endl;
			cout << "11: Buy Strong Stamina Potion (" << 30 * currentFloor << " gold)." << endl;
		}
		cout << "12: Leave." << endl;
		int op = getInput();
		system("cls");
		switch (op) {
		case 1:
			if (player.gold >= 15 * currentFloor) {
				player.gold -= 15 * currentFloor;
				player.potions.push_back("Health Potion");
				cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
			} else {
				cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
			}
			break;
		case 2:
			if (player.gold >= 10 * currentFloor) {
				player.gold -= 10 * currentFloor;
				player.potions.push_back("Shield Potion");
				cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
			}
			else {
				cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
			}
			break;
		case 3:
			if (player.gold >= 15 * currentFloor) {
				player.gold -= 15 * currentFloor;
				player.potions.push_back("Stamina Potion");
				cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
			}
			else {
				cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
			}
			break;
		case 4:
			if (availableUpgrades[0]) {
				if (player.gold >= 20 * currentFloor) {
					player.gold -= 20 * currentFloor;
					availableUpgrades[0] = false;
					cout << "Maximum shield upgraded!" << endl;
					cout << player.maxShield << " --> " << player.maxShield + 3 << "!" << endl;
					player.maxShield += 3;
					player.shield = player.maxShield;
					system("pause");
					system("cls");
					cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
				}
				else {
					cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
				}
			} else {
				cout << "Error: That wasn't a valid option.\n" << endl;
			}
			break;
		case 5:
			if (availableUpgrades[1]) {
				if (player.gold >= 30 * currentFloor) {
					player.gold -= 30 * currentFloor;
					availableUpgrades[1] = false;
					cout << "Maximum health upgraded!" << endl;
					cout << player.maxHealth << " --> " << player.maxHealth + 3 << "!" << endl;
					player.maxHealth += 3;
					player.health = player.maxHealth;
					system("pause");
					system("cls");
					cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
				}
				else {
					cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
				}
			}
			else {
				cout << "Error: That wasn't a valid option.\n" << endl;
			}
			break;
		case 6:
			if (availableUpgrades[2]) {
				if (player.gold >= 35 * currentFloor) {
					player.gold -= 35 * currentFloor;
					availableUpgrades[2] = false;
					cout << "Maximum stamina upgraded!" << endl;
					cout << player.maxStamina << " --> " << player.maxStamina + 20 << "!" << endl;
					player.maxStamina += 20;
					player.stamina = player.maxStamina;
					system("pause");
					system("cls");
					cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
				}
				else {
					cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
				}
			}
			else {
				cout << "Error: That wasn't a valid option.\n" << endl;
			}
			break;
		case 7:
			if (availableUpgrades[3]) {
				if (player.gold >= 40 * currentFloor) {
					player.gold -= 40 * currentFloor;
					availableUpgrades[3] = false;
					cout << "Maximum speed upgraded!" << endl;
					cout << player.speed << " --> " << player.speed + 2 << "!" << endl;
					player.speed += 2;
					system("pause");
					system("cls");
					cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
				}
				else {
					cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
				}
			}
			else {
				cout << "Error: That wasn't a valid option.\n" << endl;
			}
			break;
		case 8:
			if (availableUpgrades[4]) {
				if (player.gold >= 60 * currentFloor) {
					player.gold -= 60 * currentFloor;
					availableUpgrades[4] = false;
					cout << "Maximum strength upgraded!" << endl;
					cout << player.strength << " --> " << player.strength + 0.25 << "!" << endl;
					player.strength += 0.25;
					system("pause");
					system("cls");
					cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
				}
				else {
					cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
				}
			}
			else {
				cout << "Error: That wasn't a valid option.\n" << endl;
			}
			break;
		case 9:
			if (currentFloor >= 3) {
				if (player.gold >= 30 * currentFloor) {
					player.gold -= 30 * currentFloor;
					player.potions.push_back("Strong Health Potion");
					cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
				}
				else {
					cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
				}
			} else {
				cout << "Error: That was an invalid option.\n" << endl;
			}
			break;
		case 10:
			if (currentFloor >= 3) {
				if (player.gold >= 20 * currentFloor) {
					player.gold -= 20 * currentFloor;
					player.potions.push_back("Strong Shield Potion");
					cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
				}
				else {
					cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
				}
			}
			else {
				cout << "Error: That was an invalid option.\n" << endl;
			}
			break;
		case 11:
			if (currentFloor >= 3) {
				if (player.gold >= 30 * currentFloor) {
					player.gold -= 30 * currentFloor;
					player.potions.push_back("Strong Stamina Potion");
					cout << "Shopkeeper: Thank you for the purchase!\n" << endl;
				}
				else {
					cout << "Shopkeeper: You ain't got enough gold!\n" << endl;
				}
			}
			else {
				cout << "Error: That was an invalid option.\n" << endl;
			}
			break;
		case 12:
			cout << "Shopkeeper: Come back anytime!" << endl;
			hasFinished = true;
			system("pause");
			system("cls");
			break;
		default:
			cout << "Error: That wasn't a valid option.\n" << endl;
			break;
		}
	}
}

// Function that handles stats (GUI and Code).
void stats() {
	cout << "Player stats:" << endl;
	cout << "=============================================================================" << endl;
	cout << "Health: (";
	for (int i = 0; i < player.maxHealth; i++) {
		if (i + 1 > player.health) {
			cout << " ";
		} else {
			cout << "|";
		}
	}
	cout << ")" << endl;

	cout << "Shield: (";
	for (int i = 0; i < player.maxShield; i++) {
		if (i + 1 > player.shield) {
			cout << " ";
		}
		else {
			cout << "|";
		}
	}
	cout << ")" << endl;
	cout << "=============================================================================" << endl;
	cout << "Strength: " << player.strength << endl;
	cout << "Speed: " << player.speed << endl;
	cout << "Gold: " << player.gold << endl;
	cout << "=============================================================================" << endl;

	for (int i = 0; i < 5; i++) {
		cout << player.actions[i] << " (" << GetStaminaCost(player.actions[i]) << " stamina):" << endl;
		cout << GetAttackDescription(player.actions[i]) << "\n" << endl;
	}
	cout << "Stamina: " << player.maxStamina << endl;
	cout << "=============================================================================" << endl;
	if (player.potions.size() > 0) {
		cout << "Potions:" << endl;
		for (int i = 0; i < player.potions.size(); i++) {
			cout << "- " << player.potions[i] << " -" << endl;
		}
		cout << "=============================================================================" << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
}

// Function that displays both retrieving the boss and showing the boss introduction.
void BossIntroScreen() {
	enemy1 = GetBoss(currentFloor);
	enemy1.isActive = true;
	enemy2.isActive = false;
	enemy3.isActive = false;
	cout << "======================================= WARNING =======================================" << endl;
	switch (currentFloor) {
	case 1:
		cout << "--- STONE GOLEM ---" << endl;
		cout << "Built by the people to prevent anyone from delving deeper into the cave, the Stone Golem has one purpose - Destroy everyone in sight." << endl;
		break;
	case 2:
		cout << "--- THE CARETAKER ---" << endl;
		cout << "She was Omega's beast caretaker who took care of vicious animals, and she plans to use her most powerful animals against you." << endl;
		break;
	case 3:
		cout << "--- CERBERUS ---" << endl;
		cout << "Omega's personal pet is wild and uncontrollable. Its three heads will shred any oblivious adventerur to nothing." << endl;
		break;
	case 4:
		cout << "--- ABANDONNED HERO ---" << endl;
		cout << "Betrayed by the country she protected, she was sent here to rot and die. Now crazy, she plans to kill everyone on her path." << endl;
		break;
	case 5:
		cout << "--- TARUS ---" << endl;
		cout << "Omega's personal right-hand-man, Tarus built a secret base to revive Omega, and he plans to do this no matter the cost." << endl;
		break;
	case 6:
		cout << "--- OMEGA ---" << endl;
		cout << "Requiring the who world to stop, Omega is a threat to the universe. The only thing between him and the universe is you." << endl;
		break;
	}
	cout << "======================================= WARNING =======================================" << endl;
	system("pause");
	system("cls");
	cout << "! BOSS BATTLE !" << endl;
	system("pause");
	system("cls");
	if (currentFloor == 2) {
		enemy2 = Enemy("Wolf", 45, 15, 2, 30, 6, 12, { "Bite", "Strike" });
		enemy2.isActive = true;
		enemy3 = Enemy("Wolf", 45, 15, 2, 30, 6, 12, { "Bite", "Strike" });
		enemy3.isActive = true;
	}
	Combat();
	system("cls");
	switch (currentFloor) {
	case 1:
		cout << "You climb deeper into the cave, feeling brave." << endl;
		break;
	case 2:
		cout << "You climb into the depths, hearing cries for help from below." << endl;
		break;
	case 3:
		cout << "You descend into the blue light - The sound of scuttling coming from below." << endl;
		break;
	case 4:
		cout << "You climb into the final floor, the lost souls around you screaming in agony." << endl;
		break;
	case 5:
		cout << "As Tarus falls, a portal is opened in the ritual at the center of the room." << endl;
		cout << "You leap in and find yourself in the void. Omega is here - He has to be." << endl;
		cout << "You know where he is, and whatever you do, you can't let him escape into the real world..." << endl;
		break;
	case 6:
		cout << "As the void crumbles, you manage to just barely escape the void." << endl;
		cout << "You fall back into your village as you smile. It is done - Omega will never return." << endl;
		cout << "You've saved the world!" << endl;
		break;
	}
	system("pause");
	system("cls");
	if (currentFloor < 6) {
		currentFloor += 1;
		hasDiscoveredShop = false;
		eliteStatus = 0;
		hasFoundBoss = false;
		roomsExplored = 0;
		srand(time(0));
		enemies = CreateEnemies();
		for (int i = 0; i < 5; i++) {
			availableUpgrades[i] = true;
		}
	} else {
		cout << "Victory!" << endl;
		cout << "Last floor reached: " << currentFloor << endl;
		cout << "Final stats:" << endl;
		cout << "=============================================================================" << endl;
		cout << "Health: (";
		for (int i = 0; i < player.maxHealth; i++) {
			if (i + 1 > player.health) {
				cout << " ";
			}
			else {
				cout << "|";
			}
		}
		cout << ")" << endl;

		cout << "Shield: (";
		for (int i = 0; i < player.maxShield; i++) {
			if (i + 1 > player.shield) {
				cout << " ";
			}
			else {
				cout << "|";
			}
		}
		cout << ")" << endl;
		cout << "=============================================================================" << endl;
		cout << "Strength: " << player.strength << endl;
		cout << "Speed: " << player.speed << endl;
		cout << "Gold: " << player.gold << endl;
		cout << "=============================================================================" << endl;

		for (int i = 0; i < 5; i++) {
			cout << player.actions[i] << " (" << GetStaminaCost(player.actions[i]) << " stamina):" << endl;
			cout << GetAttackDescription(player.actions[i]) << "\n" << endl;
		}
		cout << "Stamina: " << player.maxStamina << endl;
		cout << "=============================================================================" << endl;
		if (player.potions.size() > 0) {
			cout << "Potions:" << endl;
			for (int i = 0; i < player.potions.size(); i++) {
				cout << "- " << player.potions[i] << " -" << endl;
			}
			cout << "=============================================================================" << endl;
		}
		cout << endl;
		system("pause");
		exit(0);
	}
}

// Function that handles the hub's GUI and elite battles.
void hub() {
	bool selectedOption = false;
	bool secondOption = false;
	int op2;
	while (!selectedOption) {
		cout << "You are in the ";
		switch (currentFloor) {
		case 1:
			cout << "upper caverns." << endl;
			break;
		case 2:
			cout << "caves." << endl;
			break;
		case 3:
			cout << "depths." << endl;
			break;
		case 4:
			cout << "crystal caverns." << endl;
			break;
		case 5:
			cout << "secret base." << endl;
			break;
		case 6:
			cout << "void." << endl;
			break;
		default:
			cout << "ERROR FLOOR." << endl;
			break;
		}

		cout << "1: Explore." << endl;
		cout << "2: Check stats." << endl;
		cout << "3: Rest." << endl;
		if (hasDiscoveredShop) {
			cout << "4: Check shop." << endl;
		}
		if (eliteStatus == 1) {
			cout << "5: Fight the elite." << endl;
		}
		if (hasFoundBoss) {
			if (currentFloor != 6) {
				cout << "6: Fight the guardian." << endl;
			}
			else {
				cout << "6: Fight Omega." << endl;
			}
		}
		int op = getInput();

		system("cls");
		switch (op) {
		case 1:
			explore();
			break;
		case 2:
			stats();
			break;
		case 3:
			rest();
			break;
		case 4:
			if (hasDiscoveredShop) {
				shop();
			} else {
				cout << "Error: That wasn't a valid option.\n" << endl;
			}
			break;
		case 5:
			if (eliteStatus == 1) {
				enemy1 = GetElite(currentFloor);
				enemy1.isActive = true;
				enemy2.isActive = false;
				enemy3.isActive = false;
				cout << "You find the elite's lair and enter, ready to face whatever is inside..." << endl;
				system("pause");
				system("cls");
				cout << "--- WARNING ---" << endl;
				cout << "ELITE BATTLE" << endl;
				cout << "--- WARNING ---\n" << endl;
				system("pause");
				system("cls");
				Combat();
				cout << "ELITE DEFEATED! CLAIM YOUR REWARD!" << endl;
				eliteStatus = 2;
				system("pause");
				system("cls");
				secondOption = false;
				while (!secondOption) {
					cout << "Select one of the five to upgrade:" << endl;
					cout << "1: Strength." << endl;
					cout << "2: Health." << endl;
					cout << "3: Shield." << endl;
					cout << "4: Stamina." << endl;
					cout << "5: Speed." << endl;

					op2 = getInput();

					system("cls");
					switch (op2) {
					case 1:
						cout << "Strength upgraded!" << endl;
						cout << player.strength << " --> " << player.strength + 0.25 << "!" << endl;
						player.strength += 0.25;
						secondOption = true;
						break;
					case 2:
						cout << "Health upgraded!" << endl;
						cout << player.maxHealth << " --> " << player.maxHealth + 3 << "!" << endl;
						player.maxHealth + 3;
						player.health = player.maxHealth;
						secondOption = true;
						break;
					case 3:
						cout << "Shield upgraded!" << endl;
						cout << player.maxShield << " --> " << player.maxShield + 3 << "!" << endl;
						player.maxShield += 3;
						player.shield = player.maxShield;
						secondOption = true;
						break;
					case 4:
						cout << "Stamina upgraded!" << endl;
						cout << player.maxStamina << " --> " << player.maxStamina + 20 << "!" << endl;
						player.maxStamina += 20;
						player.stamina = player.maxStamina;
						secondOption = true;
						break;
					case 5:
						cout << "Speed upgraded!" << endl;
						cout << player.speed << " --> " << player.speed + 2 << "!" << endl;
						player.speed += 2;
						secondOption = true;
						break;
					default:
						cout << "Error: That wasn't a valid option.\n" << endl;
						break;
					}
				}
				system("pause");
				system("cls");
			} else {
				cout << "Error: That wasn't a valid option.\n" << endl;
			}
			break;
		case 6:
			if (hasFoundBoss) {
				cout << "You follow your tracks and reach the way down, ready for the guardian within..." << endl;
				system("pause");
				system("cls");
				BossIntroScreen();
			} else {
				cout << "Error: That wasn't a valid option.\n" << endl;
			}
			break;
		default:
			cout << "Error: That wasn't a valid option.\n" << endl;
			break;
		}
	}
}

// Run at the start of a game to set up all of the variables.
void setup() {
	currentFloor = 1;
	roomsExplored = 0;
	srand(time(0));
	enemies = CreateEnemies();
	for (int i = 0; i < 5; i++) {
		availableUpgrades[i] = true;
	}
	hub();
}

// Function that handles getting the player's class.
void characterSelect() {
	bool selectedOption = false;
	while (!selectedOption) {
		cout << "Choose your class:" << endl;
		cout << "=============================================================================" << endl;
		cout << "1: Brawler." << endl;
		cout << "Health: High" << endl;
		cout << "Strength: High" << endl;
		cout << "Speed: Low" << endl;
		cout << "Special: Gains half shield at the start of each battle." << endl;
		cout << "=============================================================================" << endl;
		cout << "2: Spectre." << endl;
		cout << "Health: Medium" << endl;
		cout << "Strength: Low" << endl;
		cout << "Speed: Very High" << endl;
		cout << "Special: Regenerates 75% stamina instead of 50% stamina at the start of your turn." << endl;
		cout << "=============================================================================" << endl;
		cout << "3: Vanguard." << endl;
		cout << "Health: Low" << endl;
		cout << "Strength: Medium" << endl;
		cout << "Speed: High" << endl;
		cout << "Special: Regenerates 10% HP after each battle." << endl;
		cout << "=============================================================================" << endl;
		int op = getInput();

		system("cls");
		switch (op) {
		case 1:
			player = Player(1);
			selectedOption = true;
			break;
		case 2:
			player = Player(2);
			selectedOption = true;
			break;
		case 3:
			player = Player(3);
			selectedOption = true;
			break;
		default:
			cout << "Error: That was not an option.\n" << endl;
			break;
		}
	}
	setup();
}

// Function that shows the opening story. Feel free to improve it if you want.
void openingText() {
	cout << "Opening story:" << endl;
	cout << "Long ago there was this person named Omega." << endl;
	cout << "He was evil and stuff because the plot said so." << endl;
	cout << "Anyways so he kinda wanted to rule the world and be a tyrant." << endl;
	cout << "And he had his right hand man Tarus and his sister Phi by his side." << endl;
	cout << "So a bunch of people banished him into an interdimensional prison in a cave." << endl;
	cout << "But Phi and Tarus got away and are now trying to get him out again." << endl;
	cout << "Now some people wanted to do a little trolling." << endl;
	cout << "They said there was great treasure in the cave (despite there being dangerous people there as well)." << endl;
	cout << "And well you've decided to explore the cave." << endl;
	cout << "So that's the bad story I came up with 'cause I can't write stories. :)" << endl;
	system("pause");
	system("cls");
	characterSelect();
}

// Main menu GUI.
void mainMenu() {
	bool selectedOption = false;
	while (!selectedOption) {
		cout << "Omega's Bane" << endl;
		cout << "Made by Boinga15." << endl;
		cout << "1: Play." << endl;
		cout << "2: Quit." << endl;
		int op = getInput();

		system("cls");
		switch (op) {
		case 1:
			openingText();
			break;
		case 2:
			selectedOption = true;
			break;
		default:
			cout << "Error: That was not an option.\n" << endl;
			break;
		}
	}
}

// Basically never used except to start the program and call the main menu.
int main() {
	mainMenu();
}
