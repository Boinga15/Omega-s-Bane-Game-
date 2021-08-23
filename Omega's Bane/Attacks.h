#include<string>

#pragma once
#ifndef ATTACKS_H
#define ATTACKS_H

std::string GetAttackDescription(std::string AttackName);
std::string GetRandomAttack();
int GetStaminaCost(std::string AttackName);
int GetAttackID(std::string AttackName);

#endif