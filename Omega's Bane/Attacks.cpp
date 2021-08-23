#include "Attacks.h"
#include<map>
#include<ctime>
#include<random>
#include<string>

/*
How to add new attacks:
1: Add the attack name to the enum list.
2: Add the if statement in the 'resolveAttackOption' area.
3: Add an attack description in 'GetAttackDescription'.
4: Add the stamina cost in 'GetStaminaCost'.
5: Add the attack functionality in 'PerformAttack'.
*/

enum Attacks { 
	Option_Invalid,
	Strike,
	BowShot,
	Charge,
	Shift,
	Restore,
	Headshot,
	FuryStrike,
	Earthquake,
	DefensiveStance,
	ShockwaveClap,
	Spitfire,
	TotalRestoration,
	CrushingBlow,
	HomingBolt,
	Anihilate
};

// Used to find the ID for attacks.
Attacks resolveAttackOption(std::string input) {
	static const std::map<std::string, Attacks> optionStrings{  // The map that handles getting attack name.
		{"Strike", Strike},
		{"Bow Shot", BowShot},
		{"Charge", Charge},
		{"Shift", Shift},
		{"Restore", Restore},
		{"Headshot", Headshot},
		{"Fury Strike", FuryStrike},
		{"Earthquake", Earthquake},
		{"Defensive Stance", DefensiveStance},
		{"Shockwave Clap", ShockwaveClap},
		{"Spitfire", Spitfire},
		{"Total Restoration", TotalRestoration},
		{"Crushing Blow", CrushingBlow},
		{"Homing Bolt", HomingBolt},
		{"Anihilate", Anihilate}
	};

	for (auto it = optionStrings.begin(); it != optionStrings.end(); ++it) {
		if (it->first == input) {
			return it->second;
		}
	}
	return Option_Invalid;
}

// Generate and return attack descriptions.
std::string GetAttackDescription(std::string AttackName) {
	switch (resolveAttackOption(AttackName)) {  // This switch handles getting the descriptions.
	case Strike:
		return "A simple, accurate strike which deals damage to one target.";
		break;
	case BowShot:
		return "Fire an arrow from your bow. Somewhat accurate, but deals good damage.";
		break;
	case Charge:
		return "Hits all targets with very high accuracy, but you take a little damage as well.";
		break;
	case Shift:
		return "Teleport behind your target and deal five guaranteed weak hits.";
		break;
	case Restore:
		return "Using magic, heal yourself by a small amount.";
		break;
	case Headshot:
		return "A low accuracy attack that deals high damage.";
		break;
	case FuryStrike:
		return "Unleash several attacks against one target.";
		break;
	case Earthquake:
		return "Shake the area, dealing low accuracy high damage to all targets once.";
		break;
	case DefensiveStance:
		return "Gain a little shield.";
		break;
	case ShockwaveClap:
		return "Blast one person away with a penetrating high accuracy mediocre damage attack, dealing small damage to others.";
		break;
	case Spitfire:
		return "Unleash several crossbow bols at the entire crowd, dealing multiple weak hits against all targets";
		break;
	case TotalRestoration:
		return "Use powerful magic to restore some health and some shield.";
		break;
	case CrushingBlow:
		return "Deliver a powerful blow against a single enemy, hitting past their shield.";
		break;
	case HomingBolt:
		return "Fire a homing bolt with perfect accuracy and some damage.";
		break;
	case Anihilate:
		return "Insane damage on one target. Well... They'll never see it coming...";
		break;
	default:
		return "[ERROR - ATTACK DESCRIPTION NOT FOUND]";
		break;
	}
}

// Generate and return stamina costs.
int GetStaminaCost(std::string AttackName) {
	switch (resolveAttackOption(AttackName)) {  // This switch handles getting stamina cost.
	case Strike:
		return 10;
		break;
	case BowShot:
		return 15;
		break;
	case Charge:
		return 20;
		break;
	case Shift:
		return 30;
		break;
	case Restore:
		return 25;
		break;
	case Headshot:
		return 20;
		break;
	case FuryStrike:
		return 50;
		break;
	case Earthquake:
		return 70;
		break;
	case DefensiveStance:
		return 25;
		break;
	case ShockwaveClap:
		return 70;
		break;
	case Spitfire:
		return 60;
		break;
	case TotalRestoration:
		return 50;
		break;
	case CrushingBlow:
		return 30;
		break;
	case HomingBolt:
		return 20;
		break;
	case Anihilate:
		return 100;
		break;
	default:
		return 9999;
		break;
	}
}

// Generate a random attack.
std::string GetRandomAttack() {
	srand(time(0));
	Attacks action = static_cast<Attacks>(1 + rand() % Anihilate);
	static const std::map<std::string, Attacks> optionStrings{  // The map that handles getting attack name.
		{"Strike", Strike},
		{"Bow Shot", BowShot},
		{"Charge", Charge},
		{"Shift", Shift},
		{"Restore", Restore},
		{"Headshot", Headshot},
		{"Fury Strike", FuryStrike},
		{"Earthquake", Earthquake},
		{"Defensive Stance", DefensiveStance},
		{"Shockwave Clap", ShockwaveClap},
		{"Spitfire", Spitfire},
		{"Total Restoration", TotalRestoration},
		{"Crushing Blow", CrushingBlow},
		{"Homing Bolt", HomingBolt},
		{"Anihilate", Anihilate}
	};

	for (auto it = optionStrings.begin(); it != optionStrings.end(); ++it) {
		if (it->second == action) {
			return it->first;
		}
	}
	return "None";
}

// Return action IDs.
int GetAttackID(std::string AttackName) {
	switch (resolveAttackOption(AttackName)) {  // This switch handles getting stamina cost.
	case Strike:
		return 0;
		break;
	case BowShot:
		return 1;
		break;
	case Charge:
		return 2;
		break;
	case Shift:
		return 3;
		break;
	case Restore:
		return 4;
		break;
	case Headshot:
		return 5;
		break;
	case FuryStrike:
		return 6;
		break;
	case Earthquake:
		return 7;
		break;
	case DefensiveStance:
		return 8;
		break;
	case ShockwaveClap:
		return 9;
		break;
	case Spitfire:
		return 10;
		break;
	case TotalRestoration:
		return 11;
		break;
	case CrushingBlow:
		return 12;
		break;
	case HomingBolt:
		return 13;
		break;
	case Anihilate:
		return 14;
		break;
	default:
		return 9999;
		break;
	}
}